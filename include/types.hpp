/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#ifndef TYPES_HPP
#define TYPES_HPP

/* Debug utils */
#define TRACE(x) std::cout << (#x) << " = " << (x) << std::endl
#define TRACE_L(x,y) std::cout << (x) << " = " << (y) << std::endl
#define TRACE_IT(x) \
    {\
        unsigned counter = 0; \
        for (auto& elem : (x)) { \
            std::cout << (#x) << "[" \
            << std::to_string(counter++) << "] = " \
            << elem << std::endl; \
        }\
    }
#define ECHO(x) std::cout << (x) << std::endl

/* Automaton types */
using Entry = char;
using Alphabet = std::set<Entry>;
using Key = std::string;
using KeySet = std::set<Key>;
using PartitionSet = std::set<KeySet>;
using TransitionVector = std::vector<Key>;

#endif /* TYPES_HPP */
