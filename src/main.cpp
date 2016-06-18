/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include <iostream>

#include "DeSimoneTree.hpp"
#include "LNode.hpp"
#include "gtk.hpp"
#include "signals.hpp"
#include "Interface.hpp"
#include "Controller.hpp"

int main(int argc, char** argv) {

    gtk::init(argc, argv);

    DeSimoneTree tree("a&b");
    std::cout << tree << std::endl;

    Interface ui;
    Controller controller(ui);
    signals::set_controller(&controller);
    ui.show();

    gtk::main();
}
