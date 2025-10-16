#include "blockchain.h"
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

// Run a blockchain test with the specified configuration
void runBlockchainTest(bool usePoS, int difficulty, int blockCount, int txPerBlock) {
    std::cout << "===== Testing " << (usePoS ? "Proof of Stake" : "Proof of Work") << " =====" << std::endl;
    
    // Create blockchain with specified consensus mechanism
    Blockchain blockchain(usePoS, difficulty);
    
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

// Compare PoW and PoS performance
void compareConsensusAlgorithms() {
    std::cout << "===== Comparing PoW and PoS =====" << std::endl;
    
    // Test parameters
    const int blockCount = 10;
    const int txPerBlock = 30;
    const std::vector<int> difficulties = {3, 4};
    
    // Results
    std::vector<long> powTimes;
    long posTime = 0;
    
    // Run PoS test first
    {
        Blockchain blockchain(true, 0);  // Use PoS
        
        // Add stakeholders
        blockchain.addStakeholder("Alice", 100.0);
        blockchain.addStakeholder("Bob", 200.0);
        blockchain.addStakeholder("Charlie", 50.0);
        blockchain.addStakeholder("Dave", 150.0);
        
        // Add blocks and track time
        long totalTime = 0;
        for (int i = 0; i < blockCount; i++) {
            auto transactions = generateRandomTransactions(txPerBlock);
            totalTime += blockchain.addBlock(transactions);
        }
        
        posTime = totalTime;
        std::cout << "PoS Total Time: " << totalTime << " ms" << std::endl;
        std::cout << "PoS Average Time per Block: " << static_cast<double>(totalTime) / blockCount << " ms" << std::endl;
    }
    
    // Run PoW tests with different difficulties
    for (int difficulty : difficulties) {
        Blockchain blockchain(false, difficulty);  // Use PoW with varying difficulty
        
        // Add blocks and track time
        long totalTime = 0;
        for (int i = 0; i < blockCount; i++) {
            auto transactions = generateRandomTransactions(txPerBlock);
            totalTime += blockchain.addBlock(transactions);
        }
        
        powTimes.push_back(totalTime);
        std::cout << "PoW (difficulty " << difficulty << ") Total Time: " << totalTime << " ms" << std::endl;
        std::cout << "PoW (difficulty " << difficulty << ") Average Time per Block: " 
                  << static_cast<double>(totalTime) / blockCount << " ms" << std::endl;
    }
    
    // Calculate and display speedup
    std::cout << "\n===== Performance Comparison =====" << std::endl;
    for (size_t i = 0; i < difficulties.size(); i++) {
        double speedup = static_cast<double>(powTimes[i]) / posTime;
        std::cout << "PoS is approximately " << std::fixed << std::setprecision(2) 
                  << speedup << " times faster than PoW with difficulty " 
                  << difficulties[i] << std::endl;
    }
}

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Run tests with both consensus algorithms
    runBlockchainTest(false, 3, 3, 5);  // PoW with difficulty 3
    std::cout << "\n\n";
    runBlockchainTest(true, 0, 3, 5);   // PoS
    std::cout << "\n\n";
    
    // Compare performance
    compareConsensusAlgorithms();
    
    return 0;
}