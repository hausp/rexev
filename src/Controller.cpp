/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Controller.hpp"
#include "DeSimoneTree.hpp"
#include "Regex.hpp"

Controller::Controller(Interface& ui)
 : ui(ui), n_expr(0),
   n_atm(0) {

}

void Controller::add_regex() {
    std::pair<std::string,std::string> result;
    bool success = false;
    while(!success) {
        result = ui.show_add_dialog();
        success = true;
        if (result.first.size() == 0) {
            result.first = "RGX" + std::to_string(n_expr);
        }
        if (result.second.size() > 0) {
            try {
                expressions[n_expr++] = Regex(result.second, result.first);
            } catch (std::exception& e) {
                ui.show_error_message("Erro!", e.what());
                success = false;
            }
            if (success) {
                automata[n_atm++] = expressions[n_expr-1].to_automaton();
                ui.put_regex(result.first, n_expr-1);
                ui.put_automaton(result.first, n_atm-1);
            }
        }
    }
    ui.hide_add_dialog();
}

void Controller::edit_regex() {
    
}

void Controller::minimize_automaton() {
    auto key = atm_selection.front();
    automata[key] = automata[key].minimize();
    ui.show_automaton(automata[key].to_table());
}

void Controller::intersect_automaton() {
    for (auto key : atm_selection) {
        if (key == atm_selection.front()) {
            automata[n_atm] = automata[key];
        } else {
            automata[n_atm] = automata[key].automaton_intersection(automata[n_atm]);
        }
    }
    ui.put_automaton("INT" + std::to_string(n_atm), n_atm);
    n_atm++;    
}

void Controller::regex_equivalence() {
    if (expr_selection.size() < 2) return;
    bool eq = false;
    for (auto key : expr_selection) {
        if (key == expr_selection.front()) {
        } else {
           //eq = automata[key].minimize().equals(automata[key-1].minimize()); 
        }
    }
    if (eq) {
        // Diz que são equivalentes
    } else {
        // Diz que não
    }
}

void Controller::add_regex_selection(unsigned value) {
    expr_selection.push_front(value);
    ui.show_expression(expressions[value].get_regex().c_str());
}
void Controller::remove_regex_selection(unsigned value) {
    expr_selection.remove(value);
    if (!expr_selection.empty()) {
        auto show_sel = expr_selection.front();
        ui.show_expression(expressions[show_sel].get_regex().c_str());
    }
}

void Controller::add_automata_selection(unsigned value) {
    atm_selection.push_front(value);
    ui.show_automaton(automata[value].to_table());
}
void Controller::remove_automata_selection(unsigned value) {
    atm_selection.remove(value);
    if (!atm_selection.empty()) {
        ui.show_automaton(automata[atm_selection.front()].to_table());
    }
}

void Controller::close() {
    ui.destroy();
    gtk::quit();
}