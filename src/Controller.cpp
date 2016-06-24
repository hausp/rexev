/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Controller.hpp"
#include "DeSimoneTree.hpp"
#include "Regex.hpp"

Controller::Controller(Interface& ui)
 : ui(ui), number_of_expressions(0),
   number_of_automata(0) {

}

void Controller::add_regex() {
    //Regex regex;
    bool success = false;
    std::pair<std::string,std::string> result;
    while(!success) {
        result = ui.show_add_dialog();
        success = true;
        if (result.second.size() > 0) {
            try {
            expressions[number_of_expressions++] = std::make_pair(result.first, result.second);
            } catch (std::exception& e) {
                ui.show_error_message("Erro!", e.what());
                success = false;
            }
        }
        if (success) {
            if (result.first.size() == 0) {
                result.first = "RGX" + std::to_string(number_of_expressions-1);
            }
            ui.put_regex(result.first, number_of_expressions-1);
            ui.put_automaton(result.first, number_of_automata);
            automata[number_of_automata++] = &expressions[number_of_expressions-1].second.get_automaton();
        }
    }
    ui.select_expression(number_of_expressions-1);
    ui.hide_add_dialog();
}

void Controller::add_regex_selection(unsigned value) {
    selected_expressions.push_front(value);
    ui.show_expression(expressions[value].second.get_regex().c_str());
}
void Controller::remove_regex_selection(unsigned value) {
    selected_expressions.remove(value);
    if (!selected_expressions.empty()) {
        ui.show_expression(expressions[selected_expressions.front()].second.get_regex().c_str());
    }
}

void Controller::add_automata_selection(unsigned value) {
    selected_automata.push_front(value);
    ui.show_automaton(automata[value]->to_table());
}
void Controller::remove_automata_selection(unsigned value) {
    selected_automata.remove(value);
    if (!selected_automata.empty()) {
        ui.show_automaton(automata[value]->to_table());
    }
}

void Controller::close() {
    ui.destroy();
    gtk::quit();
}