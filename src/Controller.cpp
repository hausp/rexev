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
            result.first = "R" + std::to_string(n_expr);
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
        auto atm_key = expressions[key].get_automaton_key();
        std::pair<std::string,std::string> result;
        bool success = false;
        while(!success) {
            result = ui.show_edit_dialog(selected.get_alias(), selected.get_regex());
            success = true;
            if (result.first.size() == 0) {
                result.first = "R" + std::to_string(key);
            }
            if (result.second.size() > 0) {
                try {
                    expressions[key] = Regex(result.second, result.first);
                    expressions[key].set_automaton_key(atm_key);
                } catch (std::exception& e) {
                    ui.show_error_message("Erro!", e.what());
                    success = false;
                }
                if (success) {
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
        ui.show_general_message("Operação inválida!", 
                                "Nenhuma expressão regular selecionada.");
    }
}

void Controller::minimize_automaton() {
    if (!atm_selection.empty()) {
        for (auto key : atm_selection) {
            if (!automata[key].is_minimum()) {
                automata[n_atm] = automata[key].minimize();
                ui.put_automaton(automata[n_atm].get_name(), n_atm);
                n_atm++;
            } else {
                ui.show_general_message("Operação inválida!",
                                        "Autômato já é mínimo.");
            }
        }
        ui.select_automaton(n_atm-1);
    } else {
        ui.show_general_message("Operação inválida!",
                                "Nenhum autômato selecionado.");
    }
}

void Controller::intersect_automaton() {
    if (atm_selection.size() > 1) {
        auto first = atm_selection.front();
        atm_selection.pop_front();
        for (auto key : atm_selection) {
            automata[n_atm] = automata[first].intersection(automata[key]);
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
    if (expr_selection.size() != 2) {
        ui.show_general_message("Operação inválida!",
            "Selecione duas\nexpressões regulares.");
        return;
    }
    unsigned k1 = expressions[expr_selection.front()].get_automaton_key();
    unsigned k2 = expressions[expr_selection.back()].get_automaton_key();
    
    automata[n_atm] = automata[k1].complement();
    ui.put_automaton(automata[n_atm].get_name(), n_atm);
    n_atm++;

    automata[n_atm] = automata[k2].complement();
    ui.put_automaton(automata[n_atm].get_name(), n_atm);
    n_atm++;

    automata[n_atm] = automata[k1].intersection(automata[n_atm-1]);
    ui.put_automaton(automata[n_atm].get_name(), n_atm);
    n_atm++;

    automata[n_atm] = automata[k2].intersection(automata[n_atm-3]);
    ui.put_automaton(automata[n_atm].get_name(), n_atm);
    n_atm++;

    if (automata[n_atm-1].is_empty() && automata[n_atm-2].is_empty()) {
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
    IO io;
    auto filename = ui.save_file_dialog();
    io.write_to_file(expressions, filename);
}

void Controller::open() {
    IO io;
    auto filename = ui.open_file_dialog();
    expressions.clear();
    automata.clear();
    expr_selection.clear();
    atm_selection.clear();
    ui.clear();
    expressions = io.read_file(filename);
    n_expr = expressions.size();
    n_atm = expressions.size();
    for (unsigned i = 0; i < n_atm; i++) {
        automata[i] = expressions[i].to_automaton();
        expressions[i].set_automaton_key(i);
        ui.put_automaton(expressions[i].get_alias(), i);
        ui.put_regex(expressions[i].get_alias(), i);
    }
    ui.select_regex(n_expr);
    ui.select_automaton(n_expr);
}

void Controller::close() {
    ui.destroy();
    gtk::quit();
}