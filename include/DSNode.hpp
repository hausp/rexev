/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef DS_NODE_HPP
#define DS_NODE_HPP

#include "DeSimoneTree.hpp"

class DSNode : public std::enable_shared_from_this<DSNode> {    
    friend class DeSimoneTree;
    friend std::ostream& operator<<(std::ostream&, const DSNode&);
 public:
    virtual void down_action() = 0;
    virtual void up_action() = 0;
    virtual bool is_leaf();
    char get_symbol();

 protected:
    DSNode(char);
    node_ptr link_node();

 private:
    char symbol;
    node_ptr father;
    node_ptr left;
    node_ptr right;
    node_ptr th_link;
};

std::ostream& operator<<(std::ostream&, const DSNode&);

#endif /* DS_NODE_HPP */
