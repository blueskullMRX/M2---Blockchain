#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <random>
#include <sstream>
#include <ctime>
#include <openssl/sha.h>

// Include AC hash implementation
#include "hash.h"
#include "automate_cellulaire.h"

// Transaction structure (simplified, compatible with both implementations)
struct SimpleTransaction {
    std::string id;
    std::string sender;
    std::string receiver;
    double amount;
    
    SimpleTransaction(const std::string& id, const std::string& sender, 
                     const std::string& receiver, double amount)
        : id(id), sender(sender), receiver(receiver), amount(amount) {}
    
    std::string toString() const {
        std::stringstream ss;
        ss << id << ":" << sender << ":" << receiver << ":" << amount;
        return ss.str();
    }
};

// SHA-256 helper function
std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Simplified block structure for testing
struct TestBlock {
    int index;
    time_t timestamp;
    std::string previousHash;
    std::vector<SimpleTransaction> transactions;
    int nonce;
    std::string hash;
    
    TestBlock(int idx, const std::vector<SimpleTransaction>& txs, const std::string& prevHash)
        : index(idx), timestamp(std::time(nullptr)), previousHash(prevHash), 
          transactions(txs), nonce(0) {}
};

// Calculate block data string (common for both methods)
std::string getBlockData(const TestBlock& block) {
    std::stringstream ss;
    ss << block.index << block.timestamp << block.previousHash;
    for (const auto& tx : block.transactions) {
        ss << tx.toString();
    }
    ss << block.nonce;
    return ss.str();
}

// Mine with SHA-256
struct MiningResult {
    long timeTaken;      // in milliseconds
    int iterations;      // number of hash attempts
    std::string finalHash;
};

MiningResult mineWithSHA256(TestBlock& block, int difficulty) {
    std::string target(difficulty, '0');
    auto startTime = std::chrono::high_resolution_clock::now();
    
    int iterations = 0;
    std::string blockData = getBlockData(block);
    
    do {
        block.nonce++;
        iterations++;
        std::stringstream ss;
        ss << blockData << block.nonce;
        block.hash = sha256(ss.str());
    } while (block.hash.substr(0, difficulty) != target);
    
    auto endTime = std::chrono::high_resolution_clock::now();
    long duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    return {duration, iterations, block.hash};
}

// Mine with AC Hash (modified to use leading 'a's as difficulty measure)
MiningResult mineWithACHash(TestBlock& block, int difficulty, uint32_t rule, size_t steps) {
    // For AC hash, we look for leading 'a's since AC hash produces many 'a's
    // This is more realistic for this hash function
    std::string target(difficulty + 9, 'a');  // Looking for at least (difficulty+9) leading 'a's
    auto startTime = std::chrono::high_resolution_clock::now();
    
    int iterations = 0;
    std::string blockData = getBlockData(block);
    
    do {
        block.nonce++;
        iterations++;
        std::stringstream ss;
        ss << blockData << block.nonce;
        block.hash = ac_hash(ss.str(), rule, steps);
    } while (block.hash.substr(0, difficulty + 9) != target);
    
    auto endTime = std::chrono::high_resolution_clock::now();
    long duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    return {duration, iterations, block.hash};
}

// Generate random transactions
std::vector<SimpleTransaction> generateTransactions(int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> amountDist(1, 1000);
    
    std::vector<std::string> addresses = {
        "0xabc123", "0xdef456", "0xghi789", "0xjkl012"
    };
    
    std::vector<SimpleTransaction> transactions;
    for (int i = 0; i < count; i++) {
        std::string id = "tx" + std::to_string(i);
        std::string sender = addresses[gen() % addresses.size()];
        std::string receiver = addresses[gen() % addresses.size()];
        while (sender == receiver) {
            receiver = addresses[gen() % addresses.size()];
        }
        double amount = amountDist(gen);
        transactions.emplace_back(id, sender, receiver, amount);
    }
    return transactions;
}

// Print table separator
void printSeparator(int width) {
    std::cout << "+" << std::string(width - 2, '-') << "+" << std::endl;
}

// Print centered text
void printCentered(const std::string& text, int width) {
    int padding = (width - text.length() - 2) / 2;
    std::cout << "|" << std::string(padding, ' ') << text 
              << std::string(width - text.length() - padding - 2, ' ') << "|" << std::endl;
}

