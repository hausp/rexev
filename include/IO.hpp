/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */


/*
 *
 *
 *
 */

#include <fstream>
#include <map>
#include <utility>
#include "Regex.hpp"
#include <string>

class IO {
 public:
 	IO();
 	~IO();
 	void wright_to_file(const std::map<std::string, Regex>&, const std::string&);
 	std::map<std::string, Regex> read_file(const std::string&);

 private:

};
