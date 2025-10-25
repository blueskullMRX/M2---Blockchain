#ifndef CELLULAR_AUTOMATON_H
#define CELLULAR_AUTOMATON_H

#include <iostream>
#include <vector>
#include <bitset>

class CellularAutomaton {
private:
    std::vector<int> state;
    int rule_number;
    int rule[8]; // Tableau de règles pour les 8 configurations possibles
    
    void init_rule(int rule_num);
    int apply_rule(int left, int center, int right);
    
public:
    explicit CellularAutomaton(int rule_num);
    
    void init_state(const std::vector<int>& initial_state);
    void evolve();
    void print_state() const;
    void print_state_binary() const;
    void print_rule() const;
    std::vector<int> get_state() const;
};

#endif // CELLULAR_AUTOMATON_H