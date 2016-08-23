
#include "stdafx.h"
#include "application_cpu_performance_test.h"

#include <iostream>
#include <string>
#include <chrono>
#include <math.h>

using namespace std;
using namespace std::chrono;

//--------------------------------------------------------------------------------------------------
// Constructor 1/1
//--------------------------------------------------------------------------------------------------

ApplicationCPUPerformanceTest::ApplicationCPUPerformanceTest ( int argc, char* argv [] ) : ConsoleApplication { argc, argv }
{
}

//--------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------

ApplicationCPUPerformanceTest::~ApplicationCPUPerformanceTest ()
{
}

//--------------------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------------------

void ApplicationCPUPerformanceTest::command_interpreter ( vector <string> command_line ) 
{
	// Declare local variables.

	int test_case = 1;

	// Get the number of arguments on the command line, including the command it's self.

	int argument_count { (int) command_line.size () };
	int argument_index { 0 };

	// Execute commands.

	switch ( argument_count )
	{
		case 1:
			switch ( test_case )
			{
				case 0: command_main_program ();	break;
				case 1: command_test_1 ();			break;		
				case 2: command_test_2 ();			break;		
				case 3: command_test_3 ();			break;
			}
			break;

		case 2:			
			break;

		default:			
			break;
	}
}

//--------------------------------------------------------------------------------------------------

void ApplicationCPUPerformanceTest::command_main_program ()
{
	print_program_info ( C_PROGRAM_INFO_NA, C_PROGRAM_INFO_NA, "Main program" );
}

//--------------------------------------------------------------------------------------------------

void ApplicationCPUPerformanceTest::command_test_1 ()
{
	// Test variables.

	const double e = 2.71828182;
	const double π = 3.14159265; 

	double x { 0.0 };
	double y { 0.0 };
	double f { 0.0 };

	// Clock managment variables.

	bool       clock_start                  { true };
	long long  operation_count              { 0 };
	long long  time                         { 0 };
	int        execution_time_hours         { 0 };
	int        execution_time_minutes       { 0 };
	int        execution_time_seconds       { 0 };
	int        execution_time_milliseconds  { 0 };			
	long long  duration_m                   { 0 };
	long long  duration_s                   { 0 };
	long long  duration_ms                  { 0 };	
	long long  elapsed_time                 { 0 };
	long long  heartbeat_elapsed_time       { 0 };
	long long  heartbeat_frequency          { 0 };

	// Configure execution time.
			
	execution_time_hours        = 0;					// Execution time - Set hours.
	execution_time_minutes      = 0;					// Execution time - Set minutes.
	execution_time_seconds      = 10;					// Execution time - Set seconds.
	execution_time_milliseconds = 0;					// Execution time - Set milliseconds.

	heartbeat_frequency         = 500;					// Heart beat frequency in ms.

	// Compute total execution duration in milliseconds.

	duration_m  = execution_time_minutes      + execution_time_hours * 60;
	duration_s  = execution_time_seconds      + duration_m * 60;					
	duration_ms = execution_time_milliseconds + duration_s * 1000;	

	// Execute loop.

	cout << endl << "Test Loop: Duration = " << duration_ms << endl << endl;

	// Initialize test variables.

	x = 0;
	y = 0;

	//cout << "Planned execution duration: " << StaticUtility::time_to_string ( duration_ms ) << endl << endl;	

	operation_count = 0;	
	clock_start     = true;
	steady_clock::time_point timer_start;

	while ( time < duration_ms )
	{
		// Start the timer.

		if ( clock_start ) timer_start = steady_clock::now ();
		//steady_clock::time_point timer_start = steady_clock::now ();

		// Execute test operation.

		//x = 0.5;
		//y = function ( x );
		y = ( 3*x - x*x*x ) / 2;
		//y = -0.5*x*(x*x-3);
		//y = 2/( 1 + exp ( -2*x ) );
		//y = 1/( 1 + exp ( -2*x ) );
		//y = tanh ( π*x );
		//y = sin ( π*x/2 );		
		//y = sqrt ( x );
		//y = fast_sqrt ( x );		

		++x;

		// Update operation count.

		++operation_count;
		

		// Stop the clock and calculate the elappsed time.

		steady_clock::time_point timer_stop = steady_clock::now ();										// Stop the timer.
		steady_clock::duration   duration   = timer_stop - timer_start;									// Calculate elapsed time.
		elapsed_time                        = duration_cast < milliseconds > ( duration ).count ( );	// Convert from duration to an integer.
		

		// Update elapsed time.

		if ( elapsed_time > 0 )
		{
			// Update heartbeat.

			if ( heartbeat_elapsed_time >= heartbeat_frequency )
			{
				cout << "Heartbeat: Operation Count = " << operation_count << "\tOperations / Second = " << 1000 * operation_count / time << endl;
				heartbeat_elapsed_time = 0;				
			}
			else
			{
				heartbeat_elapsed_time += elapsed_time;
			}

			// Update total elapsed time.

			time += elapsed_time;		// Update current time step.
			clock_start = true;
		}
		else
		{
			clock_start = false;
		}
		
	}

	// Report results.

	double operation_count_per_second = (double) operation_count / (double) time;
	operation_count_per_second *= 1000;

	cout << endl << "Operation Count / second: " << (long long) operation_count_per_second << endl;
	cout << endl << "Elapsed Time:             " << common::StopClock::time_to_string ( time ) << endl << endl;
}

