#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include <string>
#include <vector>

// Classe représentant un nœud dans l'arbre de Merkle
class Node {
public:
    std::string hash;
    Node* left;
    Node* right;
    
    // Constructeur pour un nœud feuille
    Node(const std::string& data);
    
    // Constructeur pour un nœud interne
    Node(Node* left, Node* right);
    
    // Destructeur
    ~Node();
};

// Classe représentant l'arbre de Merkle
class MerkleTree {
private:
    Node* root;
    
    // Construire l'arbre à partir des nœuds feuilles
    Node* buildTree(std::vector<Node*>& nodes);
    
    // Vérifier si un hash est dans l'arbre
    bool verifyInLeaves(const std::string& data) const;
    
    // Collecter les hash des feuilles
    void collectLeafHashes(const Node* node, std::vector<std::string>& hashes) const;
    
public:
    // Constructeur
    MerkleTree(const std::vector<std::string>& data);
    
    // Destructeur
    ~MerkleTree();
    
    // Obtenir le hash racine
    std::string getRootHash() const;
    
    // Vérifier si une donnée est dans l'arbre
    bool verify(const std::string& data) const;
    
    // Récupérer tous les hash des feuilles
    std::vector<std::string> getAllLeafHashes() const;
    
    // Afficher l'arbre
    void printTree() const;
    
    // Afficher un nœud et ses enfants
    void printNode(const Node* node, int depth) const;
};

// Fonction utilitaire pour calculer le hash SHA-256
std::string sha256(const std::string& str);

#endif // MERKLE_TREE_H