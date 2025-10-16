#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <vector>

class Blockchain {
private:
    std::vector<Block> chain;
    int difficulty;  // Difficulté pour le PoW
    
public:
    // Constructeur
    Blockchain(int difficulty = 4);
    
    // Ajouter un nouveau bloc à la chaîne
    void addBlock(const std::string& data);
    
    // Vérifier si la chaîne est valide
    bool isChainValid() const;
    
    // Obtenir le dernier bloc de la chaîne
    const Block& getLatestBlock() const;
    
    // Obtenir tous les blocs
    const std::vector<Block>& getChain() const { return chain; }
    
    // Changer la difficulté
    void setDifficulty(int newDifficulty) { difficulty = newDifficulty; }
    
    // Obtenir la difficulté actuelle
    int getDifficulty() const { return difficulty; }
};

#endif // BLOCKCHAIN_H