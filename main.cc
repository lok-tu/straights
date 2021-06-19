#include <iostream>
#include <string>
#include <sstream>
#include "table.h"

int main(int argc, char* argv[]) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	if ( argc > 1 ) {
		try {
			seed = std::stoi( std::string{ argv[1] } );
		} catch( std::invalid_argument & e ) {
			std::cerr << e.what() << std::endl;
			return 1;
		} catch( std::out_of_range & e ) {
			std::cerr << e.what() << std::endl;
			return -1;
		} // catch
	} // if

	Table straights(seed);
	std::string s;
	
	straights.startGame();	

	while (std::getline(std::cin, s)) {
		std::istringstream iss{s};

		std::string cmd;
		iss >> cmd;

		if (cmd == "play") {
			std::string in;
			iss >> in;

			straights.takeTurn(cmd, in);
		}
		else if (cmd == "discard") {
			std::string in;
			iss >> in;

			straights.takeTurn(cmd, in);
		}
		else if (cmd == "deck") {
			straights.printDeck();
		}
		else if (cmd == "quit") {
			straights.endGame();
			break;
		}
		else if (cmd == "ragequit") {
			straights.rageQuit();
		}
		else if (cmd != "") {
			std::cerr << "Unrecognized command " << cmd << "!" << std::endl;
		}
	}

	return 0;
}
