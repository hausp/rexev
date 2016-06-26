/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Automaton.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <list>


Automaton::Automaton()
: k_error("\u03C6") { }

Automaton::Automaton(const Alphabet& alphabet)
 : alphabet(alphabet), k_error("\u03C6") {

}

void Automaton::set_name(const std::string& n) {
    name = n;
}

std::string Automaton::get_name() const {
    return name;
}

bool Automaton::is_minimum() const {
    return minimum;
}

bool Automaton::is_empty() const {
    return k_acceptors.empty();
}

bool Automaton::is_initial(const Key& k) const {
    return k_initial == k;
}

bool Automaton::is_final(const Key& k) const {
    return k_acceptors.count(k);
}

void Automaton::insert(const Key& k, bool initial, bool final) {
    states[k] = State();
    keys.insert(k);
    if (initial) k_initial = k;
    if (final) k_acceptors.insert(k);
    minimum = false;
}

void Automaton::make_transition(const Key& from, const Entry e, const Key& to) {
    if (!states.count(to)) states[to];
    states[from].make_transition(e, to);
    minimum = false;
}

Key& Automaton::operator()(const Key& k, const Entry e) {
    minimum = false;
    return states[k][e];

}

const Key& Automaton::operator()(const Key& k, const Entry e) const {
    return states.at(k)[e];
}

Automaton Automaton::complement() const {
    Automaton complemented = *this;
    complemented.k_acceptors = difference(keys, k_acceptors);
    return complemented;
}

Automaton Automaton::automaton_intersection(const Automaton& m) const {
    // Novo autômato para representar a intersecção
    Automaton intersect;
    // Contador para criação dos labels dos estados da intersecção
    unsigned label_count = 0;
    // Registra se foi criado algum par de estados final para a intersecção
    bool has_final_state = false;
    // Pares de estados st1 e st2 tal que st1 pertence ao autômato 'this'
    // e st2 pertence ao autômato 'm', mapeando para o label equivalente
    std::map<std::pair<Key,Key>,Key> state_pairs;
    // Novos pares de estados alcançados, inicializado com o par dos estados iniciais
    // de ambos os autômatos
    std::list<std::pair<Key,Key>> new_states = {std::make_pair(k_initial, m.k_initial)};
    // O alfbeto do autômato da intersecção recebe a intersecção dos alfabetos
    std::set_intersection(alphabet.begin(), alphabet.end(),
                          m.alphabet.begin(), m.alphabet.end(),
                          inserter(intersect.alphabet, intersect.alphabet.end()));
    // Se um dos autômatos é vazio
    if (m.is_empty() || is_empty()) {
        // A intersecção é vazia
        return intersect;
    }
    // Enquanto houver novos pares encontrados
    while (!new_states.empty()) {
        // Adquire as keys dos estados do par
        auto keys = new_states.front();
        // Recupera os estados equivalentes às keys
        auto st1 = states.at(keys.first);
        auto st2 = m.states.at(keys.second);
        // Remove o par da lista de pares novos
        new_states.pop_front();
        // Adiciona o par num map de pares para labels
        // Os labels serão usados para definir os novos estados da intersecção
        state_pairs[keys] = new_label(label_count++);
        // Para cada entrada do alfabeto da intersecção
        for (auto entry : intersect.alphabet) {
            // Verifica se ambos os estados aceitam essa entrada
            if (st1.accepts(entry) && st2.accepts(entry)) {
                // Cria um par com os estados-destino
                auto pair = std::make_pair(st1[entry], st2[entry]);
                // Se não foi adicionado previamente ao map de pares
                if (!state_pairs.count(pair))
                // Adiciona o par dos estados-destino de ambos os estados
                new_states.push_back(pair);
            }
            // Atualiza a existência de estado final
            has_final_state = has_final_state
                            || (is_final(keys.first) && m.is_final(keys.second));
        }
    }
    // Se existe estado final, então o autômato não é vazio
    if (has_final_state) {
        // Para cada par de keys definido
        for (auto pair : state_pairs) {
            // Recupera os estados equivalentes
            auto st1 = states.at(pair.first.first);
            auto st2 = m.states.at(pair.first.second);
            // Verifica se ambos são iniciais
            bool initial = is_initial(pair.first.first)
                        && m.is_initial(pair.first.second);
            // Verifica se ambos são finais
            bool final = is_final(pair.first.first)
                        && m.is_final(pair.first.second);
            // Utiliza o label definido no map para criar um novo estado na
            // intersecção, passando também a informação de ser final ou inicial
            intersect.insert(pair.second, initial, final);
            // Para cada entrada do alfabeto da intersecção
            for (auto entry : intersect.alphabet) {
                // Se ambos os estados do par aceitam essa entrada
                if (st1.accepts(entry) && st2.accepts(entry)) {
                    // Cria um novo par com as keys dos estados-destino
                    auto tpair = std::make_pair(st1[entry], st2[entry]);
                    // Recupera o label guardado sob este par
                    auto target = state_pairs.at(tpair);
                    // Cria a transição correspondente na intersecção
                    intersect.make_transition(pair.second, entry, target);
                }
            }
        }
    }
    // Retorna a intersecção
    return intersect;
}

