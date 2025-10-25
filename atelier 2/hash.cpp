#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "automate_cellulaire.h"
#include "hash.h"

using namespace std;

/* 2.2. CONVERSION DU TEXTE EN BITS 
 * Le texte d'entrée est converti en une séquence de bits de la manière suivante :
 * - Chaque caractère du string est converti en sa valeur ASCII (8 bits)
 * - Ces bits sont concaténés pour former une longue séquence binaire
 * - Si la séquence est plus courte que 256 bits, on ajoute un padding :
 *   * On ajoute un '1' suivi de '0' jusqu'à atteindre 256 bits
 * - Si la séquence est plus longue que 256 bits, on la divise en blocs de 256 bits
 *   et on les combine par XOR pour obtenir exactement 256 bits
 */
vector<int> string_to_bits(const string& input) {
    vector<int> bits;
    
    // Conversion caractère par caractère en bits
    for (char c : input) {
        for (int i = 7; i >= 0; i--) {
            bits.push_back((c >> i) & 1);
        }
    }
    
    // Si moins de 256 bits, padding
    if (bits.size() < 256) {
        bits.push_back(1); // Ajouter un '1'
        while (bits.size() < 256) {
            bits.push_back(0); // Remplir de '0'
        }
    }
    // Si plus de 256 bits, compression par XOR
    else if (bits.size() > 256) {
        vector<int> compressed(256, 0);
        for (size_t i = 0; i < bits.size(); i++) {
            compressed[i % 256] ^= bits[i];
        }
        bits = compressed;
    }
    
    return bits;
}

/**
 * 2.3. PROCESSUS DE PRODUCTION DU HASH FINAL
 * 
 * Le hash est produit en plusieurs étapes :
 * 1. Conversion du texte en 256 bits (état initial)
 * 2. Application de l'automate cellulaire pendant 'steps' générations
 * 3. À chaque génération, l'état évolue selon la règle spécifiée
 * 4. L'état final de 256 bits est converti en une chaîne hexadécimale
 * 5. Chaque groupe de 4 bits devient un chiffre hexadécimal (0-F)
 * 6. Le résultat final est une chaîne de 64 caractères hexadécimaux (256 bits / 4)
 */
string bits_to_hex(const vector<int>& bits) {
    stringstream ss;
    
    // Conversion par groupes de 4 bits en hexadécimal
    for (size_t i = 0; i < bits.size(); i += 4) {
        int nibble = 0;
        for (int j = 0; j < 4 && (i + j) < bits.size(); j++) {
            nibble = (nibble << 1) | bits[i + j];
        }
        ss << hex << nibble;
    }
    
    return ss.str();
}

/**
 * 2.1. FONCTION DE HACHAGE PRINCIPALE
 * 
 * @param input : Le texte à hacher
 * @param rule : Le numéro de la règle d'automate cellulaire (0-255)
 * @param steps : Le nombre de générations à calculer
 * @return : Une chaîne hexadécimale de 64 caractères représentant 256 bits
 */
string ac_hash(const string& input, uint32_t rule, size_t steps) {
    // Conversion du texte en bits (256 bits)
    vector<int> initial_state = string_to_bits(input);
    
    // Initialisation de l'automate cellulaire
    CellularAutomaton ca(rule);
    ca.init_state(initial_state);
    
    // Évolution de l'automate pendant 'steps' générations
    for (size_t i = 0; i < steps; i++) {
        ca.evolve();
    }
    
    // Récupération de l'état final et conversion en hexadécimal
    vector<int> final_state = ca.get_state();
    return bits_to_hex(final_state);
}