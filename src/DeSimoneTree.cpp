/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "DeSimoneTree.hpp"

#include <exception>
#include <list>

#include "Node.hpp"
#include "TNode.hpp"
#include "LNode.hpp"
#include "UNode.hpp"
#include "CNode.hpp"
#include "SNode.hpp"
#include "PNode.hpp"
#include "ONode.hpp"
#include "FSMachine.hpp"


DeSimoneTree::DeSimoneTree()
: alphabet{},
  valid_entries{'a','b','c','d','e','f','g','h','i','j','k','l',
                'm','n','o','p','q','r','s','t','u','v','w','x',
                'y','z','0','1','2','3','4','5','6','7','8','9','&'},
  lambda(new LNode()) {
}

DeSimoneTree::DeSimoneTree(string regex)
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

DeSimoneTree::Node* DeSimoneTree::init_tree(string regex) {
    /* A árvore é inicializada com lambda, a fim de simplificar
       as verificações de ponteiros nulos no algoritmo.
     */
    Node* current = lambda.get();
    
    /* Para cada caractere da expressão regular, verifica-se
       se é um símbolo do alfabeto ou uma operação.
       Para cada caso, é feita uma insersão diferente, por vezes
       realizando-se rotações, montando, assim, a árvore com
       apenas uma iteração completa sobre a string, exceto em
       casos que há parênteses, pois são tratados como árvores
       separadas.
     */
    for (unsigned i = 0; i < regex.size(); i++) {
        char entry = regex[i];

        if (valid_entries.count(entry)) {
            put_leaf(current, entry);
        } else if (entry == '|') {
            if (current->get_symbol() == '|') {
                throw std::runtime_error("Expressão regular inválida.");
            }
            put_union(current);
        } else if (entry == '.') {
            if (current->get_symbol() == '.') {
                throw std::runtime_error("Expressão regular inválida.");
            }
            put_concatenation(current);
        } else if (entry == '*') {
            if (current->get_symbol() == '*') {
                throw std::runtime_error("Expressão regular inválida.");
            }
            put_kleene_star(current);
        } else if (entry == '+') {
            if (current->get_symbol() == '+') {
                throw std::runtime_error("Expressão regular inválida.");
            }
            put_transitive_closure(current);
        } else if (entry == '?') {
            if (current->get_symbol() == '?') {
                throw std::runtime_error("Expressão regular inválida.");
            }
            put_option(current);
        } else if (entry == '(') {
            try {
                ECHO(i);
                i += put_subtree(current, regex, ++i);
                ECHO(i);
            } catch (...) {
                throw;
            }
        } else if (entry == ' ') {
        } else if (entry == '\n') {
        } else {
            throw std::runtime_error("Expressão regular inválida.");
        }
    }

    if (current->father) {
        /* Laço para buscar a raíz da árvore.
           A raíz da árvore tem como pai o lambda.
           Lambda é representado pelo símbolo '~'.
         */
        while (current->father->get_symbol() != '~') {
            current = current->father;
        }
    }
    /* As chamadas release() nos ponteiros garantem 
       que lambda não tenha filhos, visto que ele é
       utilizado como base para construir a árvore.
     */
    current->father->left.release();
    current->father->right.release();
    /* Retorna a raíz da árvore. */
    return current;
}

void DeSimoneTree::put_leaf(Node*& current, const char entry) {
    ECHO("Leaf insertion");
    /* Novo nodo terminal, guardando o símbolo lido. */
    Node* temp = new TNode(entry);
    /* Adiciona entrada ao alfabeto */
    alphabet.insert(entry);
    /* Verificação de possível concatenação implícita. */
    auto symbol = current->get_symbol();
    if (valid_entries.count(symbol) || symbol == '*' || symbol == '+' || symbol == '?') {
        put_concatenation(current);
    }
    /* Insere folha onde estiver disponível, priorizando a esquerda. */
    if (current->left) {
        /* Chamar release() evita deletar um possível nodo no filho.
           Não há risco de memory leak, pois se houver algum nodo
           à direita, este será atribuído a algum outro nodo.
           A chamada reset() deleta o conteúdo atual do ponteiro
           e coloca temp em seu lugar.
         */
        current->right.release();
        current->right.reset(temp);
    } else {
        current->right.release();
        current->left.reset(temp);
    }
    /* Define o nodo atual como pai da folha recém-colocada. */
    temp->father = current;
    /* Atualiza nodo atual. */
    current = temp;
}

void DeSimoneTree::put_union(Node*& current) {
    ECHO("Union insertion");
    Node* temp = new UNode();
    auto father_symbol = current->father->get_symbol();
    while (father_symbol != '~' || father_symbol == '|') {
        current = current->father;
        father_symbol = current->father->get_symbol();
    }
    reasign_father(temp, current);
}