//--------------------------------------------------------------------------------------------------

void ApplicationCPUPerformanceTest::command_test_2 ()
{
	double y { 0.0 };
	double x { 0.0 };

	x = 1.0;

	y = test_asm ( x );

	cout << "y = f(x) = " << y << endl;
}

//--------------------------------------------------------------------------------------------------

void ApplicationCPUPerformanceTest::command_test_3 ()
{
}

//--------------------------------------------------------------------------------------------------

double ApplicationCPUPerformanceTest::function ( double x )
{
	// Initialize local variables.
		
	double y { 0.0 };
	double f { 0.0 };

	// Compute function.

	y = ( 3*x - x*x*x ) / 2;

	// Apply domain constraints.

	     if ( x < -1 ) f = -1;
	else if ( x >  1 ) f =  1;
	else               f =  y;

	// Return result.

	return f;
}

//--------------------------------------------------------------------------------------------------

double ApplicationCPUPerformanceTest::fast_sqrt ( double x )
{
	__asm
	{
		FLD		x
		FSQRT
	}
}

//--------------------------------------------------------------------------------------------------

double ApplicationCPUPerformanceTest::test_asm ( double x )
{
	__asm
	{
		FLD		x
		FSQRT
	}
}

//--------------------------------------------------------------------------------------------------

// Overload 1/2

void ApplicationCPUPerformanceTest::print_program_info ()
{
	print_program_info ( C_PROGRAM_INFO_NA, C_PROGRAM_INFO_NA, C_PROGRAM_INFO_NA );
}

// Overload 2/2

void ApplicationCPUPerformanceTest::print_program_info ( string class_name, string function_name, string description )	
{
	cout << endl;

	cout << C_PROGRAM_INFO_PROJECT  << endl;
	cout << C_PROGRAM_INFO_PROGRAM  << endl;
	cout << C_PROGRAM_INFO_VERSION  << endl;
	cout << C_PROGRAM_INFO_DATE     << endl;
	cout << C_PROGRAM_INFO_AUTHOR   << endl;

	if ( class_name.length ()    > 0 ) cout << C_PROGRAM_INFO_CLASS       << class_name    << endl;
	if ( function_name.length () > 0 ) cout << C_PROGRAM_INFO_FUNCTION    << function_name << endl;
	if ( description.length ()   > 0 ) cout << C_PROGRAM_INFO_DESCRIPTION << description   << endl;
}

//--------------------------------------------------------------------------------------------------
