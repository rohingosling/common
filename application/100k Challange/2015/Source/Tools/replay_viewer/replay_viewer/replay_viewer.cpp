//--------------------------------------------------------------------------------------------------------------------------------------
// Project:		2015 Entelect 100k AI Challange
// Application:	ReplayViewer
// Class:       ReplayViewer
// Version:		1.0
// Date:        2015-07-10
// Author:		Rohin Gosling
//
// Description:
//
//   Console taxt art utility to visualize 1015 100k replay files.
//
//--------------------------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "replay_viewer.h"
#include "state_map.h"
#include "static_utility.h"

#include <iostream>
#include <fstream>
#include <random>
#include <functional>
#include <conio.h>
#include <chrono>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;	// We will be using some timming functions for measurement.

//--------------------------------------------------------------------------------------------------------------------------------------
// Destructor 1/1
//--------------------------------------------------------------------------------------------------------------------------------------

ReplayViewer::ReplayViewer ( int argc, char* argv [] ) : ConsoleApplication { argc, argv }
{	
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------------------------------------------

ReplayViewer::~ReplayViewer ()
{	
}


//--------------------------------------------------------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------------------------------------------------------

void ReplayViewer::command_interpreter ( vector <string> command_line ) 
{
	const string HISTORY_PATH = "R:\\Projects\\100k Challange\\2015\\Source\\Tools\\replay_viewer\\Debug\\output";

	// Get the number of arguments on the command line, including the command it's self.

	int argument_count { (int) command_line.size () };
	int argument_index { 0 };

	// Execute commands.

	switch ( argument_count )
	{
		case 1:
			cout << print_application_info ();
			cout << print_usage_info ();
			break;

		case 2:			

			argument_index = 1;
			
			if ( StaticUtility::to_lower ( command_line [ argument_index ] ) == C_OPTION_TEST )
			{
				test ();
			}
			else if ( StaticUtility::to_lower ( command_line [ argument_index ] ) == C_OPTION_HISTORY_DEPTH )
			{
			}			
			else if ( is_directory ( command_line [ argument_index ] ) )
			{
				string state_path   { command_line [ argument_index ] };
				string history_path { HISTORY_PATH };

				play ( state_path, history_path );
			}

			break;

		default:
			cout << print_application_info ();
			cout << print_usage_info ();
			break;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - printApplicationInfo
//
// DESCRIPTION:
//
// - Print the program info on the console.
//
// ARGUMENTS:
//
// - margin
//   Number of characters between teh left hand edge of the consol and the first characer of text.
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

// Overload 1/2

string ReplayViewer::print_application_info ()
{
	return print_application_info ( this->margin );
}

//--------------------------------------------------------------------------------------------------------------------------------------

// Overload 2/2

string ReplayViewer::print_application_info ( int margin )
{
	// Constants

	const string NEW_LINE  = "\n";
	const string DELIMITER = ": ";
	const char   SPACE     = 32;

	// Initialize list of field labels.

	vector <string> label_list
	{
		C_LABEL_APPLICATION_PROJECT_NAME,
		C_LABEL_APPLICATION_APPLICATION_NAME,
		C_LABEL_APPLICATION_VERSION,
		C_LABEL_APPLICATION_DATE,
		C_LABEL_APPLICATION_AUTHOR		
	};

	// Initialize list of field values.

	vector <string> value_list
	{
		this->application_project_name,
		this->application_name,        
		this->application_version,     
		this->application_date,        
		this->application_author,      
	};

	// Lambda function to simplify field string compilation.

	auto f = [] ( string margin, string label, string value, int tab, string delimiter, string new_line )
	{
		return margin + StaticUtility::text_field ( label, value, tab, delimiter ) + new_line;
	};

	// Compute the length of the maximum length label string + 1.
	// - We add 1, in order to leave a space after the longest field label string.

	int tab { (int) StaticUtility::get_max_length ( label_list ) + 1 };

	// Configure console message margin.

	string msg_margin ( margin, SPACE );
	string msg_info   ( NEW_LINE );

	/// Compile application info message.
	// - List of program info fields.

	int string_count { (int) label_list.size () };

	for ( int index = 0; index < string_count; index++ )
	{
		msg_info += f ( msg_margin, label_list [ index ], value_list [ index ], tab, DELIMITER, NEW_LINE );
	}

	// return output string.

	return msg_info;	
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - printApplicationInfo
//
// DESCRIPTION:
//
// - Print the program info on the console.
//
// ARGUMENTS:
//
// - margin
//   Number of characters between teh left hand edge of the consol and the first characer of text.
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

// Overload 1/2

string ReplayViewer::print_usage_info ()
{
	return print_usage_info ( this->margin );
}

//--------------------------------------------------------------------------------------------------------------------------------------

// Overload 2/2

string ReplayViewer::print_usage_info ( int margin )
{
	// Constants

	const string NEW_LINE  = "\n";	
	const string DELIMITER = ": ";
	const char   SPACE     = 32;

	// Initialize text message.

	vector <string> text_lines
	{
	//   0        10       20       30       40       50       60       70       80
	//   |........|........|........|........|........|........|........|........|
	//
		"USAGE:   replay_viewer [PATH] [OPTIONS]",
		"",		
		"EXAMPLE: replay_viewer R:\\Projects\\100k\\Source\\Replays\\0001 -r -s",
		"",
		"PATH:    A path to a replay folder generated by a previous execution",
		"         of the 2015 100k Challenge test harnes.",
		"",
		"OPTIONS:",		
		"",
		"  -t [0..3]       Show state history. 0=t-0, 1=t-1, 2=t-2, 3=t-3",
		"",
		"  -fps [VALUE]    Set the default frame rate in frames per seccond."
	};
	
	// Configure console message margin.

	string msg_margin ( margin, SPACE );
	string msg_info   { NEW_LINE      };

	// Compile text message.
	
	for ( string s : text_lines )	
	{
		msg_info += msg_margin + s + NEW_LINE;
	}

	// return output string.

	return msg_info;	
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - play
//
// DESCRIPTION:
//
// - Play back a selected log file.
//
// ARGUMENTS:
//
// - path
//   The path to the root folder of a replay sequence.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - path correctly specifies the location of the root folder of a valid replay sequence.
//   
// POST-CONDITIONS:
//
// - The replay sequence has been played.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ReplayViewer::play ( const string state_path, const string history_path )
{
	// Constants

	const string MAP_FILE                     = "map-detailed.txt";
	const string STATE_HISTORY_FILE           = "state_history_001.bin";
	const string EMPTY_STRING                 = "";
	const string BACK_SLASH                   = "\\";
	const char   PAD_CHAR                     = '0';
	const int    REPLAY_DIRECTORY_NAME_LENGTH = 3;
	const int    DEFAULT_STATE_WIDTH          = 19;
	const int    DEFAULT_STATE_HEIGHT         = 46;
	const int    DEFAULT_GRID_WIDTH           = 17;
	const int    DEFAULT_GRID_HEIGHT          = 23;

	// Local variables.

	string   replay_file   { EMPTY_STRING };
	string   history_file  { EMPTY_STRING };
	string   input_string  { EMPTY_STRING };
	string   output_string { EMPTY_STRING };
	string   temp          { EMPTY_STRING };
	StateMap state_map;
	ConsoleTextBuffer display_buffer ( 3 + 4 * DEFAULT_GRID_WIDTH, 2 + DEFAULT_GRID_HEIGHT );


	char    ch        { 0 };
	uint8_t data      { 0 };
	int     index     { 0 };
	int     t         { 0 };
	int     width     { DEFAULT_STATE_WIDTH  };
	int     height    { DEFAULT_STATE_HEIGHT };
	int     agent_id  { 0 };
	int     line      { 0 };
	int     col       { 0 };
	int     row       { 0 };	

	// Lambda function to compile the file path string.

	auto map_file_path = [ &replay_file, EMPTY_STRING, state_path, BACK_SLASH, PAD_CHAR, REPLAY_DIRECTORY_NAME_LENGTH, MAP_FILE ] ( int t )
	{
		replay_file += state_path;
		replay_file += BACK_SLASH;
		replay_file += StaticUtility::int_pad_left ( t, PAD_CHAR, REPLAY_DIRECTORY_NAME_LENGTH );
		replay_file += BACK_SLASH;
		replay_file += MAP_FILE;

		return replay_file;
	};

	// Compile history file path.

	history_file = history_path + "\\" + STATE_HISTORY_FILE;

	// Clock parameters.

	__int64	delta_time   { 0 };
	double  seconds      { 0 };
	double  seconds_max  { 0 };
	double  seconds_min  { 1.0 };

	// Execute test loop.

	while ( is_file ( map_file_path ( t ) ) )
	{	
		// Start the timer.

		auto timer_start = system_clock::now ( );

		// Draw file.

		width  = 19;
		height = 46;				
				
		state_map.load_state ( replay_file, history_file, width, height );

		for ( int y = 0; y < 23; y++ )
		{
			for ( int x = 0; x < 17; x++ )
			{
				index = y * 17 + x;
				data = state_map.grid_state [ index ];

				if ( data == 0x00 ) ch = (char) 0x20;
				if ( data == 0x0F ) ch = (char) 0xB0;
				if ( data == 0xFF ) ch = (char) 0xDB;
								
				display_buffer.draw_char ( 2 * ( x + 1 ) - 1, y + 1, ch );
				display_buffer.draw_char ( 2 * ( x + 1 ),     y + 1, ch );
			}
		}

		display_buffer.draw_rectangle ( 0, 0, 2 + 2 * DEFAULT_GRID_WIDTH, 2 + DEFAULT_GRID_HEIGHT, (char) 0xC5 );

		line     = 0;
		row      = 1;
		col      = 40;
		agent_id = 0;
		display_buffer.draw_text ( col, row + line++, "Agent 1:" ); line++;
		temp = "- Lives               : " + to_string ( state_map.state.agent [ agent_id ].respawn_count      );         display_buffer.draw_text ( col, row + line++, temp );		
		temp = "- Respawn             : " + to_string ( state_map.state.agent [ agent_id ].respawn_timer      ) + "   "; display_buffer.draw_text ( col, row + line++, temp );		
		temp = "- Ordinance Capacity  : " + to_string ( state_map.state.agent [ agent_id ].ordnance_capacity  );         display_buffer.draw_text ( col, row + line++, temp );		
		temp = "- Ordinance Available : " + to_string ( state_map.state.agent [ agent_id ].ordnance_available );         display_buffer.draw_text ( col, row + line++, temp );		
		temp = "- Kills               : " + to_string ( state_map.state.agent [ agent_id ].kills              );         display_buffer.draw_text ( col, row + line++, temp );		

		line++;
		col  = 40;
		display_buffer.draw_text ( col, row + line++, "Agent 1 - Drone Data:" ); line++;
		temp = "- Wave Siz            : " + to_string ( state_map.state.drone_swarm [ agent_id ].width            );         display_buffer.draw_text ( col, row + line++, temp );		
		temp = "- Velocity            : " + to_string ( state_map.state.drone_swarm [ agent_id ].velocity         ) + "   "; display_buffer.draw_text ( col, row + line++, temp );		
		temp = "- Reload Timer        : " + to_string ( state_map.state.drone_swarm [ agent_id ].reload_timer     );         display_buffer.draw_text ( col, row + line++, temp );		
		temp = "- Reload Timer Max    : " + to_string ( state_map.state.drone_swarm [ agent_id ].reload_timer_max );         display_buffer.draw_text ( col, row + line++, temp );		

		line++;
		col  = 40;
		display_buffer.draw_text ( col, row + line++, "Environment Data:" ); line++;
		temp = "- Time Step           : " + to_string ( t ); display_buffer.draw_text ( col, row + line++, temp );		
		
		

		// Flush buffer and show the path.

		this->clear_console ();		
		display_buffer.flush ();		
		replay_file.clear ();

		// Stop the clock and calculate the elappsed time.

		auto timer_stop   = system_clock::now ( );		// Stop the timer.
		auto elapsed_time = timer_stop - timer_start;	// Calculate file load time.

		// Convert elapsed time to seconds and milliseconds.
		// - Set precision to 3 decimal places.
		// - We will need to use a high precision int to hold the total elapsed time.

		delta_time  = duration_cast < milliseconds > ( elapsed_time ).count ( );
		seconds     = delta_time / 1000.0;
		seconds_min = ( seconds < seconds_min ) ? seconds : seconds_min;
		seconds_max = ( seconds > seconds_max ) ? seconds : seconds_max;

		// Display the elapsed time.

		cout << endl;
		cout << "Execution Time     : " << seconds     << endl;
		cout << "Execution Time Min : " << seconds_min << endl;
		cout << "Execution Time Max : " << seconds_max << endl;

		// Next step.
		
		StaticUtility::sleep ( 100 );
		++t;
	}

}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - play
//
// DESCRIPTION:
//
// - Play back a selected log file.
//
// ARGUMENTS:
//
// - path
//   The path to the root folder of a replay sequence.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - path correctly specifies the location of the root folder of a valid replay sequence.
//   
// POST-CONDITIONS:
//
// - The replay sequence has been played.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ReplayViewer::test_play ( const string path )
{
	// Constants.

	const string MAP_FILE                     = "map-detailed.txt";
	const string EMPTY_STRING                 = "";
	const string BACK_SLASH                   = "\\";
	const char   PAD_CHAR                     = '0';
	const int    REPLAY_DIRECTORY_NAME_LENGTH = 3;

	// Local variables.

	string replay_path   { EMPTY_STRING };
	string input_string  { EMPTY_STRING };
	string output_string { EMPTY_STRING };
	int    t			 { 0 };
	int    x			 { 0 };
	int    y			 { 0 };
	int    h			 { 0 };
	int    w			 { 0 };

	// Lambda function to compile the file path string.

	auto map_file_path = [ &replay_path, EMPTY_STRING, path, BACK_SLASH, PAD_CHAR, REPLAY_DIRECTORY_NAME_LENGTH, MAP_FILE ] ( int t )
	{
		replay_path += path;
		replay_path += BACK_SLASH;
		replay_path += StaticUtility::int_pad_left ( t, PAD_CHAR, REPLAY_DIRECTORY_NAME_LENGTH );
		replay_path += BACK_SLASH;
		replay_path += MAP_FILE;

		return replay_path;
	};

	// Execute the replay.

	this->clear_console ();	
	
	t = 0;

	while ( is_file ( map_file_path ( t ) ) )
	{
		// Draw file.

		w = 19;
		h = 46;
				
		this->buffer.load  ( replay_path, w, h );
		
		// Format data.

		x = 0;
		y = 0;
		this->buffer.draw_rectangle ( x, y,  w, h-1, ConsoleTextBuffer::CH_SINGLE_SINGLE );
		y = 10;
		this->buffer.draw_char      ( x, y, (char) 0xC3 );
		x = w-1;
		this->buffer.draw_char      ( x, y, (char) 0xB4 );
		y = 34;
		this->buffer.draw_char      ( x, y, (char) 0xB4 );
		x = 0;
		this->buffer.draw_char      ( x, y, (char) 0xC3 );

		x = 0;
		y = 10;
		this->buffer.draw_horizontal_line ( x + 1, y, w - 2, (char) 0xC4 );

		x = 0;
		y = 34;
		this->buffer.draw_horizontal_line ( x + 1, y, w - 2, (char) 0xC4 );

		// Transform characters.

		input_string  = "AAA";
		output_string = { (char) 0xFE, (char) 0xDB, (char) 0xFE };
		this->buffer.text_buffer = StaticUtility::replace_string ( this->buffer.text_buffer, input_string, output_string );

		input_string  = "VVV";
		output_string = { (char) 0xFE, (char) 0xDB, (char) 0xFE };
		this->buffer.text_buffer = StaticUtility::replace_string ( this->buffer.text_buffer, input_string, output_string );

		input_string  = "MMM";
		output_string = { (char) 0xF0, (char) 0xCF, (char) 0xF0 };
		this->buffer.text_buffer = StaticUtility::replace_string ( this->buffer.text_buffer, input_string, output_string );

		input_string  = "XXX";
		output_string = { (char) 0xF0, (char) 0xE9, (char) 0xF0 };
		this->buffer.text_buffer = StaticUtility::replace_string ( this->buffer.text_buffer, input_string, output_string );

		//input_string  = " x ";
		//output_string = { (char) 0xC6, (char) 0xE9, (char) 0xB5 };
		//this->buffer.text_buffer = StaticUtility::replace_string ( this->buffer.text_buffer, input_string, output_string );

		input_string  = "x";
		output_string = (char) 0xE9;		
		this->buffer.text_buffer = StaticUtility::replace_string ( this->buffer.text_buffer, input_string, output_string );

		input_string  = "!";
		output_string = (char) 0xCF;
		this->buffer.text_buffer = StaticUtility::replace_string ( this->buffer.text_buffer, input_string, output_string );

		input_string  = "i";
		output_string = (char) 0xD1;
		this->buffer.text_buffer = StaticUtility::replace_string ( this->buffer.text_buffer, input_string, output_string );

		input_string  = "|";
		output_string = (char) 0xF9;
		this->buffer.text_buffer = StaticUtility::replace_string ( this->buffer.text_buffer, input_string, output_string );

		input_string  = "-";
		//output_string = (char) 0xDF;
		output_string = (char) 0xB0;
		this->buffer.text_buffer = StaticUtility::replace_string ( this->buffer.text_buffer, input_string, output_string );


		// Flush buffer and show the path.

		this->clear_console ();
		this->buffer.flush ();

		//cout << replay_path << endl;
		replay_path.clear ();

		// Next step.
		
		StaticUtility::sleep ( 100 );
		++t;
	}
	
}


//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - is_directory
//
// DESCRIPTION:
//
// - Boolean function used to check whether a path referes to directory, or a file.
//   + The function returns true if the path is a directory.
//   + The function returns false if the path is a file.
//
// ARGUMENTS:
//
// - path
//   The path which we wish to test.
//
// RETURN VALUE:
//
// - Boolean value;
//   + true if the path is a directory.
//   + false if the path is a file.
//
// PRE-CONDITIONS:
//
// - N/A.
//   
// POST-CONDITIONS:
//
// - A boolean value has been returned.
//
//--------------------------------------------------------------------------------------------------------------------------------------

bool ReplayViewer::is_directory ( const string path )
{
	// Open a stream against the input path.

	ifstream file_stream ( path, ifstream::in );

	// Test to see if we can find anyting in it. If we can's, then it's a directory, and not a file.

	file_stream.seekg ( 0, ios::end );

	// Test and return the result.

	bool result = !file_stream.good();
	
	return result;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - is_file
//
// DESCRIPTION:
//
// - Boolean function used to check whether a path referes a file, or a directory.
//   + The function returns true if the path is a file.
//   + The function returns false if the path is a directory.
//
// ARGUMENTS:
//
// - path
//   The path which we wish to test.
//
// RETURN VALUE:
//
// - Boolean value;
//   + true if the path is a file.
//   + false if the path is a directory.
//
// PRE-CONDITIONS:
//
// - N/A.
//   
// POST-CONDITIONS:
//
// - A boolean value has been returned.
//
//--------------------------------------------------------------------------------------------------------------------------------------

bool ReplayViewer::is_file ( const string path )
{
	// Open a stream against the input path.

	ifstream file_stream ( path, ifstream::in );

	// Test to see if we can find anyting in it. If we can's, then it's a directory, and not a file.

	file_stream.get ();

	// Test and return the result.

	bool result = file_stream.good();
	
	return result;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - test
//
// DESCRIPTION:
//
// - General purpose test function.
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

string ReplayViewer::get_newest_subdirectory ( const string path )
{
	return string ( "EXEPTION: The function 'get_newest_subdirectory' has not been implemented yet." );
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - test
//
// DESCRIPTION:
//
// - General purpose test function.
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

void ReplayViewer::test ()
{
	// Constants.

	const int  TEST_CASE                 = 2;
	const char CH_DOT                    = (char) 0xFA;
	const char CH_BLOCK                  = (char) 0xFE;
	const char CH_FULL_BLOCK             = (char) 0xDB;
	const char CH_LINE_SINGLE_VERTICAL   = (char) 0xB3;
	const char CH_LINE_SINGLE_HORIZONTAL = (char) 0xC4;	


	// Variables.

	int    x  { 0 };
	int    y  { 0 };
	int    w  { 0 };
	string s  { "###" };
	char   ch { '#' };
	
	// Test code.

	switch ( TEST_CASE )
	{
		case 0:
			x = 2;
			y = 8;
			this->clear_console       ();
			this->buffer.clear_buffer ( CH_DOT );			
			this->buffer.draw_char    ( x, y, CH_BLOCK );			
			this->buffer.flush        ();
			break;

		case 1:
			x = 40;
			y = 30;
			this->clear_console               ();
			this->buffer.clear_buffer         ( CH_DOT );						
			this->buffer.draw_horizontal_line ( x,   y,   16, CH_LINE_SINGLE_HORIZONTAL );
			this->buffer.draw_vertical_line   ( x+8, y-8, 16, CH_LINE_SINGLE_VERTICAL   );			
			this->buffer.flush                ();
			break;

		case 2:
			this->clear_console       ();
			this->buffer.clear_buffer ( CH_DOT );			

			x = 10;	y = 50;			
			this->buffer.draw_text ( x,  y++, "| Hello World!" );			
			this->buffer.draw_text ( x,  y++, "| " );
			this->buffer.draw_text ( x,  y++, "| - The cat went up the hill." );
			this->buffer.draw_text ( x,  y++, "| - To be or not to be." );
			this->buffer.draw_text ( x,  y++, "| - That is the question." );
			this->buffer.draw_text ( x,  y++, "|" );

			
			s = "0123456789ABCDEF";			
			w = 16;	x = 40;	y = 30;			
			this->buffer.draw_text      ( x,  y + w, s );			
			this->buffer.draw_rectangle ( x,  y,   w, w, ConsoleTextBuffer::CH_SINGLE_SINGLE );

			w = 16;	x = 30;	y = 20;
			this->buffer.draw_text      ( x,  y + w, s );			
			this->buffer.draw_rectangle ( x,  y,  w, w, ConsoleTextBuffer::CH_SINGLE_SINGLE );

			w = 16;	x = 60;	y = 10;
			this->buffer.draw_text             ( x,  y + w, s );			
			this->buffer.draw_filled_rectangle ( x,  y,  w, w, CH_BLOCK );

			w = 16;	x = 2; y = 2;
			this->buffer.draw_text             ( x,  y + w, s );			
			this->buffer.draw_filled_rectangle ( x,  y,  w, w, CH_FULL_BLOCK );
						
			x = 30;	y = 2;
			this->buffer.draw_rectangle ( x - 1, y - 1, 7, 3, ConsoleTextBuffer::CH_SINGLE_SINGLE );
			for ( int i = 0; i < 5; i++ )
			{
				this->buffer.draw_text_pixel ( x + i, y, i );
			}

			x = 30;	y = 5;
			this->buffer.draw_rectangle ( x - 1, y - 1, 11, 3, ConsoleTextBuffer::CH_SINGLE_SINGLE );
			for ( int i = 8; i >= 0; i-- )
			{
				double v = i / 8.0;
				this->buffer.draw_text_pixel ( x + 8 - i, y, v );
			}

			x = 80;	y = 40;									
			this->buffer.draw_text ( x + 1,  y,     ConsoleTextBuffer::TD_RIGHT, s );
			this->buffer.draw_text ( x - 1,  y,     ConsoleTextBuffer::TD_LEFT,  s );
			this->buffer.draw_text ( x,      y - 1, ConsoleTextBuffer::TD_UP,    s );
			this->buffer.draw_text ( x,      y + 1, ConsoleTextBuffer::TD_DOWN,  s );

			x = 0;	y = 0;
			this->buffer.draw_text ( x, y, ConsoleTextBuffer::TD_RIGHT, s );
			s = "QWERTY";
			this->buffer.draw_text ( x, y + 1, ConsoleTextBuffer::TD_DOWN,  s );

			x = this->buffer.width  - 1;
			y = this->buffer.height - 1;
			this->buffer.draw_char ( x, y, 'X' );

			x = 0;
			y = this->buffer.height - 1;
			this->buffer.draw_char ( x, y, 'Y' );

			x = this->buffer.width  - 1;
			y = 0;
			this->buffer.draw_char ( x, y, 'Z' );

			ch = this->buffer.get_char ( 0, 0 );			
			this->buffer.draw_char     ( 3, 3, ch );

			ch = this->buffer.get_char ( 1, 0 );			
			this->buffer.draw_char     ( 5, 3, ch );

			ch = this->buffer.get_char ( 31, 2 );			
			this->buffer.draw_char     ( 7, 3, ch );

			ch = this->buffer.get_char ( 0, 2 );			
			this->buffer.draw_char     ( 9, 3, ch );

			x  = this->buffer.width  - 1;			
			y  = this->buffer.height - 1;			
			ch = this->buffer.get_char ( x, y );			
			this->buffer.draw_char     ( 3, 5, ch );
						
			s = this->buffer.get_text ( 0, 3, 16 );
			this->buffer.draw_text ( 7, 7, s );
						
			s = this->buffer.get_text ( 90, 0, 12 );
			this->buffer.draw_text ( 3, 9, s );

			this->buffer.flush ();

			s = "test.txt";
			this->buffer.save ( s );
			break;
	}


	// Clean up and exit.

	StaticUtility::sleep ( 500 );
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



