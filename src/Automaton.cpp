/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Automaton.hpp"
#include <iostream>
#include <algorithm>
#include <list>


Automaton::Automaton()
: k_error("\u03C6") { }

Automaton::Automaton(const Alphabet& alphabet)
 : alphabet(alphabet), k_error("\u03C6") {

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
    // Estados vivos
    std::map<Key, State> living_states;
    // Novos estados vivos encontrados, inicializado com os estados aceitadores
    std::list<Key> new_living_states = {k_acceptors.begin(),k_acceptors.end()};
    // Limpa conjunto de keys e adiciona as keys dos estados aceitadores
    keys = k_acceptors;
    // Enquanto houver novos estados vivos
    while (!new_living_states.empty()) {
        // Obtém a chave de um novo estado vivo
        auto key = new_living_states.front();
        // Obtém o estado equivalente à chave
        auto alive = states[key];
        // Adiciona o estado obtido ao conjunto de estados vivos
        living_states[key] = alive;
        // Remove a chave da lista de novos estados vivos
        new_living_states.pop_front();
        // Para cada entrada do alfabeto
        for (auto entry : alphabet) {
            // Obtém o conjunto de estados predecessores do estado vivo
            auto predecessors = predecessors_of(key, entry);
            // Para cada predecessor
            for (auto p : predecessors) {
                // Se não se encontra nos estados vivos
                if (!living_states.count(p)) {
                    // Adiciona à lista de novos estados vivos
                    new_living_states.push_back(p);
                    // Adiciona a key ao conjunto de keys
                    keys.insert(p);
                }
            }
        }
    }
    // Mapa de estados recebe mapa de estados vivos
    states = living_states;
    // Verifica se estado inicial ainda existe
    if (!states.count(k_initial)) {
        // Estado inicial não existe mais, deve ser invalidado
        k_initial = "";
    }
}

