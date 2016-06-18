/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Interface.hpp"

class Controller {
 public:
    Controller(Interface&);
    void add_regex();
    void close();

 private:
    Interface& ui;
};

#endif /* CONTROLLER_HPP */
