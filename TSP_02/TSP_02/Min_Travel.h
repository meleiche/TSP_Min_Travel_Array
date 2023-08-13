// Min_Travel_Array.h
// Graph Class - Graph is a series of connected nodes

#pragma once

class Min_Travel
{
private:
	int node_ID;
	int from_node; // closest incident node 
	int to_node;  // closet node to outgo
	double cost_incident; // min cost to arrive to node
	double cost_outgoing; // min cost to leave the node
	double cost_travel; // sum of ( Cost_Incident + Cost_Outgoing )
	int sort_in; // index for sorting Incident cost, 1 is highest cost
	int sort_out; // index for sorting Outgoing cost, 1 is highest cost
	int sort_travel; // sort for Cost_Travel
public:
	Min_Travel(void);
	~Min_Travel(void);
	void write(char ff[20]);
	void init();

	void set_node_ID(int ID);
	void set_from_node(int _from_node)       ;
	void set_to_node(int _to_node)       ; 
	void set_cost_incident(double _cost_incident)     ;
	void set_cost_outgoing(double _cost_outgoing)    ;
	void set_cost_travel(double _cost_travel)   ;  
	void set_sort_in(int _sort_in)    ;   
	void set_sort_out(int _sort_out) ;     
	void set_sort_travel(int _sort_travel)   ; 

	double get_cost_incident();
	double get_cost_outgoing();
	double get_cost_travel()   ;  

	int get_node_ID();
	int get_from_node()       ;
	int get_to_node()       ; 	
	int get_sort_in()    ;   
	int get_sort_out() ;     
	int get_sort_travel()   ; 

	BOOL check_same_node();
};

