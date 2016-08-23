
#pragma once

#include "console_application.h"
#include "static_utility.h"
#include "stop_clock.h"

using namespace std;
using namespace common;

class ApplicationCPUPerformanceTest :	public ConsoleApplication
{
	//--------------------------------------------------------------------------------------------------
	// Constants
	//--------------------------------------------------------------------------------------------------

public:

	// Program information.

	const string C_PROGRAM_INFO_PROJECT     = "PROJECT     : CPU Performance Test";
	const string C_PROGRAM_INFO_PROGRAM     = "PROGRAM     : cpu_performance.exe (CPU Perfermance Test)";
	const string C_PROGRAM_INFO_VERSION     = "VERSION     : 1.0";
	const string C_PROGRAM_INFO_DATE        = "DATE        : 2016-02-14";
	const string C_PROGRAM_INFO_AUTHOR      = "AUTHOR      : Rohin Gosling";
	const string C_PROGRAM_INFO_CLASS       = "CLASS       : TestApplication";	
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

	ApplicationCPUPerformanceTest ( int argc, char* argv [] );
	~ApplicationCPUPerformanceTest ();

	// Overriden functions.

	virtual void command_interpreter ( vector <string> command_line ) override;

	// Application commands.

	void command_main_program ();
	void command_test_1       ();
	void command_test_2       ();
	void command_test_3       ();

	// Test functions.

	double function  ( double x );
	double fast_sqrt ( double x );
	double test_asm  ( double x );
	
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

