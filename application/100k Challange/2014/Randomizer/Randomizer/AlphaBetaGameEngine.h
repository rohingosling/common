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

#pragma once

#include "AlphaBetaGameBase.h"
#include "AlphaBetaGameGrid.h"
#include "AlphaBetaGameUnit.h"

#include <string>
#include <vector>

using namespace std;

class AlphaBetaGameEngine : public AlphaBetaGameBase
{

	//------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//------------------------------------------------------------------------------------------------------------------

	public:

	using Integer = StaticUtility::Integer;
	using Real    = StaticUtility::Real;
	

	//------------------------------------------------------------------------------------------------------------------
	// Public member data.
	//------------------------------------------------------------------------------------------------------------------

	public:

	// Game grid.

	AlphaBetaGameGrid	gameGrid;		// The game grid
	

	// Game graph.

	Graph				gameGraph;		// A graph of the navigatable space on the grid.

	// Game units.

	AlphaBetaGameUnit	playerA;
	AlphaBetaGameUnit	playerB;


	//------------------------------------------------------------------------------------------------------------------
	// Public functions.
	//------------------------------------------------------------------------------------------------------------------

	public:

	// Constructors and destructors

	AlphaBetaGameEngine ( );			// Default constructor.
	~AlphaBetaGameEngine ( );			// Desctructor.

	// Unit managment.

	void InitializeUnitsFromGrid ( );

	

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

