#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "abstract_input.h"

class FileInput : public AbstractInput {

private :
	std::ifstream fin;


public :

	FileInput(std::string input_filename) {
		fin.open(input_filename, std::ios::in);
		if(!fin) {
			std::cout << " Error in opening input file, Check and rerun \n";
			exit(EXIT_FAILURE);
		}
	}

	void read() {

		std::string line;
		while (std::getline(fin, line)) {
			verifyCommand(line);
		}
		
	}

	FileInput() {

		fin.close();
	}

};