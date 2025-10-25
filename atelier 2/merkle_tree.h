#ifndef MERKLE_TREE_AC_H
#define MERKLE_TREE_AC_H

#include <string>
#include <vector>
#include "hash.h"

/**
 * A Merkle Tree implementation using AC-based hashing
 * instead of traditional SHA-256
 */
class MerkleTreeAC {
private:
    std::vector<std::string> tree;
    std::string rootHash;
    uint32_t rule;      // CA rule to use for hashing
    size_t steps;       // Number of CA steps
    
    /**
     * Build the Merkle tree from leaf nodes
     */
    void buildTree(const std::vector<std::string>& leaves);
    
    /**
     * Hash two strings together using AC hash
     */
    std::string hashPair(const std::string& left, const std::string& right);

public:
    /**
     * Constructor
     * 
     * @param data List of data strings (transactions)
     * @param rule CA rule number (default: 30)
     * @param steps Number of CA evolution steps (default: 100)
     */
    MerkleTreeAC(const std::vector<std::string>& data, uint32_t rule = 30, size_t steps = 100);
    
    /**
     * Get the root hash of the tree
     */
    std::string getRootHash() const { return rootHash; }
    
    /**
     * Get the entire tree structure
     */
    const std::vector<std::string>& getTree() const { return tree; }
};

#endif // MERKLE_TREE_AC_H
