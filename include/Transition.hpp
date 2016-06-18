/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include "State.hpp"

class Transition {
public:
	Transition();
	Transition(State*,char);
	~Transition();
private:
	State* from;
	char transition_label;

};

#endif /* TRANSITION_HPP */
