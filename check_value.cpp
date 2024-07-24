#include <iostream>
#include "random_value.h"
#include "high_scores.h"

int main(int argc, char** argv) {
	int max_value = 100;
	// argc - it is a count of arguments
	// But there is some detail - OS always pass one system argument - the name of the executable
	// So, is the application was executed without arguments at all, argc will be still == 1

	// Let's print this argument
	//if (argc > 0) {
	//	std::cout << "We have at least one argument!" << std::endl;
	//	std::cout << "argv[0] = " << argv[0] << std::endl;
	//}

	// To check - does use print some other argument we should check if the argc >= 2
	if (argc >= 2) {
	
		//std::cout << "We have one more argument!" << std::endl;
		//std::cout << "argv[1] = " << argv[1] << std::endl;

		std::string arg1_value{ argv[1] };


		// if an argument is '-table', let's show high scores table and shutdown the app
		if (arg1_value == "-table") {
			
			//std::cout << "-table argument was detected!" << std::endl;
			//std::cout << "argv[1] = " << arg1_value << std::endl;
			
			//call high_scores() in read mode
			high_scores(arg1_value, 0, 0, true);
			return -1;
		}

		// if an argument is '-max', let's check max value and get it 
		if (arg1_value == "-max") {
		//	std::cout << "-max argument was detected!" << std::endl;

			// We've detected the '-max' argument. And we expect that after this argument there is a value:
			
			if (argc < 3) {
				std::cout << "Wrong usage! The argument '-max' requires some value!" << std::endl;
				return -1;
			}
			// We need to parse the string to the int value
			max_value = std::stoi(argv[2]);
			//std::cout << "The 'max' value = " << max_value << std::endl;
		}

		// if an argument is '-level', let's set the difficult level 
		if (arg1_value == "-level") {
		//	std::cout << "-level argument was detected!" << std::endl;

			// We've detected the '-level' argument. And we expect that after this argument there is a value:
			
			if (argc < 3) {
				std::cout << "Wrong usage! The argument '-level' requires some value!" << std::endl;
				return -1;
			}
			// We need to parse the string to the int value
			int level = std::stoi(argv[2]);
			switch (level) {
				case 1:
					std::cout << "First level was selected (0-9)\n";
					max_value = 10;
					break;
				case 2:
					std::cout << "Second level was selected (0-49)\n";
					max_value = 50;
					break;
				case 3:
					std::cout << "Third level was selected (0-99)\n";
					max_value = 100;
					break;
				default:
					std::cout << "Third level was selected by default (0-99)\n";
					max_value = 100;
			}
			
			
			
			//std::cout << "The 'max' value = " << max_value << std::endl;
		}
	}







	// Ask player's name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;
	
	//const int target_value = 54;
	const int target_value = random_value_generator(max_value);
	int current_value = 0;
	bool not_win = true;
	int attempts_count = 0;

	std::cout << "Enter your guess:" << std::endl;

	do {
		std::cin >> current_value;

		if (current_value > target_value) {
			std::cout << "less than " << current_value << std::endl;
			attempts_count++;
		}
		else if (current_value < target_value) {
			std::cout << "greater than " << current_value << std::endl;
			attempts_count++;
		}
		else {
			attempts_count++;
			std::cout << "you win!" << std::endl;
			std::cout << "attempts count = " << attempts_count << std::endl << std::endl;
			//call high_scores() in write and read modes
			high_scores(user_name,  attempts_count, true, true);
			break;
		}

	} while(true);

	return 0;
}