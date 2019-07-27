#include <string>
#include <iostream>
#include <fstream>

class FileInput {

private :
	ifstream fin;


public :

	FileInput(string input_filename) {
		fin.open(input_filename, ios::in);
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

}