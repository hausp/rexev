/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "FSMachine.hpp"
#include <iostream>

FSMachine::FSMachine() {

}

FSMachine::~FSMachine() {

}

FSMachine::FSMachine(state_vec all, std::vector<char> symbols, State* initial, state_vec final) {
	states = all;
	final_states = final;
	alphabet = new char[symbols.size()];
	ab_size = symbols.size();
	int counter = 0;
	for (auto it = symbols.begin(); it != symbols.end(); ++it) {
		alphabet[counter] = (char)*it;
		counter++;
	}
	if (counter != ab_size - 1) {
		std::cout << "Deu ruim" << std::endl;
	}
	initial_state = initial;
}

std::string FSMachine::to_string() {

}

void FSMachine::terminal_print_table() {
	
}