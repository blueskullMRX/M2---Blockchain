#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <ctime>
#include <vector>
#include <sstream>
#include <iomanip>

// Déclaration anticipée de la fonction SHA-256
std::string sha256(const std::string& str);

class Block {
private:
    int index;                      // Position du bloc dans la chaîne
    time_t timestamp;               // Timestamp de création du bloc
    std::string data;               // Données stockées dans le bloc
    std::string previousHash;       // Hash du bloc précédent
    std::string hash;               // Hash du bloc actuel
    int nonce;                      // Nonce utilisé pour le PoW
    
public:
    // Constructeur
    Block(int idx, const std::string& data, const std::string& prevHash);
    
    // Calculer le hash du bloc
    std::string calculateHash() const;
    
    // Miner le bloc avec une difficulté donnée
    void mineBlock(int difficulty);
    
    // Getters
    int getIndex() const { return index; }
    std::string getData() const { return data; }
    std::string getHash() const { return hash; }
    std::string getPreviousHash() const { return previousHash; }
    time_t getTimestamp() const { return timestamp; }
    int getNonce() const { return nonce; }
    
    // Pour afficher le bloc
    std::string toString() const;
};

#endif // BLOCK_H