/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "State.hpp"

#include <ostream>

//-------------------------- State implementation ---------------------------//

State::State(const std::string& label, RState* const rejection_state,
             bool initial, bool final)
: label(label),
  rejection_state(rejection_state),
  initial(initial),
  final(final) { }

std::string State::get_label() const {
    return label;
}

bool State::is_initial() const {
    return initial;
}

bool State::is_final() const {
    return final;
}

bool State::is_rejector() const {
    return false;
}

void State::set_label(const std::string& l) {
    label = l;
}

bool State::accepts(const char entry) const {
    return transitions.count(entry);
}

void State::set_transition(const char entry, State* const target) {
    transitions[entry] = target;
}

const State* State::operator[](const char entry) const {
    try {
        return transitions.at(entry);
    } catch (...) {
        return rejection_state;
    }
}

State::operator std::string() const {
    return label;
}

std::ostream& operator<<(std::ostream& out, const State& state) {
    return out << (std::string)state;
}

//-------------------------- RState implementation --------------------------//

RState::RState()
: State("\u03D5", this) {

}

bool RState::is_rejector() const {
    return true;
}