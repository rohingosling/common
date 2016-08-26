//--------------------------------------------------------------------------------------------------------------------------------------
// Project:	Generic Console Application Platform (G-CAP).
// Class:	ConsoleApplication
// Version:	1.0
// Date:    2014
// Author:	Rohin Gosling
//
// Descriptio:
//
//   Generic console application platform.
//
//--------------------------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "ConsoleApplication.h"
#include "StaticUtility.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <cctype>

using namespace std;
using namespace std::chrono;	// We will be using some timming functions for measurement.

//--------------------------------------------------------------------------------------------------------------------------------------
//   Constructor 1.
//--------------------------------------------------------------------------------------------------------------------------------------

ConsoleApplication::ConsoleApplication ( )
{
	ConsoleApplication ( 0, nullptr );
}

//--------------------------------------------------------------------------------------------------------------------------------------
//   Constructor 2.
//--------------------------------------------------------------------------------------------------------------------------------------

ConsoleApplication::ConsoleApplication ( int argc, char* argv [ ] )
{
	// Convert C-style command line argument array, to an STL vector.
	// - If the number of arguments is set to zero, then ignore the command line arguments.

	if ( argc > 0 )
	{
		this->commandLine = getCommandLineArguments ( argc, argv );
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
//   Destructor.
//--------------------------------------------------------------------------------------------------------------------------------------

ConsoleApplication::~ConsoleApplication ( )
{
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - Run
//
// DESCRIPTION:
//
// - The Run function is used to launch the application class.
//
// - We use a "run" function, to abscract and isolate execution of an object's, code from any complexities that may
//   be ascociated with configuring and managing the C++ main function.
//
// ARGUMENTS:
//
// - N/A
//
// RETURN VALUE:
//
// - N/A
//
// PRE-CONDITIONS:
//
// - Any class wide global memory requirements have been allocated.
//   
// POST-CONDITIONS:
//
// - The application or object has completed execution.
//
// - All memory allocated by the object, has been de-alocated.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleApplication::run ( )
{
	const string C_EXECUTION_TIME = "  Execution time (seconds): ";

	// Start the timer.

	auto  timerStart = system_clock::now ( );

	// Execute the command line interpreter.

	executeCommandInterpreter ( this->commandLine );

	// Stop the clock and calculate the elappsed time.

	auto timerStop   = system_clock::now ( );		// Stop the timer.
	auto elapsedTime = timerStop - timerStart;		// Calculate file load time.

	// Convert elapsed time to seconds and milliseconds.
	// - Set precision to 3 decimal places.
	// - We will need to use a high precision int to hold the total elapsed time.

	__int64	deltaTime = duration_cast < milliseconds > ( elapsedTime ).count ( );
	double	seconds   = deltaTime / 1000.0;

	// Display the elapsed time.

	cout << endl << C_EXECUTION_TIME << seconds << endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - GetCommandLineArguments
//
// DESCRIPTION:
//
// - Convert the standard C-style command line argument array, to an STL vector.
//
// - We do this in order to simplyfy the task of accessing command line arguments
//   in a more modern coding style that is easier to work with, and less prone to 
//   errors.
//
// ARGUMENTS:
//
// - argc:
//   - The number of command line arguments.
//   - This will always be 1 or more, since the appplication executable command
//     name will always be the first argument in the list.
//
// - argv:
//   - A array of C-style strings that hold the arguments.
//   - The first argument is always the executable command.
//
//     e.g.
//
//       Given a command line program that outputs the sum of two integer arguments.
//
//       | > ADD 1 2
//       |
//       | argc = 3
//       | argv = { "ADD", "1", "2" }
//		 |
//       | Return Value = 1 + 2 = 3
//       |
//       | >
//
// RETURN VALUE:
//
// - A vector containing the command line arguments.
//
// PRE-CONDITIONS:
//
// - The C++ main function must be defined using the argc and argv arguments.
//   
// POST-CONDITIONS:
//
// - A vector containing the command line arguments.
//
//--------------------------------------------------------------------------------------------------------------------------------------

vector <string> ConsoleApplication::getCommandLineArguments ( int argc, char* argv [ ] )
{
	// Create a new vector to hold all the command line arguments.

	vector <string> commandLineArguments;

	// Loop through the standard C-style command line arguments, and add each one to the vector.

	for ( int i = 0; i != argc; i++ )
	{
		commandLineArguments.push_back ( argv [ i ] );
	}

	// Return the new command line argument vector back to the caller.

	return commandLineArguments;
}

//--------------------------------------------------------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleApplication::executeCommandInterpreter ( vector <string> commandLine )
{
	// Configure console message margin.

	string msgMargin ( "  " );


	// Compile application info message.

	string msgInfo ( "\n" );

	msgInfo += msgMargin + "PROJECT:  Entelect 100k Challenge.\n";
	msgInfo += msgMargin + "BOT NAME: Randomizer1\n";
	msgInfo += msgMargin + "VERSION:  1.0\n";
	msgInfo += msgMargin + "DATE:     2015\n";
	msgInfo += msgMargin + "AUTHOR:   Rohin Gosling\n";
	msgInfo += msgMargin + "USAGE:    randomizer [ File Path ].\n";
	msgInfo += msgMargin + "EXAMPLE:  c:\\> randomizer r:\\projects\\entelect100k\\game.state";

	// Compile Error message.

	string msgError ( "\n" );

	msgError += msgMargin + "ERROR:\n";
	msgError += msgMargin + "Please specify a valid file path and file name for the game.state file.\n\n";
	msgError += msgMargin + "Example: c:\\> randomizer r:\\projects\\entelect100k\\game.state";

	// Get the number of arguments on the command line, including the command it's self.

	int argumentCount = this->commandLine.size ( );

	// Execute commands.

	switch ( argumentCount )
	{
		case 1:
			cout << msgInfo << endl;
			break;

		case 2:		
			break;

		default:
			cout << msgError << endl;
			break;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------------------------------------------------------






