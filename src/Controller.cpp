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
                expressions[n_expr] = Regex(result.second, result.first);
            } catch (std::exception& e) {
                ui.show_error_message("Erro!", e.what());
                success = false;
            }
            if (success) {
                automata[n_atm] = expressions[n_expr].to_automaton();
                automata[n_atm].set_name(result.first);
                expressions[n_expr].set_automaton_key(n_atm);

                ui.put_regex(result.first, n_expr);
                ui.select_regex(n_expr);
                ui.put_automaton(result.first, n_atm);
                ui.select_automaton(n_atm);

                n_atm++;
                n_expr++;
            }
        }
    }
    ui.hide_add_dialog();
}

void Controller::edit_regex() {
    if (!expr_selection.empty()) {
        auto key = expr_selection.front();
        auto& selected = expressions[key];
        std::pair<std::string,std::string> result;
        bool success = false;
        while(!success) {
            result = ui.show_edit_dialog(selected.get_alias(), selected.get_regex());
            success = true;
            if (result.first.size() == 0) {
                result.first = "RGX" + std::to_string(key);
            }
            if (result.second.size() > 0) {
                try {
                    expressions[key] = Regex(result.second, result.first);
                } catch (std::exception& e) {
                    ui.show_error_message("Erro!", e.what());
                    success = false;
                }
                if (success) {
                    auto atm_key = expressions[key].get_automaton_key();
                    automata[atm_key] = expressions[key].to_automaton();
                    automata[atm_key].set_name(result.first);
                    ui.put_regex(result.first, key);
                    ui.select_regex(key);
                    ui.put_automaton(result.first, atm_key);
                    ui.select_automaton(atm_key);
                }
            }
        }
        ui.hide_add_dialog();
    } else {
        
    }
}

void Controller::minimize_automaton() {
    if (!atm_selection.empty()) {
        auto key = atm_selection.front();
        ECHO(key);
        if (!automata[key].is_minimum()) {
            ECHO("Going to minimizar");
            automata[n_atm] = automata[key].minimize();
            ECHO("Hell yeah!");
            automata[n_atm].set_name("MIN[" + automata[n_atm].get_name() + "]");
            ECHO("uou");
            ui.put_automaton(automata[n_atm].get_name(), n_atm);
            ui.select_automaton(n_atm);
            n_atm++;
        } else {
            ui.show_general_message("Operação inválida!", "Autômato já é mínimo.");
        }
    } else {
        ui.show_general_message("Operação inválida!", "Nenhum autômato selecionado.");
    }
}

void Controller::intersect_automaton() {
    if (atm_selection.size() > 1) {
        auto first = atm_selection.front();
        atm_selection.pop_front();
        for (auto key : atm_selection) {
            automata[n_atm] = automata[first].automaton_intersection(automata[key]);
            automata[n_atm].set_name("INT[" + automata[first].get_name()
                                     + "x" + automata[key].get_name() + "]");
            ui.put_automaton(automata[n_atm].get_name(), n_atm);
            first = n_atm++;
        }
        ui.select_automaton(n_atm);
    } else {
        ui.show_general_message("Operação inválida!",
            "Selecione ao menos dois autômatos\npara realizar a intersecção.");
    }
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
        ui.show_general_message("Resultado",
            "As expressões regulares selecionadas\nsão equivalentes.");
    } else {
        ui.show_general_message("Resultado",
             "As expressões regulares selecionadas\nnão são equivalentes.");
    }
}

void Controller::add_regex_selection(unsigned value) {
    expr_selection.push_front(value);
    ui.show_regex(expressions[value].get_regex().c_str());
}

void Controller::remove_regex_selection(unsigned value) {
    expr_selection.remove(value);
    if (!expr_selection.empty()) {
        auto show_sel = expr_selection.front();
        ui.show_regex(expressions[show_sel].get_regex().c_str());
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

void Controller::save() {
    auto filename = ui.save_file_dialog();
}

void Controller::open() {
    auto filename = ui.open_file_dialog();
}

void Controller::close() {
    ui.destroy();
    gtk::quit();
}