Automaton Automaton::minimize() const {
    // Cria cópia do autômato
    Automaton min = *this;
    // Remove os estados mortos da cópia
    min.remove_dead_states();
    // Remove os estados inalcançáveis da cópia
    min.remove_unreachable_states();
    // Apenas faz a remoção de estados equivalentes
    // se há mais de um estado
    if (min.states.size() > 1) {
        // Define as transições de erro
        min.set_error_transitions();
        // Remove os estados equivalentes da cópia
        min.remove_equivalent_states();
        // Esconde as transições de erro
        min.hide_error_transitions();    
    }
    min.minimum = true;
    // Retorna a cópia
    return min;
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
    if (k_initial != "") {
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
            // Para cada transição do estado alcançável
            for (auto pair : reachable) {
                // Se o estado não se encontra no conjunto
                // de estados alcançáveis
                if (!reachable_states.count(pair.second)) {
                    // Adiciona o estado ao conjunto
                    new_reachables.push_back(pair.second);
                    // Adiciona a key ao conjunto de keys
                    keys.insert(pair.second);
                }
            }
        }
        // Mapa de estados recebe mapa de estados alcançáveis
        states = reachable_states;
        // Atualiza conjunto de chaves de estados aceitadores
        k_acceptors = intersection(keys, k_acceptors);
    } else {
        states.clear();
        k_acceptors.clear();
    }
}

void Automaton::remove_equivalent_states() {
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
            auto predecessors = predecessors_of(partition, entry);
            // Para cada classe no conjunto de classes
            for (auto it = partitions.begin(); it != partitions.end();) {
                // Guarda a classe em value
                auto value = *it;
                // Calcula a intersecção da classe com os predecessores
                auto intersec = intersection(predecessors, value);
                // Calcula a diferença da classe com os predecessores
                auto diff = difference(value, predecessors);                
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
    update_states(partitions);
}

void Automaton::update_states(const PartitionSet& partitions) {
    for (auto p : partitions) {
        if (!p.empty()) {
            Key state = *p.begin();
            p.erase(state);
            while (!p.empty()) {
                Key equivalent = *p.begin();
                p.erase(equivalent);
                for (auto entry : alphabet) {
                    auto predecessors = predecessors_of(equivalent, entry);
                    for (auto s : predecessors) {
                        states[s][entry] = state;
                    }
                }
                states.erase(equivalent);
                keys.erase(equivalent);
                if (k_acceptors.count(equivalent)){
                    k_acceptors.erase(equivalent);
                }
                if (equivalent == k_initial) {
                    k_initial = state;
                }
            }
        }
    }
}

void Automaton::set_error_transitions() {
    insert(k_error);
    for (auto entry : alphabet) {
        for (auto& pair : states) {
            if (!pair.second.accepts(entry)) {
                pair.second.make_transition(entry, k_error);
            }
        }
    }
}

void Automaton::hide_error_transitions() {
    states.erase(k_error);
    for (auto entry : alphabet) {
        for (auto& pair : states) {
            if (pair.second.accepts_to(entry, k_error)) {
                pair.second.remove_transition(entry);
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

std::string Automaton::new_label(unsigned n) const {
    std::string inverse;
    auto division = std::div(n, 26);
    inverse.push_back(65 + division.rem);
    while (division.quot != 0) {
        division = div(division.quot, 26);
        inverse.push_back(64 + division.rem);
    }
    std::string label(inverse.rbegin(), inverse.rend());
    return label;
    // std::string label(1, 65 + (n % 26));
    // for (int p = floor(n/26); p > 0; p--) {
    //     label += "'";
    // }
    // return label;
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
        if (is_final(pair.first)) {
            state_str += "*";
        }
        if (is_initial(pair.first)) {
            state_str += "->";
        }
        state_str += pair.first;
        result.push_back({state_str});
        for (auto entry : alphabet) {
            std::string transition_str;
            if (pair.second.accepts(entry)) {
                transition_str += pair.second[entry];
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