/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <map>
#include <unordered_map>
#include <list>

#include "Interface.hpp"
#include "Regex.hpp"

class Controller {
 public:
    Controller(Interface&);
    void add_regex();
    void edit_regex();
    void minimize_automaton();
    void intersect_automaton();
    void regex_equivalence();
    void add_regex_selection(unsigned);
    void remove_regex_selection(unsigned);
    void add_automata_selection(unsigned);
    void remove_automata_selection(unsigned);
    void close();

 private:
    Interface& ui;
    std::unordered_map<unsigned, Regex> expressions;
    std::unordered_map<unsigned, Automaton> automata;
    std::list<unsigned> expr_selection;
    std::list<unsigned> atm_selection;
    unsigned n_expr;
    unsigned n_atm;
};

#endif /* CONTROLLER_HPP */
