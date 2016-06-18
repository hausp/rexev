/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef FS_MACHINE_HPP
#define FS_MACHINE_HPP

#include "State.hpp"
#include "Transition.hpp"
#include <string>

using state_vec = std::vector<State>
using trans_map = std::unordered_map<Transition,State>

class FSMachine {
 public:
 	FSMachine();
 	~FSMachine();

 	// Formal Definition
  	// Finite State Set, Input Alphabet, Transition Function, Initial State, Final States Set 
 	FSMachine(state_vec, std::vector<char>, trans_map, State, state_vec);
 	std::string to_string();
 	void terminal_print_table();
 private:
 	State* initial_state;
 	trans_map transitions;
 	unsigned int ab_size;
 	char alphabet[];
 	state_vec final_states;
};

#endif /* FS_MACHINE_HPP */
