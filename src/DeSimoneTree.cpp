/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include <iostream>

#include "DeSimoneTree.hpp"
#include "DSNode.hpp"
#include "LNode.hpp"
#include "FNode.hpp"
#include "UNode.hpp"
#include "CNode.hpp"
#include "SNode.hpp"
#include "ONode.hpp"



DeSimoneTree::DeSimoneTree(string regex) {
    root = init_tree(regex);
}

node_ptr DeSimoneTree::init_tree(string regex) {
    std::regex symbols {"[a-z0-9_]"};
    node_ptr current(new FNode());
    
    while (regex.size() > 0) {
        char entry = regex[0];
        regex.erase(0,1);

        if (std::isalpha(entry) || std::isdigit(entry)) {
            node_ptr temp(new LNode(entry));
            if (current->left) {
                current->right = temp;
            } else {
                current->left = temp;
            }
            temp->father = current;
            current = temp;
        } else if (entry == '|') {
            node_ptr temp(new UNode());
            while (current->father->get_symbol() != '~'
                   || current->father->get_symbol() == '|') {
                current = current->father;
            }
            reasign_father(temp, current);
        } else if (entry == '.') {
            node_ptr temp(new CNode());
            if (current->father) {
                current->father->right = temp;
            }
            reasign_father(temp, current);
        } else if (entry == '*') {
            node_ptr temp(new SNode());
            if (current->father) {
                if (current->father->left == current) {
                    current->father->left = temp;
                } else {
                    current->father->right = temp;
                }
            }
            reasign_father(temp, current);
        } else if (entry == '?') {
            node_ptr temp(new ONode());
            if (current->father) {
                if (current->father->left == current) {
                    current->father->left = temp;
                } else {
                    current->father->right = temp;
                }
            }
            reasign_father(temp, current);
        } else if (entry == '(') {
            entry = regex[0];
            unsigned size = 0;
            while (regex[size] != ')') size++;
            auto temp = init_tree(regex.substr(0, size));
            if (current->left) {
                current->right = temp;
            } else {
                current->left = temp;
            }
            temp->father = current;
            current = temp;
            regex.erase(0,size+1);
        } else {
            throw 666;
        }
    }
    while (current->father->get_symbol() != '~') {
        current = current->father;
    }
    return current;
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