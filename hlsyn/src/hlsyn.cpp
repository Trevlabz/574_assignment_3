// hlsyn.cpp : Defines the entry point for the application.
// Assignment 3
// Trevor LaBanz

#include "hlsyn.h"

using namespace std;


string comma = ",";
vector<vector<double>> typeProb;


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

	int latency = 0;

	try {														//convert arg2 to int in latency variable
		latency = stoi(argv[2]);
	}
	catch (invalid_argument&) {
		cerr << "Invalid Latency entry. Must be integer greater than 0..." << endl;	
		return 1;
	}
	catch (out_of_range&) {
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
	
	string prevCond;		
	vector<tuple<bool, string>> conditionList;	//conditionList contains <True/False condition for if/else, condition variable string> 

	vector<tuple<string, string, string, bool>> graph;

	string currentLine = "";
	string currentWord = "";

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
			currentNode->nodeConditions = conditionList;
			nodeList.push_back(currentNode);
		}

		else if (currentWord == "if") {			//handle if statement
			lineStream >> currentWord;
			if (currentWord != "(") {	//confirm parthenthesis following if
				cerr << "expecting '(' in line: " << currentLine << endl;
				return 1;
			}
			
			lineStream >> currentWord;
			if (!isVar(currentWord, inputList) && !isVar(currentWord, variableList)) {					//check condition is defined
				cerr << "Undefined condition " << currentWord << " in line: " << currentLine << endl;
				return 1;
			}

			conditionList.push_back(make_tuple(true, currentWord));		//add a condition to the conditionList
		}
		
		else if (currentWord == "}") {						//end of condition block
			prevCond = get<1>(conditionList.back());		//store previous condition for potential else statements
			conditionList.pop_back();						//remove newest condition from conditon list
		}	

		else if (currentWord == "else") {						//handle else statement
		conditionList.push_back(make_tuple(false, prevCond));	
		}
	}
	
	iFile.close();		//close input file
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Force Directed Scheduling ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
	//compute timeframes

	connectGraph(nodeList);		//make graph connections

	int minCycles = doASAP(nodeList);	//peform ASAP scheduling

	if (minCycles > latency) {	//check if asap latency is larger than latency
		cerr << "Latency of " << latency << " is too small. Minimum latency is: " << minCycles << endl;	//if it is; error
		return 1;
	}

	
	doALAP(nodeList, latency);	//perform ALAP scheduling

	for (Node* cNode : nodeList) {	//calculate width of each node
		cNode->calcWidth();
	}


	for (int i = 0; i <= 3; i++) {//initialize typeProb vector for latency
		vector<double> tempV;
		for (int j = 0; j <= latency; j++) {
			tempV.push_back(0);
		}
		typeProb.push_back(tempV);
	}

	doTypeDistribution(nodeList);			//compute the operations and type probabilites
	
	doFDS(nodeList);			//perform FDS


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Verilog File Generation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ofstream oFile(outputFile);
	
	currentLine = "";

	int nStates = calcNStates(nodeList) + 3;		//calculate number of states in nodelist and add 3 for start/stop states

	int nStateBits = floor(log2(nStates)) + 1;		//calculate the number of bits required for the number of states



	oFile << "`timescale 1ns / 1ns" << "\n\n\n";			//create header of verilog file

	oFile << "module HLSM (Clk, Rst, Start, Done, ";							//module declaration with (Clk, Rst, Start, Done, ...
	for (int i = 0;i < inputList.size(); i++) {						//append inputs
			oFile << get<0>(inputList[i]) << ", ";
	}
																			
	for (int i = 0; i < outputList.size(); i++) {						//append outputs
		if (i == outputList.size() - 1)
			oFile << get<0>(outputList[i]);
		else
			oFile << get<0>(outputList[i]) << ", ";
	}

	oFile << ");" << "\n\n";		//finish module declaration

	oFile << '\t' << "input Clk, Rst, Start;" << '\n';	//initialize standard ports
	oFile << '\t' << "output reg Done;" << '\n';
	oFile << '\t' << "reg [" << nStateBits -1 << ":0] State;"<< "\n\n";				// declare State reg

		
	for (int i = 0; i < inputList.size(); i++) {				//declare inputs
		oFile << '\t' << "input ";
		if(get<1>(inputList[i]))
			oFile <<"signed ";
		if (get<2>(inputList[i]) > 1)
			oFile << "[" << get<2>(inputList[i]) - 1 << ":0] ";
		oFile<< get<0>(inputList[i]) <<";\n";
	}
	
	oFile << '\n';

	for (int i = 0; i < outputList.size(); i++) {				//declare outputs
		oFile << '\t' << "output reg ";
		if (get<1>(outputList[i]))
			oFile << "signed ";
		if (get<2>(outputList[i]) > 1)
			oFile << "[" << get<2>(outputList[i]) - 1 << ":0] ";
		oFile << get<0>(outputList[i]) << ";\n";
	}
	
	oFile << '\n';

	for (int i = 0; i < variableList.size(); i++) {				//declare regs
		oFile << '\t' << "reg ";
		if (get<1>(variableList[i]))
			oFile << "signed ";
		if (get<2>(variableList[i]) > 1)
			oFile << "[" << get<2>(variableList[i]) - 1 << ":0] ";
		oFile << get<0>(variableList[i]) << ";\n";
	}
	

	oFile << "\n\n\n";

	oFile << '\t' << "always @(posedge Clk) begin" << '\n';

	oFile << "\t\t" << "if (Rst) begin" << '\n';

	oFile << "\t\t\t";

	for (int i = 0; i < outputList.size(); i++) {				//set outputs to zero
		oFile << get<0>(outputList[i]) << " <= 0; ";
	}

	for (int i = 0; i < variableList.size(); i++) {				//set regs to zero
		oFile << get<0>(variableList[i]) << " <= 0; ";
	}

	oFile << "\n\t\t\t" << "State <= 0; Done <= 0;\n";
	oFile << "\t\t" << "end\n";
	oFile << "\t\t" << "else begin\n";

	oFile << "\t\t\t" << "case (State)" << '\n';
	
	oFile << "\t\t\t\t" << "0 : begin " << "if (Start) State <= 2; end" << '\n';	//wait for Start=1 state
	oFile << "\t\t\t\t" << "1 : begin " << "Done <= 1; State <= 0; end" << '\n';		//Done=1 state


	oFile << nodeToVerilog(nodeList);		//create string of all states and their respective operations


	oFile << "\t\t\t" << "endcase" << '\n';	//end everything
	oFile << "\t\t" << "end" << '\n';
	oFile << '\t' << "end" << '\n';
	oFile << "endmodule";

	oFile.close();

	cout << "HLSM created in output file: " << outputFile << endl;

	return 0;
}
