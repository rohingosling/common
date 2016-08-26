//--------------------------------------------------------------------------------------------------------------------------------------
// Project:				100k Challange
// Application Name:	Randomizer1
// Class:               ConsoleApplication
// Version:				1.0
// Author:				Rohin Gosling
//
// Description:
//
//   General purpose console application platform.
//
//--------------------------------------------------------------------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class StaticUtility
{
	//----------------------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//----------------------------------------------------------------------------------------------------------------------------------

public:

	using Natural   = unsigned long;									// N: n Є {  0 ≤ x ≤ ∞  }
	using Integer   = long;												// Z: n Є { -∞ ≤ x ≤ ∞  }
	using Real      = double;											// R:
	using Complex	= struct { Real r; Real i; };						// C:
	using Alignment = enum { ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT };	// Text alignment.
	using TokenList = vector <string>;									// List of token strings.


	//----------------------------------------------------------------------------------------------------------------------------------
	// Public methods.
	//----------------------------------------------------------------------------------------------------------------------------------

public:

	// Constructors and destructors

	StaticUtility ();		// Default constructor.	
	~StaticUtility ();		// Desctructor.

	// General purpose, usefull functions.

	static Natural	 GetMaxLength      ( vector < string > stringList );
	static string	 ToUpper           ( string inputString );
	static string    ReplaceString     ( string inputString, const string& search, const string& replace );
	static TokenList TokenizeCSVString ( string inputString );

	// String conversion functions.

	static string AlignString     ( string text, Integer width, Alignment alignment );
	static string ToAlignedString ( Integer value, Integer width, Alignment alignment );
	static string ToAlignedString ( Real value, Integer precision, Integer width, Alignment alignment );


	//----------------------------------------------------------------------------------------------------------------------------------
	// Accessors and mutators
	//----------------------------------------------------------------------------------------------------------------------------------

	// ...


	//----------------------------------------------------------------------------------------------------------------------------------
	// Public member data.
	//----------------------------------------------------------------------------------------------------------------------------------

public:

	// ...


	//----------------------------------------------------------------------------------------------------------------------------------
	// Private methods.
	//----------------------------------------------------------------------------------------------------------------------------------

private:

	// ...


	//----------------------------------------------------------------------------------------------------------------------------------
	// Private member data.
	//----------------------------------------------------------------------------------------------------------------------------------

private:

	// ...
};

