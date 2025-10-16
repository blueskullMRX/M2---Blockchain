#include <iostream>
#include <vector>
#include <string>
#include "merkle_tree.h"

int main() {
    std::cout << "Extended Merkle Tree Test" << std::endl;

    try {
        // Test with even number of leaves
        std::cout << "Creating tree with even leaves" << std::endl;
        {
            std::vector<std::string> data = {"block1", "block2", "block3", "block4"};
            MerkleTree tree(data);
            
            std::cout << "Root hash (even): ";
            std::cout << tree.getRootHash().substr(0, 16) << "..." << std::endl;
            
            // Tree will be destroyed here when exiting the scope
        }
        std::cout << "Even leaves tree destroyed successfully" << std::endl;

        // Test with odd number of leaves
        std::cout << "Creating tree with odd leaves" << std::endl;
        {
            std::vector<std::string> data = {"block1", "block2", "block3"};
            MerkleTree tree(data);
            
            std::cout << "Root hash (odd): ";
            std::cout << tree.getRootHash().substr(0, 16) << "..." << std::endl;
            
            // Tree will be destroyed here when exiting the scope
        }
        std::cout << "Odd leaves tree destroyed successfully" << std::endl;
        
        // Don't end here, try further operations
        
        // Try a small data set
        std::cout << "Creating minimal tree" << std::endl;
        {
            std::vector<std::string> data = {"a", "b"};
            MerkleTree tree(data);
            
            std::cout << "Minimal root hash: ";
            std::cout << tree.getRootHash().substr(0, 16) << "..." << std::endl;
        }
        std::cout << "Minimal tree destroyed successfully" << std::endl;
        
        // Try an empty tree
        std::cout << "Creating empty tree" << std::endl;
        {
            std::vector<std::string> data;
            MerkleTree tree(data);
            
            std::cout << "Empty root hash: \"";
            std::cout << tree.getRootHash() << "\"" << std::endl;
        }
        std::cout << "Empty tree destroyed successfully" << std::endl;
        
        std::cout << "All tests completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
        return 1;
    }
    
    return 0;
}