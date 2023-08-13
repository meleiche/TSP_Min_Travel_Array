// TSP_02.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>

#include <windows.h>
#include <Commdlg.h>

//#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "TSP_02.h"
#include "Graph.h"
#include "Link.h"
#include "Min_Travel.h"
#include "Node.h"
#include "General.h"
#include "Counter.h"

using namespace std;


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
char szTitle[MAX_LOADSTRING];					// The title bar text
char szWindowClass[MAX_LOADSTRING];			// the main window class name

char szFileName[MAX_PATH] ="";
Counter Con;
Node *Node_Array;
Link *Link_Array;
Graph *Graph_Array;
Min_Travel *Min_Travel_Array;
HWND hwnd;              // owner window
HANDLE hf;              // file handle
HWND g_hMainDialog = NULL;
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
/*
//-------------------------------------------------------
// Write the input read data to external file
//-------------------------------------------------------
BOOL Write_Input_To_File()
{
	int k1, kk, l;
	char rr[300];
	FILE *log;
	char fn[] = OUTPUT_FILE ;		
	log = fopen(fn, "w");
	kk = Count.Nodes;
	l=0;
	l = strlen(szFileName);
	sprintf_s( rr, 300,  "****************************************************************************************** \n\n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "                  TSP Program  \nVersion 7.0 \nNov 2012       \n\n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "****************************************************************************************** \n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "\n\n\n------------------------------------------------------------------------------------------ \n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "                    I N P U T      D A T A    \n\n\n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "               Name of file data is %s    \n", szFileName);
	fputs(rr, log);
	sprintf_s( rr, 300,  "------------------------------------------------------------------------------------------ \n\n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "Input Array of Nodes \n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "****************************************************************************************** \n");
	fputs(rr, log);
	fclose (log) ;	
	Write_Node_Array();
	Write_Link_Array();
	log = fopen(fn, "a"); // apend
	sprintf_s( rr, 300,  "****************************************************************************************** \n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "				End of  Write_Input_To_File() \n");
	fputs(rr, log);
	sprintf_s( rr, 300,  "****************************************************************************************** \n");
	fputs(rr, log);
	fclose (log) ;
	return TRUE;
}
*/
// *************************************************************************
// Select Data file 
// *************************************************************************
void DoFileSelect(HWND hwnd)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFileName;	
	//ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = "Data Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";	
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "txt";
	if(GetOpenFileName(&ofn))
	{
		SetDlgItemText(g_hMainDialog, IDC_TEXT, szFileName);
		/*hf = CreateFile(ofn.lpstrFile, 
                    GENERIC_READ,
                    0,
                    (LPSECURITY_ATTRIBUTES) NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    (HANDLE) NULL);
					*/
	}
	MessageBox(hwnd, "Done File Select", NULL, NULL);
	return ;
}
/*
void test1() 
{
	char rr[110];
	int i;
    FILE *log;
	char fn[] = OUTPUT_FILE ;
	log = fopen(fn, "a");
	sprintf_s( rr, 110,  "Hellooooo\n");
	fputs(rr, log);
	sprintf_s( rr, 110,  "%s\n", szFileName[MAX_PATH]);
	fputs(rr, log);	
	fclose (log) ;

	return;
}
*/
// *************************************************************************
// Read Data file to count records ONLY
// *************************************************************************
BOOL Count_Records(Counter& Coun)
{
	FILE *inFile;
	errno_t err;
	char buff[MAX_REC_LEN];
	char yy[300];
	//char rr[100];
	char z[] = "z"; //separator between datasets
	int i, flag;
	i = flag = 0;	
	// --------------------------------------------------------------------
	// Open File and Count Number Of Records
	// --------------------------------------------------------------------
	//if(!(inFile = fopen(szFileName, "r")))
	//return 1;
	err  = fopen_s( &inFile, szFileName , "r" );
	if( err == 0 )
	{
		sprintf_s(yy,100, "The file was opened\n");
		MessageBox(hwnd, yy, "i",MB_OK | MB_ICONINFORMATION);
		//printf( "The file 'crt_fopen_s.c' was opened\n" );
	}
	else
	{
		sprintf_s(yy,100, "The file was not opened\n");
		MessageBox(hwnd, yy, "i",MB_OK | MB_ICONINFORMATION);
	}

	while(fgets(buff,sizeof(buff),inFile) != NULL)
	{
		// End of Links data
		if ((buff[0] == z[0]) && (flag == 0))
		{
			Coun.Links = i;
			flag = 1;  			
			sprintf_s(yy,100, "i = %d   links = %d , flag = %d ", i, Coun.Links, flag);
			MessageBox(hwnd, yy, "i",MB_OK | MB_ICONINFORMATION);				
		}
		i++;   		
	}
	
	sprintf_s(yy,250, "i = %d   links = %d  nodes = %d", i, Coun.Links, Coun.Nodes);
	MessageBox(hwnd, yy, "i",MB_OK | MB_ICONINFORMATION);
	Coun.Nodes = (i - Coun.Links - 1); // EOF	
	fclose(inFile);
	sprintf_s(yy,250, "i = %d   links = %d  nodes = %d", i, Coun.Links, Coun.Nodes);
	MessageBox(hwnd, yy, "i",MB_OK | MB_ICONINFORMATION);
	Coun.write(OUTPUT_FILE);
	return TRUE;	
}
/*
// ---------------------------------------------------------------------
// Fill Link record #i
// ---------------------------------------------------------------------
BOOL Fill_Link(char s[], int i)
{
	int  Field, k, flag, j;
	char c1[1] = ";" ;
	char c2[20];

	Field = flag = j = 0;
	Free_Array(c2, 20);
	Link_Array[i].From_Node = 0;
	Link_Array[i].To_Node	= 0;
	Link_Array[i].Length	= 0.0;

	for (k = 0; (k < MAX_REC_LEN -1) && (s[k] != '\0') ; k++)
	{
		if (s[k] == c1[0])
				flag = 1;

		if (flag == 0)
		{
			c2[j] = s[k];
			j++;
		}

		if (flag == 1)
		{
			switch(Field)
			{
				case 0:
					Link_Array[i].From_Node = atoi(c2);
				break;

				case 1:
					Link_Array[i].To_Node = atoi(c2);
				break;
			}
			Free_Array(c2, 20);
			flag = 0;
			j = 0;
			Field++;
		}
	}
	Link_Array[i].Length = atof(c2);
	return TRUE;
}
// ---------------------------------------------------------------------
// Fill Node record #i
// ---------------------------------------------------------------------
BOOL Fill_Node(char s[], int i)
{
	int   k, j;
	char c2[20];

	 k = j = 0;

	for (k = 0; (k < MAX_REC_LEN -1) && (s[k] != '\0') ; k++)
	{
		c2[j] = s[k];
		j++;
	}
	Node_Array[i].Node_ID = atoi(c2);
	Free_Array(c2, 20);

	return TRUE;
}
*/
// *************************************************************************
// Fill & Initialize Node_Array & Link_Array
// *************************************************************************
BOOL Fill_Input_Array(int N, int L)
{
	FILE *inFile;
	errno_t err;
	char line[MAX_REC_LEN];
	char rr[100];
	int i, j, m, flag1, k2;
	i = j = flag1 = k2 = m = 0;
	// --------------------------------------------------------------------
	// Open  Data File
	// --------------------------------------------------------------------
	err  = fopen_s( &inFile, szFileName , "r" );

	i = 0;
	Con.link_header(OUTPUT_FILE);
	while(fgets(line, sizeof(line) ,inFile) != NULL)
	{
		i++;
		 //Link Part
		if ( i  <= L  )
		{
			Link_Array[i-1].fill(line);
			Link_Array[i-1].write(OUTPUT_FILE);
		}
		// Node Part
		if (i == L+1) {Con.node_header(OUTPUT_FILE);}
		if ((i  > (L + 1)) &&  i  <= (L + N + 1)  )
		{
			m = (i  - L - 2);
			Node_Array[m].init();
			Node_Array[m].fill(line);
			Node_Array[m].write(OUTPUT_FILE);
		}
	}

	fclose(inFile);
	sprintf( rr, "Read Finished \n Number of Links = %d \n Number of Nodes = %d" ,L, N );
	MessageBox(hwnd, rr, "Count" ,MB_OK | MB_ICONINFORMATION);
	//Initialize_Node_Array();
	//Block_Diagonal_Cost();
	//Write_Input_To_File();
	return TRUE;

}
// ---------------------------------------------------------------------
// Sum in & out costs
// ---------------------------------------------------------------------
void sum_Min_Travel_in_out()
{
	int i;
	double in, out;
	i = 0;
	in = out = 0.0;
	for (i = 0; i < Con.Nodes ; i++)
	{
		in  += Min_Travel_Array[i].get_cost_incident();
		out += Min_Travel_Array[i].get_cost_outgoing();			
	}
	Con.set_C_In(in);
	Con.set_C_Out(out);
	return;
}
// ---------------------------------------------------------------------
// initialize Min_Travel_Array with node_ID
// ---------------------------------------------------------------------
void write_Min_Travel()
{
	int i;
	i = 0;
	for (i = 0; i < Con.Nodes ; i++)
	{		
		Min_Travel_Array[i].write(OUTPUT_FILE);		
	}	
	//MessageBox(hwnd, "End of Fill_Min_Travel_Array", "Array" ,MB_OK | MB_ICONINFORMATION);
	sum_Min_Travel_in_out();
	Con.write_cost(OUTPUT_FILE);
	return;
}
// ---------------------------------------------------------------------
// initialize Min_Travel_Array with node_ID
// ---------------------------------------------------------------------
void Init_Min_Travel_Array()
{
	int i, node;	
	i  = 0;
	node = 0;		
	for (i = 0; i < Con.Nodes ; i++)
	{
		node = Node_Array[i].get_node_ID();
		Min_Travel_Array[i].init();
		Min_Travel_Array[i].set_node_ID(node);
		//Min_Travel_Array[i].write(OUTPUT_FILE);		
	}
	Con.Min_Travel_header_init(OUTPUT_FILE);
	write_Min_Travel();
	//sum_Min_Travel_in_out();
	//Con.write_cost(OUTPUT_FILE);
	return;
}
// ---------------------------------------------------------------------
// Compute Min Travel Cost for each node
// Prevent that incident node is the outgoing node
//
// ---------------------------------------------------------------------
BOOL Fill_Min_Travel_Array()

