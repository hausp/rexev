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
#include <map>
#include <set>


class FSMachine {
 public:
 	FSMachine();
 	// Formal Definition
 	// Transitions exist inside States
  	// Finite State Set, Input Alphabet, Initial State, Final States Set 
 	FSMachine(const std::map<char,State>&, const std::set<char>&, char, const std::set<char>&);
 	~FSMachine();
 	std::string to_string();
 	void terminal_print_table();
 	void put_state(char);
 	void put_transition(char,char,char);

 private:
 	std::map<char,State> states;
 	std::set<char> alphabet;
 	char initial_state;
 	std::set<char> final_states;
};

#endif /* FS_MACHINE_HPP */
