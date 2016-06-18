/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

/**
 *
 * FSMachine class definition:
 *	This class defines a Deterministic Finite State Machine,
 *	the recognizer for a regular expression/regular grammar/
 *	regular language;
 *	Interaction Methods include to_string and
 *	print to table form, used for the graphical interface
 *	to show the automata to the user, through GUI.
 *
 **/

#ifndef FS_MACHINE_HPP
#define FS_MACHINE_HPP

#include "State.hpp"
#include <string>
#include <utility>
#include <vector>

class FSMachine {
 public:
 	FSMachine();
 	~FSMachine();

 	// Formal Definition
 	// Transitions exist inside States
  	// Finite State Set, Input Alphabet, Initial State, Final States Set 
 	FSMachine(std::vector<State*>, std::vector<char>, State*, std::vector<State*>);
 	std::string to_string();
 	void terminal_print_table();
 private:
 	State* initial_state;
 	std::vector<State*> states;
 	int ab_size;
 	std::vector<char> alphabet;
 	std::vector<State*> final_states;
};

#endif /* FS_MACHINE_HPP */
