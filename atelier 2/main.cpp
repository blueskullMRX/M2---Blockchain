#include "blockchain.h"
#include "hash.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <algorithm>
#include <chrono>

// Utility function to generate random transactions
std::vector<Transaction> generateRandomTransactions(int count) {
    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> amountDist(1, 1000);
    
    // List of demo addresses
    std::vector<std::string> addresses = {
        "0xabc123", "0xdef456", "0xghi789", "0xjkl012",
        "0xmno345", "0xpqr678", "0xstu901", "0xvwx234"
    };
    
    // Generate transactions
    std::vector<Transaction> transactions;
    for (int i = 0; i < count; i++) {
        std::string id = "tx" + std::to_string(i);
        std::string sender = addresses[gen() % addresses.size()];
        std::string receiver = addresses[gen() % addresses.size()];
        
        // Ensure sender and receiver are different
        while (sender == receiver) {
            receiver = addresses[gen() % addresses.size()];
        }
        
        double amount = amountDist(gen);
        transactions.emplace_back(id, sender, receiver, amount);
    }
    
    return transactions;
}

// Test the AC hash function with different inputs
void testACHash() {
    std::cout << "===== Testing AC Hash Function =====" << std::endl;
    
    // Test 2.4: Verify that two different inputs give different outputs
    std::string input1 = "Hello, World!";
    std::string input2 = "Hello, World?";
    std::string input3 = "Blockchain with Cellular Automaton";
    
    std::cout << "Input 1: \"" << input1 << "\"" << std::endl;
    std::string hash1 = ac_hash(input1, 30, 100);
    std::cout << "Hash 1:  " << hash1 << std::endl << std::endl;
    
    std::cout << "Input 2: \"" << input2 << "\"" << std::endl;
    std::string hash2 = ac_hash(input2, 30, 100);
    std::cout << "Hash 2:  " << hash2 << std::endl << std::endl;
    
    std::cout << "Input 3: \"" << input3 << "\"" << std::endl;
    std::string hash3 = ac_hash(input3, 30, 100);
    std::cout << "Hash 3:  " << hash3 << std::endl << std::endl;
    
    // Verify that hashes are different
    if (hash1 != hash2 && hash1 != hash3 && hash2 != hash3) {
        std::cout << " SUCCESS: All three inputs produced different hashes!" << std::endl;
    } else {
        std::cout << " FAILURE: Some hashes are identical!" << std::endl;
    }
    
    // Test with different rules
    std::cout << "\n===== Testing Different CA Rules =====" << std::endl;
    std::string testInput = "Test Input";
    
    std::cout << "Input: \"" << testInput << "\"" << std::endl;
    std::cout << "Rule 30:  " << ac_hash(testInput, 30, 100) << std::endl;
    std::cout << "Rule 90:  " << ac_hash(testInput, 90, 100) << std::endl;
    std::cout << "Rule 110: " << ac_hash(testInput, 110, 100) << std::endl;
    std::cout << std::endl;
}

// Run a blockchain test with the specified configuration
void runBlockchainTest(bool usePoS, int difficulty, int blockCount, int txPerBlock, uint32_t rule = 30) {
    std::cout << "===== Testing " << (usePoS ? "Proof of Stake" : "Proof of Work") 
              << " with AC Hash (Rule " << rule << ") =====" << std::endl;
    
    // Create blockchain with specified consensus mechanism and AC hash
    Blockchain blockchain(usePoS, difficulty, rule, 100);
    
    // Add stakeholders if using PoS
    if (usePoS) {
        blockchain.addStakeholder("Alice", 100.0);
        blockchain.addStakeholder("Bob", 200.0);
        blockchain.addStakeholder("Charlie", 50.0);
        blockchain.addStakeholder("Dave", 150.0);
        std::cout << "Total stake in system: " << blockchain.getTotalStake() << std::endl;
    } else {
        std::cout << "Mining difficulty: " << difficulty << std::endl;
    }
    
    // Track total time
    long totalTime = 0;
    
    // Add blocks
    std::cout << "Adding " << blockCount << " blocks with " << txPerBlock << " transactions each..." << std::endl;
    for (int i = 0; i < blockCount; i++) {
        // Generate random transactions
        auto transactions = generateRandomTransactions(txPerBlock);
        
        // Add block and track time
        long blockTime = blockchain.addBlock(transactions);
        totalTime += blockTime;
    }
    
    // Print chain and statistics
    blockchain.printChain();
    
    // Verify blockchain integrity
    std::cout << "Blockchain is " << (blockchain.isChainValid() ? "valid" : "invalid") << "!" << std::endl;
    
    // Print performance statistics
    std::cout << "Performance Statistics:" << std::endl;
    std::cout << "Total Time: " << totalTime << " ms" << std::endl;
    std::cout << "Average Time per Block: " << static_cast<double>(totalTime) / blockCount << " ms" << std::endl;
    std::cout << "Average Time per Transaction: " << static_cast<double>(totalTime) / (blockCount * txPerBlock) << " ms" << std::endl;
    std::cout << std::endl;
}

// Compare different CA rules
void compareCARule() {
    std::cout << "===== Comparing Different CA Rules =====" << std::endl;
    
    const int blockCount = 5;
    const int txPerBlock = 10;
    const std::vector<uint32_t> rules = {30, 90, 110};
    
    for (uint32_t rule : rules) {
        Blockchain blockchain(false, 2, rule, 100);  // Use PoW with difficulty 2
        
        long totalTime = 0;
        for (int i = 0; i < blockCount; i++) {
            auto transactions = generateRandomTransactions(txPerBlock);
            totalTime += blockchain.addBlock(transactions);
        }
        
        std::cout << "Rule " << rule << " - Total Time: " << totalTime << " ms" << std::endl;
        std::cout << "Rule " << rule << " - Average Time per Block: " 
                  << static_cast<double>(totalTime) / blockCount << " ms" << std::endl;
        std::cout << "Valid: " << (blockchain.isChainValid() ? "Yes" : "No") << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Blockchain with AC-Based Hashing" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Test the AC hash function (Task 2.4)
    testACHash();
    std::cout << "\n";
    
    // Run blockchain tests with AC-based hashing using PoS
    runBlockchainTest(true, 0, 5, 10, 30);   // PoS with Rule 30
    std::cout << "\n";
    
    // Test with different rules
    runBlockchainTest(true, 0, 3, 5, 90);   // PoS with Rule 90
    std::cout << "\n";
    
    runBlockchainTest(true, 0, 3, 5, 110);   // PoS with Rule 110
    std::cout << "\n";
    
    std::cout << "========================================" << std::endl;
    std::cout << "  All tests completed successfully!" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}
