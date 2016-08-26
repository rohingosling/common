//--------------------------------------------------------------------------------------------------------------------------------------
// Project:	Generic Console Application Platform (G-CAP).
// Version:	1.0
// Date:	2014
// Author:	Rohin Gosling
//
// Description:
//
//   Program entry point.
//
//--------------------------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "ConsoleApplication.h"

#include <iostream>

using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------------------
// Program entry point.
//----------------------------------------------------------------------------------------------------------------------------------------------------------

int main ( int argc, char* argv[] )
{
	// Create a new Soundex application.

	ConsoleApplication application { argc, argv };

	// Launch the application.

	application.run ();

	// Exit application.

	bool pasueBeforeExit = false;

	if ( pasueBeforeExit )
	{
		cout << endl;
		system ( "pause" );
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------------------------------------------