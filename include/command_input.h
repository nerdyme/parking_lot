

class CommandInput {

public :

	void read() {
		std::string line;
		while (std::getline(cin, line)) {
			verifyCommand(line);
		}

	}

}