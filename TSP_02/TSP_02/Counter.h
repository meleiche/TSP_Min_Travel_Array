// Counter.h
#pragma once
class Counter
{
public:
	int Links;
	int Nodes;
	
private:
	double C_In;  // sum of incident cost
	double C_Out; // sum of outgoing cost
	int Graphs;   // number of graphs
	int Live_Graphs; // number of existing graphs after solution
	int Virgin_Nodes; // nodes with status == 0 & Graph == 0
	double TSP_Cost_Out;
	double TSP_Cost_In;
	int Sort;
public:
	Counter(void);
	~Counter(void);
	void init();
	void write(char ff[20]);
	void write_cost(char ff[20]);
	void link_header(char ff[20]);
	void node_header(char ff[20]);
	void Min_Travel_header_init(char ff[20]);
	void Min_Travel_header_same(char ff[20]);
	void Min_Travel_header_prevent(char ff[20]);
	double get_C_In();                
    double get_C_Out();              
    double get_TSP_Cost_Out();  
    double get_TSP_Cost_In(); 

	void set_C_In(double _C_In);                
    void set_C_Out(double _C_Out);              
    void set_TSP_Cost_Out(double _TSP_Cost_Out);  
    void set_TSP_Cost_In(double _TSP_Cost_In); 

	//BOOL Count_Records();
	
};

