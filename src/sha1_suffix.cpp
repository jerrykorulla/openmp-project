#include "sha1_suffix.h"

#include <atomic>
#include <cstdint>
#include <omp.h>
#include <openssl/sha.h>
#include <string>

bool has_leading_zeros(const unsigned char* hash, int num_zeros) {
    int full_bytes = num_zeros / 8;
    int remaining_bits = num_zeros % 8;

    for (int i = 0; i < full_bytes; ++i) {
        if (hash[i] != 0x00) return false;
    }
    if (remaining_bits > 0) {
        unsigned char mask = 0xFF << (8 - remaining_bits);
        if ((hash[full_bytes] & mask) != 0) return false;
    }
    return true;
}

std::string find_suffix_with_sha1_leading_zeros(const std::string& input, int num_zeros, uint64_t& found_suffix) {
    std::atomic<bool> found(false);
    std::string result;
    found_suffix = 0;

#pragma omp parallel
    {
        std::string local_result;
        uint64_t local_suffix = 0;

#pragma omp for
        for (uint64_t suffix = 0; suffix < UINT64_MAX; ++suffix) {
            if (found.load()) continue;

            std::string str = input + std::to_string(suffix);
            unsigned char hash[SHA_DIGEST_LENGTH];
            SHA1(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), hash);

            if (has_leading_zeros(hash, num_zeros)) {
                local_result = str;
                local_suffix = suffix;
                found.store(true);
            }
        }

#pragma omp critical
        {
            if (found.load() && result.empty() && !local_result.empty()) {
                result = local_result;
                found_suffix = local_suffix;
            }
        }
    }

    return result;
}
