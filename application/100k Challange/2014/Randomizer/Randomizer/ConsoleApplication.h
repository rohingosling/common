//------------------------------------------------------------------------------------------------------------------
// Project:	Generic Console Application Platform (G-CAP).
// Class:	ConsoleApplication
// Version:	1.0
// Date:	2014
// Author:	Rohin Gosling
//
// Description:
//
//   Generic console application platform.
//
//------------------------------------------------------------------------------------------------------------------

#pragma once

#include "stdafx.h"
#include "StaticUtility.h"

#include <string>
#include <vector>

using namespace std;

class ConsoleApplication
{
	//------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//------------------------------------------------------------------------------------------------------------------

	public:

	// ...

	//------------------------------------------------------------------------------------------------------------------
	// Public member data.
	//------------------------------------------------------------------------------------------------------------------

	public:

	// ...


	//------------------------------------------------------------------------------------------------------------------
	// Public methods.
	//------------------------------------------------------------------------------------------------------------------

	public:

	// Constructors and destructors

	ConsoleApplication	( );							// Default constructor.
	ConsoleApplication	( int argc, char* argv [ ] );	// Pass through the command line arguments.
	~ConsoleApplication	( );							// Desctructor.

	// Overloaded functions.

	void Run ( );										// Launches the applcation.

	//------------------------------------------------------------------------------------------------------------------
	// Accessors and mutators
	//------------------------------------------------------------------------------------------------------------------

	// ...


	//------------------------------------------------------------------------------------------------------------------
	// Private member data.
	//------------------------------------------------------------------------------------------------------------------

	private:

	vector <string> commandLine;						// Pupulated using GetCommandLineArguments.


	//------------------------------------------------------------------------------------------------------------------
	// Private methods.
	//------------------------------------------------------------------------------------------------------------------

	private:

	// Cammand line management functions.

	vector <string> GetCommandLineArguments		( int argc, char* argv [ ] );
	virtual void    ExecuteCommandInterpreter	( vector <string> commandLine );
	
	// Application Commands

	void UpdateGameState ( string filePath );
};
