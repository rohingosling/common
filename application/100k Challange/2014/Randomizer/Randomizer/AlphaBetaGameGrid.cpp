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

#include "stdafx.h"
#include "AlphaBetaGameBase.h"
#include "AlphaBetaGameGrid.h"
#include "StaticUtility.h"

#include <math.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using Cell = AlphaBetaGameBase::Cell;

//------------------------------------------------------------------------------------------------------------------
// Constructor 1
//------------------------------------------------------------------------------------------------------------------

AlphaBetaGameGrid::AlphaBetaGameGrid ()
{
}

//------------------------------------------------------------------------------------------------------------------
// Destructor
//------------------------------------------------------------------------------------------------------------------


AlphaBetaGameGrid::~AlphaBetaGameGrid ()
{
}

//------------------------------------------------------------------------------------------------------------------
// FUNCTION NAME:
//
// - LoadGameState
//
// DESCRIPTION:
//
// - Load the game state file into memory.
//
// RETURN VALUE::
//
// - Return 0 for success.
//   Positive numbers greater than zero, will refer to error codes.
//
// PRI-CONDITIONS
//
// - The game state file should already be configured correctly.
//   
// POST-CONDITIONS
//
// - The game state file is loaded into the game buffer in RAM.
//
//------------------------------------------------------------------------------------------------------------------

