//------------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "ConsoleApplication.h"
#include "StaticUtility.h"
#include "AlphaBetaGameEngine.h"

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

//------------------------------------------------------------------------------------------------------------------
//   Constructor 1.
//------------------------------------------------------------------------------------------------------------------

ConsoleApplication::ConsoleApplication ( )
{
	ConsoleApplication ( 0, nullptr );
}

//------------------------------------------------------------------------------------------------------------------
//   Constructor 2.
//------------------------------------------------------------------------------------------------------------------

ConsoleApplication::ConsoleApplication ( int argc, char* argv [ ] )
{
	// Convert C-style command line argument array, to an STL vector.
	// - If the number of arguments is set to zero, then ignore the command line
	//   arguments.

	if ( argc > 0 )
	{
		this->commandLine = GetCommandLineArguments ( argc, argv );
	}
}

//------------------------------------------------------------------------------------------------------------------
//   Destructor.
//------------------------------------------------------------------------------------------------------------------

ConsoleApplication::~ConsoleApplication ( )
{
}

//------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - Run
//
// DESCRIPTION:
//
// - The Run function is used to launch the application class.
//
// - We use a "run" function, to abscract and isolate execution of an object's,
//   code from any complexities that may be ascociated with configuring and
//   managing the C++ main function.
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
//------------------------------------------------------------------------------------------------------------------

void ConsoleApplication::Run ( )
{
	// Start the timer.

	auto  timerStart = system_clock::now ( );	
	
	// Execute the command line interpreter.

	ExecuteCommandInterpreter ( this->commandLine );

	// Stop the clock and calculate the elappsed time.

	auto timerStop   = system_clock::now ( );		// Stop the timer.
	auto elapsedTime = timerStop - timerStart;		// Calculate file load time.

	// Convert elapsed time to seconds and milliseconds.
	// - Set precision to 3 decimal places.
	// - We will need to use a high precision int to hold the total elapsed time.

	__int64	deltaTime = duration_cast < milliseconds > ( elapsedTime ).count ();
	double	seconds   = deltaTime / 1000.0;

	// Display the elapsed time.

	cout << endl << "  Execution time (seconds): " << seconds << endl;
}

//------------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------

vector <string> ConsoleApplication::GetCommandLineArguments ( int argc, char* argv [ ] )
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

//------------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------

void ConsoleApplication::ExecuteCommandInterpreter ( vector <string> commandLine )
{
	// Configure console message margin.

	string msgMargin ( "  " );
	

	// Compile application info message.

	string msgInfo ( "\n" );

	msgInfo += msgMargin + "PROJECT:  Entelect 100k Challenge.\n";
	msgInfo += msgMargin + "BOT NAME: Randomizer\n";
	msgInfo += msgMargin + "VERSION:  1.0\n";
	msgInfo += msgMargin + "DATE:     2014\n";
	msgInfo += msgMargin + "AUTHOR:   Rohin Gosling\n";
	msgInfo += msgMargin + "USAGE:    randomizer [ File Path ].\n";
	msgInfo += msgMargin + "EXAMPLE:  c:\\> randomizer r:\\projects\\entelect100k\\game.state";

	// Compile Error message.
		
	string msgError ( "\n" );
		
	msgError += msgMargin + "ERROR:\n";
	msgError += msgMargin + "Please specify a valid file path and file name for the game.state file.\n\n";
	msgError += msgMargin + "Example: c:\\> randomizer r:\\projects\\entelect100k\\game.state";

	// Get the number of arguments on the command line, including the command 
	// it's seld.

	int argumentCount = this->commandLine.size ();

	// Execute commands.

	switch ( argumentCount )
	{
		case 1:
			cout << msgInfo << endl;
			break;

		case 2:
			UpdateGameState ( commandLine.at ( 1 ) );
			break;

		default:
			cout << msgError << endl;
			break;
	}
}

//------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - UpdateGameState
//
// DESCRIPTION:
//
// - Implements a solutions for the current game state.
//
// ARGUMENTS:
//
// - filePath
//
//   The file path to the game state.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - The file path must be formatted correctly.
//
// - The game satate file must exsist, and be formatted correctly.
//   
// POST-CONDITIONS:
//
// - A new game sate has been writen to disk.
//
//------------------------------------------------------------------------------------------------------------------

void ConsoleApplication::UpdateGameState ( string filePath )
{
	// Greate a new game grid object.

	AlphaBetaGameEngine pacMan;

	// Load game state.

	pacMan.gameGrid.LoadGameGrid ( filePath );

	// Scan the grid.
	
	pacMan.InitializeUnitsFromGrid ();
	pacMan.playerA.id = 0;
	pacMan.playerB.id = 1;

	// Give our player a handle to the grid so it can scan it it's self.
	// pacMan.playerA.parent = pacMan;

	// Load state data.
	//pacMan.playerA.LoadStateFile ();

	// Calculate next move.
	// pacMan.playerA.HoldDistanceAndLead ( );

	// Save state data.
	//pacMan.playerA.SaveStateFile ( );
	
	// Show the grid.

	system ( "cls" );
	cout << endl << pacMan.gameGrid.GridToString ();

	bool legalMoveA = true;
	bool legalMoveB = true;

	//legalMoveB = pacMan.playerB.Put ( 9, 8, &pacMan.gameGrid );

	//legalMoveA = pacMan.playerA.Put ( 4, 10, &pacMan.gameGrid );		
	legalMoveA = pacMan.playerA.Move ( pacMan.playerB.location [ 0 ].x, pacMan.playerB.location [ 0 ].y, &pacMan.gameGrid );

	

	cout << endl << pacMan.gameGrid.GridToString ( );

	cout << endl;
	cout << "  ";
	cout << "A.Legal Move: " << ( ( legalMoveA == true ) ? "TRUE" : "FALSE" ) << endl;
	cout << "  ";
	cout << "B.Legal Move: " << ( ( legalMoveB == true ) ? "TRUE" : "FALSE" ) << endl;
	

	// Save game state.

	pacMan.gameGrid.SaveGameGrid ( filePath );
}

//------------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------






