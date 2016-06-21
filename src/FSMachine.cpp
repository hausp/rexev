/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "FSMachine.hpp"
#include <iostream>

FSMachine::FSMachine() {

}

FSMachine::~FSMachine() {

}

FSMachine::FSMachine(const std::map<char,State>& k, const std::set<char>& sigma, char q0, const std::set<char>& f)
 : states(k), alphabet(sigma), initial_state(q0), final_states(f) {

}

std::string FSMachine::to_string() {
	return "Not implemented";
}

void FSMachine::terminal_print_table() {

}

void FSMachine::put_state(char label) {
	states[label] = State(label);
}

void FSMachine::put_transition(char from, char to, char label) {
	if (states.count(from) && states.count(to)) {
		states.at(from).new_transition(label, states.at(to));
	}
}