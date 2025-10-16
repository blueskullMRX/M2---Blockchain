#ifndef STAKE_H
#define STAKE_H

#include <string>

class Stake {
public:
    std::string address;  // Address of the stakeholder
    double amount;        // Amount of coins staked
    
    // Constructor
    Stake(const std::string& addr, double amt) : address(addr), amount(amt) {}
    
    // Calculate stake weight (for selection probability)
    double getWeight() const { return amount; }
};

#endif // STAKE_H