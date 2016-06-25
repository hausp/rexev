/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Automaton.hpp"
#include <iostream>
#include <algorithm>
#include <list>


Automaton::Automaton() { }

Automaton::Automaton(const Alphabet& alphabet) : alphabet(alphabet) {

}

void Automaton::insert(const Key& k, bool initial, bool final) {
    states[k] = State(initial, final);
    keys.insert(k);
    if (initial) k_initial = k;
    if (final) k_acceptors.insert(k);
}

void Automaton::make_transition(const Key& from, const Entry e, const Key& to) {
    if (!states.count(to)) states[to];
    states[from].append_transition(e, to);
}

TransitionVector& Automaton::operator()(const Key& k, const Entry e) {
    return states[k][e];

}

const TransitionVector& Automaton::operator()(const Key& k, const Entry e) const {
    return states.at(k)[e];
}


void Automaton::remove_dead_states() {
    unsigned i = 0;
    auto pair = states.begin();
    while (i < states.size()) {
        if (is_dead(pair->second)) {
            states.erase(pair);
            pair = states.begin();
        } else {
            i++;
            pair++;
        }
    }
    // states.erase(std::remove_if(states.begin(), states.end(),
    //             [this](const std::pair<std::string,State>& pair)->bool{
    //                 return this->is_dead(pair.second);
    //             }), states.end());
}

bool Automaton::is_dead(const State& state) const {
    if (state.is_final()) {
        return false;
    }
    for (auto pair : state) {
        for (auto target : pair.second) {
            if (!is_dead(states.at(target))) {
                return false;
            }
        }
    }
    return true;
}

void Automaton::remove_unreachable_states() {
    // Estados alcançáveis
    std::map<Key, State> reachable_states;
    // Novos estados alcançáveis encontrados
    std::list<Key> new_reachables = {k_initial};
    // Limpa conjunto de chaves de estados,
    // deixando apenas a chave do estado inicial
    keys = {k_initial};
    // Enquanto houver novos estados alcançáveis
    while (!new_reachables.empty()) {
        // Obtém a chave de um novo estado alcançável
        auto key = new_reachables.front();
        // Obtém o estado equivalente à chave
        auto reachable = states[key];
        // Adiciona o estado obtido ao conjunto de estados alcançáveis
        reachable_states[key] = reachable;
        // Remove a chave da lista de novos estados alcançáveis
        new_reachables.pop_front();
        // Para cada conjunto de transições do estado alcançável
        for (auto trs : reachable) {
            // Para cada estado do conjunto de transições
            for (auto t : trs.second) {
                // Se o estado t não se encontra no conjunto
                // de estados alcançáveis
                if (!reachable_states.count(t)) {
                    // Adiciona o estado t ao conjunto
                    new_reachables.push_back(t);
                    // Adiciona a key ao conjunto de keys
                    keys.insert(t);
                }
            }
        }
    }
    // Mapa de estados recebe mapa de estados alcançáveis
    states = reachable_states;
    // Atualiza conjunto de chaves de estados aceitadores
    k_acceptors = keys_intersect(k_acceptors);
}

Automaton Automaton::complement() const {
    KeySet non_acceptors;
    for (auto pair : states) {
        if (!pair.second.is_final()) {
            non_acceptors.insert(pair.first);
        }
    }

    Automaton complemented = *this;
    complemented.k_acceptors = non_acceptors;
    return complemented;
}

Automaton Automaton::union_operation(const Automaton& m) const {
    // Cria um novo autômato inicialmente igual ao autômato m
    Automaton union_atm = m;
    // Faz a união dos dois alfabetos
    std::set_union(union_atm.alphabet.begin(), union_atm.alphabet.end(),
                   alphabet.begin(), alphabet.end(),
                   inserter(union_atm.alphabet, union_atm.alphabet.begin()));
    
    // Verifica se um dos estados iniciais é também final
    bool final = k_acceptors.count(k_initial) ||
                 m.k_acceptors.count(m.k_initial);
    
    // Insere um novo estado inicial
    union_atm.insert(k_initial + "''", true, final);

    // Para cada estado em m
    for (auto s : m.states) {
        // Cria-se um novo estado equivalente em union_atm
        union_atm.insert(s.first + "'", false, s.second.is_final());
        // Para cada conjunto de transições para uma entrada no estado s
        for (auto trs : s.second) {
            // Para cada estado do conjunto de transições
            for (auto t : trs.second) {
                // Cri-se uma transição equivalente em union_atm
                union_atm.make_transition(s.first + "'", trs.first, t + "'");
            }
        }
    }
    // Retorna a união
    return union_atm;
}

