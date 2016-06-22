/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Controller.hpp"
#include "DeSimoneTree.hpp"

Controller::Controller(Interface& ui) : ui(ui) {

}

void Controller::add_regex() {
    auto result = ui.show_add_dialog();
    if (result.second.size() > 0) {
        DeSimoneTree tree;
        try {
            tree = result.second;
            ECHO(tree);
        } catch (std::exception& e) {
            ECHO(e.what());
            add_regex();
        }
        ui.hide_add_dialog();
    }   
}

void Controller::close() {
    ui.destroy();
    gtk::quit();
}