void DeSimoneTree::put_concatenation(Node*& current) {
    ECHO("Concatenation insertion");
    Node* temp = new CNode();
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

void DeSimoneTree::put_kleene_star(Node*& current) {
    ECHO("Kleene star insertion");
    Node* temp = new SNode();
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

void DeSimoneTree::put_transitive_closure(Node*& current) {
    ECHO("Transitive closure insertion");
    Node* temp = new PNode();
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

void DeSimoneTree::put_option(Node*& current) {
    ECHO("Union insertion");
    Node* temp = new ONode();
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
    ECHO("Subtree insertion");
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
                throw std::runtime_error("Expressão regular inválida.");
            }
        }

        if (size > 0) {
            ECHO(pos);
            ECHO(regex.substr(pos, size));
            auto temp = init_tree(regex.substr(pos, size));
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
        throw std::runtime_error("Expressão regular inválida.");
    }
}

void DeSimoneTree::reasign_father(Node*& temp, Node*& current) {
    // if (current->get_symbol() != '~') {
    temp->father = current->father;
    temp->left.reset(current);
    current->father = temp;
    current = temp;
    // } else {
    //     temp->father = current;
    //     current->left.reset(temp);
    //     current = temp;
    // }    
}

FSMachine DeSimoneTree::to_fsm() {
    // DOWN ACTION ON ROOT -> set chars
    // CRIA O STATE LABEL S (inicial)
    // FOR verifica símbolos vistos e define as transições
    // WHILE:
    FSMachine machine(alphabet);
    std::vector<std::set<Node*>> compositions;
    std::map<unsigned,State*> state_compositions;
    std::string state_label = "A";
    unsigned i = 0;
    unsigned j = 0;

    compositions.push_back(root->down_action());
    machine.insert("S", true, has_lambda(compositions[i]));
    state_compositions[i] = &machine["S"];
    std::list<State*> new_states = {&machine["S"]};

    ECHO(*this);
    while (new_states.size() > 0) {
        ECHO("begin of while");
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
                std::set<Node*> new_composition;
                for (auto node : entry_nodes) {
                    auto portion = node->up_action();
                    for (auto p : portion) {
                        new_composition.insert(p);
                    }
                }
                unsigned key = 0;
                bool is_new = true;
                for (auto c : compositions) { 
                    if (new_composition == c) {
                        is_new = false;
                        break;
                    }
                    key++;
                }
                if (is_new) {
                    j++;
                    compositions.push_back(new_composition);
                    machine.insert(state_label, false, has_lambda(new_composition));
                    ECHO(i+j);
                    ECHO("state composition");
                    ECHO(state_label);
                    state_compositions[i+j] = &machine[state_label];
                    current->add_transition(entry, {&machine[state_label]});
                    ECHO("transição criada:");
                    ECHO(current->get_label() + ", " + entry + " -> " + state_label);
                    new_states.push_back(&machine[state_label]);
                    state_label.at(0)++;
                } else {
                    ECHO("about to tretar");
                    current->add_transition(entry,{state_compositions.at(key)});
                    ECHO("transição criada:");
                    ECHO(current->get_label() + ", " + entry + " -> " 
                         + state_compositions.at(key)->get_label());
                }
            }
        }
        i++;
    }

    return machine;
    // for (auto node : reachable_from_root) {
    //     labels.push_back(node.get_symbol());
    //     reach.at(node.get_symbol()).push_back(node);
    // }

    // int i = 0;
    // for (auto t : alphabet) {
    //     if (t == *(labels.begin()+i)) {

    //         //State* a = new State (state_label++);
    //         //s->new_transition(t,a);
    //         //states.push_back(a);
    //         //related_nodes.at(a) = reach;
    //     }
    //     i++;
    // }

    // for (int is = 1; is != -1; is++) {
    //     final = false;
    //     reach.empty();
    //     labels.empty();
    //     reachable_from_root.empty();
    //     reachable_from_root = states[is]->up_action();
    //     for (auto node : reachable_from_root) {
    //         labels.push_back(node.get_symbol());
    //         // Talvez tenha que iniciar o vetores antes.
    //         reach.at(node.get_symbol()).push_back(node);
    //     }

    //     i = 0;
    //     bool state_exists = false;
    //     for (auto t : alphabet) {
    //         if (t == *(labels.begin()+i)) {
    //             if (t == '~') final = true;
    //             for (auto st : states) {
    //                 if (related_nodes.at(t).at(st) == related_nodes.at(t).at(s)) {
    //                     // Estado já existente
    //                     State* old = st;
    //                     states[is]->new_transition(t,old);
    //                     related_nodes.at(t).at(states[is]) = reach;
    //                     state_exists = true;
    //                     break;
    //                 }
    //             }
    //             if (!state_exists) {
    //                 State *a = new State (state_label++, final, false);
    //                 states[is]->new_transition(t,a);
    //                 states.push_back(a);
    //                 related_nodes.at(t).at(a) = reach;
    //             }
    //             state_exists = false;
    //         }
    //         i++;
    //     }
    // }

}

bool DeSimoneTree::has_lambda(const std::set<Node*>& nodes) {
        for (auto node : nodes) {
        if (node->get_symbol() == '~') {
            return true;
        }
    }
    return false;
}

DeSimoneTree::operator string() const {
    return *root;
}

std::ostream& operator<<(std::ostream& out, const DeSimoneTree& tree) {
    out << (string)tree;
    return out;
}