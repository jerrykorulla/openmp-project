#include <iostream>
#include <string>
#include "sha1_suffix.h"

int main() {
    std::string input;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    uint64_t found_suffix = 0;
    std::cout << "Searching for a suffix such that SHA1(input+suffix) starts with 9 zeros...\n";
    std::string result = find_suffix_with_sha1_leading_zeros(input, 1, found_suffix);
    if (!result.empty()) {
        std::cout << "Found suffix: " << found_suffix << "\n";
        std::cout << "Resultant string: " << result << "\n";
    } else {
        std::cout << "No suffix found (search space exhausted).\n";
    }
    return 0;
}