// Main comparison function
void compareHashMethods(int numBlocks, int difficulty, int txPerBlock, uint32_t acRule, size_t acSteps) {
    std::cout << "\n";
    printSeparator(80);
    printCentered("HASH METHOD COMPARISON: SHA-256 vs AC Hash", 80);
    printSeparator(80);
    
    std::cout << "| Configuration:" << std::string(65, ' ') << "|" << std::endl;
    std::cout << "|   - Number of blocks: " << numBlocks << std::string(54, ' ') << "|" << std::endl;
    std::cout << "|   - Difficulty (SHA-256): " << difficulty << " leading zeros" << std::string(34, ' ') << "|" << std::endl;
    std::cout << "|   - Difficulty (AC Hash): " << (difficulty + 9) << " leading 'a's" << std::string(37, ' ') << "|" << std::endl;
    std::cout << "|   - Transactions per block: " << txPerBlock << std::string(48, ' ') << "|" << std::endl;
    std::cout << "|   - AC Rule: " << acRule << " (steps: " << acSteps << ")" << std::string(47, ' ') << "|" << std::endl;
    printSeparator(80);
    
    // Test SHA-256
    std::cout << "\nMining with SHA-256..." << std::endl;
    std::vector<MiningResult> sha256Results;
    std::string prevHash = "0";
    
    for (int i = 0; i < numBlocks; i++) {
        auto transactions = generateTransactions(txPerBlock);
        TestBlock block(i, transactions, prevHash);
        
        auto result = mineWithSHA256(block, difficulty);
        sha256Results.push_back(result);
        prevHash = block.hash;
        
        std::cout << "  Block " << i << ": " << result.timeTaken << " ms, " 
                  << result.iterations << " iterations" << std::endl;
    }
    
    // Test AC Hash
    std::cout << "\nMining with AC Hash (Rule " << acRule << ")..." << std::endl;
    std::vector<MiningResult> acResults;
    prevHash = "0";
    
    for (int i = 0; i < numBlocks; i++) {
        auto transactions = generateTransactions(txPerBlock);
        TestBlock block(i, transactions, prevHash);
        
        auto result = mineWithACHash(block, difficulty, acRule, acSteps);
        acResults.push_back(result);
        prevHash = block.hash;
        
        std::cout << "  Block " << i << ": " << result.timeTaken << " ms, " 
                  << result.iterations << " iterations" << std::endl;
    }
    
    // Calculate statistics
    long sha256TotalTime = 0, acTotalTime = 0;
    int sha256TotalIterations = 0, acTotalIterations = 0;
    
    for (const auto& result : sha256Results) {
        sha256TotalTime += result.timeTaken;
        sha256TotalIterations += result.iterations;
    }
    
    for (const auto& result : acResults) {
        acTotalTime += result.timeTaken;
        acTotalIterations += result.iterations;
    }
    
    double sha256AvgTime = (double)sha256TotalTime / numBlocks;
    double acAvgTime = (double)acTotalTime / numBlocks;
    double sha256AvgIterations = (double)sha256TotalIterations / numBlocks;
    double acAvgIterations = (double)acTotalIterations / numBlocks;
    
    // Print results table
    std::cout << "\n";
    printSeparator(80);
    printCentered("COMPARISON RESULTS", 80);
    printSeparator(80);
    std::cout << "| Metric                              | SHA-256        | AC Hash        |" << std::endl;
    printSeparator(80);
    
    std::cout << "| Total mining time (ms)              | " 
              << std::setw(14) << std::right << sha256TotalTime 
              << " | " << std::setw(14) << std::right << acTotalTime << " |" << std::endl;
    
    std::cout << "| Average time per block (ms)         | " 
              << std::setw(14) << std::right << std::fixed << std::setprecision(2) << sha256AvgTime 
              << " | " << std::setw(14) << std::right << acAvgTime << " |" << std::endl;
    
    std::cout << "| Total iterations                    | " 
              << std::setw(14) << std::right << sha256TotalIterations 
              << " | " << std::setw(14) << std::right << acTotalIterations << " |" << std::endl;
    
    std::cout << "| Average iterations per block        | " 
              << std::setw(14) << std::right << std::fixed << std::setprecision(2) << sha256AvgIterations 
              << " | " << std::setw(14) << std::right << acAvgIterations << " |" << std::endl;
    
    std::cout << "| Time per iteration (μs)             | " 
              << std::setw(14) << std::right << std::fixed << std::setprecision(2) 
              << (sha256TotalTime * 1000.0 / sha256TotalIterations)
              << " | " << std::setw(14) << std::right 
              << (acTotalTime * 1000.0 / acTotalIterations) << " |" << std::endl;
    
    printSeparator(80);
    
    // Performance ratio
    double timeRatio = (double)acAvgTime / sha256AvgTime;
    double iterRatio = (double)acAvgIterations / sha256AvgIterations;
    
    std::cout << "\n";
    printSeparator(80);
    printCentered("PERFORMANCE RATIO (AC Hash / SHA-256)", 80);
    printSeparator(80);
    std::cout << "| Time ratio:        " << std::fixed << std::setprecision(2) << timeRatio << "x" 
              << std::string(57, ' ') << "|" << std::endl;
    std::cout << "| Iteration ratio:   " << std::fixed << std::setprecision(2) << iterRatio << "x" 
              << std::string(57, ' ') << "|" << std::endl;
    printSeparator(80);
    
    if (timeRatio < 1.0) {
        std::cout << "\n✓ AC Hash is faster than SHA-256!" << std::endl;
    } else {
        std::cout << "\n✓ SHA-256 is faster than AC Hash by " 
                  << std::fixed << std::setprecision(1) << timeRatio << "x" << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "================================================" << std::endl;
    std::cout << "   BLOCKCHAIN HASH COMPARISON BENCHMARK" << std::endl;
    std::cout << "   SHA-256 vs Cellular Automaton Hash" << std::endl;
    std::cout << "================================================" << std::endl;
    
    // Test with difficulty 1 (easier for AC hash)
    std::cout << "\n### TEST 1: Difficulty = 1 ###" << std::endl;
    compareHashMethods(10, 1, 5, 30, 100);
    
    // Test with difficulty 2
    std::cout << "\n### TEST 2: Difficulty = 2 ###" << std::endl;
    compareHashMethods(10, 2, 5, 30, 100);
    
    // Test with different AC rules
    std::cout << "\n### TEST 3: Different AC Rules (Difficulty = 1) ###" << std::endl;
    std::cout << "\n--- Rule 90 ---" << std::endl;
    compareHashMethods(10, 1, 5, 90, 100);
    
    std::cout << "\n--- Rule 110 ---" << std::endl;
    compareHashMethods(10, 1, 5, 110, 100);
    
    std::cout << "\n================================================" << std::endl;
    std::cout << "   BENCHMARK COMPLETED" << std::endl;
    std::cout << "================================================" << std::endl;
    
    return 0;
}
