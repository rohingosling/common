
#include "stdafx.h"
#include "stop_clock.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;	// We will be using some timming functions for measurement.
using namespace common;

namespace common
{
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::StopClock ()
	{
		// Reset the clock.

		reset ();
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::~StopClock ()
	{
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	void StopClock::reset ()
	{		
		this->start_time    = get_time();
		this->stop_time     = start_time;
		this->lap_time      = 0;
		this->elapsed_time  = 0;
		this->clock_running	= false;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::start()
	{
		// Start the clock.

		if ( !this->clock_running )
		{
			this->start_time    = get_time();			// Get the current system time in miliseconds.
			this->stop_time     = this->start_time;		// Set the initial stop time to be the same as the start time.
			this->elapsed_time  = 0;					// Set the elepased time to zero.
			this->lap_time      = 0;					// Set the last lap time to zero.
			this->clock_running = true;					// Flag the clock as started.
		}

		// Return the last start time.

		return this->start_time;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::stop ()
	{
		// Stop the clock.

		if ( this->clock_running )
		{	
			this->stop_time     = get_time();							// Get the current system time in miliseconds.
			this->elapsed_time  = this->stop_time - this->start_time;	// Compute the time elapsed since the clock was started.
			this->lap_time      = this->stop_time - this->lap_time;		// Compute the last lap time.
			this->clock_running = false;								// Flag the clock as stopped.
		}

		// Return the last stop time.

		return this->stop_time;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::resume ()
	{
		// Get the current time.

		Time current_time = get_time ();

		// Stop the clock.

		if ( !this->clock_running )
		{				
			this->clock_running = true;		// Flag the clock as started again.
		}

		// Return the last stop time.

		return current_time;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::get_time ()
	{
		// Get the current time, measured in miliseconds, and stored as a chrono.h steady_clock time_point.
		// Then convert the time_point time to an unsigned long long.

		steady_clock::time_point time_now     = steady_clock::now ();
		Time                     current_time = time_point_cast <milliseconds> ( time_now ).time_since_epoch ().count ();

		// REturn the current time to caller.

		return current_time;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::get_elapsed_time ()
	{	
		// Compute the elapsed time.

		if ( this->clock_running )
		{	
			Time current_time  = get_time ();							// Get the current time.
			this->elapsed_time = current_time - this->start_time;		// Compute the time elapsed since the clock was started.			
		}

		// Return the last elapsed time.

		return this->elapsed_time;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::get_lap_time ()
	{
		// Compute lap time.

		if ( this->clock_running )
		{	
			Time current_time  = get_time ();							// Get the current time.
			this->elapsed_time = current_time - this->start_time;		// Compute the time elapsed since the clock was started.			
		}

		// Return the last elapsed time.

		return this->lap_time;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	bool StopClock::is_clock_running ()
	{
		return this->clock_running;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::get_start_time ()
	{
		return this->start_time;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::get_stop_time ()
	{
		return this->stop_time;
	}
	
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	string StopClock::time_to_string ( StopClock::Time time )
	{
		return time_to_string ( time, true, true, true, true, true );
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	string StopClock::time_to_string ( StopClock::Time total_ms, bool days_enabled, bool hours_enabled, bool minutes_enabled, bool seconds_enabled, bool milliseconds_enabled )
	{
		// Declare constants.

		// Temporal factors.		
		
		const int    SECONDS_PER_DAY        = 86400;	// 60 seconds x 60 minutes x 24 hours = 86400 seconds in a day.
		const int    SECONDS_PER_HOUR       = 3600;		// 60 seconds x 60 minutes = 3600 seconds in an hour.
		const int    SECONDS_PER_MINUTE     = 60;		// 60 seconds in a minute		
		const int    MILISECONDS_PER_SECOND = 1000;		// 60 seconds in a minute

		// Display parameters.

		const int    WIDTH_D         = 3;													// Digit width for days.
		const int    WIDTH_HMS       = 2;													// Digit width for hours, minutes and seconds.
		const int    WIDTH_MS        = 3;													// Digit sidth for milliseconds.		
		const string DELIMITER_EMPTY = "";													// Empty deliminator.
		const string DELIMITER_DH    = ":";													// Deliminator between days and hours.
		const string DELIMITER_HMS   = ":";													// Deliminator between hours, minutes and seconds.
		const string DELIMITER_MS    = ".";													// Deliminator between seconds and milliseconds.
		const char   PADDING         = '0';													// Left padding chacater.
		const char   DISABLED_CHAR   = '-';													// Character to use for disabled strings.		
		const string DISABLED_DAYS   = { DISABLED_CHAR, DISABLED_CHAR, DISABLED_CHAR };		// Disabled string dor days.
		const string DISABLED_HMS    = { DISABLED_CHAR, DISABLED_CHAR };					// Disabled string for hours, minutes, or seconds.
		const string DISABLED_MS     = { DISABLED_CHAR, DISABLED_CHAR, DISABLED_CHAR };		// Disabled string for milliseconds.

		// Declare local variables.

		stringstream time_string_stream;
		string       time_string;

		// Compute temporal components.
		//
		// Example 1:
		//   443235052 ms = "005:03:07:15.052"
		//                  ( 5 Days, 3 Hours, 7 Minutes, 15 Seconds, and 52 milliseconds )
		//
		// Example 2:
		//   1000*( 60*60*24*d + 60*60*h + 60*m + s ) + ms miliseconds = "00d:0h:0m:0s.0ms"
		//                                                               ( d Days, h Hours, m Minutes, s Seconds, and ms milliseconds )
																			
		Time total_seconds = total_ms / MILISECONDS_PER_SECOND;								// Total seconds.
		Time days          = total_seconds / SECONDS_PER_DAY;								// Remaining days.
		Time hours         = ( total_seconds % SECONDS_PER_DAY ) / SECONDS_PER_HOUR;		// Remaining hours.
		Time minutes       = ( total_seconds % SECONDS_PER_HOUR ) / SECONDS_PER_MINUTE;		// Remaining minutes.
		Time seconds       = total_seconds % SECONDS_PER_MINUTE;							// Remaining seconds.
		Time milliseconds  = total_ms % MILISECONDS_PER_SECOND;								// Remaining milliseconds.

		// Compile time string.

		// Remaining Days.

		if (  days_enabled ) time_string_stream << setfill ( PADDING ) << setw ( WIDTH_D ) << days;
		if ( !days_enabled ) time_string_stream << setfill ( PADDING ) << setw ( WIDTH_D ) << DISABLED_DAYS;
		time_string_stream << DELIMITER_DH;

		// Remaining Hours.

		if (  hours_enabled ) time_string_stream << setfill ( PADDING ) << setw ( WIDTH_HMS ) << hours;
		if ( !hours_enabled ) time_string_stream << setfill ( PADDING ) << setw ( WIDTH_HMS ) << DISABLED_HMS;
		time_string_stream << DELIMITER_HMS;

		// Remaining Minutes.

		if (  minutes_enabled ) time_string_stream << setfill ( PADDING ) << setw ( WIDTH_HMS ) << minutes;
		if ( !minutes_enabled ) time_string_stream << setfill ( PADDING ) << setw ( WIDTH_HMS ) << DISABLED_HMS;
		time_string_stream << DELIMITER_HMS;

		// Remainaing Seconds.

		if (  seconds_enabled ) time_string_stream << setfill ( PADDING ) << setw ( WIDTH_HMS ) << seconds;
		if ( !seconds_enabled ) time_string_stream << setfill ( PADDING ) << setw ( WIDTH_HMS ) << DISABLED_HMS;
		time_string_stream << DELIMITER_MS;

		// Remaining Miliseconds.

		if (  milliseconds_enabled ) time_string_stream << setfill ( PADDING ) << setw ( WIDTH_MS ) << milliseconds;
		if ( !milliseconds_enabled ) time_string_stream << setfill ( PADDING ) << setw ( WIDTH_MS ) << DISABLED_MS;			
		
		// Convert string stream to string, and return to caller.

		time_string = time_string_stream.str ();

		return time_string;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::formated_time_to_ms ( StopClock::Time days, StopClock::Time hours, StopClock::Time minutes, StopClock::Time seconds, StopClock::Time miliseconds )
	{
		// Initialize temporal factors.

		const Time MS_PER_SECOND = 1000;					// 1000 miliseconds in a second.
		const Time MS_PER_MINUTE = MS_PER_SECOND * 60;		// 60 seconds in a minute.
		const Time MS_PER_HOUR   = MS_PER_MINUTE * 60;		// 60 minutes in an hour.
		const Time MS_PER_DAY    = MS_PER_HOUR   * 24;		// 24 hours in a day.

		// Compute total miliseconds.

		Time total_milliseconds = MS_PER_DAY * days + MS_PER_HOUR * hours + MS_PER_MINUTE * minutes + MS_PER_SECOND * seconds + miliseconds;

		// Return miliseconds to caller.

		return total_milliseconds;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::time_to_seconds ( StopClock::Time time )
	{
		const Time MS_PER_SECOND = 1000;

		return time / MS_PER_SECOND;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::time_to_minutes ( StopClock::Time time )
	{
		const Time MS_PER_MINUTE = 60000;

		return time / MS_PER_MINUTE;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::time_to_hours ( StopClock::Time time )
	{
		const Time MS_PER_HOUR = 3600000;

		return time / MS_PER_HOUR;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::time_to_days( StopClock::Time time )
	{
		const Time MS_PER_DAY = 86400000;

		return time / MS_PER_DAY;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::get_milliseconds ( StopClock::Time total_ms )
	{
		// Declare temporal factor constant/s.
		
		const int MILISECONDS_PER_SECOND = 1000;		// 60 seconds in a minute

		// Compute temporal component.																			
		
		Time milliseconds = total_ms % MILISECONDS_PER_SECOND;

		// Return temporal component to caller.

		return milliseconds;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::get_seconds ( StopClock::Time total_ms )
	{
		// Declare temporal factor constant/s.				
		
		const int SECONDS_PER_MINUTE     = 60;		// 60 seconds in a minute		
		const int MILISECONDS_PER_SECOND = 1000;	// 60 seconds in a minute

		// Compute temporal components.
																			
		Time total_seconds = total_ms / MILISECONDS_PER_SECOND;
		Time seconds       = total_seconds % SECONDS_PER_MINUTE;

		// Return temporal component to caller.

		return seconds;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::get_minutes ( StopClock::Time total_ms )
	{
		// Declare temporal factor constant/s.					
		
		const int SECONDS_PER_HOUR       = 3600;	// 60 seconds x 60 minutes = 3600 seconds in an hour.
		const int SECONDS_PER_MINUTE     = 60;		// 60 seconds in a minute		
		const int MILISECONDS_PER_SECOND = 1000;	// 60 seconds in a minute

		// Compute temporal components.
																			
		Time total_seconds = total_ms / MILISECONDS_PER_SECOND;
		Time minutes       = ( total_seconds % SECONDS_PER_HOUR ) / SECONDS_PER_MINUTE;

		// Return temporal component to caller.

		return minutes;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::get_hours ( StopClock::Time total_ms )
	{
		// Declare temporal factor constant/s.			
		
		const int SECONDS_PER_DAY        = 86400;		// 60 seconds x 60 minutes x 24 hours = 86400 seconds in a day.
		const int SECONDS_PER_HOUR       = 3600;		// 60 seconds x 60 minutes = 3600 seconds in an hour.		
		const int MILISECONDS_PER_SECOND = 1000;		// 60 seconds in a minute

		// Compute temporal components.
																			
		Time total_seconds = total_ms / MILISECONDS_PER_SECOND;
		Time days          = total_seconds / SECONDS_PER_DAY;
		Time hours         = ( total_seconds % SECONDS_PER_DAY ) / SECONDS_PER_HOUR;

		// Return temporal component to caller.

		return hours;
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------

	StopClock::Time StopClock::get_days( StopClock::Time total_ms )
	{
		// Declare temporal factor constant/s.		
		
		const int SECONDS_PER_DAY        = 86400;		// 60 seconds x 60 minutes x 24 hours = 86400 seconds in a day.		
		const int MILISECONDS_PER_SECOND = 1000;		// 60 seconds in a minute

		// Compute temporal components.
																			
		Time total_seconds = total_ms / MILISECONDS_PER_SECOND;
		Time days          = total_seconds / SECONDS_PER_DAY;
		
		// Return temporal component to caller.

		return days;
	}
}
