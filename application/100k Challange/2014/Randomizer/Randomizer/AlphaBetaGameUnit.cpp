//------------------------------------------------------------------------------------------------------------------
// Project:				100k Challange
// Application Name:	Randomizer
// Class:               AlphaBetaAgent
// Version:				1.0
// Author:				Rohin Gosling
//
// Description:
//
//   Turn based AI agent, driven by huristicaly guided alpha-beta search space.
//
//------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "AlphaBetaGameUnit.h"
#include "AlphaBetaGameGrid.h"

#include <math.h>

#include <string>
#include <vector>
#include <iostream>

using namespace std;

//------------------------------------------------------------------------------------------------------------------
// Constructor 1
//------------------------------------------------------------------------------------------------------------------

AlphaBetaGameUnit::AlphaBetaGameUnit ()
{
}

//------------------------------------------------------------------------------------------------------------------
// Destructor.
//------------------------------------------------------------------------------------------------------------------

AlphaBetaGameUnit::~AlphaBetaGameUnit ()
{
}

//------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - HoldDistanceAndLead
//
// DESCRIPTION:
//
// - Non-Historical movement command.
//   i.e. Does not require historical data or state data.
//
// - Aproach apponent, and then hold a constant distance, while coping the 
//   apponents direction.
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
//------------------------------------------------------------------------------------------------------------------

bool AlphaBetaGameUnit::Put ( Integer x, Integer y, AlphaBetaGameGrid* gameGrid )
{
	// Select the current location.

	Integer i = 0;
	Integer xi = this->location [ i ].x;
	Integer yi = this->location [ i ].y;

	// Validate the legality of the new location.

	bool   legalMove    = true;
	Cell   apponentCell = 0x00;

	// don't bump into the wall.

	if ( gameGrid->Peek ( x, y ) == '#' ) legalMove = false;

	// Don't sep on poison.

	if ( gameGrid->Peek ( x, y ) == '!' ) legalMove = false;

	// Don't get eaten.

	if ( this->id == 0 ) apponentCell = 'B';
	if ( this->id == 1  )apponentCell = 'A';

	if ( !( ( ( xi == 9 ) && ( yi == 9 ) ) || ( ( xi == 9 ) && ( yi == 11 ) ) ) )
	{
		if ( ( gameGrid->Peek ( x + 1, y ) == apponentCell ) || ( gameGrid->Peek ( x - 1, y ) == apponentCell ) ) legalMove = false;
		if ( ( gameGrid->Peek ( x, y + 1 ) == apponentCell ) || ( gameGrid->Peek ( x, y - 1 ) == apponentCell ) ) legalMove = false;
	}

	// Don't eat people comming out the respawn area.

	if ( ( ( xi == 10 ) && ( yi == 8 ) ) || ( ( xi == 8 ) && ( yi == 8 ) ) )
	{
		if ( gameGrid->Peek ( 9, 8 ) == apponentCell ) legalMove = false;
	}

	if ( ( ( xi == 10 ) && ( yi == 12 ) ) || ( ( xi == 8 ) && ( yi == 12 ) ) )
	{
		if ( gameGrid->Peek ( 9, 12 ) == apponentCell ) legalMove = false;
	}

	// Don't wonder around the re-spawn area.
	
	if ( ( x == 8 )  && ( y == 10 ) ) legalMove = false;
	if ( ( x == 9 )  && ( y == 10 ) ) legalMove = false;
	if ( ( x == 10 ) && ( y == 10 ) ) legalMove = false;

	// Don't enter the respawn area.
	
	i = 0;

	if ( !( ( xi == 9 ) && ( yi == 10 ) ) && ( x == 9 ) && ( y == 9 ) )  legalMove = false;	
	if ( !( ( xi == 9 ) && ( yi == 10 ) ) && ( x == 9 ) && ( y == 11 ) ) legalMove = false;

	// Don't stand around.

	if ( ( x == xi ) && ( y == yi ) ) legalMove = false;
	
	// Place player in new location.

	if ( legalMove )
	{

		// Put a space where we are now.

		gameGrid->Poke ( this->location [ i ].x, this->location [ i ].y, 0x20 );

		// Put us in the new location.

		if ( this->id == 0 ) gameGrid->Poke ( x, y, 'A' );
		if ( this->id == 1 ) gameGrid->Poke ( x, y, 'B' );

		// Update current location.

		i = 3;
		this->location [ i ].x = this->location [ -i ].x;
		this->location [ i ].y = this->location [ -i ].y;

		i = 2;
		this->location [ i ].x = this->location [ -i ].x;
		this->location [ i ].y = this->location [ -i ].y;

		i = 1;
		this->location [ i ].x = this->location [ -i ].x;
		this->location [ i ].y = this->location [ -i ].y;

		i = 0;
		this->location [ i ].x = x;
		this->location [ i ].y = y;		
	}

	return legalMove;
}

