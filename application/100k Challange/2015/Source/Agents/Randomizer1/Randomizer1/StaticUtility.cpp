//--------------------------------------------------------------------------------------------------------------------------------------
// Project:				100k Challange
// Application Name:	Randomizer
// Class:               StaticUtility
// Version:				1.0
// Author:				Rohin Gosling
//
// Description:
//
//   General purpose console application platform.
//
//--------------------------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "StaticUtility.h"

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>


//--------------------------------------------------------------------------------------------------------------------------------------
// Constructor 1.
//--------------------------------------------------------------------------------------------------------------------------------------

StaticUtility::StaticUtility ()
{
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Destructor.
//--------------------------------------------------------------------------------------------------------------------------------------

StaticUtility::~StaticUtility ()
{
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - GetMaxLength
//
// Description:
//
// - Return the length of the longest string in a list of strings.
//
// Arguments:   
//
// - stringList:
//   - A list of strings in the form of a vector.
//   - We will itterate through this list and look for the longest string.
//
// Return Value:
//
// - The length of the longest string in the list.
//
// Pre-Conditions:
//
// - A list of zero or more strings in the form of an STL vector <string>, should be pre-popilated for use.
//
// - In the case of an empty vecotor, the function returns zero.
//   
// Post-Conditions:
//
// - An integer representing the length of the longest string in the vector is returned to the caller.
//
// - The string list it's self is left unchanged.
//
//--------------------------------------------------------------------------------------------------------------------------------------

StaticUtility::Natural StaticUtility::GetMaxLength ( vector < string > stringList )
{
	// Set the length to zero by default.
	// If the list is empty, then the defualt value of 0 is returned.

	StaticUtility::Natural maxLength = 0;

	// For each string elment of the list.
	// - If the length of the string is greater than our current length,
	// - then update the current length to the newly discovered longest length,
	// - else just keep the lenght as it is.

	for each ( string s in stringList )
	{
		maxLength = ( s.length () > maxLength ) ? s.length () : maxLength;
	}

	// Return the longest string length of all strings in the list.

	return maxLength;
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - ToUpper
//
// Description:
//
// - Converts all characters in a string to upper case.
//
// Arguments:   
//
// - inputString:
//   - The string we wish to convert.
//
// Return Value:
//
// - An all upper case copy of inputString..
//
// Pre-Conditions:
//
// - N/A
//   
// Post-Conditions:
//
// - A new copy of the strings is created and converted to an all upper case verions of inputString.
//
//--------------------------------------------------------------------------------------------------------------------------------------

string StaticUtility::ToUpper ( string inputString )
{
	// Create an upper case version of the input string.

	string upperCaseInputString ( inputString );
	transform ( upperCaseInputString.begin (), upperCaseInputString.end (), upperCaseInputString.begin (), toupper );

	return upperCaseInputString;
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - ReplaceString
//
// Description:
//
// - Searches for all occurences of a substring in inputString, and replace all occurances of the found substring
//   with a replacement string.
//
// Arguments:   
//
// - inputString:
//
//   - The string we wish to search and replace with in.
//
//   - We will make a copy of this string, so the original sring used to supply the argument will remain unchanged.
//
// - search:
//
//   - The sub string we wish to search for.
//
// - replace:
//
//   - The string we wish replace teh substring with.
//
//
// Return Value:
//
// - A copy of the input string, with all occureances of search, replaced by, replace.
//
// Pre-Conditions:
//
// - N/A
//   
// Post-Conditions:
//
// - A copy of the input string, with all occureances of search, replaced by, replace.
//
// - The original input string used for the input string argument, will remain unchanged.
//
//--------------------------------------------------------------------------------------------------------------------------------------

string StaticUtility::ReplaceString ( string inputString, const string& search, const string& replace )
{
	size_t pos = 0;

	while ( ( pos = inputString.find ( search, pos ) ) != string::npos )
	{
		inputString.replace ( pos, search.length (), replace );
		pos += replace.length ();
	}

	return inputString;
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - TokenizeCSVString
//
// Description:
//
// - Parse out all the comma seperated sub strings in an input string, and assign
//   them one by one, to a vector.
//
//   Example:
//
//   - inputString  = "One,Two,Three,Four"
//   - outputVector = { "One", "Two", "Three", "Four" }
//
// Arguments:
//
// - inputString:
//
//   The CSV formatted input string to read.
//
// Return Value:
//
// - A vector, who's elements corespond to the CSV fileds of the input string.
//   If the input string is either empty, or if no valid substrings may be
//   found, then the out put vector is returned as an empty vector.
//
// Pre-Conditions:
//
// - The input string must be a valid CSV formated string.
//   No spaces after the delimiter;
//   e.g.
//     "One,Two" is correct
//     "One, Two" is incorrect because of the space after the ',' character.
//   
// Post-Conditions:
//
// - The out put string has been populated with the CSV sub-strings of the input
//   string.
//
//--------------------------------------------------------------------------------------------------------------------------------------

vector <string> StaticUtility::TokenizeCSVString ( string inputString )
{
	vector <string> tokenList;
	string          csvTemp { inputString };
	string          element { "" };
	int             delimiter = 0;

	do
	{
		delimiter = csvTemp.find ( "," );
		element = csvTemp.substr ( 0, delimiter );
		csvTemp = csvTemp.substr ( delimiter + 1, csvTemp.length () - delimiter );

		tokenList.push_back ( element );

	}
	while ( delimiter >= 0 );

	return tokenList;
}


//------------------------------------------------------------------------------
// AlignString.
//------------------------------------------------------------------------------

string StaticUtility::AlignString ( string text, Integer width, Alignment alignment )
{
	string  alignedString    ( "" );    // Initialise the output string to empty to start with. We will build it up as we go.           
	char    paddingCharacter ( 0x20 );	// Some white space character. SPC is usualy a good choice.
	Integer paddingLength    ( 0 );     // Initialize the padding to zero. We will calculate it later as required.        

	// Calculate the padding length.
	// - The padding length will be used as a padding specifier in the case where text.length() <= width.
	// - The padding length will be used as an offset into text, in cases where text.length() > width.

	paddingLength = width - text.length ();

	switch ( alignment )
	{
		case ALIGN_LEFT:
		{
			if ( ( Integer ) text.length () <= width )
			{
				alignedString = text + string ( paddingLength, 0x20 );
			}
			else
			{
				alignedString = text.substr ( 0, width );
			}
		}
		break;

		case ALIGN_RIGHT:
		{
			if ( ( Integer ) text.length () <= width )
			{
				alignedString = string ( paddingLength, 0x20 ) + text;
			}
			else
			{
				alignedString = text.substr ( -paddingLength, width );
			}
		}
		break;

		case ALIGN_CENTER:
		{
			if ( ( Integer ) text.length () <= width )
			{
				alignedString = string ( paddingLength / 2, 0x20 ) + text;
			}
			else
			{
				alignedString = text.substr ( -paddingLength / 2, width );
			}
		}
		break;
	}

	// Return the aligned string.

	return alignedString;
}

//------------------------------------------------------------------------------
// ToAlignedString.
//------------------------------------------------------------------------------

string StaticUtility::ToAlignedString ( Integer value, Integer width, Alignment alignment )
{
	return AlignString ( to_string ( value ), width, alignment );
}

//------------------------------------------------------------------------------
// ToAlignedString.
//
// DEPENDENCIES:
//
//   sstream
//------------------------------------------------------------------------------

string StaticUtility::ToAlignedString ( Real value, Integer precision, Integer width, Alignment alignment )
{
	ostringstream outputString;
	outputString << fixed << setprecision ( precision ) << value;
	return AlignString ( outputString.str (), width, alignment );
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
