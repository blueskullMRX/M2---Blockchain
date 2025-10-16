#include "blockchain.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>

// Fonction pour afficher tous les blocs de la blockchain
void printBlockchain(const Blockchain& bc) {
    const std::vector<Block>& chain = bc.getChain();
    
    std::cout << "===== État de la Blockchain =====" << std::endl;
    for (const auto& block : chain) {
        std::cout << block.toString();
    }
    std::cout << "=================================" << std::endl << std::endl;
}

// Fonction pour tester la blockchain avec différentes difficultés
void testDifficulty(int minDifficulty, int maxDifficulty) {
    std::cout << "Test de Proof of Work avec differentes difficultes" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    // Tableau pour stocker les temps de minage par difficulte
    std::vector<std::pair<int, double>> miningTimes;
    
    // Tester chaque niveau de difficulte
    for (int diff = minDifficulty; diff <= maxDifficulty; diff++) {
        std::cout << "\nDifficulte: " << diff << " (Le hash doit commencer par " << std::string(diff, '0') << ")" << std::endl;
        
        // Créer une nouvelle blockchain avec la difficulté actuelle
        Blockchain blockchain(diff);
        
        // Chronométrer le temps de minage d'un bloc
        auto startTime = std::chrono::high_resolution_clock::now();
        
        // Ajouter un bloc (sera miné avec la difficulté actuelle)
        blockchain.addBlock("Transaction data for difficulty " + std::to_string(diff));
        
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        
        // Afficher le dernier bloc
        std::cout << "Bloc miné avec difficulté " << diff << ":" << std::endl;
        std::cout << blockchain.getLatestBlock().toString();
        
        // Stocker le temps de minage
        miningTimes.push_back({diff, duration / 1000.0}); // Convertir en secondes
    }
    
    // Afficher un tableau recapitulatif
    std::cout << "\n===== Recapitulatif des temps de minage =====" << std::endl;
    std::cout << "| Difficulte | Temps (s) |" << std::endl;
    std::cout << "|------------|-----------|" << std::endl;
    
    for (const auto& entry : miningTimes) {
        std::cout << "| " << std::setw(10) << entry.first 
                  << " | " << std::setw(9) << std::fixed << std::setprecision(3) << entry.second 
                  << " |" << std::endl;
    }
    
    std::cout << "===========================================" << std::endl;
}

// Fonction principale
int main() {
    // Demonstration de base avec une blockchain de difficulte 4
    int baseDifficulty = 4;
    std::cout << "Demonstration d'une blockchain avec difficulte " << baseDifficulty << std::endl;
    std::cout << "=======================================" << std::endl;
    
    Blockchain blockchain(baseDifficulty);
    
    std::cout << "Ajout du bloc 1..." << std::endl;
    blockchain.addBlock("Premier bloc avec quelques transactions");
    
    std::cout << "\nAjout du bloc 2..." << std::endl;
    blockchain.addBlock("Deuxième bloc avec d'autres transactions");
    
    std::cout << "\nAjout du bloc 3..." << std::endl;
    blockchain.addBlock("Troisième bloc avec encore plus de transactions");
    
    // Afficher l'état de la blockchain
    printBlockchain(blockchain);
    
    // Vérifier l'intégrité de la blockchain
    std::cout << "La blockchain est " 
              << (blockchain.isChainValid() ? "valide" : "invalide") 
              << "!" << std::endl << std::endl;
    
    // Tester différentes difficultés (adapter selon la puissance de la machine)
    testDifficulty(1, 6);
    
    return 0;
}