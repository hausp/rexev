/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <map>
#include <list>

#include "Interface.hpp"
#include "Regex.hpp"

class Controller {
 public:
    Controller(Interface&);
    void add_regex();
    void add_regex_selection(unsigned);
    void remove_regex_selection(unsigned);
    void close();

 private:
    Interface& ui;
    std::map<unsigned,std::pair<std::string,Regex>> expressions;
    std::list<unsigned> selected_expressions;
    std::list<unsigned> selected_automata;
    unsigned number_of_expressions;
    unsigned number_of_automata;
};

#endif /* CONTROLLER_HPP */
