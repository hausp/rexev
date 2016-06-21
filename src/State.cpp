/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "State.hpp"

State::State() {
	label = 'Z';	
}

State::State(char l) {
	label = l;
}

State::~State() {

}

char State::get_label() {
	return label;
}

State::State* State::get_transition(char transition_label) {
	return (State*)*transitions.find(transition_label);
}

void State::new_transition(char transition_label, State* destination) {
	std::pair<char, State::State*> new_transition (label, destination);
	transitions.insert(new_transition);
}