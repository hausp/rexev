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
    std::pair<std::string,std::string> show_edit_dialog(const std::string&, const std::string&);
    void hide_add_dialog();
    void show_error_message(const char*, const char*);
    void show_general_message(const char*, const char*);
    void put_regex(const std::string&, unsigned);
    void put_automaton(const std::string&, unsigned);
    void show_regex(const char*);
    void show_automaton(const std::vector<std::vector<std::string>>&);
    void select_regex(unsigned);
    void select_automaton(unsigned);
    void destroy();
    std::string open_file_dialog();
    std::string save_file_dialog();

 private:
    GtkBuilder* builder;
    GtkWidget* window;
    GtkWidget* dialog;

    void init();
    std::pair<std::string,std::string> extract_add_dialog_entries();
    void clean_add_dialog();
    std::string build_file_dialog(const GtkFileChooserAction&,
                                const std::string&, const std::string&);
};

#endif /* INTERFACE_HPP */
