/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

/**
 *
 * State class definition:
 *	This class defines a data structure that
 *	contains information necessary for the construction
 *	of a FSM. States have a reference to other states
 * 	accessable from the current state, accessable via
 * 	the get_transition method.
 *
 **/

#ifndef STATE_HPP
#define STATE_HPP

#include <unordered_map>

class State {
 public:
 	State();
 	State(char);
 	~State();
 	char get_label();
 	State* get_transition(char);
 	void new_transition(char, State*);
 private:
 	char label;
 	std::unordered_map<char,State*> transitions;

};

#endif /* STATE_HPP */
