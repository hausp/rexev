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
