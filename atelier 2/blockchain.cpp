#include "blockchain.h"
#include <iostream>
#include <random>
#include <chrono>

Blockchain::Blockchain(bool usePoS, int difficulty, uint32_t hashRule, size_t hashSteps)
    : difficulty(difficulty), totalStake(0), usePoS(usePoS), 
      hashRule(hashRule), hashSteps(hashSteps), rng(std::random_device()()) {
    createGenesisBlock();
}

void Blockchain::createGenesisBlock() {
    // Create a genesis block with no transactions
    std::vector<Transaction> genesisTransactions;
    Block genesisBlock(0, genesisTransactions, "0", hashRule, hashSteps);
    
    // If using PoS, validate the genesis block with a system validator
    if (usePoS) {
        genesisBlock.validateBlock("System");
    } else {
        // For genesis block, don't mine - just accept it as is
        // Mining with AC hash can take a very long time due to the hash distribution
        std::cout << "Genesis block created (mining skipped for AC hash)" << std::endl;
    }
    
    // Add the genesis block to the chain
    chain.push_back(genesisBlock);
}

Block Blockchain::getLatestBlock() const {
    return chain.back();
}

long Blockchain::addBlock(const std::vector<Transaction>& transactions) {
    // Get the latest block
    Block latestBlock = getLatestBlock();
    int newIndex = latestBlock.getIndex() + 1;
    
    // Create a new block with AC hash parameters
    Block newBlock(newIndex, transactions, latestBlock.getHash(), hashRule, hashSteps);
    
    // Mine or validate the block based on consensus mechanism
    long blockTime = 0;
    if (usePoS) {
        // Select a validator and validate the block
        std::string validator = selectValidator();
        blockTime = newBlock.validateBlock(validator);
    } else {
        // Mine the block with the current difficulty
        blockTime = newBlock.mineBlock(difficulty);
    }
    
    // Add the new block to the chain
    chain.push_back(newBlock);
    return blockTime;
}

std::string Blockchain::selectValidator() const {
    // If there are no stakeholders, return a system validator
    if (stakeholders.empty()) {
        return "System";
    }
    
    // Select a validator randomly based on stake weight
    std::uniform_real_distribution<double> dist(0.0, totalStake);
    // Note: rng is mutable, so we can use it in a const function
    double selection = dist(const_cast<std::mt19937&>(rng));
    
    double cumulativeStake = 0;
    for (const auto& stakeholder : stakeholders) {
        cumulativeStake += stakeholder.stake;
        if (selection <= cumulativeStake) {
            return stakeholder.address;
        }
    }
    
    // Fallback to the first stakeholder if something goes wrong
    return stakeholders[0].address;
}

void Blockchain::addStakeholder(const std::string& address, double stake) {
    stakeholders.push_back(Stakeholder(address, stake));
    totalStake += stake;
}

bool Blockchain::isChainValid() const {
    // Check each block in the chain
    for (size_t i = 1; i < chain.size(); i++) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];
        
        // Check if the block points to the correct previous block
        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            std::cout << "Invalid previous hash in block " << i << std::endl;
            return false;
        }
        
        // Check if the block's hash is valid
        if (currentBlock.getHash() != currentBlock.calculateHash()) {
            std::cout << "Invalid hash in block " << i << std::endl;
            return false;
        }
    }
    
    return true;
}

void Blockchain::printChain() const {
    std::cout << "===== Blockchain State (AC-Based Hashing) =====" << std::endl;
    std::cout << "Hash Algorithm: Cellular Automaton (Rule " << hashRule 
              << ", " << hashSteps << " steps)" << std::endl;
    std::cout << "Consensus: " << (usePoS ? "Proof of Stake" : "Proof of Work") << std::endl;
    if (!usePoS) {
        std::cout << "Difficulty: " << difficulty << std::endl;
    } else {
        std::cout << "Stakeholders: " << stakeholders.size() << std::endl;
        std::cout << "Total Stake: " << totalStake << std::endl;
    }
    std::cout << "Block Count: " << chain.size() << std::endl;
    std::cout << std::endl;
    
    for (const auto& block : chain) {
        std::cout << block.toString();
    }
    
    std::cout << "===============================================" << std::endl;
}
