#include <iostream>
#include <fstream>
#include <string>

int high_scores(std::string user_name, int attempts_count, bool write, bool read) {

	const std::string high_scores_filename = "high_scores.txt";

	// Read the high score file and look for a duplicates. 
	// If found, choose best score and write it (if current one is better than listed in table)
	if (write)
		{
		std::ifstream in_file{high_scores_filename};
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		std::cout << "High scores table (debug):" << std::endl;


		int high_score = 0;
		
		std::string temp;
		std::string high_score_str;
		std::string attempts_count_str;
		
        temp = "";
		int replace_flag = 0; // this var will be 0 if there was no replaces in file

		while (true) {

			std::string str;
            std::getline(in_file, str, ' '); //read username up to space and read to string
            if(!in_file) break;
            

			// Read the high score to int var
			in_file >> high_score;
			
			
			//Ignore the end of line symbol
			in_file.ignore();

			size_t position = 0;
			 
			
			while(position != std::string::npos) // do check whole string (current line)
            {   size_t position_start = position;
                position = str.find(user_name, position);
                
                if(position != std::string::npos && high_score > attempts_count)
                {   
					//std::cout << "welcome back! You get a new high score!\n";
                    high_score = attempts_count;
					replace_flag++;
                
                    
                    // write to temp string all until found username.    |
                     temp += str.substr(position_start, position - position_start);
                    
                    // Set the same username
                   
                    temp += user_name;
					
					//adjust the position
                    position += user_name.size();
				

                }
                else    // if duplicates were not found, just write username from table to temp string
                {
					temp += str.substr(position_start, 
                                           position - position_start);
					
                }
				
            }
            
			// add score to temp string
			temp += " ";
			high_score_str = std::to_string(high_score);
			temp += high_score_str;
			
			temp += "\n";
			

			if (in_file.fail()) {
				break;
			}


			
		}
		// if current player username was unique and nothing was replaced,
		// just add it to the end temp string 	
		if (replace_flag == 0 ) {
			attempts_count_str = std::to_string(attempts_count);
			temp += user_name;
			temp += " ";
			temp += attempts_count_str;
			temp += "\n";
		}	
		in_file. close();
		
		
        // Write all temp string to the file.   |
        
        std::ofstream out_file(high_scores_filename);
        out_file << temp.substr(0, temp.size());
        out_file.close();
        
    	
        //std::cout << "\nNew file:\n" << temp << "\n";
		

	};

    
	// Read mode - read the high score file and print all results
	if (read)
		{
		std::ifstream in_file{high_scores_filename};
		if (!in_file.is_open()) {
			std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		std::cout << "High scores table:" << std::endl;

		std::string username;
		int high_score = 0;
		
		while (true) {
			// Read the username first
			in_file >> username;
			// Read the high score next
			in_file >> high_score;
			// Ignore the end of line symbol
			in_file.ignore();
						
			if (in_file.fail()) {
				break;
			}

			// Print the information to the screen
			std::cout << username << '\t' << high_score<< std::endl;
			
			
		}

	};



	return 0;
}