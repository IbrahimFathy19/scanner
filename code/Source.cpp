#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Source.h"
#include <vector>


int main() {

	const std::string input_file_dir = "input.txt",
		rw_file_dir = "reserved_words.txt",
		ss_file_dir = "special_symbols.txt",
		output_file_dir = "output.txt";

	std::fstream rw_fstream;
	std::fstream in_fstream;
	std::fstream ss_fstream;

	std::fstream out_fstream;

	// open files
	if (open_file(in_fstream, input_file_dir) == false
		|| open_file(rw_fstream, rw_file_dir) == false
		|| open_file(ss_fstream, ss_file_dir) == false
		|| open_file_output(out_fstream, output_file_dir) == false) {

		exit(0);

	}

	enum State
	{
		START, INCOMMENT, INNUM, INID, INASSIGN, DONE
	};
	State s = START;

	struct token {

		std::string token_value;
		std::string token_type;
	};
	token t;
	std::vector <token> token_vec;


	std::string str;
	char c;
	while (in_fstream.get(c)) {
		
		if (in_fstream.eof())
			s = DONE;

		if (s == START) {

			if (isalpha(c)) { /*start INID*/ 

				s = INID; 
				str.push_back(c);

			} 
			else if (c == ':') { /*start INASSIGN*/

				s = INASSIGN;
				str.push_back(c);

			}
			else if (isdigit(c)) { /*start INNUM*/

				s = INNUM;
				str.push_back(c);
			}
			else if (c == '{') { /*start INCOMMENT*/

				s = INCOMMENT;

			}
			else if (isblank(c) || c == '\n') {
				s = START;
			}
			else {
				s = DONE;
			}
			
		} 
		else if (s == INNUM) {

			if (isdigit(c)) { /*continue INNUM*/

				s = INNUM;
				str.push_back(c);

			}
			else {
				s = DONE;
			}
		}	 
		else if (s == INID) {

			if (isdigit(c) || isalpha(c)) { /*continue INID*/
				 
				s = INID;
				str.push_back(c);

			}
			else {  
				s = DONE;
			}
		}
		else if (s == INASSIGN) {
			 
			if (c == '=') {
	
				str.push_back(c);
				s = DONE;
				
			}

		}
		else if (s == INCOMMENT) {

			if (c == '}') {

				s = START;

			}
		}
			

		if (s == DONE) {

			t.token_value = str;

			if (!str.empty()) {
				if (isdigit(str[0]))
					t.token_type = "number";
				else if (isalpha(str[0]))
				{
					if (is_keyword(rw_fstream, t.token_value)) {

						t.token_type = "keyword";

					}
					else
						t.token_type = "Identifier";
				} 
				else if (str == ":=")
					t.token_type = "assign";
			token_vec.push_back(t); 
			}
			 
			if (is_special_symbol(ss_fstream, c) && str != ":=") {

				t.token_type = "special symbol"; 
				t.token_value = c; 
				token_vec.push_back(t);
	
			}
		
			s = START;
			str.clear();
			if (c == ':')
			{
				s = INASSIGN;
				str = c;
			}

		}
	}

	for (std::vector<token>::iterator i = token_vec.begin(); i != token_vec.end(); i++)
	{
		out_fstream << (*i).token_value << ", " << (*i).token_type << "\n";
	}
	std::cout << "Done, Check output.txt file\n";
	
	
	
	
	return 0;
}


bool open_file(std::fstream& is, const std::string& file_name) {
	
	is.open(file_name.c_str());
	if (is.fail()) {

		std::cout << "Error opening file " << file_name << "\n";
		return false;

	}

	return true;
}
bool open_file_output(std::fstream& is, const std::string& file_name) {

	is.open(file_name.c_str(), std::ios::out | std::ios::trunc);
	if (is.fail()) {

		std::cout << "Error opening file " << file_name << "\n";
		return false;

	}

	return true;
}

bool is_keyword(std::fstream& is, const std::string& token) {

	is.clear();
	is.seekg(0, std::ios::beg);//move the get position to the start

	std::string word;
	while (is >> word) {
		if (word == token) {
			return true;
		}
	}
	return false;
}

bool is_special_symbol(std::fstream& is, char token) {

	is.clear();
	is.seekg(0, std::ios::beg);//move the get position to the start

	char symbol;
	while (is >> symbol) {
		if (symbol == token) {
			return true;
		}
	}
	return false;

}