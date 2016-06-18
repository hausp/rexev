/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "signals.hpp"
#include "Controller.hpp"

namespace {
    Controller* controller;
} // private

namespace signals {
    void set_controller(Controller* c) {
        controller = c;
    }

    void add_regex() {
        controller->add_regex();
    }

    void close() {
        controller->close();
    }

} // signals