void Automaton::remove_unreachable_states() {
    // Estados alcançáveis
    std::map<Key, State> reachable_states;
    // Novos estados alcançáveis encontrados
    std::list<Key> new_reachables = {k_initial};
    // Limpa o conjunto de keys e adiciona a key do estado inicial
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
    k_acceptors = intersection(keys, k_acceptors);
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

Automaton Automaton::automaton_intersection(const Automaton& fsm) const {
    Automaton intersec;    
    
    // Une os alfabetos
    std::set_union(alphabet.begin(), alphabet.end(),
                    fsm.alphabet.begin(), fsm.alphabet.end(),
                    std::inserter(intersec.alphabet, intersec.alphabet.end()));

    int i = keys.size();
    Automaton temp = fsm;
    for (auto state : temp.keys) {
        state.at(0) += i;
    }

    // Produto cartesiano dos keys
    Key acc_key;
    KeySet final_keys;
    for (auto l : keys) {
        for (auto n : temp.keys) {
            final_keys.insert(l+n);
        }
    }

    // Chave inicial
    acc_key = *(final_keys.begin());

    // Produto cartesiano dos aceitadores
    KeySet acc_pairs;
    for (auto l : k_acceptors) {
        for (auto n : temp.k_acceptors) {
            acc_pairs.insert(l+n);
        }
    }

    // Adiciona os keys ao novo autômato  ??? Depende da implementação do State
    intersec.keys = final_keys;
    intersec.k_acceptors = acc_pairs;

    // Retira acc_key de final_keys para inserí-la como chave inicial
    final_keys.erase(acc_key);

    // Insere acc_key
    if (acc_pairs.count(acc_key)) {
        intersec.insert(acc_key, true, true); 
    } else {
        intersec.insert(acc_key, true, false);
    }

    // Cria os estados em questão
    for (auto l : final_keys) {
        if (acc_pairs.count(l)) {
            intersec.insert(l, false, true);
        } else {
            intersec.insert(l);
        }
    }

    // Define as transições
    for (auto pair : intersec.keys) {
        auto st0 = pair[0]+"";
        auto st1 = pair[1]+"";
        for (auto entry : intersec.alphabet) {
           if (states.at(st0).accepts(entry) && states.at(st1).accepts(entry)) {
                std::vector<Key> dest0 = states.at(st0)[entry];
                std::vector<Key> dest1 = states.at(st1)[entry];
                for (auto k0 : dest0) {
                    for (auto k1 : dest1) {
                        intersec.make_transition(pair, entry, k0+k1); 
                    }
                }
            }
        }
    }

    // Cria o estado inicial
    /*bool initial_is_final = false;
    if (states[initial].is_final() && temp.states.at(temp.initial).is_final()) {
        initial_is_final = true;
    }
    intersec.k_initial = "A";
    intersec.insert("A", true, initial_is_final);

    // Cria as transições do estado inicial = transições dos iniciais anteriores
    for (auto entry : intersect.alphabet) {
        if (fsm.states.at("A").accepts(entry) && states.at("A").accepts(entry)) {
            intersec.make_transition(intersec.k_initial, entry, "A"+('A'+i));
        }
    }*/

    return intersec;
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
    // Cria cópia do autômato
    Automaton minimum = *this;
    // Remove os estados mortos da cópia
    minimum.remove_dead_states();
    // Remove os estados inalcançáveis da cópia
    minimum.remove_unreachable_states();
    // Remove os estados equivalentes da cópia
    minimum.remove_equivalent_states();
    // Retorna a cópia
    return minimum;
}

void Automaton::remove_equivalent_states() {
    // Adiciona as transições de erro
    set_error_transitions();
    // Classes de equivalência
    PartitionSet partitions = {k_acceptors, difference(keys, k_acceptors)};
    // Novas classes de equivalência encontradas
    // Sempre é adicionada a menor classe dentre as duas novas
    PartitionSet new_partitions = {k_acceptors};

    // Enquanto houver novas classes de equivalência
    while(!new_partitions.empty()) {
        // Pega a primeira classe de equivalência
        auto partition = *new_partitions.begin();
        // Remove-a da lista
        new_partitions.erase(partition);

        // Para cada entrada do alfabeto
        for (auto entry : alphabet) {
            // Calcula os predecessores da classe
            ECHO(entry);
            TRACE_IT(partition);
            auto predecessors = predecessors_of(partition, entry);
            TRACE_IT(predecessors);
            // Para cada classe no conjunto de classes
            for (auto it = partitions.begin(); it != partitions.end();) {
                // Guarda a classe em value
                auto value = *it;
                // Calcula a intersecção da classe com os predecessores
                auto intersec = intersection(predecessors, value);
                TRACE_IT(intersec);
                // Calcula a diferença da classe com os predecessores
                auto diff = difference(value, predecessors);
                TRACE_IT(diff);
                
                // Se ambas, intersecção e diferença, não forem vazias
                if (!intersec.empty() && !diff.empty()) {
                    // Remove a classe selecionada
                    it = partitions.erase(it);
                    // Adiciona a intersecção e a diferença como classes
                    partitions.insert(intersec);
                    partitions.insert(diff);
                    // Se a classe removida está na lista de novas classes
                    if (new_partitions.count(value)) {
                        // Remove-a da lista
                        new_partitions.erase(value);
                        // Adiciona a interseção e a diferença como novas classes
                        new_partitions.insert(intersec);
                        new_partitions.insert(diff);
                    } else {
                        // A classe removida não está na lista de novas classes
                        // Então verifica-se qual a menor classe, a da
                        // Intersecção ou a da diferença
                        if (intersec.size() <= diff.size()) {
                            // A interseção é a menor (ou igual), portanto
                            // é adicionada à lista de novas classes
                            new_partitions.insert(intersec);
                        } else {
                            // A diferença é a menor, portanto é adicionada
                            // à lista de novas classes
                            new_partitions.insert(diff);
                        }
                    }
                } else {
                    // Como nenhuma partição foi removida, incrementa o iterador
                    it++;
                }
            }
        }
    }

    for (auto p : partitions) {
        TRACE_IT(p);
        Key state = *p.begin();
        p.erase(state);
        while (!p.empty()) {
            Key equivalent = *p.begin();
            p.erase(equivalent);
            for (auto entry : alphabet) {
                auto predecessors = predecessors_of(equivalent, entry);
                for (auto s : predecessors) {
                    states[s][entry] = {state};
                }
            }
            states.erase(equivalent);
            keys.erase(equivalent);
            if (k_acceptors.count(equivalent)){
                k_acceptors.erase(equivalent);
            }
            if (equivalent == k_initial) {
                k_initial = state;
                states[state].set_initial(true);
            }
        }
    }
}

void Automaton::set_error_transitions() {
    insert(k_error);
    for (auto entry : alphabet) {
        for (auto& pair : states) {
            if (!pair.second.accepts(entry)) {
                pair.second.append_transition(entry, k_error);
            }
        }
    }
}

KeySet Automaton::difference(const KeySet& s1, const KeySet& s2) const {
    KeySet difference;
    std::set_difference(s1.begin(), s1.end(),
                        s2.begin(), s2.end(),
                        inserter(difference, difference.end()));
    return difference;
}

KeySet Automaton::intersection(const KeySet& s1, const KeySet& s2) const {
    KeySet intersection;
    std::set_intersection(s1.begin(), s1.end(),
                          s2.begin(), s2.end(),
                          inserter(intersection, intersection.end()));
    return intersection;
}

KeySet Automaton::predecessors_of(const KeySet& set, const Entry e) const {
    KeySet predecessors;
    for (auto pair : states) {
        for (auto target : set) {
            if (pair.second.accepts_to(e, target)) {
                predecessors.insert(pair.first);
            }
        }
    }
    return predecessors;
}

KeySet Automaton::predecessors_of(const Key& target, const Entry e) const {
    KeySet predecessors;
    for (auto pair : states) {
        if (pair.second.accepts_to(e, target)) {
            predecessors.insert(pair.first);
        }
    }
    return predecessors;
}

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