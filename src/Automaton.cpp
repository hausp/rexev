/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Automaton.hpp"
#include <iostream>
#include <algorithm>

Automaton::Automaton() { }

Automaton::Automaton(const std::set<char>& alphabet) : alphabet(alphabet) {

}

void Automaton::insert(const std::string& entry, bool initial, bool final) {
    states[entry] = State(initial, final);
    if (initial) initial_state = entry;
    if (final) final_states.insert(entry);
}

void Automaton::make_transition(const std::string& from, char label,
                                const std::string& to) {
    if (!states.count(to)) states[to];
    states[from].append_transition(label, to);
}

std::vector<std::string>& Automaton::operator()(const std::string& state,
                                                const char entry) {
    return states[state][entry];

}

const std::vector<std::string>& Automaton::operator()(const std::string& state,
                                                      const char entry) const {
    return states.at(state)[entry];
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
    std::map<std::string, State> reachable_states;
    reachable_states[initial_state] = states[initial_state];
    for (auto pair : states) {
        if (!reachable_states.count(pair.first)) {
            bool reachable = false;
            for (auto rpair : reachable_states) {
                for (auto transition : rpair.second) {
                    for (auto t : transition.second) {
                        if (t == pair.first) {
                            reachable = true;
                            break;
                        }
                    }
                    if (reachable) break;
                }
                if (reachable) break;
            }
            if (reachable) {
                reachable_states.insert(pair);
            }
        }
    }
    // for (auto pair : reachable_states) {
    //     for (auto t : alphabet) {
    //         for (auto s : pair.second) {
    //             reachable_states[s] = states[s];
    //         }
    //     }
    // }
    states = reachable_states;
}

Automaton Automaton::complement() {
    std::set<std::string> non_final_states;
    for (auto pair : states) {
        if (!pair.second.is_final()) {
            non_final_states.insert(pair.first);
        }
    }

    Automaton complemented = *this;
    complemented.final_states = non_final_states;
    return complemented;
}

Automaton Automaton::automaton_intersection(const Automaton& fsm) {
    Automaton intersec;    
    
    // Une os alfabetos
    std::set_union(alphabet.begin(), alphabet.end(),
                    fsm.alphabet.begin(), fsm.alphabet.end(),
                    std::back_inserter(intersec.alphabet));

    int i = labels.size();
    Automaton temp = fsm;
    for (auto state : temp.labels) {
        state.at(0) += i;
    }

    // Produto cartesiano dos labels
    std::set<std::string> final_labels;
    for (auto l : labels) {
        for (auto n : temp.labels) {
            final_labels.insert(l+n);
        }
    }

    // Produto cartesiano dos aceitadores
    std::set<std::string> acc_pairs;
    for (auto l : acceptors) {
        for (auto n : temp.acceptors) {
            acc_pairs.insert(l+n);
        }
    }

    // Adiciona os labels ao novo autômato  ??? Depende da implementação do State
    intersec.labels = final_labels;
    intersec.acceptors = acc_pairs;

    // Cria os estados em questão
    for (auto l : final_labels) {
        if (acc_pairs.count(l)) {
            intersec.insert(l, false, true);
        } else {
            intersec.insert(l);
        }
    }

    // Define as transições
    for (auto pair : final_labels) {
        auto st0 = pair[0];
        auto st1 = pair[1];
        for (auto entry : intersect.alphabet) {
           if (states[st0].accepts(entry) && states[st1].accepts(entry)) {
                std::string dest0 = states[st0][entry];
                std::string dest1 = states[st1][entry];
                intersect.make_transition(pair, entry, dest0+dest1); 
            }
        }
    }


    // Cria o estado inicial
    bool initial_is_final = false;
    if (states[initial].is_final() && temp.states.at(temp.initial).is_final()) {
        initial_is_final = true;
    }
    intersec.initial = "A";
    intersec.insert("A", true, initial_is_final);

    // Cria as transições do estado inicial = transições dos iniciais anteriores
    for (auto entry : intersect.alphabet) {
        if (fsm.states.at("A").accepts(entry) && states.at("A").accepts(entry)) {
            intersect.make_transition(intersect.initial, entry, "A"+('A'+i));
        }
    }

    return intersect;
}

Automaton Automaton::union_operation(const Automaton& fsm) {
    // std::set<char> united_alphabet;
    // for (auto c : alphabet) {
    //     united_alphabet.insert(c);
    // }
    // for (auto c : fsm.alphabet) {
    //     united_alphabet.insert(c);
    // }
    // Automaton united_machine (united_machine);
    
    // bool initial_is_final = false;
    // if (final_states.count(initial_state) && fsm.final_states.count(fsm.initial_state)) {
    //     initial_is_final = true;
    // }
    
    // std::string initial_label = initial_state+"\'"+"\'";
    // State initial (initial_label, nullptr, true, initial_is_final);
    // for (auto st : states) {
    //     united_machine[st.first] = st.second;
    // }
    // for (auto st : fsm.states) {
    //     st.second.set_label(st.first+"\'");
    //     united_machine[st.first+"\'"] = st.second;
    // }
    // united_machine[initial_label] = initial;
    // united_machine.initial_state = initial_label;

    // for (auto c : united_machine.alphabet) {
    //     if (!united_machine[initial_state][c].empty()) {
    //         for (auto t : united_machine[initial_state][c]) {
    //             united_machine.make_transition(initial_label, c, t->get_label());
    //         }
    //     }
    //     if (!united_machine[initial_state+"\'"][c].empty()) {
    //         for (auto t : united_machine[initial_state+"\'"][c]) {
    //             united_machine.make_transition(initial_label, c, t->get_label());
    //         }
    //     }
    // }

    // return united_machine;
}

Automaton Automaton::minimize() {
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
    // for (auto st : final_states) {
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
}

Automaton::operator std::string() const {
    // std::string out = "      ";
    // for (auto entry : alphabet) {
    //     out += "| ";
    //     out += entry;
    //     out += " ";
    // }
    // out += "\n";
    // for (auto s : states) {
    //     out += " ";
    //     if (s.second.is_final()) out += "*";
    //     else out += " ";
    //     if (s.second.is_initial()) out += "->";
    //     else out += "  ";
    //     out += s.second.get_label();
    //     out += " ";
    //     for (auto entry : alphabet) {
    //         bool test = true;
    //         out += "| ";
    //         for (auto t : s.second[entry]) {
    //             test = false;
    //             out += t->get_label();
    //         }
    //         if (test) out += " ";
    //         out += " ";
    //     }
    //     out += "\n";
    // }
    // return out;
}

std::vector<std::vector<std::string>> Automaton::to_table() {
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