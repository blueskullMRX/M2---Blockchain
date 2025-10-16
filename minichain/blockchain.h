#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <string>
#include <random>
#include "block.h"
#include "transaction.h"

// Structure to represent a stakeholder for PoS
struct Stakeholder {
    std::string address;  // Address of the stakeholder
    double stake;         // Amount of stake (coins)
    
    Stakeholder(const std::string& address, double stake) 
        : address(address), stake(stake) {}
};

/**
 * Represents a blockchain with support for both PoW and PoS
 */
class Blockchain {
private:
    std::vector<Block> chain;
    int difficulty;                     // Mining difficulty for PoW
    std::vector<Stakeholder> stakeholders; // List of stakeholders for PoS
    double totalStake;                  // Total stake in the system
    bool usePoS;                        // Whether to use PoS (true) or PoW (false)
    
    mutable std::mt19937 rng;           // Random number generator for PoS
    
    /**
     * Create the genesis block
     */
    void createGenesisBlock();
    
    /**
     * Select a validator based on stake (PoS)
     * 
     * @return Address of the selected validator
     */
    std::string selectValidator() const;

public:
    /**
     * Constructor
     * 
     * @param usePoS Whether to use PoS (true) or PoW (false)
     * @param difficulty Mining difficulty for PoW (ignored if usePoS is true)
     */
    Blockchain(bool usePoS = false, int difficulty = 4);
    
    /**
     * Get the latest block in the chain
     */
    Block getLatestBlock() const;
    
    /**
     * Add a new block with the given transactions
     * 
     * @param transactions List of transactions to include in the block
     * @return Time taken to add the block in milliseconds
     */
    long addBlock(const std::vector<Transaction>& transactions);
    
    /**
     * Add a stakeholder for PoS
     * 
     * @param address Address of the stakeholder
     * @param stake Amount of stake (coins)
     */
    void addStakeholder(const std::string& address, double stake);
    
    /**
     * Verify the integrity of the blockchain
     * 
     * @return true if the chain is valid, false otherwise
     */
    bool isChainValid() const;
    
    /**
     * Get the entire blockchain
     */
    const std::vector<Block>& getChain() const { return chain; }
    
    /**
     * Get the total stake in the system
     */
    double getTotalStake() const { return totalStake; }
    
    /**
     * Get the list of stakeholders
     */
    const std::vector<Stakeholder>& getStakeholders() const { return stakeholders; }
    
    /**
     * Check if using PoS
     */
    bool isUsingPoS() const { return usePoS; }
    
    /**
     * Get the mining difficulty
     */
    int getDifficulty() const { return difficulty; }
    
    /**
     * Set the mining difficulty
     */
    void setDifficulty(int newDifficulty) { difficulty = newDifficulty; }
    
    /**
     * Switch between PoW and PoS
     */
    void setConsensusMode(bool usePoS) { this->usePoS = usePoS; }
    
    /**
     * Print the entire blockchain
     */
    void printChain() const;
};

#endif // BLOCKCHAIN_H