bool AlphaBetaGameUnit::Move ( Integer x, Integer y, AlphaBetaGameGrid* gameGrid )
{
	// Select the current location.

	Real    width       = gameGrid->gridWidth;
	Real    height      = gameGrid->gridHeight;
	Integer	i			= 0;
	Real	xi = this->location [ i ].x;
	Real	yi = this->location [ i ].y;
	Real    dx          = xi - x;
	Real    dy          = yi - y;
	bool	legalMove	= false;

	// Attempt a move

	
	if ( dx <= 0 )
	{	
		if ( !legalMove ) legalMove = MoveRight ( gameGrid );
		if ( !legalMove ) legalMove = MoveUp    ( gameGrid );		
		if ( !legalMove ) legalMove = MoveDown  ( gameGrid );
		if ( !legalMove ) legalMove = MoveLeft ( gameGrid );
	}
	else
	{	
		if ( !legalMove ) legalMove = MoveLeft  ( gameGrid );
		if ( !legalMove ) legalMove = MoveUp ( gameGrid );
		if ( !legalMove ) legalMove = MoveDown  ( gameGrid );
		if ( !legalMove ) legalMove = MoveRight ( gameGrid );		
		
	}
	


	cout << endl << "  ";
	cout << "dx = " << StaticUtility::ToAlignedString ( dx, 3, 8, StaticUtility::ALIGN_RIGHT );
	cout << endl << "  ";
	cout << "dy = " << StaticUtility::ToAlignedString ( dy, 3, 8, StaticUtility::ALIGN_RIGHT );
	cout << endl;

	return legalMove;
}

bool AlphaBetaGameUnit::MoveUp ( AlphaBetaGameGrid* gameGrid )
{
	// Select the current location.

	Integer i  = 0;
	Integer xi = this->location [ i ].x;
	Integer yi = this->location [ i ].y;

	// Validate the legality of the new location.
	
	return Put ( xi, yi - 1, gameGrid );
}

bool AlphaBetaGameUnit::MoveDown ( AlphaBetaGameGrid* gameGrid )
{
	// Select the current location.

	Integer i = 0;
	Integer xi = this->location [ i ].x;
	Integer yi = this->location [ i ].y;

	// Validate the legality of the new location.

	return Put ( xi, yi + 1, gameGrid );
}

bool AlphaBetaGameUnit::MoveLeft ( AlphaBetaGameGrid* gameGrid )
{
	// Select the current location.

	Integer i			= 0;
	Integer xi			= this->location [ i ].x;
	Integer yi			= this->location [ i ].y;
	bool	legalMove	= true;

	// Validate the legality of the new location.

	if ( xi <= 0 )
	{
		legalMove = Put ( gameGrid->gridWidth - 1, yi, gameGrid );
	}
	else
	{
		legalMove = Put ( xi - 1, yi, gameGrid );
	}

	return legalMove;
}

bool AlphaBetaGameUnit::MoveRight ( AlphaBetaGameGrid* gameGrid )
{
	// Select the current location.

	Integer i			= 0;
	Integer xi			= this->location [ i ].x;
	Integer yi			= this->location [ i ].y;
	bool	legalMove	= true;

	// Validate the legality of the new location.

	if ( xi >= gameGrid->gridWidth - 1 )
	{
		legalMove = Put ( 0, yi, gameGrid );
	}
	else
	{
		legalMove = Put ( xi + 1, yi, gameGrid );
	}

	return legalMove;
}

//------------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------
