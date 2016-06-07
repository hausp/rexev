/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include <iostream>

#include "DeSimoneTree.hpp"
#include "Node.hpp"
#include "TNode.hpp"
#include "LNode.hpp"
#include "UNode.hpp"
#include "CNode.hpp"
#include "SNode.hpp"
#include "ONode.hpp"

#define RECENT_COMPILER 0
#define TRACE(x) std::cout << (#x) << " = " << (x) << std::endl
#define TRACE_L(x,y) std::cout << (x) << " = " << (y) << std::endl
#define TRACE_IT(x) \
    unsigned counter = 0; \
    for (auto& elem : (x)) { \
        std::cout << (#x) << "[" << std::to_string(counter++) << "] = " << elem << std::endl; \
    }
#define ECHO(x) std::cout << (x) << std::endl

DeSimoneTree::DeSimoneTree(string regex) {
    root = init_tree(regex);
    auto temp = root->link_node();
    temp->th_link = std::make_shared<LNode>();
}

DeSimoneTree::node_ptr DeSimoneTree::init_tree(string regex) {
    node_ptr current(new LNode());
    
    while (regex.size() > 0) {
        char entry = regex[0];
        regex.erase(0,1);

        if (std::isalnum(entry)) {
            if (std::isalnum(current->get_symbol())
                || current->get_symbol() == '*'
                || current->get_symbol() == '?') {
                put_concatenation(current);
            }
            put_leaf(current, entry);
        } else if (entry == '|') {
            put_union(current);
        } else if (entry == '.') {
            put_concatenation(current);
        } else if (entry == '*') {
            put_kleene_star(current);
        } else if (entry == '?') {
            put_option(current);
        } else if (entry == '(') {
            if (std::isalnum(current->get_symbol())
                || current->get_symbol() == '*'
                || current->get_symbol() == '?') {
                put_concatenation(current);
            }
            put_subtree(current, regex);
        } else {
            throw 666;
        }
    }
    while (current->father->get_symbol() != '~') {
        current = current->father;
    }
    return current;
}

void DeSimoneTree::put_leaf(node_ptr& current, const char entry) {
    //ECHO("Leaf insertion");
    node_ptr temp(new TNode(entry));
    if (current->left) {
        current->right = temp;
    } else {
        current->left = temp;
    }
    temp->father = current;
    current = temp;
}

void DeSimoneTree::put_union(node_ptr& current) {
    //ECHO("Union insertion");
    node_ptr temp(new UNode());
    while (current->father->get_symbol() != '~'
           || current->father->get_symbol() == '|') {
        current = current->father;
    }
    reasign_father(temp, current);
}

void DeSimoneTree::put_concatenation(node_ptr& current) {
    //ECHO("Concatenation insertion");
    node_ptr temp(new CNode());
    if (current->father) {
        current->father->right = temp;
    }
    reasign_father(temp, current);
}

void DeSimoneTree::put_kleene_star(node_ptr& current) {
    //ECHO("Kleene star insertion");
    node_ptr temp(new SNode());
    if (current->father) {
        if (current->father->left == current) {
            current->father->left = temp;
        } else {
            current->father->right = temp;
        }
    }
    reasign_father(temp, current);
}

void DeSimoneTree::put_option(node_ptr& current) {
    //ECHO("Union insertion");
    node_ptr temp(new ONode());
    if (current->father) {
        if (current->father->left == current) {
            current->father->left = temp;
        } else {
            current->father->right = temp;
        }
    }
    reasign_father(temp, current);
}

void DeSimoneTree::put_subtree(node_ptr& current, std::string& regex) {
    //ECHO("Subtree insertion");
    // if (current->get_symbol() == '*' || current->get_symbol() == '?') {
    //     put_concatenation(current);
    // }
    unsigned size = 0;
    unsigned branches = 0;
    while (regex[size] != ')' || branches > 0) {
        if (regex[size] != '(') branches++;
        if (regex[size] != ')') branches--;
        size++;
    }
    auto temp = init_tree(regex.substr(0, size));
    if (current->left) {
        current->right = temp;
    } else {
        current->left = temp;
    }
    temp->father = current;
    current = temp;
    regex.erase(0,size+1);
    if (std::isalnum(regex[0]) || regex[0] == '(') {
        put_concatenation(current);
    }
}


void DeSimoneTree::reasign_father(node_ptr& temp, node_ptr& current) {
    temp->father = current->father;
    temp->left = current;
    current->father = temp;
    current = temp;
}

std::ostream& operator<<(std::ostream& out, const DeSimoneTree& tree) {
    out << *(tree.root);
    return out;
}