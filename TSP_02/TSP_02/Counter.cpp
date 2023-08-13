// Counter.cpp
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#include "Counter.h"

Counter::Counter(void)
{
	Links     = 0;
	Nodes     = 0;
	C_In      = 0.0; 
	C_Out     = 0.0; 
	Graphs    = 0; 
	Live_Graphs  = 0;
	Virgin_Nodes = 0; 
	TSP_Cost_Out = 0.0;
	TSP_Cost_In  = 0.0;
	Sort = 0;
}

Counter::~Counter(void)
{
}

void Counter::init()
{
	Links     = 0;
	Nodes     = 0;
	C_In      = 0.0; 
	C_Out     = 0.0; 
	Graphs    = 0; 
	Live_Graphs  = 0;
	Virgin_Nodes = 0; 
	TSP_Cost_Out = 0.0;
	TSP_Cost_In  = 0.0;
	Sort = 0;
}

void Counter::write(char ff[20])
{
	 ofstream fn;	
	fn.open(ff,ios::app); // open file in append mode
	fn << "Writing Counter to a file:\n";
	fn << "Links  = "        << Links           << '\n';
	fn << "Nodes  = "        << Nodes           << '\n';
	fn << "C_In   = "        << C_In            << '\n';
	fn << "C_Out  = "        << C_Out           << '\n';
	fn << "Graphs = "        << Graphs          << '\n';
	fn << "Live_Graphs  = "  << Live_Graphs     << '\n';
	fn << "Virgin_Nodes = "  << Virgin_Nodes    << '\n';
	fn << "TSP_Cost_Out = "  << TSP_Cost_Out    << '\n';
	fn << "TSP_Cost_In  = "  << TSP_Cost_In     << '\n';
	fn << "Sort = "          << Sort            << '\n';
	fn.close(); 
};

void Counter::link_header(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << "***********************************************************\n";
	fn << "          L I N K     A R R A Y    D A T A \n";
	fn << "***********************************************************\n";
	fn << "    From_Node " << "   To_Node "  <<  "    Length " << '\n';
	fn << "    ========== " << " ========== " <<  " ========== " << '\n';	
	fn.close();
	return;
}

void Counter::node_header(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << "***********************************************************\n";
	fn << "              N O D E    A R R A Y     \n";
	fn << "***********************************************************\n";
	fn << "      Cost in" << "    Previous " << "       ID " ;
	fn << "          Next " << "        Cost out" << "    Status" << "       Graph"  <<'\n';
	fn << "    ========== " << " ========== " <<  " ========== " << "    ========== ";	
	fn << "    ========== " << " ========== " <<  " ========== " << '\n';	
	fn.close();
	return;
}

void Counter::Min_Travel_header_init(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << "*****************************************************************************\n";
	fn << "              M I N     T R A V E L    A R R A Y - Z e r o   V a l u e s     \n";
	fn << "*****************************************************************************\n";
	fn << "      Sort in      Cost in       Previous      ID         Next         Cost out       Sort Out   Cost Travel Sort Travel \n";
	fn << "      =======      ========      ========   ==========   =======      ==========     ==========  =========== =========== \n";
		
	/*
	fn << "      Sort in" ;
	fn << "    Cost in" << "Previous " << "       ID " ;
	fn << "       Next " << "        Cost out" << "         Sort Out" << "Cost Travel"  <<  "Sort Travel"  <<'\n';
	fn << "    ========== " << " ========== " ;	
	fn << "    ========== " << " ========== " <<  " ========== " << "    ========== ";
	fn << "    ========== " << " ========== " <<  " ========== " << '\n';
	*/
	fn.close();
	return;
}

void Counter::Min_Travel_header_same(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << "*****************************************************************************\n";
	fn << "              M I N     T R A V E L    A R R A Y - S A M E   N O D E      \n";
	fn << "*****************************************************************************\n";
	fn << "      Sort in      Cost in       Previous      ID         Next         Cost out       Sort Out   Cost Travel Sort Travel\n";
	fn << "    ========== " << " ========== " ;	
	fn << "    ========== " << " ========== " <<  " ========== " << "    ========== ";
	fn << "    ========== " << " ========== " <<  " ========== " << '\n';	
	fn.close();
	return;
}

void Counter::Min_Travel_header_prevent(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode
	fn << "*****************************************************************************\n";
	fn << " M I N     T R A V E L    A R R A Y - S A M E   N O D E  P r e v e n t e d   \n";
	fn << "*****************************************************************************\n";
	fn << "      Sort in      Cost in       Previous      ID         Next         Cost out       Sort Out   Cost Travel Sort Travel\n";	
	fn << "    ========== " << " ========== " ;	
	fn << "    ========== " << " ========== " <<  " ========== " << "    ========== ";
	fn << "    ========== " << " ========== " <<  " ========== " << '\n';	
	fn.close();
	return;
}

void Counter::write_cost(char ff[20])
{
	 ofstream fn;	
	fn.open(ff,ios::app); // open file in append mode
	fn << "Writing Total Cost:\n";
	fn << "========================"   << '\n';
	fn << "Total Incident Cost  = "        << C_In            << '\n';
	fn << "Total Outgoing Cost  = "        << C_Out           << '\n';
	fn.close(); 
};

double Counter::get_C_In()
{
	return C_In;
};
double Counter::get_C_Out()
{
	return C_Out;
};
double Counter::get_TSP_Cost_Out()
{
	return TSP_Cost_Out;
};
double Counter::get_TSP_Cost_In()
{
	return TSP_Cost_In;
}; 

void Counter::set_C_In(double _C_In)
{
	C_In = _C_In;
};                
void Counter::set_C_Out(double _C_Out)
{
	C_Out = _C_Out;	
};              
void Counter::set_TSP_Cost_Out(double _TSP_Cost_Out)
{
	TSP_Cost_Out = _TSP_Cost_Out;
};  
void Counter::set_TSP_Cost_In(double _TSP_Cost_In)
{
	TSP_Cost_In = _TSP_Cost_In;
}; 