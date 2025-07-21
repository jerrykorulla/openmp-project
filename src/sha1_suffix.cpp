#include <string>
#include <cstdint>
#include <openssl/sha.h>
#include <omp.h>
#include <sstream>
#include <iomanip>
#include <atomic>
#include "sha1_suffix.h"

static std::string sha1_hex(const std::string& str) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), hash);
    std::ostringstream oss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return oss.str();
}

std::string find_suffix_with_sha1_leading_zeros(const std::string& input, int num_zeros, uint64_t& found_suffix) {
    std::atomic<bool> found(false);
    std::string result;
    found_suffix = 0;
    std::string target(num_zeros, '0');

    #pragma omp parallel
    {
        std::string local_result;
        uint64_t local_suffix = 0;
        #pragma omp for
        for (uint64_t suffix = 0; suffix < UINT64_MAX; ++suffix) {
            if (found.load()) continue;
            std::string candidate = input + std::to_string(suffix);
            std::string hash_hex = sha1_hex(candidate);
            if (hash_hex.substr(0, num_zeros) == target) {
                local_result = candidate;
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
