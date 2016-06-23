/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Controller.hpp"
#include "DeSimoneTree.hpp"
#include "Regex.hpp"

Controller::Controller(Interface& ui)
 : ui(ui), number_of_expressions(0) {

}

void Controller::add_regex() {
    Regex regex;
    bool success = false;
    std::pair<std::string,std::string> result;
    while(!success) {
        result = ui.show_add_dialog();
        success = true;
        if (result.second.size() > 0) {
            try {
            regex = result.second;
            } catch (std::exception& e) {
                ui.show_error_message("Erro!", e.what());
                success = false;
            }
        }
        if (success) {
            ECHO((std::string)regex);
            if (result.first.size() == 0) {
                result.first = "RGX" + std::to_string(number_of_expressions);
            }
            ui.put_regex(result.first, number_of_expressions);
            expressions[number_of_expressions++] = std::make_pair(result.first, regex);
        }
    }
    ui.select_expression(number_of_expressions-1);
    ui.show_expression(result.second.c_str());
    ui.hide_add_dialog();
}

void Controller::close() {
    ui.destroy();
    gtk::quit();
}