/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <utility>

#include "gtk.hpp"

class Interface {
 public:
    Interface();
    void show();
    std::pair<std::string,std::string> show_add_dialog();
    void hide_add_dialog();
    void show_error_message(const char*, const char*);
    void put_regex(const std::string&, unsigned);
    void put_automaton(const std::string&, unsigned);
    void show_expression(const char*);
    void show_automaton(const std::vector<std::vector<std::string>>&);
    void select_expression(unsigned);
    void select_automaton(unsigned);
    void destroy();

 private:
    GtkBuilder* builder;
    GtkWidget* window;
    GtkWidget* dialog;

    void init();
    std::pair<std::string,std::string> extract_add_dialog_entries();
    void clean_add_dialog();
};

#endif /* INTERFACE_HPP */
