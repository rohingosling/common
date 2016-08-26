//------------------------------------------------------------------------------------------------------------------
// Project:	Alpha-Beta Game Grid (ABGD)
// Class:	AlphaBetaGameGrid
// Version:	1.0
// Date:    2014
// Author:	Rohin Gosling
//
// Description:
//
//   AlphaBetaGameGrid manages the game grid of discreet grid based games.
//
//------------------------------------------------------------------------------------------------------------------

#pragma once

#include "AlphaBetaGameBase.h"

#include <string>
#include <vector>

using namespace std;

class AlphaBetaGameGrid : AlphaBetaGameBase
{
	//------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//------------------------------------------------------------------------------------------------------------------

	public:

	using Integer = StaticUtility::Integer;
	

	//------------------------------------------------------------------------------------------------------------------
	// Public member data.
	//------------------------------------------------------------------------------------------------------------------

	public:
	
	// Game grid.

	CellGrid			cellGrid;		// The game grid
	Integer				gridWidth;		// Grid width.
	Integer				gridHeight;		// Grid Height.
	
	//------------------------------------------------------------------------------------------------------------------
	// Public functions.
	//------------------------------------------------------------------------------------------------------------------

	public:

	// Constructors and destructors

	AlphaBetaGameGrid ( );			// Default constructor.
	~AlphaBetaGameGrid ( );			// Desctructor.

	// File managment.

	unsigned int	LoadGameGrid	( string fileName );
	void			SaveGameGrid	( string fileName );

	// Game grid management.

	void			ClearGameGrid	();
	void			ClearGameGrid   ( Cell cell );
	string			GridToString	();
	Cell			Peek			( Integer x, Integer y );
	void			Poke			( Integer x, Integer y, Cell cell );

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

