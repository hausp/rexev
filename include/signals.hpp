/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include "gtk.hpp"

class Controller;

namespace signals {
    void set_controller(Controller*);
    gboolean regex_selection(GtkTreeSelection*, GtkTreeModel*,
                             GtkTreePath*, gboolean, gpointer);
    gboolean automata_selection(GtkTreeSelection*, GtkTreeModel*,
                                GtkTreePath*, gboolean, gpointer);
    void add_regex();
    void edit_regex();
    void minimize();
    void intersect();
    void regex_equivalence();
    void save();
    void open();
    void close();
}

#endif /* SIGNALS_HPP */