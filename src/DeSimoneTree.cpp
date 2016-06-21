/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "DeSimoneTree.hpp"
#include "Node.hpp"
#include "TNode.hpp"
#include "LNode.hpp"
#include "UNode.hpp"
#include "CNode.hpp"
#include "SNode.hpp"
#include "PNode.hpp"
#include "ONode.hpp"

DeSimoneTree::DeSimoneTree()
: alphabet{'a','b','c','d','e','f','g','h','i','j','k','l',
           'm','n','o','p','q','r','s','t','u','v','w','x',
           'y','z','0','1','2','3','4','5','6','7','8','9','&'},
  lambda(new LNode()) {
}

DeSimoneTree::DeSimoneTree(string regex)
: alphabet{'a','b','c','d','e','f','g','h','i','j','k','l',
           'm','n','o','p','q','r','s','t','u','v','w','x',
           'y','z','0','1','2','3','4','5','6','7','8','9','&'},
  lambda(new LNode()),
  root(init_tree(regex)) {
    auto temp = root->link_node();
    temp->th_link = lambda.get();
}

bool DeSimoneTree::is_terminal(char entry) {
    return alphabet.count(entry);
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
    while (regex.size() > 0) {
        /* Lê-se o primeiro caractere da string,
           em seguida deletando-o da mesma. */
        char entry = regex[0];
        regex.erase(0,1);

        if (alphabet.count(entry)) {
            put_leaf(current, entry);
        } else if (entry == '|') {
            put_union(current);
        } else if (entry == '.') {
            put_concatenation(current);
        } else if (entry == '*') {
            put_kleene_star(current);
        } else if (entry == '+') {
            put_transitive_closure(current);
        } else if (entry == '?') {
            put_option(current);
        } else if (entry == '(') {
            if (!put_subtree(current, regex)) {
                throw 1;
            }
        } else if (entry == ' ') {
        } else if (entry == '\n') {
        } else {
            throw 1;
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
    //ECHO("Leaf insertion");
    /* Novo nodo terminal, guardando o símbolo lido. */
    Node* temp = new TNode(entry);
    /* Verificação de possível concatenação implícita. */
    auto next = current->get_symbol();
    if (alphabet.count(next) || next == '*' || next == '+' || next == '?') {
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
    //ECHO("Union insertion");
    Node* temp = new UNode();
    auto father_symbol = current->father->get_symbol();
    while (father_symbol != '~' || father_symbol == '|') {
        current = current->father;
    }
    reasign_father(temp, current);
}

void DeSimoneTree::put_concatenation(Node*& current) {
    //ECHO("Concatenation insertion");
    Node* temp = new CNode();
    if (current->father) {
        current->father->right.release();
        current->father->right.reset(temp);
    }
    reasign_father(temp, current);
}

void DeSimoneTree::put_kleene_star(Node*& current) {
    //ECHO("Kleene star insertion");
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
    //ECHO("Transitive closure insertion");
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
    //ECHO("Union insertion");
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

bool DeSimoneTree::put_subtree(Node*& current, std::string& regex) {
    //ECHO("Subtree insertion");
    if (regex.size() > 0) {
        auto symbol = current->get_symbol();
        if (alphabet.count(symbol) || symbol == '*' || symbol == '+' || symbol == '?') {
            put_concatenation(current);
        }
        unsigned size = 0;
        unsigned branches = 0;
        
        while (regex[size] != ')' || branches > 0) {
            if (regex[size] != '(') branches++;
            if (regex[size] != ')') branches--;
            if (++size == regex.size()) return false;
        }

        if (size > 0) {
            auto temp = init_tree(regex.substr(0, size));
            if (current->left) {
                current->right.release();
                current->right.reset(temp);
            } else {
                current->left.release();
                current->left.reset(temp);
            }
            temp->father = current;
            current = temp;
            regex.erase(0,size+1);
            if (alphabet.count(regex[0]) || regex[0] == '(') {
                put_concatenation(current);
            }
        } else {
            regex.erase(0,1);
        }
        return true;
    } else {
        return false;
    }
}

void DeSimoneTree::reasign_father(Node*& temp, Node*& current) {
    temp->father = current->father;
    temp->left.reset(current);
    current->father = temp;
    current = temp;
}

DeSimoneTree::operator string() const {
    return *root;
}

std::ostream& operator<<(std::ostream& out, const DeSimoneTree& tree) {
    out << (string)tree;
    return out;
}