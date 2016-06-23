/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <map>

#include "Interface.hpp"
#include "Regex.hpp"

class Controller {
 public:
    Controller(Interface&);
    void add_regex();
    void close();

 private:
    Interface& ui;
    std::map<unsigned,std::pair<std::string,Regex>> expressions;
    unsigned number_of_expressions;
};

#endif /* CONTROLLER_HPP */