unsigned int AlphaBetaGameGrid::LoadGameGrid ( string fileName )
{
	// Clear the existing game state buffer.

	ClearGameGrid ();

	// Load in the game state file.

	string       line;
	ifstream     inputFile ( fileName );
	unsigned int lineCount = 0;

	// Open the file for reading.

	if ( inputFile.is_open ( ) )
	{
		while ( getline ( inputFile, line ) )
		{
			// Calculate the game grid width.
			// - We do this by counting how many characters there are, other 
			//   than new line or chariage returns.
			// - We will do this only on the first itteration through the loop.
			//   Therefore, our width estimate is based purely on the length of 
			//   the first line.

			if ( lineCount == 0 )
			{
				this->gridWidth = line.length ( );
			}

			// Load a line of data from the game state file.

			for ( char c : line )
			{
				this->cellGrid.push_back ( c );
			}

			// Update the line count.

			++lineCount;
		}

		// Store the grid hight, basedon the last line we read from the file.

		this->gridHeight = lineCount;

		// CLose the file.

		inputFile.close ( );
	}
	else
	{
		// Show an exeption message if we were not able to open the file.

		cout << endl << "ERROR: Unable to open file, " << fileName << "." << endl;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------
// FUNCTION NAME:
//
// - SaveGameState
//
// DESCRIPTION:
//
// - Save the next game state to disk.
//
// ARGUMENTS:
//
// - fileName
//
//   - The file name of game state to save.
//
//   - The file name should be, game.state.
//
// RETURN VALUE::
//
// - N/A
//
// PRI-CONDITIONS
//
// - this->gridWidth must have already been initialized.
//
// - 4 Seconds have not yet passed.
//
// - The game state is required to be saved within 4 seconds of being loaded.
//   
// POST-CONDITIONS
//
// - The game state has been saved in under 4 seconds.
//
//------------------------------------------------------------------------------------------------------------------

void AlphaBetaGameGrid::SaveGameGrid ( string fileName )
{
	// Open a file for writing.

	ofstream gameGridFile ( fileName );

	if ( gameGridFile.is_open ( ) )
	{
		// Write the contents of game state buffer to the file stream.

		long cCount = 0;

		for each ( Cell c in this->cellGrid )
		{
			gameGridFile.put ( ( char ) c );
			++cCount;

			if ( cCount >= this->gridWidth )
			{
				gameGridFile.put ( '\n' );
				cCount = 0;
			}
		}

		// Close the file.

		gameGridFile.close ( );
	}
	else
	{
		// Show an exeption message if we were not able to write to the file.

		cout << endl << "ERROR: Unable to write to file, " << fileName << "." << endl;
	}
}

//------------------------------------------------------------------------------------------------------------------
// FUNCTION NAME:
//
// - ClearGameGrid
//
// Description:
//
// - Clears a game grid.
//
// - May also be used to initialize all cells in a game grid to a spceific Cell
//   value.
//
// ARGUMENTS:
//
// - gameGrid
//
//   - A pointer to a game grid.
//
//   - We don't reference the classe's game grid directly, in order to allow the 
//     FUNCTION NAME to be more flexible.
//
// - cell
//
//   - An optional Cell value (char), to set each cell in the grid to.
//
// RETURN VALUE::
//
// - N/A
//
// PRI-CONDITIONS
//
// - The game state is required to be saved within 4 seconds of being loaded.
//   
// POST-CONDITIONS
//
// - The game state has been saved in under 4 seconds.
//
// NOTES:
//
// - White Space Characters:
//
//   Char	Hex	Symbol	Description
//   ------	---	-------	-------------------
//   ' '	20	SPC		Space.
//   '\n'	0A	LF		New line.
//   '\r'	0D	CR		Carriage return.
//   '\f'	0C	FF		Form feed.
//   '\t'	09	TAB		Horizontal tab.
//   '\v'	0B	VT		Vertical tab.
//   ------	---	-------	-------------------
//
//------------------------------------------------------------------------------------------------------------------

// Overload 1/2

void AlphaBetaGameGrid::ClearGameGrid ()
{
	// Specify all cells to be spaces.

	Cell whiteSpace = 0x20;

	// Clear the game grid and set all cells to white space.

	ClearGameGrid ( whiteSpace );
}

// Overload 2/2

void AlphaBetaGameGrid::ClearGameGrid ( Cell newCell )
{	
	// Initialize a counter to count though each cell in the grid.

	StaticUtility::Integer cellIndex = 0;

	// Loop through all cells in the grid and set them to the value specified
	// through  cell.

	for each ( Cell cell in this->cellGrid )
	{
		this->cellGrid.at ( cellIndex ) = newCell;	// Set the cell.
		++cellIndex;								// Select the next cell.
	}
}

//------------------------------------------------------------------------------------------------------------------
// FUNCTION NAME:
//
// - ShowGameGrid
//
// DESCRIPTION:
//
// - Dumps the game grid data to teh console.
//
// ARGUMENTS:
//
// - N/A
//
// RETURN VALUE::
//
// - N/A
//
// PRI-CONDITIONS
//
// - this->gridWidth must have already been initialized.
//
// - A valid game grid must already have been loaded and configreed correctly.
//   
// POST-CONDITIONS
//
// - The game grid has been dumped to the console.
//
//------------------------------------------------------------------------------------------------------------------

string AlphaBetaGameGrid::GridToString ()
{
	// Display parameters.

	bool wideDisplay = true;

	// Initialize the output string.

	string  margin		      ( "  " );		// Initialize the display margin.
	string  gridString	      ( margin );	// Start with the margin.
	Cell    displayCell	      ( 0x20 );		// Space by default.
	string  displayCellString ( "" );		// Teh display version of the cell grid.
	string  lineNumberString  ( "" );		// The line number to display in the left hand column.
	
	// Print out the game grid.

	Integer columnCount = 0;
	Integer rowCount    = 0;

	// Add column ruler.

	Integer rulerStart = 0;					// STart counting ruler ticks at this number.
	 
	gridString += string ( 4, 0x20 );;
	for ( columnCount = rulerStart; columnCount < this->gridWidth; columnCount++ )
	{
		gridString += StaticUtility::ToAlignedString ( columnCount, 3, StaticUtility::ALIGN_LEFT );
	}
	gridString += "\n";
	gridString += margin;

	// Add grid data.

	columnCount = 0;
	rowCount    = 0;

	for each ( Cell cell in this->cellGrid )
	{
		// Map cell data to display data.

		switch ( cell )
		{
			case ' ':
				displayCell       = ( Cell ) 0x20;
				displayCellString = { displayCell, displayCell, displayCell };
				break;

			case '#':
				displayCell       = ( Cell ) 0xDB;
				displayCellString = { displayCell, displayCell, displayCell };
				break;

			case 'A':
				displayCell = 'A';
				displayCellString = { '(', displayCell, ')' };
				break;

			case 'B':
				displayCell = 'B';
				displayCellString = { '(', displayCell, ')' };
				break;

			case '.':
				displayCell = ( Cell ) 0xF9;
				displayCellString = { ' ', displayCell, ' ' };
				break;

			case '*':
				displayCell = ( Cell ) 0xE9;
				displayCellString = { ' ', displayCell, ' ' };
				break;

			case '!':
				displayCell = ( Cell ) 0xFE;
				displayCellString = { ' ', displayCell, ' ' };
				break;

			case '+':
				displayCell = ( Cell ) 0x20;
				displayCellString = { ' ', displayCell, ' ' };
				break;

			default:
				displayCell = '+';
				displayCellString = { ' ', displayCell, ' ' };
				break;
		}


		// Add row ruler.

		
		if ( columnCount <= 0 )
		{
			lineNumberString = StaticUtility::ToAlignedString ( rowCount + rulerStart, 2, StaticUtility::ALIGN_RIGHT );			
			lineNumberString += ( Cell ) 0x20;
			gridString += lineNumberString;
		}


		// Add the cell character to the string build.

		if ( columnCount < this->gridWidth-1 )
		{
			if ( wideDisplay )
			{
				gridString += displayCellString;
			}
			else
			{
				gridString.push_back ( displayCell );
			}

			// Update column count.

			++columnCount;
		}
		else
		{
			if ( wideDisplay )
			{
				gridString += displayCellString;
			}
			else
			{
				gridString.push_back ( displayCell );
			}
			gridString.push_back ( '\n' );
			gridString += margin;
			columnCount = 0;

			// Update the row count.

			++rowCount;
		}
	}

	return gridString;
}


//------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - Peek
//
// DESCRIPTION:
//
// - REturns the Cell located at coordinates (x,y).
//
// ARGUMENTS:
//
// - ( x, y )
//
//   The oordinates of the Cell to query.
//
// RETURN VALUE:
//
// - The Cell specified by coordinates x and y.
//
// PRE-CONDITIONS:
//
// - Teh cell grid needs to have been initialized already.
//   
// POST-CONDITIONS:
//
// - The Cell specified by coordinates x and y has been returned.
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

Cell AlphaBetaGameGrid::Peek ( Integer x, Integer y )
{
	Integer offset = x;
	Integer row    = y * this->gridWidth;
		
	return this->cellGrid.at ( row + offset );
}

//------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - Poke
//
// DESCRIPTION:
//
// - Sets a cell specified by (x,y) to the value of cell.
//
// ARGUMENTS:
//
// - (x,y)
//
//   The coordinates of the Cell we would like to set.
//
// - cell
//
//   The character value of the cell to be set.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - The grid needs to already exist.
//   
// POST-CONDITIONS:
//
// - Teh cell specified by (x,y) has been set to Cell.
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

void AlphaBetaGameGrid::Poke ( Integer x, Integer y, Cell cell )
{
	Integer offset = x;
	Integer row    = y * this->gridWidth;

	this->cellGrid.at ( row + offset ) = cell;
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
// NOTES:
//
// - N/A.
//
// REFERENCES:
//
// - N/A.
//
//------------------------------------------------------------------------------------------------------------------