Automaton Automaton::minimize() const {
   
}

void Automaton::remove_equivalent_states() {
    PartitionSet partitions = {k_acceptors, keys_except(k_acceptors)};
    PartitionSet new_partitions = {k_acceptors};

    while(!new_partitions.empty()) {
        auto partition = *new_partitions.begin();
        new_partitions.erase(partition);

        for (auto entry : alphabet) {
            auto predecessors = predecessors_of(partition, entry);
            for (auto p : partitions) {
            }
        }
    }
}

KeySet Automaton::keys_except(const KeySet& expt) const {
    KeySet keys_except;
    std::set_difference(keys.begin(), keys.end(),
                        expt.begin(), expt.end(),
                        inserter(keys_except, keys_except.end()));
    return keys_except;
}

KeySet Automaton::keys_intersect(const KeySet& set) const {
    KeySet keys_intersect;
    std::set_intersection(keys.begin(), keys.end(),
                          set.begin(), set.end(),
                          inserter(keys_intersect, keys_intersect.end()));
    return keys_intersect;
}

KeySet Automaton::predecessors_of(const KeySet& set, const Entry e) const {
    KeySet predecessors;
    for (auto key : keys) {
        for (auto target : set) {
            if (states.at(key).accepts_to(e, target)) {
                predecessors.insert(key);
                break;
            }
        }
    }
    return predecessors;
}

//std::set<

    // Automaton minimezed_automata = *this;
    // minimezed_automata.remove_unreachable_states();
    // minimezed_automata.remove_dead_states();
    // for (auto t : minimezed_automata.alphabet) {
    //     for (auto st : minimezed_automata.states) {
    //         if (!st.second.accepts(t)) st.second[t].push_back(&minimezed_automata.rejection_state);
    //     }
    // }
    // std::map<std::string, std::vector<State>> state_set;
    // state_set["\u03D5"].push_back(minimezed_automata.rejection_state);
    // std::string state_count = "A";
    // for (auto st : acceptors) {
    //     state_set[state_count].push_back(minimezed_automata[st]);
    // }
    // state_count.at(0)++;
    /*while (true) {
        for (auto st : state_set) {
            if (st.second.size() > 1) {
                for (unsigned i = 1; i < st.second.size()-1; i++) {
                    for (auto a : minimezed_automata.alphabet) {
                        std::string dest, cest;
                        // This shit is confusing
                        dest = ((*st.second.begin())[a].at(0).get_label());
                        cest = ((*(st.second.begin()+i))[a].at(0).get_label());
                        for (auto ts : state_set) {
                        	for (auto k : ts.second) {
                        		if (k.get_transition(a).get_label() == dest) dest = "\'"+ts.first;
                        		if (k.get_transition(a).get_label() == cest) cest = "\'"+ts.first;
                        	}
                        }
                        if (dest != cest) {
                        	State diff_state = *st.second.begin();
                        	st.second.erase(st.second.begin()+i);
                        	state_set[state_count].push_back(diff_state);
                        }
                    }
                }   
            }
        }
        state_count.at(0)++;
    }*/

    //return minimezed_automata;
//}

std::vector<std::vector<std::string>> Automaton::to_table() const {
    std::vector<std::vector<std::string>> result;
    
    result.push_back({"\u03B4"});
    
    for (char entry : alphabet) {
        result[0].push_back(std::string(1, entry));
    }
    
    unsigned i = 1;
    for (auto pair : states) {
        std::string state_str = "";
        
        if (pair.second.is_final()) {
            state_str += "*";
        }
        if (pair.second.is_initial()) {
            state_str += "->";
        }
        
        state_str += pair.first;
        
        result.push_back({state_str});
        
        for (auto entry : alphabet) {
            std::string transition_str = "";
        
            for (auto s : pair.second[entry]) {
                transition_str += s;
            }
        
            if (transition_str.size() == 0) {
                transition_str += "\u2014";
            }
        
            result[i].push_back(transition_str);
        }
        i++;
    }
    return result;
}