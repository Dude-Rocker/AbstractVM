#include "../inc/avm.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
	bool warn = false;
	std::string flg("-warning");
	const char *file = 0;

	if (argc > 2) {
		if (argc > 3 || (flg != argv[1] && flg != argv[2])) {
			std::cout << "Error: too many arguments" << std::endl;
			return 0;
		} else if (flg == argv[1])
			file = argv[2];
		else {
			file = argv[1];
		}
		warn = true;
	} else if (argc == 2 && flg == argv[1])
		warn = true;
	else
		file = argv[1];
	Avm avm;
	try {
		avm.read_stream(file, warn);
	} catch (std::exception const & ex) {
		std::cout << ex.what();
	}
	return 0;
}
