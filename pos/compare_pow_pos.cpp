#include "../pow/blockchain.h"
#include "pos_blockchain.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>

// Function to print a blockchain
void printBlockchain(const std::vector<PosBlock>& chain) {
    std::cout << "===== Blockchain State =====" << std::endl;
    for (const auto& block : chain) {
        std::cout << block.toString();
    }
    std::cout << "===========================" << std::endl << std::endl;
}

// Compare the performance of PoW and PoS
void comparePerformance(int numBlocks, int powDifficulty) {
    std::cout << "Comparing Performance: PoW vs PoS for " << numBlocks << " blocks" << std::endl;
    std::cout << "=========================================================" << std::endl;
    
    // Initialize both blockchains
    Blockchain powChain(powDifficulty);
    PosBlockchain posChain;
    
    // Add stakeholders to PoS chain
    posChain.addStakeholder("Alice", 100.0);
    posChain.addStakeholder("Bob", 200.0);
    posChain.addStakeholder("Charlie", 50.0);
    posChain.addStakeholder("Dave", 150.0);
    
    // Measure PoW performance
    std::cout << "Mining " << numBlocks << " blocks with PoW (difficulty " << powDifficulty << ")..." << std::endl;
    auto powStartTime = std::chrono::high_resolution_clock::now();
    
    for (int i = 1; i <= numBlocks; i++) {
        powChain.addBlock("Block " + std::to_string(i) + " data");
    }
    
    auto powEndTime = std::chrono::high_resolution_clock::now();
    auto powDuration = std::chrono::duration_cast<std::chrono::milliseconds>(powEndTime - powStartTime).count();
    
    // Measure PoS performance
    std::cout << "\nValidating " << numBlocks << " blocks with PoS..." << std::endl;
    auto posStartTime = std::chrono::high_resolution_clock::now();
    
    for (int i = 1; i <= numBlocks; i++) {
        posChain.addBlock("Block " + std::to_string(i) + " data");
    }
    
    auto posEndTime = std::chrono::high_resolution_clock::now();
    auto posDuration = std::chrono::duration_cast<std::chrono::milliseconds>(posEndTime - posStartTime).count();
    
    // Results
    std::cout << "\n===== Performance Results =====" << std::endl;
    std::cout << "PoW Total Time: " << powDuration << " ms" << std::endl;
    std::cout << "PoW Average Time per Block: " << static_cast<double>(powDuration) / numBlocks << " ms" << std::endl;
    std::cout << "PoS Total Time: " << posDuration << " ms" << std::endl;
    std::cout << "PoS Average Time per Block: " << static_cast<double>(posDuration) / numBlocks << " ms" << std::endl;
    
    double speedup = static_cast<double>(powDuration) / posDuration;
    std::cout << "PoS is approximately " << std::fixed << std::setprecision(2) << speedup 
              << " times faster than PoW" << std::endl;
    
    // Verify both chains are valid
    std::cout << "\nPoW chain is " << (powChain.isChainValid() ? "valid" : "invalid") << std::endl;
    std::cout << "PoS chain is " << (posChain.isChainValid() ? "valid" : "invalid") << std::endl;
}

int main() {
    // Test basic functionality of PoS blockchain
    std::cout << "===== Testing Proof of Stake Blockchain =====" << std::endl;
    
    PosBlockchain blockchain;
    
    // Add stakeholders with different stake amounts
    blockchain.addStakeholder("Alice", 100.0);
    blockchain.addStakeholder("Bob", 200.0);
    blockchain.addStakeholder("Charlie", 50.0);
    blockchain.addStakeholder("Dave", 150.0);
    
    std::cout << "Total stake in system: " << blockchain.getTotalStake() << std::endl;
    std::cout << "Adding blocks..." << std::endl;
    
    // Add some blocks
    blockchain.addBlock("First block with transactions");
    blockchain.addBlock("Second block with more transactions");
    blockchain.addBlock("Third block with even more transactions");
    
    // Print blockchain
    printBlockchain(blockchain.getChain());
    
    // Verify integrity
    std::cout << "Blockchain is " << (blockchain.isChainValid() ? "valid" : "invalid") << "!" << std::endl << std::endl;
    
    // Compare performance of PoW and PoS
    comparePerformance(5, 4);  // 5 blocks, PoW difficulty 4
    std::cout << "\n\n--------------------------------------------\n\n";
    comparePerformance(5, 5);  // 5 blocks, PoW difficulty 5
    
    return 0;
}