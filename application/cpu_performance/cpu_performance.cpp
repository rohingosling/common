//--------------------------------------------------------------------------------------------------
// Project:	    Generic Console Application Platform (G-CAP).
// Application: CPU Performance Test
// Class:       N/A
// Version:	    1.0
// Date:	    2016
// Author:	    Rohin Gosling
//
// Description:
//
//   Program entry point.
//
// Implementation Notes:
//
//   1. Write a batch file to import required DLL's.
//      - Batch file name:     import.bat
//      - Batch file location: Source folder.
//
//   2. Add call to import.bat, to Project - Configuration Properties/Build Events/Pre-Buid Event.
//
//   3. Optional, but useful. Add the batch file to the project.
//
//--------------------------------------------------------------------------------------------------

#pragma once

#include "stdafx.h"
#include "application_cpu_performance_test.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <exception>

using namespace std;

//--------------------------------------------------------------------------------------------------
// Constants.
//--------------------------------------------------------------------------------------------------

// Message text.

const string C_MSG_EXCEPTION         = "EXCEPTION: ";
const string C_MSG_UNKNOWN_EXCEPTION = "UNKNOWN EXCEPTION: ";

// System commands.

const string C_CMD_PAUSE = "pause";

// Program control.

const bool C_PAUSE_BEFORE_EXIT = true;		// Set to true in order to pause after execution.

//--------------------------------------------------------------------------------------------------
// Functions Declerations.
//--------------------------------------------------------------------------------------------------

void exit_application ( bool pasue_before_exit );


//--------------------------------------------------------------------------------------------------
// C++ main ( Program entry point ).
//--------------------------------------------------------------------------------------------------

int main ( int argc, char* argv[] )
{
	try
	{
		// Run tests.

		ApplicationCPUPerformanceTest application ( argc, argv );

		application.run ();

		// TODO:
						
		// Exit application.

		exit_application ( C_PAUSE_BEFORE_EXIT );
	}
	catch ( exception& e ) { cout << endl << C_MSG_EXCEPTION << e.what() << endl; }
	catch ( ... )          { cout << endl << C_MSG_UNKNOWN_EXCEPTION     << endl; }

	return 0;
}

//--------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - exit_application
//
// DESCRIPTION:
//
// - Provides a wrapper for any cleanup and termination code.
//
// ARGUMENTS:
//
// - pasue_before_exit
//
//   Boolean flag to specify whether or not to pause the console application before terminating.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - N/A.
//   
// POST-CONDITIONS:
//
// - The application is cleaned up and ready to be terminated.
//
//--------------------------------------------------------------------------------------------------

void exit_application ( bool pasue_before_exit )
{
	if ( pasue_before_exit )
	{
		cout << endl;
		system ( C_CMD_PAUSE.c_str () );
	}
}

//--------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - FunctionName
//
// DESCRIPTION:
//
// - Function descrition.
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
// - N/A.
//   
// POST-CONDITIONS:
//
// - N/A.
//
//--------------------------------------------------------------------------------------------------
