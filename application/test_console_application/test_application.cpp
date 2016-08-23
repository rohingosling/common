//--------------------------------------------------------------------------------------------------
// Project:	    Generic Console Application (G-Cap).
// Application: Console application test.
// Class:	    TestApplication
// Version:	    1.0
// Date:	    2015
// Author:	    Rohin Gosling
//
// Description:
//
//   Test class, used to test teh console application framework.
//
//--------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "test_application.h"

#include <iostream>
#include <string>

using namespace std;

//--------------------------------------------------------------------------------------------------
// Constructor 1/1
//--------------------------------------------------------------------------------------------------

TestApplication::TestApplication ( int argc, char* argv [] ) : ConsoleApplication { argc, argv }
{
}

//--------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------

TestApplication::~TestApplication ()
{
}

//--------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - ExecuteCommandInterpreter
//
// DESCRIPTION:
//
// - Execute commands passed in through the command line.
//
// - ExecuteCommandInterpreter should be overloaded in a derived class, and not
//   called directly.
//
//   1. Extend ConsoleApplication.
//   2. Overload ExecuteCommandInterpreter() to implement commands.
//   3. Call an instance of the derived class in Main.cpp.
//
// ARGUMENTS:
//
// - N/A
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - N/A
//   
// POST-CONDITIONS:
//
// - The apropriate commands, as defined in a derived class, have been executed.
//
//--------------------------------------------------------------------------------------------------

void TestApplication::command_interpreter ( vector <string> command_line ) 
{
	// Declare local variables.

	int test_case { 0 };
	int x         { 0 };

	// Get the number of arguments on the command line, including the command it's self.

	int argument_count { (int) command_line.size () };
	int argument_index { 0 };

	// Execute commands.

	switch ( argument_count )
	{
		case 1:
			switch ( test_case )
			{
				case 0: command_main_program ();	break;
				case 1: command_test_1 ();			break;		// Test 2D vector element ordering for weight amtrix.
				case 2: command_test_2 ();			break;		// Test Layer.
				case 3: command_test_3 ();			break;
			}
			break;

		case 2:	
			x = atoi ( command_line [ 1 ].c_str () );
			cout << endl << x*x << endl;
			break;

		default:			
			break;
	}
}

//--------------------------------------------------------------------------------------------------

void TestApplication::command_main_program ()
{
	print_program_info ( C_PROGRAM_INFO_NA, C_PROGRAM_INFO_NA, "Main program" );
}

//--------------------------------------------------------------------------------------------------

void TestApplication::command_test_1 ()
{	
	cout << endl << "COMMAND: Test #1" << endl;
}

//--------------------------------------------------------------------------------------------------

void TestApplication::command_test_2 ()
{
	cout << endl << "COMMAND: Test #2" << endl;
}

//--------------------------------------------------------------------------------------------------

void TestApplication::command_test_3 ()
{
	cout << endl << "COMMAND: Test #3" << endl;
}

//--------------------------------------------------------------------------------------------------

// Overload 1/2

void TestApplication::print_program_info ()
{
	print_program_info ( C_PROGRAM_INFO_NA, C_PROGRAM_INFO_NA, C_PROGRAM_INFO_NA );
}

// Overload 2/2

void TestApplication::print_program_info ( string class_name, string function_name, string description )	
{
	cout << endl;

	cout << C_PROGRAM_INFO_PROJECT  << endl;
	cout << C_PROGRAM_INFO_PROGRAM  << endl;
	cout << C_PROGRAM_INFO_VERSION  << endl;
	cout << C_PROGRAM_INFO_DATE     << endl;
	cout << C_PROGRAM_INFO_AUTHOR   << endl;

	if ( class_name.length ()    > 0 ) cout << C_PROGRAM_INFO_CLASS       << class_name    << endl;
	if ( function_name.length () > 0 ) cout << C_PROGRAM_INFO_FUNCTION    << function_name << endl;
	if ( description.length ()   > 0 ) cout << C_PROGRAM_INFO_DESCRIPTION << description   << endl;
}

//--------------------------------------------------------------------------------------------------

