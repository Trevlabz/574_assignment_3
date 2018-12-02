// hlsyn.cpp : Defines the entry point for the application.
// Assignment 3
// Trevor LaBanz

#include "hlsyn.h"
//#include "node.h"
#include "general.h"

using namespace std;


string comma = ",";

int main(int argc, char *argv[]){

	if (argc < 4) {								 								//usage statment if missing arguments
		cout << "Usage: " << argv[0] << " cFile latency verilogFile" << endl;
		return 1;
	}

	string inputFile = argv[1];
	
	//string tempFile = "temp.txt";
	
	string outputFile = argv[3];

	if (inputFile.substr(inputFile.length() - 2, inputFile.length()) != ".c") {
		cerr << "Input file does not have .c extension" << endl;
		return 1;
	}

	ifstream iFile(inputFile);

	if (iFile.fail()) {															//input cFile missing
		cerr << "Input file " << argv[1] << " failed to open" << endl;
		return 1;
	}
	else if (iFile.peek() == std::ifstream::traits_type::eof()) {				//input cFile missing
		cerr << "Input File is empty!" << endl;
		return 1;
	}

	try {														//convert arg2 to int in latency variable
		int latency = stoi(argv[2]);
	}
	catch (invalid_argument& e) {
		cerr << "Invalid Latency entry. Must be integer greater than 0..." << endl;	
		return 1;
	}
	catch (out_of_range& e) {
		cerr << "Invalid Latency entry. Too large of value..." << endl;
		return 1;
	}
	catch (...) {
		cerr << "Error with Latency entry. Must be an integer greater than 0..." << endl;
		return 1;
	}


	if (outputFile.substr(outputFile.length() - 2, outputFile.length()) != ".v") {	//output file missing .v extension
		cerr << "Output file does not have .v extension" << endl;
		return 1;
	}


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CFile Translate ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	vector<tuple<string, bool, int>> inputList;			//vector of tuples containing <name, isSigned? {true=signed}, datawidth> 		
	vector<tuple<string, bool, int>> outputList;		//vector of tuples containing <name, isSigned? {true=signed}, datawidth>
	vector<tuple<string, bool, int>> variableList;		//vector of tuples containing <name, isSigned? {true=signed}, datawidth>

	vector<Node*> nodeList;			//create vector of nodes called nodeList

	vector<tuple<string, string, string, bool>> graph;

	string currentLine;
	string currentWord;

	while(getline(iFile, currentLine)) {	//read input cFile to build sequencing graph
		currentWord = "";

		stringstream lineStream(currentLine);

		lineStream >> currentWord;

		
		if (currentWord == "input") {					//if input add inputs to input list
			bool isSigned;
			int dataSize;
			lineStream >> currentWord;
			
			if (currentWord.substr(0, 3) == "Int") {			//parse dataType
				isSigned = true;
				dataSize = stoi(currentWord.substr(3, 2));
			}
			else if (currentWord.substr(0, 4) == "UInt") {
				isSigned = false;
				dataSize = stoi(currentWord.substr(4, 2));
			}
			else {
				cerr << "Unknown input dataType: " << currentWord << endl;
				return 1;
			}

			while (lineStream >> currentWord) {
				if (currentWord.substr(0, 2) == "//") {
					break;
				}
				else {
					removeSubstrs(currentWord, comma);
					inputList.push_back(make_tuple(currentWord, isSigned, dataSize));
				}
			}

		}

		else if (currentWord == "output") {				//if output add outputs to output list
			bool isSigned;
			int dataSize;
			lineStream >> currentWord;

			if (currentWord.substr(0, 3) == "Int") {			//parse dataType
				isSigned = true;
				dataSize = stoi(currentWord.substr(3, 2));
			}
			else if (currentWord.substr(0, 4) == "UInt") {
				isSigned = false;
				dataSize = stoi(currentWord.substr(4, 2));
			}
			else {
				cerr << "Unknown output dataType: " << currentWord << endl;
				return 1;
			}

			while (lineStream >> currentWord) {
				if (currentWord.substr(0, 2) == "//") {
					break;
				}
				else {
					removeSubstrs(currentWord, comma);
					outputList.push_back(make_tuple(currentWord, isSigned, dataSize));
				}
			}

		}

		else if (currentWord == "variable") {			//if variable add outputs to variable list
			bool isSigned;
			int dataSize;
			lineStream >> currentWord;

			if (currentWord.substr(0, 3) == "Int") {			//parse dataType
				isSigned = true;
				dataSize = stoi(currentWord.substr(3, 2));
			}
			else if (currentWord.substr(0, 4) == "UInt") {
				isSigned = false;
				dataSize = stoi(currentWord.substr(4, 2));
			}
			else {
				cerr << "Unknown input dataType: " << currentWord << endl;
				return 1;
			}

			while (lineStream >> currentWord) {
				if (currentWord.substr(0, 2) == "//") {
					break;
				}
				else {
					removeSubstrs(currentWord, comma);
					variableList.push_back(make_tuple(currentWord, isSigned, dataSize));
				}
			}

		}

		else if (currentLine.find("=") != std::string::npos) {				//handle operation line
			Node* currentNode;
			currentNode = createOperation(currentLine, inputList, outputList, variableList);
			if (currentNode == NULL)
				return 1;
			nodeList.push_back(currentNode);

		}

		else if (currentWord == "if") {

		}
		else if (currentWord == "else") {


		}
	
	}
	
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Force Directed Scheduling ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	//perform FDS

	//ez


	   	  



	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Verilog File Generation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	//create header of verilog file

	//module declaration with (Clk, Rst, Start, Done, <inputs>, <outputs>)
	
	//<<"	input Clk, Rst, Start;"<<endl;

	//<<"	output reg Done;"<<endl;

	//declare other inputs, outputs, and variables

	//reset handling/clock handling

	//create initial states and end states

	//add states for each time in Scheduled Graph

	//end module


	return 0;
}
