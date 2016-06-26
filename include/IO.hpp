/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */


/*
 *
 *
 *
 */

#include <fstream>
#include <unordered_map>
#include <utility>
#include "Regex.hpp"
#include <string>
 #include <algorithm>

class IO {
 public:
 	IO();
 	~IO();
 	void write_to_file(const std::unordered_map<unsigned, Regex>&, const std::string&);
 	std::unordered_map<unsigned, Regex> read_file(const std::string&);

 private:

};
