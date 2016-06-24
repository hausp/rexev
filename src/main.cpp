/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include <iostream>
#include <string>

#include "DeSimoneTree.hpp"
#include "Interface.hpp"
#include "Controller.hpp"
#include "Automaton.hpp"
#include "signals.hpp"
#include "gtk.hpp"


int main(int argc, char** argv) {
    gtk::init(argc, argv);
    Interface ui;
    Controller controller(ui);
    signals::set_controller(&controller);
    ui.show();
    gtk::main();
}
