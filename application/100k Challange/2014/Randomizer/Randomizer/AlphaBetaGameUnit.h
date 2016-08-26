//------------------------------------------------------------------------------------------------------------------
// Project:				100k Challange
// Application Name:	Randomizer
// Class:               AlphaBetaGameUnit
// Version:				1.0
// Author:				Rohin Gosling
//
// Description:
//
//   Turn based AI agent, driven by huristicaly guided alpha-beta search space.
//
//------------------------------------------------------------------------------------------------------------------

#pragma once

#include "StaticUtility.h"
#include "AlphaBetaGameBase.h"
#include "AlphaBetaGameGrid.h"


#include <string>
#include <vector>

using namespace std;
using Integer = StaticUtility::Integer;
using Real    = StaticUtility::Real;

class AlphaBetaGameUnit : AlphaBetaGameBase
{
	//------------------------------------------------------------------------------------------------------------------
	// Constants
	//------------------------------------------------------------------------------------------------------------------

	static const Integer PathHistory = 4;						// This includes the current location.

	//------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//------------------------------------------------------------------------------------------------------------------

	public:

	enum UnitState
	{
		STATE_TEST,
		STATE_START,
		STATE_STOP,
		STATE_RESPAWN,
		STATE_NEUTRAL,
		STATE_DEFENSIVE,
		STATE_AGGRESSIVE,
		STATE_ROAM		
	};


	//------------------------------------------------------------------------------------------------------------------
	// Public member data.
	//------------------------------------------------------------------------------------------------------------------

	public:
	
	Integer					id;							// A = 0, B = 2/
	UnitState				state;						// Unit state.
	GridVector				direction;					// Current direction. durection = location - lastLocation.
	GridVector				location [ PathHistory ];	// Location on the grid. t -0		
	Real					euclideanDistance;			// Euclidean distance to apponenet.
	Integer					manhattanDistance;			// Manhattan distance to apponenet.
	Integer					poisonInventory;			// Number of poison pills left.
	Integer					score;						// Current score.
	vector <Vertex>			pillList;					// Ordered list of pills.

	//AlphaBetaGameGrid parent;

	//------------------------------------------------------------------------------------------------------------------
	// Public functions.
	//------------------------------------------------------------------------------------------------------------------

	public:

	// Constructors and destructors

	AlphaBetaGameUnit	();		// Default constructor.
	~AlphaBetaGameUnit	();		// Desctructor.

	// File commands

	//void LoadStateFile () {};
	//void SaveStateFile () {};

	// Movement commands.

	bool	Put						( Integer x, Integer y, AlphaBetaGameGrid* gameGrid );
	bool	Move					( Integer x, Integer y, AlphaBetaGameGrid* gameGrid );
	bool	MoveUp					( AlphaBetaGameGrid* gameGrid );
	bool	MoveDown				( AlphaBetaGameGrid* gameGrid );
	bool	MoveLeft				( AlphaBetaGameGrid* gameGrid );
	bool	MoveRight				( AlphaBetaGameGrid* gameGrid );
	bool	RandomMove				( AlphaBetaGameGrid* gameGrid );
	void	MoveToNextPill			();
	void	MoveToNextBonusPill		();
	void	MoveToPoisonPill		();
	void	InterceptApponenet		();
	void	FollowApponent			();
	void	AvoidApponent			();
	void	HoldDistanceAndLead		();
	void	CopyApponent			();
	void	MirrorApponent			();


	//------------------------------------------------------------------------------------------------------------------
	// Accessors and mutators
	//------------------------------------------------------------------------------------------------------------------

	// ...


	//------------------------------------------------------------------------------------------------------------------
	// Private member data.
	//------------------------------------------------------------------------------------------------------------------

	private:

	// ...


	//------------------------------------------------------------------------------------------------------------------
	// Private methods.
	//------------------------------------------------------------------------------------------------------------------

	private:

	// ...
};

