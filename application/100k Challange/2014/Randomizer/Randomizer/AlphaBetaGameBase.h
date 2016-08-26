//------------------------------------------------------------------------------------------------------------------
// Project:	Alpha-Beta Game Grid (ABGD)
// Class:	AlphaBetaGameBase
// Version:	1.0
// Date:    2014
// Author:	Rohin Gosling
//
// Description:
//
//   Base class for all ABGD classes and components.
//
//------------------------------------------------------------------------------------------------------------------

#pragma once

#include "StaticUtility.h"

#include <string>
#include <vector>

using namespace std;
using Integer = StaticUtility::Integer;
using Real    = StaticUtility::Real;

class AlphaBetaGameBase
{
	//------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//------------------------------------------------------------------------------------------------------------------

	public:

	// Game grid types.

	using UnitID		= char;
	using GridVector	= struct { Integer x; Integer y; };		// Coordinate on the grid.
	using Cell			= UnitID;
	using CellGrid		= vector <Cell>;						// Buffer offset: z = y*width + x
	

	// Graph theory types.

	using Vertex		= struct { string name; Real value; GridVector v; };
	using Edge			= struct { Vertex a; Vertex b; Real weight; };
	using Graph			= struct { string name; vector <Vertex> verticies; vector <Edge> edges; };

	//------------------------------------------------------------------------------------------------------------------
	// Public member data.
	//------------------------------------------------------------------------------------------------------------------

	protected:

	string className;
	string displayName;


	//------------------------------------------------------------------------------------------------------------------
	// Public methods.
	//------------------------------------------------------------------------------------------------------------------

	public:

	// Constructors and destructors

	// ...


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

