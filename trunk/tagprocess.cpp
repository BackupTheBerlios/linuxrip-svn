/* tagprocess.cpp */

/*
Tagprocess, a string modifier for linuxrip.
Copyright (C) 2006 madman2003(madman2003@gmail.com).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>

class AdjustString {
	public:
		AdjustString(std::string InputString = "" ) {
			LowerCaseWords.push_back("if");
			LowerCaseWords.push_back("when");
			LowerCaseWords.push_back("of");
			LowerCaseWords.push_back("the");
			LowerCaseWords.push_back("and");
			LowerCaseWords.push_back("or");
			LowerCaseWords.push_back("a");
			LowerCaseWords.push_back("inf");
			LowerCaseWords.push_back("with");
			LowerCaseWords.push_back("than");
			LowerCaseWords.push_back("at");
			UpperCaseWords.push_back("cd1");
			UpperCaseWords.push_back("cd2");
			UpperCaseWords.push_back("cd3");
			UpperCaseWords.push_back("cd4");
			UpperCaseWords.push_back("cd5");
			UpperCaseWords.push_back("i");
			UpperCaseWords.push_back("ii");
			UpperCaseWords.push_back("iii");
			UpperCaseWords.push_back("iv");
			UpperCaseWords.push_back("v");
			UpperCaseWords.push_back("vi");
			UpperCaseWords.push_back("vii");
			UpperCaseWords.push_back("viii");
			UpperCaseWords.push_back("ix");
			UpperCaseWords.push_back("x");
			state = 0;
			start = 1;
			firstletter = 0;
			capital = 1;
			Input = InputString;
		}
		
		void SplitWords() {
			for ( int i=0; i<Input.length(); i++ ) {
				if ( Input.substr(i,1) == " " ) {
					Words.push_back(Input.substr(firstletter, i-firstletter));
					firstletter = i+1;
				}
			}
			Words.push_back(Input.substr(firstletter, Input.length()-firstletter));
		}
		
		std::string Convert(int element) {
			Word = Words.at(element);
			start = 1;
			state = 0;
			
			/* Convert  all characters to lowercase, so we can process it properly */
			for ( int i=0; i<sizeof(Word); i++ ) {
				Word[i] = std::tolower(Word[i]);
			}
			/* Check for any special criteria */
			for ( int i=0; i<LowerCaseWords.size(); i++ ) {
				if ( Word == LowerCaseWords.at(i) ) {
					state = 2;
					break;
				}
			}
			for ( int i=0; i<UpperCaseWords.size(); i++ ) {
				if ( Word == UpperCaseWords.at(i) ) {
					state = 1;
					break;
				}
			}
			
			/* The final conversion */
			for ( int i=0; i<sizeof(Word); i++ ) {
				switch(state) {
				case 1:
					Word[i] = std::toupper(Word[i]);
					break;
				case 2:
					if ( element > 0 ) {
						Word[i] = std::tolower(Word[i]);
						break;
					}
				default:
					if ( start && capital ) {
						Word[i] = std::toupper(Word[i]);
					} else {
						Word[i] = std::tolower(Word[i]);
					}
					start = 0;
					break;
				}
			}
			return Word;
		}
		
		void ConvertAll() {
			SplitWords();
			for ( int i=0; i<Words.size(); i++ ) {
				Word = Convert(i);
				Words.erase(Words.begin()+i,Words.begin()+i+1);
				Words.insert(Words.begin()+i, Word);
			}
		}
		
		/* Display each character of the string */
		void Display() {
			for ( int i=0; i<Words.size(); i++ ) {
				std::cout << Words.at(i);
				if ( i<Words.size()-1 ) {
					std::cout << " ";
				}
			}
		}
		
		void SetNoCapital() {
			capital = 0;
		}
	
	private:
		std::string Input;
		std::string Word;
		std::vector <std::string> Words;
		std::vector <std::string> LowerCaseWords;
		std::vector <std::string> UpperCaseWords;
		int state;
		int start;
		int firstletter;
		int capital;
};

int main(int Argc, char *Argv[]) {
	/* Convert input to something usefull */
	std::vector <std::string> Args(Argv, Argv + Argc);
	int choice = 0;
	std::string Word = "";
	if ( Argc <= 2 ) {
		choice = 1;
	} else {
		Word = Args.at(2);
	}
	AdjustString string(Word);
	if ( Argc >= 5 ) {
		if ( Args.at(4) == "--noprocess" ) {
			string.SplitWords();
			string.Display();
			return 0;
		}
		if ( Args.at(3) == "--nocapital" ) {
			string.SetNoCapital();
		}
	}
	if ( Argc == 4 ) {
		if ( Args.at(3) == "--noprocess" ) {
			string.SplitWords();
			string.Display();
			return 0;
		}
		if ( Args.at(3) == "--nocapital" ) {
			string.SetNoCapital();
		}
	}
	switch(choice) {
		case 1:
			std::cout << "Tagprocess." << std::endl;
			std::cout << "Usage: ./tagprocess --convert 'string' [--nocapital] [--noprocess]" << std::endl;
			break;
		default:
			string.ConvertAll();
			string.Display();
			break;
	}
	return 0;	
}
