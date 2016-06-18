/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "FSMachine.hpp"
#include <iostream>

FSMachine::FSMachine() {

}

FSMachine::~FSMachine() {

}

FSMachine::FSMachine(std::vector<State*> all, std::vector<char> symbols, State* initial, std::vector<State*> final) {
	states = all;
	final_states = final;
	alphabet = (symbols);
	ab_size = symbols.size();
	initial_state = initial;
}

std::string FSMachine::to_string() {
	return "Not implemented";
}

void FSMachine::terminal_print_table() {

}