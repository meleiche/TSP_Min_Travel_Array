// Node.cpp
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#include "Node.h" // Class definition



bool Node::init()
{
	node_ID    = 0;
	next_node  = 0;    
	previous_node = 0; 
	cost_incident = 0.0;
	cost_outgoing = 0.0;
	status = 0;         
	graph  = 0;          
	return true;
};

void Node::write(char ff[20])
{
	ofstream fn;
	fn.open(ff,ios::app); // open file in append mode

	fn.setf(ios::right);
	fn.width(10);	
	fn << cost_incident  ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);	
	fn << previous_node  ;
	
	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << node_ID ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << next_node ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << cost_outgoing ;
	
	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << status ;

	fn << "  ";
	fn.setf(ios::right);
	fn.width(10);
	fn << graph << '\n';

	fn.close();
	return;
};

void Node::fill(char s[])
{
	int   k, j;
	char c2[20];

	k = j = 0;	

	for (k = 0; (k < 200) && (s[k] != '\0') ; k++)
	{
		c2[j] = s[k];
		j++;
	}
	node_ID = atoi(c2);
	return ;
}

int Node::get_node_ID()
{
	return node_ID;
};

int Node::get_next_node()
{
	return next_node;
};

int Node::get_previous_node()
{
	return previous_node;
};

int Node::get_status()
{
	return status;
};

int Node::get_graph()
{
	return graph;
};

double Node::get_cost_incident()
{
	return cost_incident;
	
};

double Node::get_cost_outgoing()
{
	return cost_outgoing;
};

void Node::set_next_node(int _next_node)
{
	next_node = _next_node;
	return;
};

void Node::set_previous_node(int _previous_node)
{
	previous_node = _previous_node;
	return;
};

void Node::set_status(int _status)
{
	status = _status;
	return;
};

void Node::set_graph(int _graph)
{
	graph = _graph;
	return;
};

void Node::set_cost_incident(double _cost_incident)
{
	cost_incident = _cost_incident;
	return;
};

void Node::set_cost_outgoing(double _cost_outgoing)
{
	cost_outgoing = _cost_outgoing;
	return;
};
