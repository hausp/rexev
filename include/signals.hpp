/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include "gtk.hpp"

class Controller;

namespace signals {
    void set_controller(Controller*);
    void add_regex();
    void regex_selected(GtkTreeView*);
    void close();
}

#endif /* SIGNALS_HPP */