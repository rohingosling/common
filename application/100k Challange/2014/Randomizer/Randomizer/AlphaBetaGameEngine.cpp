#pragma once
//------------------------------------------------------------------------------------------------------------------
// Project:	Alpha-Beta Game Grid (ABGD)
// Class:	AlphaBetaGameEngine
// Version:	1.0
// Date:    2014
// Author:	Rohin Gosling
//
// Description:
//
//   Primary game managmentment class. It serves as a container for all game uints and other content.
//
//------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "AlphaBetaGameEngine.h"

using Integer = StaticUtility::Integer;
using Real    = StaticUtility::Real;
using Cell    = AlphaBetaGameBase::Cell;

//------------------------------------------------------------------------------------------------------------------
// Constructor 1
//------------------------------------------------------------------------------------------------------------------

AlphaBetaGameEngine::AlphaBetaGameEngine ()
{
}

//------------------------------------------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------------------------------------------

AlphaBetaGameEngine::~AlphaBetaGameEngine ()
{
}

//------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - InitializeUnitsFromGrid
//
// DESCRIPTION:
//
// - Scan the grid and extract information about the units found on the grid.
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
// - The grid should be initialized.
//   
// POST-CONDITIONS:
//
// - N/A.
//
// NOTES:
//
// - N/A.
//
// REFERENCES:
//
// - N/A.
//
//------------------------------------------------------------------------------------------------------------------

void AlphaBetaGameEngine::InitializeUnitsFromGrid ( )
{
	// Get Game grid data.

	Integer gridWidth  = this->gameGrid.gridWidth;
	Integer gridHeight = this->gameGrid.gridHeight;
	Integer i          = 0;							// Unit location history index. 0 = current location.

	// Get player coordinates

	Integer x = 0;
	Integer y = 0;

	i = 0;

	for each ( Cell cell in this->gameGrid.cellGrid )
	{
		// Scan for players, A or B.

		if ( cell == 'A' )
		{			
			
			this->playerA.location[i].x = x;
			this->playerA.location[i].y = y;
		}

		if ( cell == 'B' )
		{
			this->playerB.location[i].x = x;
			this->playerB.location[i].y = y;
		}

		// update coordinates.

		if ( x < gridWidth - 1 )
		{
			++x;
		}
		else
		{
			x = 0;
			++y;
		}
	}

	// Calculate Euclidean distance.

	this->playerA.euclideanDistance = sqrt ( x*x + y*y );
	this->playerB.euclideanDistance = this->playerA.euclideanDistance;

	// Calculate ManhattanDistance distance.

	this->playerA.manhattanDistance = abs ( x ) + abs ( y );
	this->playerB.manhattanDistance = this->playerA.manhattanDistance;

	// State.

	this->playerA.state = AlphaBetaGameUnit::UnitState::STATE_TEST;
	this->playerB.state = AlphaBetaGameUnit::UnitState::STATE_TEST;

	// Set scores to zero

	this->playerA.score = 0;
	this->playerB.score = 0;
}
