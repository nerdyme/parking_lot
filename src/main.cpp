#include <iostream>
#include <cstdio>
#include "command_input.h"
#include "file_input.h"


void usage(char *binary) {

	std::cout<<" Usage in command mode requires only binary file\n " 
	<< binary <<'\n';
	std::cout  << " Usage in file mode requires binary file and 1 argument with input file name \n" << binary << "  " << "<input_file>" <<'\n';

}


int main(int argc, char **argv) {


AbstractInput *input;

if(argc == 1) { //Command Mode

	input = new CommandInput();

} else if (argc ==2) { //File mode

	input = new FileInput(argv[1]);

} else {

	std::cout <<"Wrong Usage of binary" <<'\n';
	usage(argv[0]);
	exit(EXIT_FAILURE);
}

input->read();
return 1;
}