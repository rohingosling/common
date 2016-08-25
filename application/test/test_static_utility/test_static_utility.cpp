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
// Apendix A - DLL Managment
//
//   Create a DLL:
//
//     1. Set target configuration type to DLL.
//        Properties\Configuration Properties\General\Configuration Type = “Dynamic Library (.dll)
//     
//     2. Add a namespace to the DLL class.
//     
//     3. Add export symbol to compiler command line.
//        e.g. For the export symbol, “CLASS_NAME_EXPORTS”, then;
//        Properties\Configuration Properties\C/C++\Command Line\Additional Options = “/D CLASS_NAME_EXPORTS”
//     
//     4. Add a #define to the DLL header file, for the export symbol.
//        e.g. For the export symbol, “CLASS_NAME_EXPORTS”, then;
//     
//        #ifdef CLASS_NAME_EXPORTS
//            #define CLASS_NAME_API __declspec ( dllexport ) 
//        #else
//            #define CLASS_NAME_API __declspec ( dllimport ) 
//        #endif
//     
//     5. Apply the export symbol modifier to either the entire class, or selected members.
//
//     6. Specify explicate STL template classes to export before class decleration, where required.
//        e.g. template class __declspec ( dllexport ) std::vector<string>;
//             or
//        e.g. template class CLASS_NAME_API std::vector<string>;
//
//
//   Reference a DLL (Test):
//   
//     1. Create a test application.
//   
//     2. Add a reference to the DLL.
//        Properties\Common Properties\Add New Reference
//   
//     3. Add the DLL’s header file directory to the project.
//        Properties\Configuration Properties\VC++ Directories
//
//
//   Reference a DLL (Implicate Linking):
//   
//     1. Create DLL comsumer application.
//
//     2. Copy both the DLL's .dll and .lib files, in the output folder.
//
//     3. Copy the DLL's header file to the source code folder.
//   
//     4. Add a reference to the LIB file.
//        Properties\Configuration Properties\Linker\Input\Aditional Dependencies = file_name.lib 
//
//
//   Reference a DLL (Explicate Linking):
//
//     1. TODO:
//
//     2. TODO:
//
//--------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "static_utility.h"
#include "stop_clock.h"

#include <iostream>
#include <string>
#include <exception>

#include <Windows.h>
#include <mmsystem.h>

using namespace std;
using namespace common;

//--------------------------------------------------------------------------------------------------
// Data types
//--------------------------------------------------------------------------------------------------

enum class Sound
{
	START,
	STOP,
	EVENT_1,
	EVENT_2
};

enum class TestCase
{
	DEFAULT,
	STATIC_UTILITY_TEST_1,
	STATIC_UTILITY_TEST_2,
	STOP_CLOCK_TEST_1,
	STOP_CLOCK_TEST_2,
};


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
const bool C_SOUND_ENABLED     = true;		// Enable UI audio feedback.


//--------------------------------------------------------------------------------------------------
// Functions Declerations.
//--------------------------------------------------------------------------------------------------

// Program control functions.

void run              ( TestCase test_case );
void exit_application ( bool pasue_before_exit );
void play_sound       ( Sound sound );

// Test case functions. To be called from run.

void program_info               ();
void test_case_default          ();
void test_case_static_utility_1 ();
void test_case_static_utility_2 ();
void test_case_stop_clock_1     ();
void test_case_stop_clock_2     ();


//--------------------------------------------------------------------------------------------------
// C++ main ( Program entry point ).
//--------------------------------------------------------------------------------------------------

