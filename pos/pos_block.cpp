#include "pos_block.h"
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

// Helper function to calculate SHA-256 hash
inline std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Constructor for PosBlock
PosBlock::PosBlock(int idx, const std::string& data, const std::string& prevHash, const std::string& validator) 
    : index(idx), timestamp(std::time(nullptr)), data(data), previousHash(prevHash), validator(validator) {
    hash = calculateHash();
}

// Calculate the hash of the block
std::string PosBlock::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << data << previousHash << validator;
    return sha256(ss.str());
}

// String representation of the block
std::string PosBlock::toString() const {
    std::stringstream ss;
    ss << "Block #" << index << " [" << std::endl;
    ss << "  Timestamp: " << timestamp << std::endl;
    ss << "  Data: " << data << std::endl;
    ss << "  Previous Hash: " << previousHash << std::endl;
    ss << "  Hash: " << hash << std::endl;
    ss << "  Validator: " << validator << std::endl;
    ss << "]" << std::endl;
    return ss.str();
}