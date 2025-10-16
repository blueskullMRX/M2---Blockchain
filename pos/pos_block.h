#ifndef POS_BLOCK_H
#define POS_BLOCK_H

#include <string>
#include <ctime>
#include <vector>
#include <sstream>

class PosBlock {
private:
    int index;                      // Position of the block in the chain
    time_t timestamp;               // Timestamp of when the block was created
    std::string data;               // Data stored in the block
    std::string previousHash;       // Hash of the previous block
    std::string hash;               // Hash of the current block
    std::string validator;          // Address of the validator who created this block
    
public:
    // Constructor
    PosBlock(int idx, const std::string& data, const std::string& prevHash, const std::string& validator);
    
    // Calculate the hash of the block
    std::string calculateHash() const;
    
    // Getters
    int getIndex() const { return index; }
    std::string getData() const { return data; }
    std::string getHash() const { return hash; }
    std::string getPreviousHash() const { return previousHash; }
    time_t getTimestamp() const { return timestamp; }
    std::string getValidator() const { return validator; }
    
    // For displaying the block
    std::string toString() const;
};

#endif // POS_BLOCK_H