#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <sstream>

/**
 * Represents a simple transaction in the blockchain
 */
class Transaction {
private:
    std::string id;
    std::string sender;
    std::string receiver;
    double amount;

public:
    /**
     * Constructor for a transaction
     * 
     * @param id Unique identifier for the transaction
     * @param sender Address of the sender
     * @param receiver Address of the receiver
     * @param amount Amount being transferred
     */
    Transaction(const std::string& id, const std::string& sender, 
                const std::string& receiver, double amount)
        : id(id), sender(sender), receiver(receiver), amount(amount) {}
    
    /**
     * Get transaction ID
     */
    std::string getId() const { return id; }
    
    /**
     * Get sender address
     */
    std::string getSender() const { return sender; }
    
    /**
     * Get receiver address
     */
    std::string getReceiver() const { return receiver; }
    
    /**
     * Get transaction amount
     */
    double getAmount() const { return amount; }
    
    /**
     * Convert transaction to a string for hashing
     */
    std::string toString() const {
        std::stringstream ss;
        ss << id << ":" << sender << ":" << receiver << ":" << amount;
        return ss.str();
    }
};

#endif // TRANSACTION_H
