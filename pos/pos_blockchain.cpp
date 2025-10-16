#include "pos_blockchain.h"
#include <iostream>
#include <chrono>
#include <numeric>

// Constructor
PosBlockchain::PosBlockchain() {
    // Initialize RNG with random seed
    std::random_device rd;
    rng.seed(rd());
    
    // Create genesis block
    chain.emplace_back(PosBlock(0, "Genesis Block", "0", "System"));
}

// Add a stakeholder to the network
void PosBlockchain::addStakeholder(const std::string& address, double amount) {
    stakeholders[address] = amount;
}

// Select a validator based on stake weight
std::string PosBlockchain::selectValidator() {
    // If no stakeholders, return system as validator
    if (stakeholders.empty()) {
        return "System";
    }
    
    // Calculate total stake
    double totalStake = getTotalStake();
    
    // Generate a random value between 0 and total stake
    std::uniform_real_distribution<double> dist(0, totalStake);
    double randomValue = dist(rng);
    
    // Select a validator based on their stake proportion (weighted random selection)
    double cumulativeWeight = 0.0;
    for (const auto& stakeholder : stakeholders) {
        cumulativeWeight += stakeholder.second;
        if (randomValue <= cumulativeWeight) {
            return stakeholder.first;
        }
    }
    
    // Fallback (should not reach here)
    return stakeholders.begin()->first;
}

// Add a new block to the blockchain
void PosBlockchain::addBlock(const std::string& data) {
    const PosBlock& previousBlock = getLatestBlock();
    
    // Select a validator based on stake
    std::string validator = selectValidator();
    
    // Create a new block
    PosBlock newBlock(previousBlock.getIndex() + 1, data, previousBlock.getHash(), validator);
    
    std::cout << "Block validated by: " << validator << std::endl;
    std::cout << "Block hash: " << newBlock.getHash() << std::endl;
    
    // Add the block to the chain
    chain.push_back(newBlock);
}

// Get the total stake in the system
double PosBlockchain::getTotalStake() const {
    double total = 0.0;
    for (const auto& stakeholder : stakeholders) {
        total += stakeholder.second;
    }
    return total;
}

// Verify if the blockchain is valid
bool PosBlockchain::isChainValid() const {
    // Need at least 2 blocks to validate
    if (chain.size() <= 1) return true;
    
    // Check each block
    for (size_t i = 1; i < chain.size(); i++) {
        const PosBlock& currentBlock = chain[i];
        const PosBlock& previousBlock = chain[i - 1];
        
        // Verify hash
        if (currentBlock.getHash() != currentBlock.calculateHash()) {
            std::cout << "Invalid hash for block #" << i << std::endl;
            return false;
        }
        
        // Verify previous hash link
        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            std::cout << "Broken chain between blocks #" << (i-1) << " and #" << i << std::endl;
            return false;
        }
    }
    
    return true;
}

// Get the latest block
const PosBlock& PosBlockchain::getLatestBlock() const {
    return chain.back();
}