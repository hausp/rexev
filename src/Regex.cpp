/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "Regex.hpp"

Regex::Regex(const string& r)
: regex(r), regex_tree(r) {

}