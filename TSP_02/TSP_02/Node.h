// Node.h
#pragma once
#ifndef _NODE_
#define _NODE_

class Node
{
private:
    int node_ID;
    int next_node;     // Next node in solution
    int previous_node; // Node before the current in solution
    double cost_incident; // min cost to arrive to node
    double cost_outgoing; // min cost to leave the node
    int status;          // to mark status: 0=virgin, 1=start, 2=end, 3=embedded (finished)
    int graph;          // ID of sub-graph created from min_travel_array, 0 means not in any graph

public:
	bool init();
	void fill(char s[]);
	void write(char ff[20]);
	int get_node_ID();
	int get_next_node();    
	int get_previous_node();
	int get_status();       
	int get_graph();    
	double get_cost_incident();
	double get_cost_outgoing();

	    
	void set_next_node(int _next_node) ;   
	void set_previous_node(int _previous_node);
	void set_status(int _status) ;      
	void set_graph(int _graph) ;   
	void set_cost_incident(double _cost_incident)     ;
	void set_cost_outgoing(double _cost_outgoing)    ;
};

#endif