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
//   Test class, used to test the console application framework.
//
//--------------------------------------------------------------------------------------------------

#pragma once

#include "console_application.h"

using namespace std;
using namespace common;

class TestApplication :	public ConsoleApplication
{
	//--------------------------------------------------------------------------------------------------
	// Constants
	//--------------------------------------------------------------------------------------------------

public:

	// Program information.

	const string C_PROGRAM_INFO_PROJECT     = "PROJECT     : Console Application Test";
	const string C_PROGRAM_INFO_PROGRAM     = "PROGRAM     : test.exe (Console Application Test program)";
	const string C_PROGRAM_INFO_VERSION     = "VERSION     : 1.0";
	const string C_PROGRAM_INFO_DATE        = "DATE        : 2016-01-25";
	const string C_PROGRAM_INFO_AUTHOR      = "AUTHOR      : Rohin Gosling";
	const string C_PROGRAM_INFO_CLASS       = "CLASS       : ";	
	const string C_PROGRAM_INFO_FUNCTION    = "FUNCTION    : ";	
	const string C_PROGRAM_INFO_DESCRIPTION = "DESCRIPTION : ";
	const string C_PROGRAM_INFO_NA          = "N/A";

private:
	
	// ...

	//--------------------------------------------------------------------------------------------------
	// Data type aliases
	//--------------------------------------------------------------------------------------------------

public:

	// ...

	//--------------------------------------------------------------------------------------------------
	// Functions.
	//--------------------------------------------------------------------------------------------------

public:

	// Constructors and destructors

	TestApplication ( int argc, char* argv [] );
	~TestApplication ();

	// Overriden functions.

	virtual void command_interpreter ( vector <string> command_line ) override;

	// Application commands.

	void command_main_program ();
	void command_test_1       ();
	void command_test_2       ();
	void command_test_3       ();
	
	// Display functions.

	void print_program_info ();	
	void print_program_info ( string class_name, string function_name, string description );	
		
private:

	// ...

	//--------------------------------------------------------------------------------------------------
	// Accessors and mutators
	//--------------------------------------------------------------------------------------------------

	// Accessors

	// ...

	// Mutators.

	// ...

	//--------------------------------------------------------------------------------------------------
	// Member data.
	//--------------------------------------------------------------------------------------------------

public:

	// ...
	
private:

	// ...
};

