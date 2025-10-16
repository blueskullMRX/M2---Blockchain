#include "block.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <chrono>
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

Block::Block(int index, const std::vector<Transaction>& transactions, const std::string& previousHash)
    : index(index), timestamp(std::time(nullptr)), previousHash(previousHash), 
      transactions(transactions), nonce(0), validator("") {
    // Calculate Merkle root for the transactions
    merkleRoot = calculateMerkleRoot();
    // Calculate the initial hash
    hash = calculateHash();
}

std::string Block::calculateMerkleRoot() const {
    // If there are no transactions, return a placeholder hash
    if (transactions.empty()) {
        return sha256("empty_merkle_root");
    }
    
    // Extract transaction strings for Merkle tree
    std::vector<std::string> transactionStrings;
    for (const auto& tx : transactions) {
        transactionStrings.push_back(tx.toString());
    }
    
    // Create Merkle tree and get root hash
    MerkleTree merkleTree(transactionStrings);
    return merkleTree.getRootHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << previousHash << merkleRoot << nonce << validator;
    return sha256(ss.str());
}

long Block::mineBlock(int difficulty) {
    // Create a target string with leading zeros
    std::string target(difficulty, '0');
    
    // Record start time
    auto startTime = std::chrono::high_resolution_clock::now();
    
    // Increment nonce until we find a hash with the required number of leading zeros
    while (hash.substr(0, difficulty) != target) {
        nonce++;
        hash = calculateHash();
    }
    
    // Record end time and calculate duration
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    std::cout << "Block mined! Hash: " << hash << std::endl;
    std::cout << "Mining time: " << duration << " ms" << std::endl;
    
    return duration;
}

long Block::validateBlock(const std::string& validatorAddress) {
    // Record start time
    auto startTime = std::chrono::high_resolution_clock::now();
    
    // In PoS, the validator simply signs the block
    validator = validatorAddress;
    
    // Recalculate the hash with the validator
    hash = calculateHash();
    
    // Record end time and calculate duration
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    std::cout << "Block validated by: " << validator << std::endl;
    std::cout << "Block hash: " << hash << std::endl;
    
    return duration;
}

std::string Block::toString() const {
    std::stringstream ss;
    ss << "Block #" << index << " [" << std::endl;
    ss << "  Timestamp: " << timestamp << std::endl;
    ss << "  Previous Hash: " << previousHash << std::endl;
    ss << "  Merkle Root: " << merkleRoot << std::endl;
    ss << "  Transactions: " << transactions.size() << std::endl;
    for (size_t i = 0; i < transactions.size(); i++) {
        if (i < 3) { // Show only first 3 transactions to avoid clutter
            const auto& tx = transactions[i];
            ss << "    " << tx.getId() << ": " << tx.getSender() << " -> " 
               << tx.getReceiver() << " (" << tx.getAmount() << ")" << std::endl;
        } else if (i == 3) {
            ss << "    ... and " << (transactions.size() - 3) << " more transactions" << std::endl;
            break;
        }
    }
    if (!validator.empty()) {
        ss << "  Validator: " << validator << std::endl;
    } else {
        ss << "  Nonce: " << nonce << std::endl;
    }
    ss << "  Hash: " << hash << std::endl;
    ss << "]" << std::endl;
    return ss.str();
}