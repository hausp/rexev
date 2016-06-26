/* created by Vinicius Freitas<vinicius.mctf@grad.ufsc.br> 
   and Marleson Graf<aszdrick@gmail.com> [2016] */

#include "IO.hpp"

IO::IO() {

}

IO::~IO() {

}

void IO::write_to_file(const std::unordered_map<unsigned, Regex>& my_regexes, const std::string& filename) {
	std::ofstream io_entity;
	io_entity.open(filename, std::ofstream::out | std::ofstream::app);
	for (auto& re : my_regexes) {
		io_entity << re.second.get_alias() << "=" << re.second.get_regex() << "\n";
	}
	io_entity.close();
	return;
}

std::unordered_map<unsigned, Regex> IO::read_file(const std::string& filename) {
	std::unordered_map<unsigned, Regex> regexes;
	unsigned i = 0;
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
					 if (c == '\n') {
						regexes.insert(
							std::make_pair(
								i,
								Regex(regex, name)
							)
						);	
						break;
					}
					regex += c;
				}
			} else {
				name += c;
				c = io_entity.get();
			}
			if (c == '\n') break;
		}
		i++;
	}
	return regexes;
}