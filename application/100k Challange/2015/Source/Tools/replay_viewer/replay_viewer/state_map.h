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

#pragma once

#include "console_text_buffer.h"

#include <string>
#include <vector>
#include <stdint.h>

class StateMap : public ConsoleTextBuffer
{
	//--------------------------------------------------------------------------------------------------------------------------------------
	// Constants
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// Agent referenceing.

	static const int C_AGENT_COUNT = 2;
	static const int C_AGENT_1     = 0;
	static const int C_AGENT_2     = 1;

	// Grid dimantions.

	static const int C_GRID_WIDTH  = 17;
	static const int C_GRID_HEIGHT = 23;

private:

	// Default values.

	const int C_DEFAULT_HISTORY_DEPTH = 1;

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	using DroneSwarmData = struct
	{
		int width;
		int velocity;		
		int reload_timer;
		int reload_timer_max;
	};

	using AgentData = struct 
	{
		int respawn_count;
		int respawn_timer;
		int ordnance_capacity;
		int ordnance_available;
		int kills;		
	};

	using GridData = vector <uint8_t>;						// Used for storing a normalized version of the grid.	

	using State = struct
	{
		AgentData      agent        [ C_AGENT_COUNT ];
		DroneSwarmData drone_swarm  [ C_AGENT_COUNT ];
		GridData       partial_grid [ C_AGENT_COUNT ];		// Agent's view of agent's half of the grid..	
	};

private:

	// ...
		

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Functions.
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// Constructors and destructors

	StateMap ();
	~StateMap ();

	// File managment functions.
		
	void     load_state      ( string state_file, string history_file, int width, int height );	
	GridData load_history    ( string file_name );	
	void     save_history    ( string file_name, GridData grid );	
	void     normalize_grid  ();
	GridData flatten_history ( vector <GridData> grid_list );
		
	// ...
	
private:

	// Utility functions.

	GridData flip_grid             ( GridData state );
	void     retreive_agent_1_data ();
	void     retreive_agent_2_data ();

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Accessors and mutators
	//--------------------------------------------------------------------------------------------------------------------------------------
	
public:

	// Accessors

	// ...
	
	// Mutators

	// ...

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Member data.
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	GridData grid_normalized;					// Normalized grid. Each cell can only take on values from the unit set, (0.0, 0.25, 0.5, 0.75, 1.0).	
	GridData grid_normalized_history;			// t-1
	GridData grid_state;						// Flattened version of the grid history.

	// Entity data

	State state;								// State data for all the participating agends.

	// Control parameters.

	int history_depth;							// The number of time steps into the games hitory that we will consider.
	int time_step;								// The current game itteration/round.

private:

	// ...
};



