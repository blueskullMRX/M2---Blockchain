#include "automate_cellulaire.h"
#include <iostream>
#include <vector>

using namespace std;

void CellularAutomaton::init_rule(int rule_num) {
    rule_number = rule_num;
    for (int i = 0; i < 8; i++) {
        rule[i] = (rule_num >> i) & 1;
    }
}

int CellularAutomaton::apply_rule(int left, int center, int right) {
    int index = (left << 2) | (center << 1) | right;
    return rule[index];
}

CellularAutomaton::CellularAutomaton(int rule_num) {
    init_rule(rule_num);
}

void CellularAutomaton::init_state(const vector<int>& initial_state) {
    state = initial_state;
}

void CellularAutomaton::evolve() {
    vector<int> new_state(state.size());

    for (size_t i = 0; i < state.size(); i++) {
        int left = (i > 0) ? state[i-1] : 0;
        int center = state[i];
        int right = (i < state.size()-1) ? state[i+1] : 0;

        new_state[i] = apply_rule(left, center, right);
    }

    state = new_state;
}

void CellularAutomaton::print_state() const {
    for (int cell : state) {
        cout << (cell ? "#" : " ");
    }
    cout << endl;
}

void CellularAutomaton::print_state_binary() const {
    for (int cell : state) {
        cout << cell;
    }
    cout << endl;
}

void CellularAutomaton::print_rule() const {
    cout << "Règle " << rule_number << " (binaire: ";
    for (int i = 7; i >= 0; i--) {
        cout << rule[i];
    }
    cout << ")" << endl;
    cout << "Configuration | Résultat" << endl;
    cout << "--------------|----------" << endl;
    for (int i = 7; i >= 0; i--) {
        cout << "     " << ((i >> 2) & 1) << ((i >> 1) & 1) << (i & 1);
        cout << "       |    " << rule[i] << endl;
    }
}

vector<int> CellularAutomaton::get_state() const {
    return state;
}


