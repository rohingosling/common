//--------------------------------------------------------------------------------------------------------------------------------------
// Project:		2015 Entelect 100k AI Challange
// Application:	Visualizers, agents and trainers.
// Class:       StateMap
// Version:		1.0
// Date:        2015-07-10
// Author:		Rohin Gosling
//
// Description:
//
//   100k state map reader.
//
//--------------------------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "state_map.h"
#include "static_utility.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------
// Constructor 1/1
//--------------------------------------------------------------------------------------------------------------------------------------

StateMap::StateMap ()
{
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------------------------------------------

StateMap::~StateMap ()
{
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - load_state
//
// DESCRIPTION:
//
// - Load in a state file.
//
// ARGUMENTS:
//
// - file_name
//   File path for the file to load.
//
// - history_file
//   history file.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - The file must exist.
//   
// POST-CONDITIONS:
//
// - The file has been loaded, and all relevent data buffers populated.
//
//--------------------------------------------------------------------------------------------------------------------------------------
	
void StateMap::load_state ( string state_file, string history_file, int width, int height )
{
	// Load the file in to the base ConsoleTextBuffer text_buffer.

	load ( state_file, width, height );

	// retrieve agent data.

	retreive_agent_1_data ();
	retreive_agent_2_data ();

	// Generate normalised grid.

	normalize_grid ();
	
	// Load history.

	this->grid_normalized_history = load_history ( history_file );

	// Save the history file.

	save_history ( history_file, this->grid_normalized );

	// Generate flattened state.

	vector <GridData> grid_list;

	grid_list.push_back ( this->grid_normalized );
	grid_list.push_back ( this->grid_normalized_history );

	this->grid_state = flatten_history ( grid_list );
}

//--------------------------------------------------------------------------------------------------------------------------------------

void StateMap::retreive_agent_1_data ()
{
	int agent_id = C_AGENT_1;

	// Extract general data fields for agent 1

	this->state.agent [ agent_id ].respawn_count = stoi ( get_text ( 8,  36, 9 ) );
	this->state.agent [ agent_id ].respawn_timer = stoi ( get_text ( 10, 39, 7 ) );
	this->state.agent [ agent_id ].kills         = stoi ( get_text ( 8,  37, 10 ) );

	// Get ordinance data for agent 1.

	string ordinance          = get_text ( 11, 35, 6 );
	string ordinance_capacity = StaticUtility::get_denominator_string ( ordinance );
	string ordinance_away     = StaticUtility::get_numerator_string   ( ordinance );

	int capacity  = stoi ( ordinance_capacity );
	int away      = stoi ( ordinance_away );
	int available = capacity - away;

	this->state.agent [ agent_id ].ordnance_capacity  = capacity;
	this->state.agent [ agent_id ].ordnance_available = available;

	// Get drone swarm data for agent 1.

	this->state.drone_swarm [ agent_id ].width    = stoi ( get_text ( 12,  42, 6 ) );
	this->state.drone_swarm [ agent_id ].velocity = stoi ( get_text ( 10,  41, 8 ) );

	// Get reload timer data.

	string reload           = get_text ( 9, 40, 9 );
	string reload_timer     = StaticUtility::get_numerator_string   ( reload );
	string reload_timer_max = StaticUtility::get_denominator_string ( reload );
	
	this->state.drone_swarm [ agent_id ].reload_timer     = stoi ( reload_timer     );
	this->state.drone_swarm [ agent_id ].reload_timer_max = stoi ( reload_timer_max );
}

//--------------------------------------------------------------------------------------------------------------------------------------

void StateMap::retreive_agent_2_data ()
{
	int agent_id = C_AGENT_2;

	// Extract general data fields for agent 1

	this->state.agent [ agent_id ].respawn_count = stoi ( get_text ( 8,  8, 9 ) );
	this->state.agent [ agent_id ].respawn_timer = stoi ( get_text ( 10, 5, 7 ) );
	this->state.agent [ agent_id ].kills         = stoi ( get_text ( 8,  7, 10 ) );

	// Get ordinance data for agent 1.

	string ordinance          = get_text ( 11, 9, 6 );
	string ordinance_capacity = StaticUtility::get_denominator_string ( ordinance );
	string ordinance_away     = StaticUtility::get_numerator_string   ( ordinance );

	int capacity  = stoi ( ordinance_capacity );
	int away      = stoi ( ordinance_away );
	int available = capacity - away;

	this->state.agent [ agent_id ].ordnance_capacity  = capacity;
	this->state.agent [ agent_id ].ordnance_available = available;

	// Get drone swarm data for agent 1.

	this->state.drone_swarm [ agent_id ].width    =      stoi ( get_text ( 12,  2, 6 ) );
	this->state.drone_swarm [ agent_id ].velocity = -1 * stoi ( get_text ( 10,  3, 8 ) );		// x -1 because player 2 sees drones moving in the oposite directions.

	// Get reload timer data.

	string reload           = get_text ( 9, 4, 9 );
	string reload_timer     = StaticUtility::get_numerator_string   ( reload );
	string reload_timer_max = StaticUtility::get_denominator_string ( reload );
	
	this->state.drone_swarm [ agent_id ].reload_timer     = stoi ( reload_timer     );
	this->state.drone_swarm [ agent_id ].reload_timer_max = stoi ( reload_timer_max );
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - normalize_grid
//
// DESCRIPTION:
//
// - Generate a normalized data buffer from the raw text data.
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
// - The file must exist.
//   
// POST-CONDITIONS:
//
// - A normalized veriosn of the raw text data has been generated and stored.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void StateMap::normalize_grid ()
{
	// Constants.

	const char CH_NEW_LINE = '\n';
	const char CH_SPACE    = ' ';
	const char CH_M        = 'M';
	const char CH_X        = 'X';
	const char CH_DASH     = '-';
	
	// Local data.

	int     width           { C_GRID_WIDTH };
	int     height          { C_GRID_HEIGHT };
	int     x_offset        { 1 };
	int     y_offset        { 11 };
	char    ch              { 0 };	
	uint8_t data            { 0 };
	int     data_index      { 0 };
	uint8_t data_resolution { 64 };
	int     data_size       { width * height };

	// Clear the grid.

	this->grid_normalized.clear ();

	// Build normalized data map.

	for ( int y = 0; y < height; y++ )
	{
		for ( int x = 0; x < width; x++ )
		{
			// Get the current character

			ch = get_char ( x + x_offset, y + y_offset );

			if ( ch != CH_NEW_LINE )
			{	
				// Map character to byte data value.

				switch ( ch )
				{
					case CH_SPACE: data = 0x00;		break;
					case CH_DASH:  data = 0x0F;		break;	
					case CH_X:     data = 0x0F;		break;
					default:       data = 0xFF;
				}

				// Add the data value to the grid buffer.

				this->grid_normalized.push_back ( data );

				++data_index;
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - load_history
//
// DESCRIPTION:
//
// - Load the history file.
//
// ARGUMENTS:
//
// - file_name
//   File path for the history file.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - The file must exist.
//   
// POST-CONDITIONS:
//
// - The file has been loaded, and all relevent data buffers populated.
//
//--------------------------------------------------------------------------------------------------------------------------------------

StateMap::GridData StateMap::load_history ( string file_name )
{
	streampos size = this->grid_normalized.size();
	GridData  grid_data ( size );
	char*     data = (char*) grid_data.data();

	ifstream file ( file_name, ios::in | ios::binary );

	if ( file.is_open () )
	{	
		file.seekg ( 0, ios::beg );
		file.read  ( data, size );
		file.close ();
	}

	return grid_data;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - save_history
//
// DESCRIPTION:
//
// - Save the current state for later use.
//
// ARGUMENTS:
//
// - file_name
//   File path for the history file.
//
// - grid
//   binary representation of the game grid.
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
// - The file has been saved to disk.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void StateMap::save_history ( string file_name, StateMap::GridData grid )
{
	streampos size = grid.size ();
	uint8_t*  data = grid.data ();

	ofstream file ( file_name, ios::out | ios::binary );

	if ( file.is_open() )
	{			
		file.write ( (char*) data, size );
		file.close ();
	}
	else
	{
		cout << "\nEXCEPTION: Unable to open file.\n";
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - flatten_history
//
// DESCRIPTION:
//
// - Merge and flatten all grids in the input grid list.
//
// ARGUMENTS:
//
// - grid_list
//   - List of grids to be merged and flattened.
//   - The first element is t, the seconds element is t-1, the third t-2, etc.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - grid_list must be pre-populated with valid lists.
//   
// POST-CONDITIONS:
//
// - A flattned version of the grid list has been returned to the caller.
//
//--------------------------------------------------------------------------------------------------------------------------------------

StateMap::GridData StateMap::flatten_history ( vector<StateMap::GridData> grid_list )
{
	const int TIME_T_0 = 0;
	const int TIME_T_1 = 1;

	GridData grid_data;
	int      size = grid_list [ 0 ].size ();
	uint8_t  data;

	for ( int i = 0; i < size; i++ )
	{
		data = grid_list [ TIME_T_0 ] [ i ];

		if ( data != 0x00 )
		{	
			grid_data.push_back ( data );
		}
		else
		{	
			data = grid_list [ TIME_T_1 ] [ i ];			
			data = ( data == 0x0F ) ? 0x00 : data; 
			data = ( data == 0xFF ) ? 0x0F : data; 
			grid_data.push_back ( data );			
		}		
	}

	return grid_data;
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