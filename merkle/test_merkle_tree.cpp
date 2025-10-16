#include <iostream>
#include <vector>
#include <string>
#include "merkle_tree.h"

// Fonction d'aide pour afficher les résultats des tests
void displayTestResult(const std::string& testName, bool result) {
    std::cout << "Test " << testName << ": " << (result ? "PASSED" : "FAILED") << std::endl;
}

// Fonction pour tester la construction d'un arbre avec un nombre pair de feuilles
bool testEvenNumberOfLeaves() {
    std::vector<std::string> data = {"block1", "block2", "block3", "block4"};
    MerkleTree tree(data);
    
    std::cout << "Tree with 4 leaves:" << std::endl;
    tree.printTree();
    
    // Vérifier que le hash racine n'est pas vide
    std::string rootHash = tree.getRootHash();
    return !rootHash.empty();
}

// Fonction pour tester la construction d'un arbre avec un nombre impair de feuilles
bool testOddNumberOfLeaves() {
    std::cout << "Starting testOddNumberOfLeaves..." << std::endl;
    std::vector<std::string> data = {"block1", "block2", "block3"};
    std::cout << "Created data vector" << std::endl;
    MerkleTree tree(data);
    std::cout << "Created tree" << std::endl;
    
    std::cout << "Tree with 3 leaves (last one duplicated internally):" << std::endl;
    tree.printTree();
    std::cout << "Tree printed" << std::endl;
    
    // Vérifier que le hash racine n'est pas vide
    std::string rootHash = tree.getRootHash();
    std::cout << "Root hash obtained: " << rootHash << std::endl;
    return !rootHash.empty();
}

// Fonction pour tester la vérification de la présence d'une donnée dans l'arbre
bool testVerification() {
    std::vector<std::string> data = {"block1", "block2", "block3", "block4"};
    MerkleTree tree(data);
    
    // Vérifier qu'une donnée présente est correctement identifiée
    bool containsBlock1 = tree.verify("block1");
    
    // Vérifier qu'une donnée absente est correctement identifiée
    bool containsBlock5 = tree.verify("block5");
    
    return containsBlock1 && !containsBlock5;
}

// Fonction pour tester la cohérence des hash
bool testHashConsistency() {
    // Créer deux arbres avec les mêmes données
    std::vector<std::string> data1 = {"block1", "block2", "block3", "block4"};
    std::vector<std::string> data2 = {"block1", "block2", "block3", "block4"};
    
    MerkleTree tree1(data1);
    MerkleTree tree2(data2);
    
    // Les hash racines doivent être identiques
    std::string rootHash1 = tree1.getRootHash();
    std::string rootHash2 = tree2.getRootHash();
    
    // Créer un arbre avec des données différentes
    std::vector<std::string> data3 = {"block1", "block2", "block3", "block5"};
    MerkleTree tree3(data3);
    std::string rootHash3 = tree3.getRootHash();
    
    return (rootHash1 == rootHash2) && (rootHash1 != rootHash3);
}

// Test pour un arbre vide
bool testEmptyTree() {
    std::vector<std::string> data;
    MerkleTree tree(data);
    
    std::cout << "Empty tree:" << std::endl;
    tree.printTree();
    
    // Le hash racine doit être vide
    std::string rootHash = tree.getRootHash();
    return rootHash.empty();
}

