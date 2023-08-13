//Min_Travel.cpp
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#include "Min_Travel.h"
using namespace std;


Min_Travel::Min_Travel(void)
{
}


Min_Travel::~Min_Travel(void)
{
}

void Min_Travel::init()
{
	node_ID        = 0;         
	from_node      = 0;         
	to_node        = 0;         
	cost_incident  = 0.0;         
	cost_outgoing  = 0.0;         
	cost_travel    = 0.0;         
	sort_in        = 0;         
	sort_out       = 0;         
	sort_travel    = 0;   
	return;
}

//******************************************************
// Write the Node_Min_Travel_Array to external file
//******************************************************
void Min_Travel::write(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode

	fn.setf(ios::right);
	fn.width(10);	
	fn << sort_in  ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);	
	fn << cost_incident  ;
	
	fn << "    ";
	fn.setf(ios::right);
	fn.width(10);
	fn << from_node ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << node_ID ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << to_node ;
	
	fn << "     ";
	fn.setf(ios::right);
	fn.width(10);
	fn << cost_outgoing ;

	fn << "     ";
	fn.setf(ios::right);
	fn.width(10);
	fn << sort_out ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << cost_travel ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << sort_travel << '\n';

	fn.close();
	return;
};

void Min_Travel::set_node_ID(int ID)
{
	node_ID = ID;
	return;
};

void Min_Travel::set_from_node(int _from_node)
{
	from_node = _from_node;
	return;
};

void Min_Travel::set_to_node(int _to_node)
{
	to_node = _to_node;
	return;
};

void Min_Travel::set_cost_incident(double _cost_incident)
{
	cost_incident = _cost_incident;
	return;
};

void Min_Travel::set_cost_outgoing(double _cost_outgoing)
{
	cost_outgoing = _cost_outgoing;
	return;
};

void Min_Travel::set_cost_travel(double _cost_travel)
{
	cost_travel = _cost_travel;
	return;
};

void Min_Travel::set_sort_in(int _sort_in)
{
	sort_in = _sort_in;
	return;
};

void Min_Travel::set_sort_out(int _sort_out)
{
	sort_out = _sort_out;
	return;
};

void Min_Travel::set_sort_travel(int _sort_travel)
{
	sort_travel = _sort_travel;
	return;
};

double Min_Travel::get_cost_incident()
{
	return cost_incident;
	
};

double Min_Travel::get_cost_outgoing()
{
	return cost_outgoing;
};

double Min_Travel::get_cost_travel()
{
	return cost_travel;
};

int Min_Travel::get_node_ID()
{
	return node_ID;
};

int Min_Travel::get_from_node()
{
	return from_node;
};

int Min_Travel::get_to_node()
{
	return to_node ;
};

int Min_Travel::get_sort_in()
{
	return sort_in;
};

int Min_Travel::get_sort_out()
{
	return sort_out;
};

int Min_Travel::get_sort_travel()
{
	return sort_travel ;
};

// ---------------------------------------------------------------------
// Check that incident_node == outgoing_node
// ---------------------------------------------------------------------
BOOL Min_Travel::check_same_node()
{
	if ( from_node == to_node )
		return TRUE ;
	return FALSE ;
}