/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Controller.hpp"
#include "DeSimoneTree.hpp"
#include "Regex.hpp"

Controller::Controller(Interface& ui) : ui(ui) {

}

void Controller::add_regex() {
    Regex regex;
    bool success = false;
    while(!success) {
        auto result = ui.show_add_dialog();
        success = true;
        if (result.second.size() > 0) {
            try {
            regex = result.second;
            ECHO((std::string)regex);
            } catch (std::exception& e) {
                ECHO(e.what());
                ui.show_error_message("Erro!", e.what());
                success = false;
            }
        }
    }
    ui.hide_add_dialog();
}

void Controller::close() {
    ui.destroy();
    gtk::quit();
}