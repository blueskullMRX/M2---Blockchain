#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <ctime>
#include "../merkle/merkle_tree.h"
#include "transaction.h"

/**
 * Represents a block in the blockchain
 * Can be mined with PoW or validated with PoS
 */
class Block {
private:
    int index;                   // Block index in the blockchain
    time_t timestamp;            // Time the block was created
    std::string previousHash;    // Hash of the previous block
    std::string merkleRoot;      // Merkle root of transactions
    std::vector<Transaction> transactions; // Transactions in this block
    int nonce;                   // Nonce for PoW
    std::string validator;       // Validator address for PoS
    std::string hash;            // Hash of this block

    /**
     * Calculate the Merkle root of the transactions
     */
    std::string calculateMerkleRoot() const;
    
public:
    /**
     * Constructor for a block
     * 
     * @param index Index in the blockchain
     * @param transactions List of transactions to include
     * @param previousHash Hash of the previous block
     */
    Block(int index, const std::vector<Transaction>& transactions, const std::string& previousHash);
    
    /**
     * Calculate the hash of the block
     */
    std::string calculateHash() const;
    
    /**
     * Mine the block with Proof of Work
     * 
     * @param difficulty Mining difficulty (number of leading zeros)
     * @return Time taken to mine the block in milliseconds
     */
    long mineBlock(int difficulty);
    
    /**
     * Validate the block with Proof of Stake
     * 
     * @param validatorAddress Address of the chosen validator
     * @return Time taken to validate the block in milliseconds
     */
    long validateBlock(const std::string& validatorAddress);
    
    /**
     * Get the block hash
     */
    std::string getHash() const { return hash; }
    
    /**
     * Get the hash of the previous block
     */
    std::string getPreviousHash() const { return previousHash; }
    
    /**
     * Get the block index
     */
    int getIndex() const { return index; }
    
    /**
     * Get the block timestamp
     */
    time_t getTimestamp() const { return timestamp; }
    
    /**
     * Get the block's Merkle root
     */
    std::string getMerkleRoot() const { return merkleRoot; }
    
    /**
     * Get the block's transactions
     */
    const std::vector<Transaction>& getTransactions() const { return transactions; }
    
    /**
     * Get the validator (PoS)
     */
    std::string getValidator() const { return validator; }
    
    /**
     * Convert the block to a string for display
     */
    std::string toString() const;
};

#endif // BLOCK_H