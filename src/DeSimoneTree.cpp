/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "DeSimoneTree.hpp"

#include <exception>
#include <list>
#include <cmath>

#include "Node.hpp"
#include "TNode.hpp"
#include "LNode.hpp"
#include "UNode.hpp"
#include "CNode.hpp"
#include "SNode.hpp"
#include "PNode.hpp"
#include "ONode.hpp"
#include "Automaton.hpp"

using Node = DeSimoneTree::Node;

DeSimoneTree::DeSimoneTree()
: alphabet{},
  valid_entries{'a','b','c','d','e','f','g','h','i','j','k','l',
                'm','n','o','p','q','r','s','t','u','v','w','x',
                'y','z','0','1','2','3','4','5','6','7','8','9','&'},
  lambda(new LNode()) {
}

DeSimoneTree::DeSimoneTree(std::string regex)
: alphabet{},
  valid_entries{'a','b','c','d','e','f','g','h','i','j','k','l',
                'm','n','o','p','q','r','s','t','u','v','w','x',
                'y','z','0','1','2','3','4','5','6','7','8','9','&'},
  lambda(new LNode()),
  root(init_tree(regex)) {
    auto temp = root->link_node();
    temp->th_link = lambda.get();
}

bool DeSimoneTree::is_terminal(char entry) {
    return valid_entries.count(entry);
}

DeSimoneTree::Node* DeSimoneTree::init_tree(std::string regex) {
    // A árvore é inicializada com lambda, a fim de simplificar
    // as verificações de ponteiros nulos no algoritmo.
    Node* current = lambda.get();
    
    // Para cada caractere da expressão regular, verifica-se
    // se é um símbolo do alfabeto ou uma operação.
    // Para cada caso, é feita uma insersão diferente, por vezes
    // realizando-se rotações, montando, assim, a árvore com
    // apenas uma iteração completa sobre a string, exceto em
    // casos que há parênteses, pois são tratados como árvores
    // separadas.
    for (unsigned i = 0; i < regex.size(); i++) {
        char entry = regex[i];

        if (valid_entries.count(entry)) {
            put_leaf(current, entry);
        } else if (entry == '|') {
            if (regex[i+1] == '|') {
                throw i+1;
            }
            put_union(current);
        } else if (entry == '.') {
            if (regex[i+1] == '.') {
                throw i+1;
            }
            put_concatenation(current);
        } else if (entry == '*') {
            if (regex[i+1] == '*') {
                throw i+1;
            }
            put_kleene_star(current);
        } else if (entry == '+') {
            if (regex[i+1] == '+') {
                throw i+1;
            }
            put_transitive_closure(current);
        } else if (entry == '?') {
            if (regex[i+1] == '?') {
                throw i+1;
            }
            put_option(current);
        } else if (entry == '(') {
            i += put_subtree(current, regex, ++i);
        } else if (entry == ' ') {
        } else if (entry == '\n') {
        } else {
            throw i+1;
        }
    }

    if (current->father) {
        // Laço para buscar a raíz da árvore.
        // A raíz da árvore tem como pai o lambda.
        // Lambda é representado pelo símbolo '~'.
        while (current->father->get_symbol() != '~') {
            current = current->father;
        }
    }
    // As chamadas release() nos ponteiros garantem 
    // que lambda não tenha filhos, visto que ele é
    // utilizado como base para construir a árvore.
    current->father->left.release();
    current->father->right.release();
    // Retorna a raíz da árvore.
    return current;
}

void DeSimoneTree::put_leaf(Node*& current, const char entry) {
    //ECHO("Leaf insertion");
    // Novo nodo terminal, guardando o símbolo lido.
    Node* temp = new TNode(entry);
    // Adiciona entrada ao alfabeto
    alphabet.insert(entry);
    // Verificação de possível concatenação implícita.
    auto symbol = current->get_symbol();
    if (valid_entries.count(symbol) || symbol == '*' || symbol == '+' || symbol == '?') {
        put_concatenation(current);
    }
    // Insere folha onde estiver disponível, priorizando a esquerda.
    if (current->left) {
        // Chamar release() evita deletar um possível nodo no filho.
        // Não há risco de memory leak, pois se houver algum nodo
        // à direita, este será atribuído a algum outro nodo.
        // A chamada reset() deleta o conteúdo atual do ponteiro
        // e coloca temp em seu lugar.
        current->right.release();
        current->right.reset(temp);
    } else {
        current->right.release();
        current->left.reset(temp);
    }
    // Define o nodo atual como pai da folha recém-colocada.
    temp->father = current;
    // Atualiza nodo atual.
    current = temp;
}

void DeSimoneTree::put_union(Node*& current) {
    //ECHO("Union insertion");
    Node* temp = new UNode();
    auto father_symbol = current->father->get_symbol();
    while (father_symbol != '~' || father_symbol == '|') {
        current = current->father;
        father_symbol = current->father->get_symbol();
    }
    reasign_father(temp, current);
}

void DeSimoneTree::put_concatenation(Node*& current) {
    //ECHO("Concatenation insertion");
    Node* temp = new CNode();
    put_node(temp, current);
}

void DeSimoneTree::put_kleene_star(Node*& current) {
    //ECHO("Kleene star insertion");
    Node* temp = new SNode();
    put_node(temp, current);
}

