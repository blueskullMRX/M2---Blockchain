#ifndef AC_HASH_H
#define AC_HASH_H

#include <string>
#include <cstdint>
#include <cstddef>

// Compute a 256-bit (64 hex chars) hash from input using a 1D elementary
// cellular automaton.
// Parameters:
//  - input: text to hash
//  - rule: automaton rule number (0-255)
//  - steps: number of generations to run
// Returns: 64-character hex string representing 256 bits
std::string ac_hash(const std::string& input, uint32_t rule, size_t steps);

#endif // AC_HASH_H
