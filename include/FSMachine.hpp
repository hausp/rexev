/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

/**
 *
 * FSMachine class definition:
 *  This class defines a Deterministic Finite State Machine,
 *  the recognizer for a regular expression/regular grammar/
 *  regular language;
 *  Interaction Methods include to_string and
 *  print to table form, used for the graphical interface
 *  to show the automata to the user, through GUI.
 *
 **/

#ifndef FS_MACHINE_HPP
#define FS_MACHINE_HPP

#include <map>
#include <set>
#include <string>
#include <utility>

#include "State.hpp"

class FSMachine {
 public:
    FSMachine();
    FSMachine(const std::set<char>&);
    // Formal Definition
    // Transitions exist inside States
    // Finite State Set, Input Alphabet, Initial State, Final States Set 
    //FSMachine(const std::map<char,State>&, const std::set<char>&, char, const std::set<char>&);
    void insert(const std::string&, bool = false, bool = false);
    void make_transition(const std::string&, const char, const std::string&);
    State operator[](const std::string&);
    const State operator[](const std::string&) const;

    void remove_dead_states();
    void remove_unreachable_states();

 private:
    std::map<std::string, State> states;
    std::set<char> alphabet;
    std::string initial_state;
    std::set<std::string> final_states;
    RState rejection_state;
};

#endif /* FS_MACHINE_HPP */
