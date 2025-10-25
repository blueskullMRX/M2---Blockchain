#include "merkle_tree.h"
#include <iostream>
#include <cmath>

MerkleTreeAC::MerkleTreeAC(const std::vector<std::string>& data, uint32_t rule, size_t steps)
    : rule(rule), steps(steps) {
    if (data.empty()) {
        rootHash = ac_hash("empty_merkle_root", rule, steps);
        return;
    }
    
    // Hash each piece of data to create leaf nodes
    std::vector<std::string> leaves;
    for (const auto& item : data) {
        leaves.push_back(ac_hash(item, rule, steps));
    }
    
    // Build the tree
    buildTree(leaves);
}

void MerkleTreeAC::buildTree(const std::vector<std::string>& leaves) {
    // Start with leaf nodes
    std::vector<std::string> currentLevel = leaves;
    tree = leaves;
    
    // Build tree level by level
    while (currentLevel.size() > 1) {
        std::vector<std::string> nextLevel;
        
        // Process pairs of nodes
        for (size_t i = 0; i < currentLevel.size(); i += 2) {
            if (i + 1 < currentLevel.size()) {
                // Hash pair of nodes
                std::string combined = hashPair(currentLevel[i], currentLevel[i + 1]);
                nextLevel.push_back(combined);
            } else {
                // Odd node out - hash with itself
                std::string combined = hashPair(currentLevel[i], currentLevel[i]);
                nextLevel.push_back(combined);
            }
        }
        
        // Add this level to the tree
        tree.insert(tree.end(), nextLevel.begin(), nextLevel.end());
        currentLevel = nextLevel;
    }
    
    // The last node is the root
    rootHash = currentLevel[0];
}

std::string MerkleTreeAC::hashPair(const std::string& left, const std::string& right) {
    // Combine the two hashes and hash again using AC hash
    std::string combined = left + right;
    return ac_hash(combined, rule, steps);
}
