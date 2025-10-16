#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include "merkle_tree.h"

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

// Constructeur pour un nœud feuille (contenant les données de base)
Node::Node(const std::string& data) : left(nullptr), right(nullptr) {
    hash = sha256(data);
}

// Constructeur pour un nœud interne (parent de deux nœuds)
Node::Node(Node* left, Node* right) : left(left), right(right) {
    hash = sha256(left->hash + right->hash);
}

// Destructeur
Node::~Node() {
    // Add safety checks
    if (left != right) {
        delete left;
        delete right;
    } else if (left) {
        // If left and right point to the same node (duplicated last node case),
        // only delete one of them to avoid double free
        delete left;
        right = nullptr; // Prevent second deletion of the same pointer
    }
}

// Implémentation des méthodes de la classe MerkleTree

// Construire récursivement l'arbre à partir des nœuds feuilles
Node* MerkleTree::buildTree(std::vector<Node*>& nodes) {
    if (nodes.size() == 1) {
        return nodes[0];
    }
    
    std::vector<Node*> parents;
    
    // Regrouper les nœuds deux par deux pour créer leurs parents
    for (size_t i = 0; i < nodes.size(); i += 2) {
        if (i + 1 < nodes.size()) {
            parents.push_back(new Node(nodes[i], nodes[i + 1]));
        } else {
            // Si le nombre de nœuds est impair, dupliquer le dernier nœud
            parents.push_back(new Node(nodes[i], nodes[i]));
        }
    }
    
    // Appel récursif pour continuer à construire les niveaux supérieurs de l'arbre
    return buildTree(parents);
}

// Constructeur à partir d'un vecteur de données
MerkleTree::MerkleTree(const std::vector<std::string>& data) {
    // Créer les nœuds feuilles
    std::vector<Node*> leaves;
    for (const auto& item : data) {
        leaves.push_back(new Node(item));
    }
    
    // Vérifier si la liste des données est vide
    if (leaves.empty()) {
        root = nullptr;
    } else {
        // Construire l'arbre
        root = buildTree(leaves);
    }
}

// Destructeur
MerkleTree::~MerkleTree() {
    delete root;
}

// Obtenir le hash racine (hash représentant l'ensemble des données)
std::string MerkleTree::getRootHash() const {
    return root ? root->hash : "";
}

// Vérifier si une donnée est présente dans l'arbre
bool MerkleTree::verify(const std::string& data) const {
    if (!root) return false;
    return verifyInLeaves(data);
}

// Vérifier si une donnée est présente dans les feuilles
bool MerkleTree::verifyInLeaves(const std::string& data) const {
    // Recréer le hash de la donnée
    std::string dataHash = sha256(data);
    
    // Récupérer tous les hash des feuilles
    std::vector<std::string> leaves = getAllLeafHashes();
    
    // Comparer avec les hash des feuilles
    for (const auto& leaf : leaves) {
        if (leaf == dataHash) {
            return true;
        }
    }
    
    return false;
}

// Récupérer tous les hash des feuilles
std::vector<std::string> MerkleTree::getAllLeafHashes() const {
    std::vector<std::string> result;
    if (root) {
        collectLeafHashes(root, result);
    }
    return result;
}

// Collecter récursivement les hash des feuilles
void MerkleTree::collectLeafHashes(const Node* node, std::vector<std::string>& hashes) const {
    if (!node) return;
    
    // Si c'est une feuille (pas de fils)
    if (!node->left && !node->right) {
        hashes.push_back(node->hash);
    } else {
        // Continuer la recherche récursive
        collectLeafHashes(node->left, hashes);
        collectLeafHashes(node->right, hashes);
    }
}

// Afficher l'arbre pour le débogage
void MerkleTree::printTree() const {
    printNode(root, 0);
}

// Afficher un nœud et ses enfants
void MerkleTree::printNode(const Node* node, int depth) const {
    if (!node) return;
    
    std::string indent(depth * 4, ' ');
    std::cout << indent << "Hash: " << node->hash.substr(0, 10) << "..." << std::endl;
    
    if (node->left || node->right) {
        if (node->left) printNode(node->left, depth + 1);
        if (node->right) printNode(node->right, depth + 1);
    }
}