int main ( int argc, char* argv[] )
{
	try
	{
		// Execute main program.

		run ( TestCase::STOP_CLOCK_TEST_1 );	
		
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
// - run
//
// DESCRIPTION:
//
// - Application execution function.
// - Launches the main application.
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
// - The application has been executed.
//
//--------------------------------------------------------------------------------------------------

void run ( TestCase test_case )
{	
	program_info ();

	switch ( test_case )
	{
		case TestCase::DEFAULT:					test_case_default ();			break;
		case TestCase::STATIC_UTILITY_TEST_1:	test_case_static_utility_1 ();	break;
		case TestCase::STATIC_UTILITY_TEST_2:	test_case_static_utility_2 ();	break;
		case TestCase::STOP_CLOCK_TEST_1:		test_case_stop_clock_1 ();		break;
		case TestCase::STOP_CLOCK_TEST_2:		test_case_stop_clock_2 ();		break;
	};
}

//--------------------------------------------------------------------------------------------------
// Test Case: Default.
//--------------------------------------------------------------------------------------------------

void program_info ()
{
	cout << endl;
	cout << "PROGRAM: StaticUtility and StopClock test driver." << endl;
	cout << "VERSION: 1.0"                                      << endl;
	cout << "DATE:    2016-03-29"                               << endl;
}

//--------------------------------------------------------------------------------------------------
// Test Case: Default.
//--------------------------------------------------------------------------------------------------

void test_case_default ()
{
	cout << "Hello World!" << endl;
}

//--------------------------------------------------------------------------------------------------
// Test Case: StaticUtility - Test Case 1
//--------------------------------------------------------------------------------------------------

void test_case_static_utility_1 ()
{
	int d { 100 };
	int a { 0 };
	int b { 9 };

	// Test static utility.

	for ( int i = a; i <= b; i++ )
	{
		if ( i == a )
		{
			cout << endl << "S = {";
		}

		cout << i;
						
		if ( (i>=a) && (i<b) )
		{
			cout << ",";
		}
		if ( i == b )
		{
			cout << "}" << endl;
		}
						
		play_sound ( Sound::EVENT_1 );
			
		StaticUtility::sleep ( d );
	}
}

//--------------------------------------------------------------------------------------------------
// Test Case: StaticUtility - Test Case 2
//--------------------------------------------------------------------------------------------------

void test_case_static_utility_2 ()
{
	test_case_default ();
}

//--------------------------------------------------------------------------------------------------
// Test Case: StopClock - Test Case 1
//--------------------------------------------------------------------------------------------------

void test_case_stop_clock_1 ()
{
	// Create an instance of StopClock.

	StopClock clock;

	// Test StopClock.

	StopClock::Time days        = 0;
	StopClock::Time hours       = 0;
	StopClock::Time minutes     = 0;
	StopClock::Time seconds     = 4;
	StopClock::Time miliseconds = 0;
	StopClock::Time t           = StopClock::formated_time_to_ms ( days, hours, minutes, seconds, miliseconds );

	StopClock::Time time_remaining { 0 };

	clock.start ();
	cout << endl;
	cout << "ETA:           " << StopClock::time_to_string ( t                                                         ) << endl;
	cout << "Start Time:    " << StopClock::time_to_string ( clock.get_start_time(), false, true,  true,  true,  true  ) << " GMT" << endl;
	//cout << "               " << StopClock::time_to_string ( clock.get_start_time(), false, false, true,  true,  true  ) << " GMT" << endl;
	//cout << "               " << StopClock::time_to_string ( clock.get_start_time(), false, true,  false, true,  true  ) << " GMT" << endl;
	//cout << "               " << StopClock::time_to_string ( clock.get_start_time(), false, true,  true,  false, true  ) << " GMT" << endl;
	//cout << "               " << StopClock::time_to_string ( clock.get_start_time(), false, true,  true,  true,  false ) << " GMT" << endl;
	//cout << "               " << StopClock::time_to_string ( clock.get_start_time(), false, false, false, false, false ) << " GMT" << endl;	
	//cout << "               " << StopClock::time_to_string ( clock.get_start_time(), false, false, true,  true,  false ) << " GMT" << endl;
	//cout << "               " << StopClock::time_to_string ( clock.get_start_time(), true,  false, false, false, false ) << " GMT" << endl;
	//cout << "               " << StopClock::time_to_string ( clock.get_start_time(), false, true,  false, false, false ) << " GMT" << endl;
	//cout << "               " << StopClock::time_to_string ( clock.get_start_time(), false, false, true,  false, false ) << " GMT" << endl;
	//cout << "               " << StopClock::time_to_string ( clock.get_start_time(), false, false, false, true,  false ) << " GMT" << endl;
	//cout << "               " << StopClock::time_to_string ( clock.get_start_time(), false, false, false, false, true  ) << " GMT" << endl;
	cout << "Elappsed Time: " << StopClock::time_to_string ( clock.get_elapsed_time()                                  ) << endl;
	play_sound ( Sound::START );	

	cout << endl;
	cout << setprecision (2) << fixed;

	while ( clock.get_elapsed_time() < t )
	{
		time_remaining =  t - clock.get_elapsed_time ();

		cout << "Time: [" << StopClock::time_to_string ( clock.get_elapsed_time() ) << "]" << endl;
		cout << "Time components: ";
		cout << StopClock::time_to_days    ( time_remaining ) << " days, ";
		cout << StopClock::time_to_hours   ( time_remaining ) << " hours, ";
		cout << StopClock::time_to_minutes ( time_remaining ) << " min, ";
		cout << StopClock::time_to_seconds ( time_remaining ) << " sec.";
		cout << endl;
		cout << "Time remaining:  ";
		cout << StopClock::get_days         ( time_remaining ) << " days, ";
		cout << StopClock::get_hours        ( time_remaining ) << " hours, ";
		cout << StopClock::get_minutes      ( time_remaining ) << " min, ";
		cout << StopClock::get_seconds      ( time_remaining ) << " sec, ";
		cout << StopClock::get_milliseconds ( time_remaining ) << " mm.";
		cout << endl;
		play_sound ( Sound::EVENT_2 );

		for ( int ti = 0; ti < 5; ti++ )
		{
			cout << ".";			
			play_sound ( Sound::EVENT_1 );
			StaticUtility::sleep ( 80 );
		}
		cout << endl << endl;		
	}

	// Stop the clock.

	clock.stop ();
	cout << endl;
	cout << "Start Time:    " << StopClock::time_to_string ( clock.get_stop_time(), false, true, true, true, true ) << " GMT" << endl;
	cout << "Elappsed Time: " << StopClock::time_to_string ( clock.get_elapsed_time() ) << endl;
	play_sound ( Sound::STOP );
}

//--------------------------------------------------------------------------------------------------
// Test Case: StopClock - Test Case 2
//--------------------------------------------------------------------------------------------------

void test_case_stop_clock_2 ()
{
	test_case_default ();
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
// - play_sound
//
// DESCRIPTION:
//
// - Play sounds, made out of combinations of Windows.h Beep(freequency,period) function calls.
// - The Windows.h Beep function specifies freequency in Hz.
// - The Windows.h Beep function specifies period in ms.
//
// ARGUMENTS:
//
// - sound
//   This is an enum used to specify which sound to play.
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
// - A sound has been played through the computers speaker.
//
//--------------------------------------------------------------------------------------------------

void play_sound ( Sound sound )
{
	if ( C_SOUND_ENABLED )
	{		
		
		int freequency_0  { 10000 };
		int freequency_1  { 11000 };
		int freequency_2  { 12000 };
		int freequency_3  { 13000 };
		int freequency_4  { 14000 };
		int freequency_5  { 15000 };
		int freequency_6  { 16000 };
		int freequency_7  { 17000 };
		int freequency_8  { 18000 };
		int freequency_9  { 19000 };
		int freequency_10 { 20000 };
		int period_45     { 70 };
		int period_80     { 140 };

		switch ( sound )
		{
			case Sound::START:
				Beep ( freequency_0, period_45 );
				Beep ( freequency_2, period_80 );
				break;

			case Sound::STOP:
				Beep ( freequency_2, period_45 );
				Beep ( freequency_0, period_80 );
				break;

			case Sound::EVENT_1:
				Beep ( freequency_8, period_45 );
				break;

			case Sound::EVENT_2:
				Beep ( freequency_1, period_45 );
				break;

			default:
				break;
		}
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
