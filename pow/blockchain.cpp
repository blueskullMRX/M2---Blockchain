#include "blockchain.h"
#include <iostream>
#include <chrono>

// Constructeur de Blockchain
Blockchain::Blockchain(int difficulty) : difficulty(difficulty) {
    // Créer le bloc genesis
    chain.emplace_back(Block(0, "Genesis Block", "0"));
}

// Ajouter un nouveau bloc à la blockchain
void Blockchain::addBlock(const std::string& data) {
    // Obtenir le bloc précédent
    const Block& previousBlock = getLatestBlock();
    
    // Créer un nouveau bloc
    Block newBlock(previousBlock.getIndex() + 1, data, previousBlock.getHash());
    
    // Miner le nouveau bloc
    auto startTime = std::chrono::high_resolution_clock::now();
    
    newBlock.mineBlock(difficulty);
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    std::cout << "Temps de minage: " << duration << " ms" << std::endl;
    
    // Ajouter le bloc miné à la chaîne
    chain.push_back(newBlock);
}

// Vérifier si la chaîne est valide
bool Blockchain::isChainValid() const {
    // Il faut au moins deux blocs pour faire une vérification
    if (chain.size() <= 1) return true;
    
    // Parcourir la chaîne et vérifier chaque bloc
    for (size_t i = 1; i < chain.size(); i++) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];
        
        // Vérifier que le hash du bloc est correct
        if (currentBlock.getHash() != currentBlock.calculateHash()) {
            std::cout << "Hash invalide pour le bloc #" << i << std::endl;
            return false;
        }
        
        // Vérifier que le bloc pointe bien vers le précédent
        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            std::cout << "Lien cassé entre les blocs #" << (i-1) << " et #" << i << std::endl;
            return false;
        }
    }
    
    return true;
}

// Obtenir le dernier bloc de la chaîne
const Block& Blockchain::getLatestBlock() const {
    return chain.back();
}