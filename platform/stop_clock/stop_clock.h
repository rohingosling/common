//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// Project:	    Common Console Platform (CCP)
// Class:	    StopClock
// Version:	    1.0
// Date:	    2015
// Author:	    Rohin Gosling
//
// Description:
//
//   StopClock is a stopwatch inspired clock and timming class.
//   - StopClock offers functions to easily and neatly strack and measure time, measured in miliseconds.
//   - Underlying clock API is the C++11 crono.h library.
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
//     5. Optional:
//        Add distribution batch file's to automate distribution of built DLL's, LIB's and H files.
//        Properties\Configuration Properties\Build Events\Post-Build Events
//
//
//   Reference a DLL (Explicate Linking):
//
//     1. TODO:
//
//     2. TODO:
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// DLL managment.
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifdef STOP_CLOCK_EXPORTS
	#define STOP_CLOCK_API __declspec ( dllexport ) 
#else
	#define STOP_CLOCK_API __declspec ( dllimport ) 
#endif

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// Include files.
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"

#include <string>


//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// Namespace
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

using namespace std;

namespace common
{
	//----------------------------------------------------------------------------------------------------------------------------------------------------------
	// Class
	//----------------------------------------------------------------------------------------------------------------------------------------------------------

	class STOP_CLOCK_API StopClock
	{
		//------------------------------------------------------------------------------------------------------------------------------------------------------
		// Constants
		//------------------------------------------------------------------------------------------------------------------------------------------------------

	public:

		// ...

	private:

		// ...		

		//------------------------------------------------------------------------------------------------------------------------------------------------------
		// Data types and aliases
		//------------------------------------------------------------------------------------------------------------------------------------------------------

	public:

		using Time       = unsigned long long;		// system time in miliseconds.
		using AnalogTime = double;					// Fractional expresion of milisecond time, as seconds, minutes, hours, or days.

		//------------------------------------------------------------------------------------------------------------------------------------------------------
		// Functions.
		//------------------------------------------------------------------------------------------------------------------------------------------------------

	public:

		// Constructors and destructors.

		StopClock ();
		~StopClock ();

		// Clock control functions.

		Time        start            ();		// Start the clock and return the system time at which the clock was started.
		Time        stop             ();		// Stop the clock and return the system time the clock stopped at. 
		Time        resume           ();		// Re-start the clock from the last stopped time.
		static Time get_time         ();		// Get system time in ms.
		Time        get_elapsed_time ();		// Time since start in ms.
		Time        get_lap_time     ();		// Get the elapsed time since the last lap.
		void        reset            ();		// Stop and reset the clock.

		// Static casting functions.

		static string time_to_string      ( Time time );
		static string time_to_string      ( Time time , bool days, bool hours, bool minutes, bool seconds, bool miliseconds );
		static Time   formated_time_to_ms (             Time days, Time hours, Time minutes, Time seconds, Time miliseconds );
		static Time   time_to_seconds     ( Time time );
		static Time   time_to_minutes     ( Time time );
		static Time   time_to_hours       ( Time time );
		static Time   time_to_days        ( Time time );	
		static Time   get_milliseconds    ( Time time );
		static Time   get_seconds         ( Time time );
		static Time   get_minutes         ( Time time );
		static Time   get_hours           ( Time time );
		static Time   get_days            ( Time time );		
		

		//------------------------------------------------------------------------------------------------------------------------------------------------------
		// Accessors and mutators
		//------------------------------------------------------------------------------------------------------------------------------------------------------

	public:

		// Accessors

		bool is_clock_running ();
		Time get_start_time ();
		Time get_stop_time ();

		// Mutators.

		// ...

		//------------------------------------------------------------------------------------------------------------------------------------------------------
		// Data.
		//------------------------------------------------------------------------------------------------------------------------------------------------------

	public:

		// ...

	private:

		// Time clock control data.

		Time start_time;
		Time stop_time;
		Time lap_time;
		Time elapsed_time;
		bool clock_running;
	};
}