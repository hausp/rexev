/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef STATE_HPP
#define STATE_HPP

class State {
 public:
 	State();
 	State(char);
 	~State();
 	char get_label();
 private:
 	char label;

};

#endif /* STATE_HPP */
