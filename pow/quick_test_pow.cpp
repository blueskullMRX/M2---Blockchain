#include "blockchain.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>

// Fonction pour afficher tous les blocs de la blockchain
void printBlockchain(const Blockchain& bc) {
    const std::vector<Block>& chain = bc.getChain();
    
    std::cout << "===== Etat de la Blockchain =====" << std::endl;
    for (const auto& block : chain) {
        std::cout << block.toString();
    }
    std::cout << "=================================" << std::endl << std::endl;
}

int main() {
    // Test avec des difficultes raisonnables
    std::cout << "Test de Proof of Work avec differentes difficultes" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    // Tableau pour stocker les temps de minage par difficulte
    std::vector<std::pair<int, double>> miningTimes;
    
    // Tester les niveaux de difficulte de 1 a 5
    for (int diff = 1; diff <= 5; diff++) {
        std::cout << "\nDifficulte: " << diff << " (Le hash doit commencer par " << std::string(diff, '0') << ")" << std::endl;
        
        // Creer une nouvelle blockchain avec la difficulte actuelle
        Blockchain blockchain(diff);
        
        // Chronometrer le temps de minage d'un bloc
        auto startTime = std::chrono::high_resolution_clock::now();
        
        // Ajouter un bloc (sera mine avec la difficulte actuelle)
        blockchain.addBlock("Transaction data for difficulty " + std::to_string(diff));
        
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        
        // Afficher le dernier bloc
        std::cout << "Bloc mine avec difficulte " << diff << ":" << std::endl;
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
    
    return 0;
}