void DeSimoneTree::put_transitive_closure(Node*& current) {
    //ECHO("Transitive closure insertion");
    Node* temp = new PNode();
    put_node(temp, current);
}

void DeSimoneTree::put_option(Node*& current) {
    //ECHO("Union insertion");
    Node* temp = new ONode();
    put_node(temp, current);
}

void DeSimoneTree::put_node(Node*& temp, Node*& current) {
    if (current->father) {
        if (current->father->left.get() == current) {
            current->father->left.release();
            current->father->left.reset(temp);
        } else {
            current->father->right.release();
            current->father->right.reset(temp);
        }
    }
    reasign_father(temp, current);
}

unsigned DeSimoneTree::put_subtree(Node*& current, std::string& regex, unsigned pos) {
    //ECHO("Subtree insertion");
    if (pos < regex.size()-1) {
        auto symbol = current->get_symbol();
        if (valid_entries.count(symbol) || symbol == '*' || symbol == '+' || symbol == '?') {
            put_concatenation(current);
        }
        unsigned size = 0;
        unsigned branches = 0;
        
        while (regex[pos + size] != ')' || branches > 0) {
            if (regex[pos + size] == '(') branches++;
            if (regex[pos + size] == ')') branches--;
            if (++size + pos == regex.size()) {
                throw pos;
            }
        }

        if (size > 0) {
            Node* temp;
            try {
                temp = init_tree(regex.substr(pos, size));
            } catch (unsigned e) {
                throw pos + e;
            }
            if (current->left) {
                current->right.release();
                current->right.reset(temp);
            } else {
                current->left.release();
                current->left.reset(temp);
            }
            temp->father = current;
            current = temp;
            if (valid_entries.count(regex[pos + size+1]) || regex[pos + size+1] == '(') {
                put_concatenation(current);
            }
        }
        return size;
    } else {
        throw pos;
    }
}

void DeSimoneTree::reasign_father(Node*& temp, Node*& current) {
    temp->father = current->father;
    temp->left.reset(current);
    current->father = temp;
    current = temp;
}

Automaton DeSimoneTree::to_automaton() {
    //ECHO("to_automaton");
    Automaton automaton(alphabet);
    std::vector<std::set<Node*>> compositions;
    std::list<std::string> new_states;
    std::vector<std::string> states;
    std::string state_label = "B";
    unsigned i = 0;

    states.push_back("A");
    compositions.push_back(root->down_action());
    automaton.insert("A", true, has_lambda(compositions[i]));
    new_states.push_back("A");

    while (new_states.size() > 0) {
        auto current = new_states.front();
        new_states.pop_front();
        for (auto entry : alphabet) {
            std::set<Node*> entry_nodes;
            for (auto node : compositions[i]) {
                if (node->get_symbol() == entry) {
                    entry_nodes.insert(node);
                }
            }
            if (entry_nodes.size() > 0) {
                // Para as folhas que contém o símbolo entry,
                // pega a nova composição de nodos
                std::set<Node*> new_composition = get_composition(entry_nodes);
                // Verifica se a composição já existe
                int key = search_composition(compositions, new_composition);
                if (key != -1) {
                    // Composição já existe
                    // Cria transição para o estado equivalente
                    automaton.make_transition(current, entry, states[key]);
                } else {
                    // Composição nova
                    // Adiciona novo estado e cria transição para ele
                    states.push_back(state_label);
                    compositions.push_back(new_composition);
                    automaton.insert(state_label, false, has_lambda(new_composition));
                    new_states.push_back(state_label);
                    automaton.make_transition(current, entry, state_label);
                    state_label = new_label(states.size());
                }
            }
        }
        i++;
    }
    return automaton;
}

bool DeSimoneTree::has_lambda(const std::set<Node*>& nodes) {
        for (auto node : nodes) {
        if (node->get_symbol() == '~') {
            return true;
        }
    }
    return false;
}

std::string DeSimoneTree::new_label(unsigned n) {
    std::string ultra_danger;
    
    auto division = std::div(n, 26);
    ECHO(division.quot);
    ECHO(division.rem);
    ultra_danger.push_back(65 + division.rem);
    while (division.quot != 0) {
        division = div(division.quot, 26);
        ultra_danger.push_back(65 + division.rem);
    }
    std::string danger(ultra_danger.rbegin(), ultra_danger.rend());
    TRACE(danger);
    // std::string label(1, 65 + (n % 26));
    // for (int p = floor(n/26); p > 0; p--) {
    //     label += "'";
    // }
    return danger;
}

int DeSimoneTree::search_composition(const std::vector<std::set<Node*>>& list,
                                     const std::set<Node*>& composition) {
    for (unsigned k = 0; k < list.size(); k++) { 
        if (composition == list[k]) {
            return k;
        }
    }
    return -1;
}

std::set<Node*> DeSimoneTree::get_composition(const std::set<Node*>& entry_nodes) {
    std::set<Node*> composition;
    for (auto node : entry_nodes) {
        auto portion = node->up_action();
        for (auto p : portion) {
            composition.insert(p);
        }
    }
    return composition;
}

DeSimoneTree::operator std::string() const {
    return *root;
}

std::ostream& operator<<(std::ostream& out, const DeSimoneTree& tree) {
    out << (std::string)tree;
    return out;
}