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

#pragma once

#include "stdafx.h"
#include "console_application.h"
#include "console_text_buffer.h"
#include "static_utility.h"

class ReplayViewer : public ConsoleApplication
{
	//--------------------------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// State structure.

	using AgentState = struct
	{
		uint8_t  current_step;
		int8_t   respawn_timer;
		uint8_t  missile_count;
		uint8_t  missiles_away;
		uint16_t kills;		
		uint8_t  drone_wave_size;
		int8_t   drone_velocity_x;
		uint8_t  drone_energy;
	};

	using State = struct
	{
		AgentState        agent1;
		AgentState        agent2;
		ConsoleTextBuffer buffer;
	};

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Constants
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// Text field values.

	const string C_APPLICATION_PROJECT_NAME = "Entelect 100k AI Challange";
	const string C_APPLICATION_NAME         = "Replay Viewer";
	const string C_APPLICATION_VERSION      = "1.0";
	const string C_APPLICATION_DATE         = "2015-07-15";
	const string C_APPLICATION_AUTHOR       = "Rohin Gosling";

	// Text field labels.

	const string C_LABEL_APPLICATION_PROJECT_NAME     = "PROJECT";
	const string C_LABEL_APPLICATION_APPLICATION_NAME = "APPLICATION";
	const string C_LABEL_APPLICATION_VERSION          = "VERSION";
	const string C_LABEL_APPLICATION_DATE             = "DATE";
	const string C_LABEL_APPLICATION_AUTHOR           = "AUTHOR";

	// Command line argument options.

	const string C_OPTION_TEST          = "-t";
	const string C_OPTION_HISTORY_DEPTH = "-d";

	// Console parameters.

	const int C_CONSOLE_WIDTH  = 100;
	const int C_CONSOLE_HEIGHT = 60;

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Functions.
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// Constructors and destructors

	ReplayViewer  ( int argc, char* argv [] );
	~ReplayViewer ();

	// Overriden functions.

	virtual void command_interpreter ( vector <string> command_line ) override;

	// Display functions.

	string print_application_info ();
	string print_application_info ( int margin );
	string print_usage_info       ();
	string print_usage_info       ( int margin );

	// Replay functions.

	void test_play ( const string path );
	void play      ( const string state_path, const string history_path );

private:

	// File managmentment functions.

	bool   is_directory            ( const string path );
	bool   is_file                 ( const string path );
	string get_next_step_directory ( const string path, int t, int  );
	string get_newest_subdirectory ( const string path );	

	// Test functions.

	void test ();	


	//--------------------------------------------------------------------------------------------------------------------------------------
	// Accessors and mutators
	//--------------------------------------------------------------------------------------------------------------------------------------

	// Accessors

	// ...

	// Mutators

	// ...

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Member data.
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// State animation table.

	vector <State> state_table;

private:

	// Application info.

	string application_project_name { C_APPLICATION_PROJECT_NAME };
	string application_name         { C_APPLICATION_NAME };
	string application_version      { C_APPLICATION_VERSION };
	string application_date         { C_APPLICATION_DATE };
	string application_author       { C_APPLICATION_AUTHOR };

	// Console display buffer.

	ConsoleTextBuffer buffer { C_CONSOLE_WIDTH, C_CONSOLE_HEIGHT };
};