{
	int i, j, node, aa, bb, tt, ff;
	double d, t, t1, t2, dd;
	ofstream fn;

	i = j = 0;
	node = tt = ff = aa = bb = 0;
	t = t1 = t2 = dd = 0.0;
	// Fill the incident side of min Travel Array
	//MessageBox(hwnd, "Start of Fill_Min_Travel_Array", "Array" ,MB_OK | MB_ICONINFORMATION);
	for (i = 0; i < Con.Nodes ; i++)
	{		
		// Fill the incident side of min Travel Array
		d = (double) INFINITY;
		node = Node_Array[i].get_node_ID();
		for (j = 0; j < Con.Links ; j++)
		{
			aa = Link_Array[j].get_To_Node();
			bb = Link_Array[j].get_From_Node();
			dd = Link_Array[j].get_Length();
			if (node == aa && dd < d)
			{
				d = dd;
				Min_Travel_Array[node-1].set_from_node(bb);
			}
		} 
		Min_Travel_Array[node-1].set_cost_incident(d);

		// Fill the outgoing side of min Travel Array
		d = (double) INFINITY;
		for (j = 0; j < Con.Links ; j++)
		{
			aa = Link_Array[j].get_To_Node();
			bb = Link_Array[j].get_From_Node();
			dd = Link_Array[j].get_Length();
			if (node == bb && dd < d)
			{
				d = dd;
				Min_Travel_Array[node-1].set_to_node(aa);
			}
		} 
		Min_Travel_Array[i].set_cost_outgoing(d);	

		//while (Check_Same_Node(i) )   Prevent_Same_Node(i);

		t1 = 	Min_Travel_Array[i].get_cost_outgoing()  ;
		t2 = 	Min_Travel_Array[i].get_cost_incident();
		t = 	t1 + t2 ;
		Min_Travel_Array[i].set_cost_travel(t);
	} 

	// Write Min_Travel_Array to File
	Con.Min_Travel_header_same(OUTPUT_FILE);
	write_Min_Travel();
	/*
	for (i = 0; i < Con.Nodes ; i++)
	{		
		Min_Travel_Array[i].write(OUTPUT_FILE);		
	}	
	//MessageBox(hwnd, "End of Fill_Min_Travel_Array", "Array" ,MB_OK | MB_ICONINFORMATION);
	sum_Min_Travel_in_out();
	Con.write_cost(OUTPUT_FILE);
	*/
	fn.open(OUTPUT_FILE,ios::app); // open file in append mode
	fn <<  "            >>>>>>>     End of:  Fill_Min_Travel_Array()  \n"  ;
	fn.close();
	return TRUE;
}
// ---------------------------------------------------------------------
// Change the incident and outgoing nodes
// The selected node is available for join according to its staus
// ---------------------------------------------------------------------
void Prevent_Same_Node(int node)
{	
	int j, f, first, second_in, second_out, cc;
	double d, first_cost_in, first_cost_out, second_in_cost, second_out_cost, c1, c2, c3 ;
	ofstream fn;	
	
	second_in = second_out = f = cc = 0;
	second_in_cost = second_out_cost = c1 = c2 = c3 = 0.0 ;
	
	first = Min_Travel_Array[node-1].get_from_node() ;
	first_cost_in = Min_Travel_Array[node-1].get_cost_incident();
	first_cost_out = Min_Travel_Array[node-1].get_cost_outgoing();	
		
	// Fill the incident side of min Travel Array
	d = (double) INFINITY;
	for (j = 0; j < Con.Links ; j++)
	{
		if ( (node == Link_Array[j].get_To_Node() )   &&
			 (Link_Array[j].get_From_Node() != first) &&
			 (Link_Array[j].get_Length() < d)
			) 
		{
			d = Link_Array[j].get_Length();
			second_in = Link_Array[j].get_From_Node();
		}
		
	}
	second_in_cost = d;

	// Fill the outgoing side of min Travel Array
	d = (double) INFINITY;
	for (j = 0; j < Con.Links ; j++)
	{
		if ( (node == Link_Array[j].get_From_Node() ) &&
			 (Link_Array[j].get_To_Node() != first)   &&
			 (Link_Array[j].get_Length() < d)
			) 
		{
			d = Link_Array[j].get_Length();
			second_out = Link_Array[j].get_To_Node();
		}
	}
	second_out_cost = d; 		
	
	// first in && second out
	c1 = first_cost_in + second_out_cost;
	// second_in && first out
	c2 = second_in_cost + first_cost_out;	
	// second_in && second out
	c3 = second_in_cost + second_out_cost;

	if ( (c1 <= c2) && (c1 <= c3)  )   cc = 1	  ;
	if ( (c2 <  c1) && (c2 <  c3)  )   cc = 2	  ;
	if ( (c3 <  c1) && (c3 <  c2)  )   cc = 3	  ;

	fn.open(OUTPUT_FILE,ios::app); // open file in append mode
	fn <<  "Node Same = " << node << "  \n"  ;	
	fn <<  "         first_cost_in = " << first_cost_in ;
	fn <<  "         first_cost_out = " << first_cost_out 	<< "  \n"  ;
	fn <<  "         second_in_cost = " << second_in_cost ;
	fn <<  "         second_out_cost = " << second_out_cost 	<< "  \n"  ;
	fn <<  "         cc = " << cc 	<< "  \n"  ;
	fn.close();

	if ( cc == 1 )
	{
		Min_Travel_Array[node-1].set_from_node(first);
		Min_Travel_Array[node-1].set_to_node(second_out);
		Min_Travel_Array[node-1].set_cost_incident(first_cost_in);
		Min_Travel_Array[node-1].set_cost_outgoing(second_out_cost);
	}

	// second_in && first out
	if ( cc == 2 )
	{
		Min_Travel_Array[node-1].set_from_node(second_in);
		Min_Travel_Array[node-1].set_to_node(first);
		Min_Travel_Array[node-1].set_cost_incident(second_in_cost);
		Min_Travel_Array[node-1].set_cost_outgoing(first_cost_out);
	}

	// second_in && second out
	if ( cc == 3 )
	{
		Min_Travel_Array[node-1].set_from_node(second_in);
		Min_Travel_Array[node-1].set_to_node(second_out);
		Min_Travel_Array[node-1].set_cost_incident(second_in_cost);
		Min_Travel_Array[node-1].set_cost_outgoing(second_out_cost);
	}		
	
	return ;
}
// ---------------------------------------------------------------------
// Min Travel Array - same-node prevented
// ---------------------------------------------------------------------
void Min_Initial()
{
	int i, node;	
	ofstream fn;

	i  = 0;
	node = 0;		
	for (i = 0; i < Con.Nodes ; i++)
	{
		node = 	Min_Travel_Array[i].get_node_ID();
		//fn.open(OUTPUT_FILE,ios::app); // open file in append mode		
		//fn <<  "  \n"  << "*** Node  = " << node   ;
		//fn.close();
		if (Min_Travel_Array[i].check_same_node()) 	
		{
			fn.open(OUTPUT_FILE,ios::app); // open file in append mode		
			fn <<  " >>>>> XXX       Node  = " << node << "  \n"  ;
			fn.close();
			Prevent_Same_Node(node)  ;
		}
	}
	
	Con.Min_Travel_header_prevent(OUTPUT_FILE);
	write_Min_Travel();	
	
	return;
}
// *************************************************************************
// Main function to solve problem
// *************************************************************************
void Run()
{
	DoFileSelect(hwnd);	
	Con.init();
	Count_Records(Con);
	Con.write(OUTPUT_FILE);
	Node_Array = new Node[Con.Nodes];
	Link_Array  = new Link[Con.Links];
	Min_Travel_Array = new Min_Travel[Con.Nodes];
	Fill_Input_Array(Con.Nodes, Con.Links);
	Init_Min_Travel_Array();
	Fill_Min_Travel_Array();
	Min_Initial();
	return;
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	 	// TODO: Place code here.
 /*
	  //char fn[] = OUTPUT_FILE ;
	  ofstream fout(OUTPUT_FILE);
	  fout << "Writing this to a file 8.\n";	
	  fout << "DDD = "  << "\n";
	  fout << endl;
	  
	  fout << endl;
	  fout << "szFileName =" << ((void*)szFileName);
	  fout << endl;
	  fout.close();

	  for (i=0;i<=100; i++ ) 
	  {	  
		//fn << szFileName[i];
		  fn << DDD[i];
	  }
	  //fn.write((char *)&szFileName, sizeof(szFileName));
	   fn << endl;
	  fn << "File NAme:" << endl;
	
	  fn << endl;
	  fn << *szFileName;
	  fn << endl;


	  fn.close();

	  Node nn1;
	  //Counter Count;
	  nn1.init();
	  nn1.write(OUTPUT_FILE);
	  Con.write(OUTPUT_FILE);
	  

	char rr[300];
	//char *www[MAX_PATH] = ((void *)szFileName);
	int i;
    FILE *log;
	char fn[] = OUTPUT_FILE ;
	log = fopen(fn, "a");
	sprintf_s( rr, 300,  "hiiiiiiiiiiiii\n");
	fputs(rr, log);
	//sprintf_s( rr, 110,  "%p\n", &szFileName);
	sprintf_s( rr, 300, "*szFileName(p,s,c): 1)%p 2)%s 3)%c END\n", ((void *)(szFileName+2)), *szFileName, *szFileName);
	fputs(rr, log);  
	sprintf_s( rr, 300, "\n szFileName(c,s,p): 1)%c 2)%s 3)%p END\n",  szFileName+1,  szFileName,  szFileName);
	fputs(rr, log);
	sprintf_s( rr, 300, "&szFileName(c,s,p): 1)%c 2)%s 3)%p END\n", &szFileName, &szFileName, &szFileName);
	fputs(rr, log);
	
	fclose (log) ;
	
	for (i=0;i<=100; i++ ) 
	  {	  
		sprintf_s( rr, 300,  "%C",);
		 fputs(rr, log);
	}
	for (i=0;i<=100; i++ ) 
	  {	  
		sprintf_s( rr, 300,  "%10.3f      (%6d) ");
		 fputs(rr, log);
	  }

*/
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TSP_02, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TSP_02));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TSP_02));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TSP_02);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_File_Select:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			Run();			
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		{
			
			return (INT_PTR)TRUE;
		}

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
