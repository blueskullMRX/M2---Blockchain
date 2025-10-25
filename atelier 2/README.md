# Atelier 2: Automate Cellulaire & Blockchain# Minichain with Cellular Automaton Hash



## Table des MatièresThis is a modified version of the minichain blockchain that uses **Cellular Automaton (CA) based hashing** instead of traditional SHA-256.

1. [Vue d'ensemble](#vue-densemble)

2. [Partie 1: Automate Cellulaire 1D](#partie-1-automate-cellulaire-1d)## Features

3. [Partie 2: Fonction de Hachage](#partie-2-fonction-de-hachage)

4. [Partie 3: Arbre de Merkle](#partie-3-arbre-de-merkle)- **AC-Based Hashing**: Uses a 1D elementary cellular automaton to compute 256-bit hashes

5. [Partie 4: Blockchain](#partie-4-blockchain)- **Configurable CA Rules**: Support for different rules (Rule 30, Rule 90, Rule 110, etc.)

6. [Tests et Comparaisons](#tests-et-comparaisons)- **Merkle Trees**: Transaction validation using Merkle trees with AC hashing

7. [Compilation et Exécution](#compilation-et-exécution)- **Dual Consensus**: Support for both Proof of Work (PoW) and Proof of Stake (PoS)

8. [Résultats et Analyses](#résultats-et-analyses)- **No OpenSSL Dependency**: Pure C++ implementation without external cryptographic libraries



---## Components



## Vue d'ensemble### 1. Cellular Automaton (`automate_cellulaire.h/cpp`)

- 1D elementary cellular automaton with binary state

Ce projet implémente une blockchain complète basée sur des automates cellulaires (AC) pour le hachage cryptographique, remplaçant SHA-256 par une fonction de hachage personnalisée utilisant les règles 30, 90 et 110 des AC 1D.- Configurable rule number (0-255)

- Neighborhood radius r = 1

### Objectifs pédagogiques- Evolves state according to transition rules

- Comprendre les automates cellulaires et leur comportement chaotique

- Créer une fonction de hachage à partir d'un AC### 2. AC Hash Function (`hash.h/cpp`)

- Implémenter un arbre de Merkle avec hachage AC- Converts input text to 256-bit representation

- Construire une blockchain avec consensus PoS (Proof of Stake)- Applies cellular automaton evolution

- Comparer les performances AC Hash vs SHA-256- Produces fixed 256-bit (64 hex characters) output

- Configurable rule and evolution steps

### Structure du projet

```### 3. AC-Based Merkle Tree (`merkle_tree.h/cpp`)

atelier 2/- Binary Merkle tree using AC hash

├── automate_cellulaire.cpp/h    # Moteur AC 1D- Efficient transaction validation

├── hash.cpp/h                   # Fonction de hachage AC- Root hash computed from transaction leaves

├── merkle_tree.cpp/h            # Arbre de Merkle

├── block.cpp/h                  # Structure de bloc### 4. Blockchain (`block.h/cpp`, `blockchain.h/cpp`)

├── blockchain.cpp/h             # Blockchain avec PoS- Block structure with AC-based hashing

├── transaction.h                # Structure de transaction- Support for PoW and PoS consensus

├── main.cpp                     # Programme principal- Chain validation and integrity checking

├── simple_comparison.cpp        # Suite de tests complète (Tests 1-12)

├── compare_hash.cpp             # Comparaison mining détaillée## Building and Running

├── Makefile                     # Automatisation de compilation

└── README.md                    # Ce fichier### Compilation

```

```bash

---# Using Makefile

make

## Partie 1: Automate Cellulaire 1D

# Or manually with g++

### Fichiers: `automate_cellulaire.cpp`, `automate_cellulaire.h`g++ -std=c++11 -Wall automate_cellulaire.cpp hash.cpp merkle_tree.cpp block.cpp blockchain.cpp main.cpp -o minichain_ac

```

### Implémentation

### Running

#### Tâche 1.1: Structure CA

```cpp```bash

struct CA {# Using Makefile

    std::vector<bool> state;  // État actuel (256 cellules)make run

    uint32_t rule;            // Règle (0-255)

};# Or directly

```./minichain_ac

```

#### Tâche 1.2: Initialisation

```cpp### Clean

void init_state(CA& ca, const std::vector<bool>& bits);

``````bash

- Initialise l'état avec 256 bitsmake clean

- Copie directe dans `ca.state````



#### Tâche 1.3: Évolution## Testing

```cpp

void evolve(CA& ca);The `main.cpp` includes several tests:

```

- Rayon de voisinage: r=1 (3 cellules)1. **AC Hash Function Test** (Task 2.4)

- Conditions aux limites: périodiques (tore)   - Verifies that different inputs produce different hashes

- Applique la règle pour calculer le nouvel état   - Tests with Rules 30, 90, and 110

- Exemple: Règle 30 → `00011110` en binaire

2. **Blockchain Tests**

### Règles implémentées   - PoW with AC-based hashing

- **Règle 30**: Chaotique, utilisée par Wolfram   - PoS with AC-based hashing

- **Règle 90**: Rapide, patterns réguliers   - Blockchain validation

- **Règle 110**: Turing-complet, complexe

3. **CA Rule Comparison**

### Test   - Performance comparison of different CA rules

```cpp

// Exemple d'utilisation## Configuration

CA ca;

ca.rule = 30;You can customize the AC hash parameters:

std::vector<bool> initial(256, false);

initial[128] = true;  // Seed au centre```cpp

init_state(ca, initial);// In blockchain constructor

Blockchain blockchain(

for (int i = 0; i < 100; i++) {    false,  // usePoS (false = PoW, true = PoS)

    evolve(ca);  // 100 étapes d'évolution    2,      // difficulty (for PoW)

}    30,     // hashRule (CA rule number)

```    100     // hashSteps (number of CA generations)

);

---```



## Partie 2: Fonction de Hachage### Recommended CA Rules



### Fichiers: `hash.cpp`, `hash.h`- **Rule 30**: Chaotic behavior, good for cryptographic hashing

- **Rule 90**: XOR-based pattern, fast and simple

### Implémentation- **Rule 110**: Complex patterns, Turing-complete



#### Tâche 2.1: Fonction ac_hash## Differences from Original Minichain

```cpp

std::string ac_hash(const std::string& input, uint32_t rule, size_t steps);1. **No OpenSSL dependency**: Replaced SHA-256 with AC-based hash

```2. **Configurable hash algorithm**: Can change CA rule and steps

3. **Includes AC hash tests**: Demonstrates hash properties

#### Tâche 2.2: Conversion texte → bits4. **Modified Merkle tree**: Uses AC hash instead of SHA-256

```cpp

std::vector<bool> string_to_bits(const std::string& str);## Hash Properties

```

**Processus:**The AC-based hash function provides:

1. Convertir chaque caractère en 8 bits

2. Si < 256 bits → padding avec des zéros- **Deterministic**: Same input always produces same output

3. Si > 256 bits → compression par XOR par blocs- **Fixed-size output**: Always 256 bits (64 hex characters)

- **Avalanche effect**: Small input changes cause large output changes

**Exemple:**- **Collision resistance**: Different inputs produce different outputs (tested)

```

"Hello" → 'H'=72, 'e'=101, 'l'=108, 'l'=108, 'o'=111## Performance Notes

        → 01001000 01100101 01101100 01101100 01101111 + padding...

```- AC hash is generally slower than SHA-256 due to multiple iterations

- Performance depends on:

#### Tâche 2.3: Production du hash 256 bits  - Number of evolution steps

```cpp  - CA rule complexity

std::string bits_to_hex(const std::vector<bool>& bits);  - Input size

```- Trade-off between security and performance

- Exécute l'AC pendant `steps` évolutions (typiquement 100)

- État final = hash 256 bits## Example Output

- Conversion en hexadécimal (64 caractères)

```

#### Tâche 2.4: Différentes entrées → différentes sorties===== Testing AC Hash Function =====

```cppInput 1: "Hello, World!"

// Test de collisionHash 1:  a3f2c1d4e5b6...

assert(ac_hash("test1", 30, 100) != ac_hash("test2", 30, 100));

```Input 2: "Hello, World?"

Hash 2:  8d7c6b5a4e3f...

### Propriétés du hash AC

- **Déterministe**: Même entrée → même sortie✓ SUCCESS: All three inputs produced different hashes!

- **Rapide**: ~0.03-0.04 ms par hash```

- **Longueur fixe**: Toujours 256 bits (64 hex)

- **Distribution unique**: Patterns différents de SHA-256## Tasks Completed



### Exemples de hashes✅ **Task 1.1**: `init_state()` function implemented  

```✅ **Task 1.2**: `evolve()` function with configurable rules  

Input: "Hello World"✅ **Task 1.3**: Verified with Rules 30, 90, 110  

Rule 30:  aaaaaaaaaaaaa8ab78ea306a8b0344ac...✅ **Task 2.1**: `ac_hash()` function with correct signature  

Rule 90:  9372960e8377820ac6180597e2007475...✅ **Task 2.2**: Text-to-bits conversion documented  

Rule 110: 87c4df07d9df73806389b9c37658efa7...✅ **Task 2.3**: 256-bit hash production documented  

```✅ **Task 2.4**: Test verifying different inputs → different outputs  

✅ **Bonus**: Integration with blockchain and Merkle trees

**Note**: Règle 30 produit beaucoup de 'a' au début (zéros en binaire), ce qui pose problème pour le mining PoW traditionnel.

## Authors

---

Based on the original minichain implementation, modified to use Cellular Automaton hashing.

## Partie 3: Arbre de Merkle

### Fichiers: `merkle_tree.cpp`, `merkle_tree.h`

### Structure
```cpp
struct MerkleNode {
    std::string hash;
    MerkleNode* left;
    MerkleNode* right;
    
    bool isLeaf() const;
};
```

### Fonctionnalités

#### Construction de l'arbre
```cpp
MerkleNode* build_merkle_tree(const std::vector<std::string>& data, 
                               uint32_t rule, size_t steps);
```
- Crée des feuilles avec hash de chaque transaction
- Combine les hashes deux par deux: `parent = hash(left + right)`
- Si nombre impair: duplique le dernier

#### Racine de Merkle
```cpp
std::string get_merkle_root(const std::vector<std::string>& transactions);
```
- Retourne le hash à la racine de l'arbre
- Utilisé comme identifiant unique des transactions

#### Preuve de Merkle
```cpp
std::vector<std::string> get_merkle_proof(MerkleNode* root, 
                                          const std::string& txHash);
bool verify_merkle_proof(const std::string& txHash, 
                         const std::vector<std::string>& proof,
                         const std::string& merkleRoot);
```
- Génère/vérifie une preuve qu'une transaction est dans l'arbre
- Complexité: O(log n)

### Exemple d'utilisation
```cpp
std::vector<std::string> txs = {"tx1", "tx2", "tx3", "tx4"};
std::string root = get_merkle_root(txs);

// Arbre:
//         root
//        /    \
//    h(1,2)   h(3,4)
//     / \      / \
//   h1  h2   h3  h4
```

---

## Partie 4: Blockchain

### Fichiers: `block.cpp`, `block.h`, `blockchain.cpp`, `blockchain.h`, `transaction.h`, `main.cpp`

### Structure Transaction
```cpp
struct Transaction {
    std::string from;
    std::string to;
    double amount;
    long timestamp;
    
    std::string toString() const;
    std::string hash(uint32_t rule, size_t steps) const;
};
```

### Structure Block
```cpp
class Block {
    int index;
    long timestamp;
    std::vector<Transaction> transactions;
    std::string previousHash;
    std::string merkleRoot;
    int nonce;
    std::string blockHash;
    
    // Pour PoS
    std::string validator;
    double stake;
    
public:
    std::string calculateHash();
    void mineBlock(int difficulty);  // PoW (non utilisé avec AC Hash)
    bool validateBlock(const std::string& prevHash);
};
```

### Blockchain
```cpp
class Blockchain {
    std::vector<Block> chain;
    int difficulty;
    uint32_t hashRule;
    size_t hashSteps;
    
public:
    void createGenesisBlock();
    Block createBlock(const std::vector<Transaction>& txs, 
                     const std::string& validator, double stake);
    void addBlock(Block newBlock);
    bool isChainValid();
    void printChain();
};
```

### Consensus: Proof of Stake (PoS)

**Pourquoi PoS au lieu de PoW?**

L'AC Hash (surtout Règle 30) produit beaucoup de zéros en début de hash, rendant le mining PoW impraticable:
- Difficulté traditionnelle: trouver hash avec N zéros au début
- Règle 30: Presque tous les hashes commencent par des zéros
- Résultat: Blocs trouvés trop facilement → pas de sécurité

**Solution PoS:**
```cpp
Block createBlock(const std::vector<Transaction>& txs, 
                 const std::string& validator, 
                 double stake) {
    // Pas de mining
    // Validation basée sur stake du validateur
    block.validator = validator;
    block.stake = stake;
    return block;
}
```

### Création du bloc Genesis
```cpp
void Blockchain::createGenesisBlock() {
    std::vector<Transaction> genesisTx = {
        {"System", "Genesis", 0.0, time(nullptr)}
    };
    
    Block genesis(0, genesisTx, "0", "GenesisValidator", 1000.0);
    chain.push_back(genesis);
}
```

### Validation de la blockchain
```cpp
bool Blockchain::isChainValid() {
    for (size_t i = 1; i < chain.size(); i++) {
        Block& current = chain[i];
        Block& previous = chain[i-1];
        
        // Vérifier hash du bloc
        if (current.getHash() != current.calculateHash()) 
            return false;
        
        // Vérifier lien avec bloc précédent
        if (current.getPreviousHash() != previous.getHash())
            return false;
        
        // Vérifier racine de Merkle
        if (!current.validateBlock(previous.getHash()))
            return false;
    }
    return true;
}
```

### Programme principal (main.cpp)
```cpp
int main() {
    // Créer blockchain avec Règle 90 (plus rapide)
    Blockchain blockchain(0, 90, 100);
    
    // Créer bloc Genesis
    blockchain.createGenesisBlock();
    
    // Ajouter des transactions
    std::vector<Transaction> txs1 = {
        {"Alice", "Bob", 50.0, time(nullptr)},
        {"Bob", "Charlie", 25.0, time(nullptr)}
    };
    
    Block block1 = blockchain.createBlock(txs1, "Validator1", 500.0);
    blockchain.addBlock(block1);
    
    // Valider et afficher
    std::cout << "Blockchain valid: " << blockchain.isChainValid() << std::endl;
    blockchain.printChain();
    
    return 0;
}
```

---

## Tests et Comparaisons

### Suite de tests complète: `simple_comparison.cpp`

Programme de test exhaustif incluant 12 tests:

#### Tests 1-4: Comparaison de performance
- SHA-256 vs AC Hash (Règles 30, 90, 110)
- 1000 itérations pour timing précis
- Vitesse relative

#### Test 5: Effet avalanche
```cpp
void testAvalancheEffect(uint32_t rule, size_t steps);
```
- Change 1 bit en entrée → mesure changements en sortie
- Idéal: 50% des bits changent
- **Résultats**:
  - Règle 30: 19.91% ❌
  - Règle 90: 3.12% ❌
  - Règle 110: 19.69% ❌
  - **Évaluation**: PAUVRE pour toutes les règles AC

#### Test 6: Distribution des bits
```cpp
void testBitDistribution(uint32_t rule, size_t steps);
```
- Analyse 256,000+ bits
- Vérifie équilibre 0/1
- **Résultats**:
  - Règle 30: 49.34% ✅ EXCELLENT
  - Règle 90: 42.02% ❌ PAUVRE
  - Règle 110: 32.10% ❌ PAUVRE

#### Test 7: Comparaison des règles
```cpp
void compareRules();
```
- Performance + qualité combinées
- Système de scoring
- **Recommandation**: Règle 30 (meilleur équilibre)

#### Test 8: Avantages de AC Hash
1. **Simplicité éducative**: Facile à comprendre et implémenter
2. **Personnalisable**: Multiples règles, paramètres ajustables
3. **Distribution unique**: Patterns différents de SHA-256
4. **Matériel minimal**: Pas besoin d'ASICs

#### Test 9: Faiblesses de AC Hash
1. **Performance**: 33-36x plus lent que SHA-256
2. **Distribution problématique**: Règle 30 produit trop de zéros
3. **Analyse cryptographique**: Pas de preuve de sécurité formelle
4. **Prévisibilité**: Évolution déterministe
5. **Compatibilité**: Non compatible avec infrastructure existante

#### Test 10: Propositions d'amélioration
1. **Approche hybride**: `SHA256(AC_hash(input))`
2. **Sélection dynamique**: Choisir règle selon input
3. **Rayon variable**: Utiliser r=2 ou r=3
4. **Évolution parallèle**: Multiples AC combinés
5. **Nombre d'étapes adaptatif**: Ajuster selon besoin sécurité
6. **Padding amélioré**: Construction Merkle-Damgård

#### Test 11: Tableau récapitulatif complet
- Performance comparée
- Métriques de qualité
- Recommandations par cas d'usage

#### Test 12: Résumé d'exécution automatisée
- Statut de tous les tests
- Instructions d'utilisation

### Comparaison mining: `compare_hash.cpp`

Programme de comparaison détaillée du mining (plus lent, ~5-10 min):
- Teste difficulty 1-4 pour SHA-256
- Mesure temps de mining par bloc
- Compare avec AC Hash (trop rapide pour être sécurisé)

---

## Compilation et Exécution

### Prérequis
- **Compilateur**: g++ avec support C++11
- **Bibliothèques**: OpenSSL (pour SHA-256 dans comparaisons)
- **OS**: Windows avec MinGW/MSYS64 ou Linux

### Option 1: Makefile (si make disponible)
```bash
# Compiler la blockchain
make

# Exécuter la blockchain
make run

# Compiler et exécuter les tests
make test

# Nettoyer
make clean
```

### Option 2: Compilation manuelle

#### Blockchain principale
```bash
cd "c:\Users\AMGZA\OneDrive\Bureau\M2\blockchain\atelier 2"
g++ -std=c++11 -O2 automate_cellulaire.cpp hash.cpp merkle_tree.cpp block.cpp blockchain.cpp main.cpp -o blockchain_ac.exe
.\blockchain_ac.exe
```

#### Suite de tests complète
```bash
g++ -std=c++11 -O2 simple_comparison.cpp automate_cellulaire.cpp hash.cpp -o simple_comparison.exe -lssl -lcrypto
.\simple_comparison.exe
```

#### Comparaison mining (long)
```bash
g++ -std=c++11 -O2 compare_hash.cpp automate_cellulaire.cpp hash.cpp -o compare_hash.exe -lssl -lcrypto
.\compare_hash.exe
```

### Commande PowerShell tout-en-un
```powershell
# Tests rapides (~15 secondes)
cd "c:\Users\AMGZA\OneDrive\Bureau\M2\blockchain\atelier 2" ; g++ -std=c++11 -O2 simple_comparison.cpp automate_cellulaire.cpp hash.cpp -o simple_comparison.exe -lssl -lcrypto ; .\simple_comparison.exe
```

### Avertissements de compilation
```
warning: 'int SHA256_Init(SHA256_CTX*)' is deprecated
```
Ces avertissements OpenSSL 3.0 sont normaux et peuvent être ignorés.

---

## Résultats et Analyses

### Performance (1000 hashes)

| Fonction Hash | Temps Total | Par Hash | vs SHA-256 |
|---------------|-------------|----------|------------|
| **SHA-256** | 1 ms | 0.001 ms | 1.0x (base) |
| **AC Règle 30** | 34 ms | 0.034 ms | **34x plus lent** |
| **AC Règle 90** | 36 ms | 0.036 ms | **36x plus lent** |
| **AC Règle 110** | 33 ms | 0.033 ms | **33x plus lent** |

### Qualité des hashes

| Métrique | Règle 30 | Règle 90 | Règle 110 | Idéal |
|----------|----------|----------|-----------|-------|
| **Effet avalanche** | 19.91% | 3.12% | 19.69% | 50% |
| **Distribution bits** | 49.34% ✅ | 42.02% | 32.10% | 50% |
| **Résistance collision** | Inconnue | Inconnue | Inconnue | 2^128 |
| **Résistance préimage** | Inconnue | Inconnue | Inconnue | 2^256 |

### Recommandations

#### Pour production
- **Utiliser SHA-256**
- Raisons: Sécurité prouvée, performance optimale, standardisation

#### Pour éducation/recherche
- **Utiliser AC Hash Règle 30**
- Raisons: Meilleure distribution bits, visualisation intéressante

#### Pour expérimentation
- **AC Hash + PoS**
- Raisons: Évite problèmes de mining, consensus alternatif

#### Meilleure performance AC
- **Règle 110**: Légèrement plus rapide (0.033 ms)

#### Meilleure qualité AC
- **Règle 30**: Distribution excellente (49.34%)

### Points clés

✅ **Avantages AC Hash**:
- Pédagogique et simple à comprendre
- Personnalisable (multiples règles)
- Pas besoin de matériel spécialisé
- Distribution unique

❌ **Limitations AC Hash**:
- 33-36x plus lent que SHA-256
- Effet avalanche faible (3-20% au lieu de 50%)
- Pas d'analyse cryptographique formelle
- Règle 30: trop de zéros → mining PoW impossible
- Non compatible avec blockchains existantes

### Conclusion

**AC Hash est excellent pour l'apprentissage** mais ne devrait pas être utilisé en production. Les automates cellulaires démontrent comment des règles simples peuvent générer de la complexité, mais ils manquent des propriétés cryptographiques nécessaires pour une sécurité réelle.

Pour une blockchain fonctionnelle avec AC Hash, **le consensus PoS est obligatoire** pour contourner les problèmes de distribution des hashes.

---

## Structure finale du projet

```
atelier 2/
├── README.md                      # Documentation complète (ce fichier)
│
├── Automate Cellulaire (Partie 1)
│   ├── automate_cellulaire.h      # Interface AC
│   └── automate_cellulaire.cpp    # Implémentation AC (Tasks 1.1-1.3)
│
├── Fonction de Hachage (Partie 2)
│   ├── hash.h                     # Interface hash AC
│   └── hash.cpp                   # Implémentation hash (Tasks 2.1-2.4)
│
├── Arbre de Merkle (Partie 3)
│   ├── merkle_tree.h              # Interface Merkle
│   └── merkle_tree.cpp            # Implémentation Merkle
│
├── Blockchain (Partie 4)
│   ├── transaction.h              # Structure Transaction
│   ├── block.h                    # Interface Block
│   ├── block.cpp                  # Implémentation Block
│   ├── blockchain.h               # Interface Blockchain
│   ├── blockchain.cpp             # Implémentation Blockchain (PoS)
│   └── main.cpp                   # Programme principal
│
├── Tests et Comparaisons
│   ├── simple_comparison.cpp      # Tests 1-12 complets
│   └── compare_hash.cpp           # Comparaison mining détaillée
│
├── Exécutables
│   ├── blockchain_ac.exe          # Blockchain fonctionnelle
│   └── simple_comparison.exe      # Suite de tests
│
└── Build
    └── Makefile                   # Automatisation compilation
```

---

## Auteur et Contexte

**Projet**: Atelier 2 - Blockchain avec Automate Cellulaire  
**Cours**: M2 Blockchain  
**Date**: Octobre 2025  
**Objectif**: Comprendre les fondements des blockchains en implémentant un système complet avec fonction de hachage personnalisée basée sur les automates cellulaires

**Apprentissages clés**:
1. Les automates cellulaires peuvent générer du chaos à partir de règles simples
2. Une fonction de hachage nécessite des propriétés cryptographiques spécifiques
3. L'arbre de Merkle permet une vérification efficace des transactions
4. Le consensus (PoW/PoS) est crucial pour la sécurité de la blockchain
5. Les compromis performance/sécurité sont essentiels en cryptographie

---

## Références

### Automates Cellulaires
- **Stephen Wolfram**: "A New Kind of Science" (2002)
- **Règle 30**: Utilisée pour générateur de nombres aléatoires
- **Règle 110**: Prouvée Turing-complète

### Blockchain
- **Bitcoin**: Premier blockchain avec PoW et SHA-256
- **Ethereum**: Transition PoW → PoS
- **Merkle Tree**: Utilisé dans Bitcoin pour SPV (Simple Payment Verification)

### Hachage Cryptographique
- **SHA-256**: Standard NIST FIPS 180-4
- **Propriétés requises**: Déterminisme, rapidité, effet avalanche, résistance aux collisions
- **Applications**: Blockchain, signatures numériques, HMAC

---

## Support et Questions

Pour toute question sur ce projet:
1. Consulter ce README en entier
2. Examiner les commentaires dans le code source
3. Exécuter `simple_comparison.exe` pour voir tous les tests
4. Référer aux résultats d'analyse inclus

**Note importante**: Ce projet est à visée pédagogique. Ne pas utiliser AC Hash en production sans analyse cryptographique approfondie.