// Fonction principale exécutant les tests
int main() {
    std::cout << "===== MERKLE TREE TESTS =====" << std::endl << std::endl;
    
    try {
        // Exécuter les tests
        displayTestResult("Even number of leaves", testEvenNumberOfLeaves());
        std::cout << std::endl;
        
        try {
            bool oddResult = testOddNumberOfLeaves();
            displayTestResult("Odd number of leaves", oddResult);
            std::cout << "Odd number test completed successfully" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Exception in odd number test: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception in odd number test" << std::endl;
        }
        std::cout << std::endl;
        
        // Extra test to see where it crashes
        std::cout << "About to start verification test" << std::endl;
        std::cout.flush();
        
        // Test de vérification
        try {
            std::cout << "Testing verification..." << std::endl;
            std::vector<std::string> data = {"block1", "block2", "block3", "block4"};
            MerkleTree tree(data);
            
            std::string dataToVerify = "block1";
            std::cout << "Calculating hash..." << std::endl;
            std::string dataHash = sha256(dataToVerify);
            
            std::cout << "Hash of '" << dataToVerify << "': " << dataHash << std::endl;
            std::cout << "Is '" << dataToVerify << "' in the tree: " << (tree.verify(dataToVerify) ? "Yes" : "No") << std::endl;
            
            std::string invalidData = "block5";
            std::cout << "Is '" << invalidData << "' in the tree: " << (tree.verify(invalidData) ? "Yes" : "No") << std::endl;
            std::cout << "Verification test completed!" << std::endl;
            
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Exception in verification test: " << e.what() << std::endl;
            return 1;
        } catch (...) {
            std::cerr << "Unknown exception in verification test" << std::endl;
            return 1;
        }
        
        // Test hash consistency
        try {
            std::cout << "Testing hash consistency..." << std::endl;
            bool hashConsistencyResult = testHashConsistency();
            displayTestResult("Hash consistency", hashConsistencyResult);
            std::cout << "Hash consistency test completed!" << std::endl;
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Exception in hash consistency test: " << e.what() << std::endl;
            return 1;
        } catch (...) {
            std::cerr << "Unknown exception in hash consistency test" << std::endl;
            return 1;
        }
        
        // Test empty tree
        try {
            std::cout << "Testing empty tree..." << std::endl;
            bool emptyTreeResult = testEmptyTree();
            displayTestResult("Empty tree", emptyTreeResult);
            std::cout << "Empty tree test completed!" << std::endl;
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Exception in empty tree test: " << e.what() << std::endl;
            return 1;
        } catch (...) {
            std::cerr << "Unknown exception in empty tree test" << std::endl;
            return 1;
        }
        
        // Test blockchain example
        try {
            std::cout << "===== BLOCKCHAIN EXAMPLE =====" << std::endl << std::endl;
            
            std::vector<std::string> transactions = {
                "Alice sends 1 BTC to Bob",
                "Bob sends 0.5 BTC to Charlie",
                "David sends 5 BTC to Alice",
                "Charlie sends 0.1 BTC to David"
            };
            
            std::cout << "Transactions in block:" << std::endl;
            for (const auto& tx : transactions) {
                std::cout << " - " << tx << std::endl;
            }
            std::cout << std::endl;
            
            MerkleTree blockTree(transactions);
            std::cout << "Merkle tree of transactions:" << std::endl;
            blockTree.printTree();
            std::cout << std::endl;
            
            std::cout << "Root hash (would be stored in the block header): " << blockTree.getRootHash() << std::endl;
            
            // Vérifier une transaction
            std::string txToVerify = "Bob sends 0.5 BTC to Charlie";
            std::cout << "Verifying transaction: \"" << txToVerify << "\"" << std::endl;
            std::cout << "Transaction is " << (blockTree.verify(txToVerify) ? "VALID" : "INVALID") << " in the block" << std::endl;
            
            // Vérifier une transaction frauduleuse
            std::string fraudTx = "Bob sends 100 BTC to Mallory";
            std::cout << "Verifying fraudulent transaction: \"" << fraudTx << "\"" << std::endl;
            std::cout << "Transaction is " << (blockTree.verify(fraudTx) ? "VALID" : "INVALID") << " in the block" << std::endl;
            std::cout << std::endl;
            
            std::cout << "All tests completed successfully!" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Exception in blockchain example: " << e.what() << std::endl;
            return 1;
        } catch (...) {
            std::cerr << "Unknown exception in blockchain example" << std::endl;
            return 1;
        }
        
        // Test de vérification
        try {
            std::cout << "Testing verification..." << std::endl;
            std::vector<std::string> data = {"block1", "block2", "block3", "block4"};
            MerkleTree tree(data);
            
            std::string dataToVerify = "block1";
            std::cout << "Calculating hash..." << std::endl;
            std::string dataHash = sha256(dataToVerify);
            
            std::cout << "Hash of '" << dataToVerify << "': " << dataHash << std::endl;
            std::cout << "Is '" << dataToVerify << "' in the tree: " << (tree.verify(dataToVerify) ? "Yes" : "No") << std::endl;
            
            std::string invalidData = "block5";
            std::cout << "Is '" << invalidData << "' in the tree: " << (tree.verify(invalidData) ? "Yes" : "No") << std::endl;
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Exception in verification test: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception in verification test" << std::endl;
        }
        
        displayTestResult("Hash consistency", testHashConsistency());
        std::cout << std::endl;
        
        displayTestResult("Empty tree", testEmptyTree());
        std::cout << std::endl;
        
        // Test supplémentaire avec un exemple concret de blockchain
        std::cout << "===== BLOCKCHAIN EXAMPLE =====" << std::endl << std::endl;
        
        std::vector<std::string> transactions = {
            "Alice sends 1 BTC to Bob",
            "Bob sends 0.5 BTC to Charlie",
            "David sends 5 BTC to Alice",
            "Charlie sends 0.1 BTC to David"
        };
        
        std::cout << "Transactions in block:" << std::endl;
        for (const auto& tx : transactions) {
            std::cout << " - " << tx << std::endl;
        }
        std::cout << std::endl;
        
        MerkleTree blockTree(transactions);
        std::cout << "Merkle tree of transactions:" << std::endl;
        blockTree.printTree();
        std::cout << std::endl;
        
        std::cout << "Root hash (would be stored in the block header): " << blockTree.getRootHash() << std::endl;
        
        // Vérifier une transaction
        std::string txToVerify = "Bob sends 0.5 BTC to Charlie";
        std::cout << "Verifying transaction: \"" << txToVerify << "\"" << std::endl;
        std::cout << "Transaction is " << (blockTree.verify(txToVerify) ? "VALID" : "INVALID") << " in the block" << std::endl;
        
        // Vérifier une transaction frauduleuse
        std::string fraudTx = "Bob sends 100 BTC to Mallory";
        std::cout << "Verifying fraudulent transaction: \"" << fraudTx << "\"" << std::endl;
        std::cout << "Transaction is " << (blockTree.verify(fraudTx) ? "VALID" : "INVALID") << " in the block" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception caught in main" << std::endl;
    }
    
    return 0;
}