#pragma once
#include <string>
#include <cstdint>

// Finds a numeric suffix such that the SHA1 hash of (input + suffix) in hex starts with num_zeros zeros.
// Returns the resultant string, and sets found_suffix to the suffix value found.
std::string find_suffix_with_sha1_leading_zeros(const std::string& input, int num_zeros, uint64_t& found_suffix);
