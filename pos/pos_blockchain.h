#ifndef POS_BLOCKCHAIN_H
#define POS_BLOCKCHAIN_H

#include "pos_block.h"
#include "stake.h"
#include <vector>
#include <random>
#include <map>

class PosBlockchain {
private:
    std::vector<PosBlock> chain;
    std::map<std::string, double> stakeholders;  // Map of address -> stake amount
    mutable std::mt19937 rng;  // Random number generator
    
    // Select a validator based on stake weight
    std::string selectValidator();
    
public:
    // Constructor
    PosBlockchain();
    
    // Add a new stakeholder to the system
    void addStakeholder(const std::string& address, double amount);
    
    // Add a new block to the chain
    void addBlock(const std::string& data);
    
    // Verify if the chain is valid
    bool isChainValid() const;
    
    // Get the latest block
    const PosBlock& getLatestBlock() const;
    
    // Get all blocks
    const std::vector<PosBlock>& getChain() const { return chain; }
    
    // Get total stake in the system
    double getTotalStake() const;
    
    // Get all stakeholders
    const std::map<std::string, double>& getStakeholders() const { return stakeholders; }
};

#endif // POS_BLOCKCHAIN_H