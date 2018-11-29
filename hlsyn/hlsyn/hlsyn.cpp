// hlsyn.cpp : Defines the entry point for the application.
// Assignment 3
// Trevor LaBanz

#include "hlsyn.h"
#include "node.h"

using namespace std;




int main(int argc, char *argv[]){

	if (argc < 4) {																//usage statment if missing arguments
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

	vector<tuple<string, string, int>> inputList;		//vector of tuples containing <input name, Signed/Unsigned, datawidth> 		
	vector<tuple<string, string, int>> outputList;		//vector of tuples containing <input name, Signed/Unsigned, datawidth>
	vector<tuple<string, string, int>> variableList;	//vector of tuples containing <input name, Signed/Unsigned, datawidth>

	vector<Node*> nodeList;			//create vector of nodes called nodeList

	string currentLine;
	string currentWord;

	while(getline(iFile, currentLine)) {	//read input cFile to build sequencing graph

		stringstream lineStream(currentLine);

		lineStream >> currentWord;

		
		//if input 
			//add inputs to inputList

		//if output
			//add outputs to outputList

		//if variable
			//add variables to variableList

		//if add or increment
			//create add or increment Node
	
		//if sub or decrement
			//create subtract or decrement Node

		//if MUL
			//create MUL Node

		//if DIV
			//create DIV Node

		//if MOD
			//create MOD Node

		//if GT
			//create COMP Node

		//if LT
			//create COMP Node

		//if EQ
			//create COMP Node

		//if MUX
			//create MUX Node

		//if SHL
			//create SHL Node

		//if SHR
			//create SHR Node


		//if IF STATEMENT
			//create if statement Nodes


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
