//--------------------------------------------------------------------------------------------------
// Project:	    Generic Console Application Platform (G-CAP).
// Application: N/A
// Class:       N/A
// Version:	    1.1
// Date:	    2014
// Author:	    Rohin Gosling
//
// Description:
//
//   Program entry point.
//
//--------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "math_ml.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <exception>

using namespace std;
using namespace common;

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

		cout << setfill ( '0' ) << setw ( 5 ) << fixed << setprecision ( 3 );

		double s =  1.0 / 2.0;	
		double a = -1.0 - s;
		double b =  1.0 + s;			
		double k =  0.0;

		cout << "sgn(x)" << endl;
		for ( double x = a; x <= b; x += s ) cout << "\tf(" << x << ") \t= " << MathML::sgn ( x ) << endl;
		cout << endl;

		cout << "sgn(x)" << endl;
		for ( double x = a; x <= b; x += s ) cout << "\tf(" << x << ") \t= " << MathML::step ( x ) << endl;
		cout << endl;

		cout << "relu(x)" << endl;
		for ( double x = a; x <= b; x += s ) cout << "\tf(" << x << ") \t= " << MathML::relu ( x ) << endl;
		cout << endl;

		cout << "sigmoid(x)" << endl;
		for ( double x = a; x <= b; x += s ) cout << "\tf(" << x << ") \t= " << MathML::sigmoid ( x ) << endl;
		cout << endl;

		cout << "softplus(x)" << endl;
		for ( double x = a; x <= b; x += s ) cout << "\tf(" << x << ") \t= " << MathML::softplus ( x ) << endl;
		cout << endl;

		k = 4.0;
		cout << "softplus_normal(x," << k << ")" << endl;
		for ( double x = a; x <= b; x += s ) cout << "\tf(" << x << ") \t= " << MathML::softplus_normal ( x, k ) << endl;
		cout << endl;

		cout << "cubic(x)" << endl;
		for ( double x = a; x <= b; x += s ) cout << "\tf(" << x << ") \t= " << MathML::cubic ( x ) << endl;
		cout << endl;

		cout << "Normalized: tanh(x)" << endl;
		for ( double x = a; x <= b; x += s ) cout << "\tf(" << x << ") \t= " << MathML::tanh_normal ( x ) << endl;
		cout << endl;

		k = 1.0;
		cout << "Parameterized Normalized: tanh(x," << k << ")" << endl;
		for ( double x = a; x <= b; x += s ) cout << "\tf(" << x << ") \t= " << MathML::tanh_normal ( x, k ) << endl;
		cout << endl;
				
		a = 0.0;
		b = 1.0;
		s = 0.1;

		cout << "Testing fast square root." << endl;
		cout << "\ty=sqrt(x)\ty=fast_sqrt(x)" << endl;
		for ( double x = a; x <= b; x += s )
		{
			cout << "\t" << (double)  sqrt ( x ) << "\t\t" << (double) MathML::fast_sqrt ( x ) << endl;
		}
		cout << endl;
						
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
