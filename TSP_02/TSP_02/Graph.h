#pragma once
class Graph
{
private:
	int ID;
	int start_node;   
	int end_node;
	double cost_incident; // min cost to arrive to start-node
	double cost_outgoing; // min cost to leave the end-node
	double cost_travel; // Cost_Incident + Cost_Outgoing
	int from_node; // to be joined to the start-node
	int to_node;  // to be joined to the end-node
	int sort; // sort graph rank
	int sort_in;  // rank of overall new nodes
	int sort_out; // rank of overall new nodes
public:
	Graph(void);
	~Graph(void);
	void init();
	void write(char ff[20]);
};

