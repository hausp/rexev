/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "signals.hpp"
#include "Controller.hpp"

namespace {
    Controller* controller;
} // private

namespace signals {
    void set_controller(Controller* c) {
        controller = c;
    }

    gboolean regex_selection(GtkTreeSelection* selection, GtkTreeModel* model,
                             GtkTreePath *path, gboolean selected, gpointer) {
        GtkTreeIter iter;
        unsigned value;
        gtk_tree_model_get_iter(model, &iter, path);
        gtk_tree_model_get(model, &iter, 1, &value, -1);
        if (selected) {
            controller->remove_regex_selection(value);
        } else {
            controller->add_regex_selection(value);
        }
        return true;
    }


    gboolean automata_selection(GtkTreeSelection* selection, GtkTreeModel* model,
                                GtkTreePath *path, gboolean selected, gpointer) {
        GtkTreeIter iter;
        unsigned value;
        gtk_tree_model_get_iter(model, &iter, path);
        gtk_tree_model_get(model, &iter, 1, &value, -1);
        if (selected) {
            controller->remove_automata_selection(value);
        } else {
            controller->add_automata_selection(value);
        }
        return true;
    }

    void add_regex() {
        controller->add_regex();
    }

    void edit_regex() {
        controller->edit_regex();
    }

    void minimize() {
        controller->minimize_automaton();
    }

    void intersect() {
        controller->intersect_automaton();
    }

    void regex_equivalence() {
        controller->regex_equivalence();
    }

    void save() {
        controller->save();
    }

    void open() {
        controller->open();
    }

    void close() {
        controller->close();
    }

} // signals