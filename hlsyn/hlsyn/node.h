//node.h

#include <string>
#include <vector>

using namespace std;

/*
Node Class
	Properties:
		1. Operation Type (str)
		2. inputs	(vector<str>)
		3. outputs	(vector<str>)
		4. ASAP TIME
		5. ALAP TIME
		6. TIME FRAME WIDTH
		7. SCHEDULED TIME
		8. CYCLE DELAY

*/


class Node {
public:
	
	//properties
	string operation;

	int ASAPStart;
	int ALAPStart;
	int width;			//ALAP-ASAP+1
	int scheduledTime;	//scheduled time determined by FDS
	int cycleDelay;		//number of cycles required for operation

	vector<string> nodeInputs;	
	string nodeOutput;

	vector<Node*> predecessors;
	vector<Node*> succesors;



	//methods

	Node(string op);
	~Node();

	
	void newInput(string input);
	void newOutput(string output);
	
	void addPred(Node* p);
	void addSucc(Node* s);


private:
	void setCycleDelay(string op);

};
