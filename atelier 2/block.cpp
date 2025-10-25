#include "block.h"
#include "hash.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <chrono>

Block::Block(int index, const std::vector<Transaction>& transactions, 
             const std::string& previousHash, uint32_t hashRule, size_t hashSteps)
    : index(index), timestamp(std::time(nullptr)), previousHash(previousHash), 
      transactions(transactions), nonce(0), validator(""), 
      hashRule(hashRule), hashSteps(hashSteps) {
    // Calculate Merkle root for the transactions
    merkleRoot = calculateMerkleRoot();
    // Calculate the initial hash
    hash = calculateHash();
}

std::string Block::calculateMerkleRoot() const {
    // If there are no transactions, return a placeholder hash
    if (transactions.empty()) {
        return ac_hash("empty_merkle_root", hashRule, hashSteps);
    }
    
    // Extract transaction strings for Merkle tree
    std::vector<std::string> transactionStrings;
    for (const auto& tx : transactions) {
        transactionStrings.push_back(tx.toString());
    }
    
    // Create Merkle tree using AC hash and get root hash
    MerkleTreeAC merkleTree(transactionStrings, hashRule, hashSteps);
    return merkleTree.getRootHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << previousHash << merkleRoot << nonce << validator;
    // Use AC hash instead of SHA-256
    return ac_hash(ss.str(), hashRule, hashSteps);
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
    
    // Recalculate the hash with the validator using AC hash
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
    ss << "  Hash (AC-based): " << hash << std::endl;
    ss << "]" << std::endl;
    return ss.str();
}
