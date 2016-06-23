/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "IO.hpp"

IO::IO() {

}

IO::~IO() {

}

void IO::wright_to_file(const std::map<std::string, Regex>& my_regexes, const std::string& filename) {
	std::ofstream io_entity;
	io_entity.open(filename, std::ofstream::out | std::ofstream::app);
	for (auto re : my_regexes) {
		io_entity << re.first << "=" << re.second.get_regex() << "\n";
	}
	io_entity.close();
	return;
}

std::map<std::string, Regex> IO::read_file(const std::string& filename) {
	std::map<std::string, Regex> regexes;
	std::ifstream io_entity;
	io_entity.open(filename, std::ifstream::in);

	char c;
	while (io_entity.good()) {
		std::string name = "";
		std::string regex = "";
		c = io_entity.get();
		while (io_entity.good()) {
			if (c == '=') {
				while (io_entity.good()) {
					c = io_entity.get();
					regex += c;
				}
			}
			if (c == '\n') break;
			name += c;
			c = io_entity.get();
			Regex reg (regex);
			regexes[name] = reg;
		}
	}
	return regexes;
}