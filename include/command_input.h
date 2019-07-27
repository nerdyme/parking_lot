#pragma once

#include <string>
#include <iostream>
#include "abstract_input.h"


class CommandInput : public AbstractInput{

public :

	void read() {
		std::string line;
		while (std::getline(std::cin, line)) {
			verifyCommand(line);
		    }

		}

};