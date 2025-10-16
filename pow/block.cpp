#include "block.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <chrono>

// Fonction pour calculer le hash SHA-256 d'une chaîne de caractères
inline std::string sha256(const std::string& str) {
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

// Constructeur de Block
Block::Block(int idx, const std::string& data, const std::string& prevHash) 
    : index(idx), timestamp(std::time(nullptr)), data(data), previousHash(prevHash), nonce(0) {
    hash = calculateHash();
}

// Calculer le hash du bloc en utilisant ses attributs
std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << data << previousHash << nonce;
    return sha256(ss.str());
}

// Miner le bloc avec une difficulté donnée
void Block::mineBlock(int difficulty) {
    // Créer une chaîne de caractères qui servira de "cible" pour le PoW
    // Par exemple, difficulty = 4 signifie que le hash doit commencer par "0000"
    std::string target(difficulty, '0');
    
    // Continuer à incrémenter le nonce jusqu'à ce que le hash commence par la cible
    while (hash.substr(0, difficulty) != target) {
        nonce++;
        hash = calculateHash();
    }
    
    std::cout << "Bloc miné ! Hash: " << hash << std::endl;
}

// Affichage du bloc sous forme de chaîne de caractères
std::string Block::toString() const {
    std::stringstream ss;
    ss << "Block #" << index << " [" << std::endl;
    ss << "  Timestamp: " << timestamp << std::endl;
    ss << "  Data: " << data << std::endl;
    ss << "  Previous Hash: " << previousHash << std::endl;
    ss << "  Hash: " << hash << std::endl;
    ss << "  Nonce: " << nonce << std::endl;
    ss << "]" << std::endl;
    return ss.str();
}