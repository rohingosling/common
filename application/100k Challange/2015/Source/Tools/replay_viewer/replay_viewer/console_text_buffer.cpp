//--------------------------------------------------------------------------------------------------------------------------------------
// Project:	    Generic Console Application Platform (G-CAP).
// Application: N/A
// Class:	    ConsoleTextBuffer
// Version:	    1.0
// Date:	    2014
// Author:	    Rohin Gosling
//
// Description:
//
//   Square text buffer used for outputing pre-rendered text art.
//
//--------------------------------------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "console_text_buffer.h"

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <sstream>
#include <stdio.h>
#include <fstream>

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------------
// Constructor 1/3
//--------------------------------------------------------------------------------------------------------------------------------------

ConsoleTextBuffer::ConsoleTextBuffer ()
{
	// Allocate memory for the buffer.

	initialize ( C_DEFAULT_WIDTH, C_DEFAULT_HEIGHT, CH_DEFAULT_BLANK );
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Constructor 2/3
//--------------------------------------------------------------------------------------------------------------------------------------

ConsoleTextBuffer::ConsoleTextBuffer ( int width, int height )
{
	// Allocate memory for the buffer.

	initialize ( width, height, CH_DEFAULT_BLANK );
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Constructor 3/3
//--------------------------------------------------------------------------------------------------------------------------------------

ConsoleTextBuffer::ConsoleTextBuffer ( int width, int height, char ch )
{
	// Allocate memory for the buffer.

	initialize ( width, height, ch );
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------------------------------------------

ConsoleTextBuffer::~ConsoleTextBuffer ()
{
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - initialize
//
// DESCRIPTION:
//
// - Initialize the class.
//
// ARGUMENTS:
//
// - width
//   Width of the text buffer.
//
// - height
//   Height of the text buffer.
//
// - ch
//   The character to initialize all cells in teh grid with.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - Both width and height are natural numbers, greater than 0.
// - ch is a valid 8-bit ASCII character code.
//   
// POST-CONDITIONS:
//
// - Memory has been alocted to the buffer.
// - The width and hight memeber variables have been updated.
// - The ASCII union table used by the smart overlay feature has been loaded with character union rules.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleTextBuffer::initialize ( int width, int height, char ch )
{
	// Allocation memory for the text buffer.

	initialize_buffer ( width, height, ch );

	// Load character union rules into the ASCII union lookup table.

	initialize_ascii_union ();
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - initialize_buffer
//
// DESCRIPTION:
//
// - Allocate memory for the text buffer.
//
// ARGUMENTS:
//
// - width
//   Width of the text buffer.
//
// - height
//   Height of the text buffer.
//
// - ch
//   The character to initialize all cells in teh grid with.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - Both width and height are natural numbers, greater than 0.
// - ch is a valid 8-bit ASCII character code.
//   
// POST-CONDITIONS:
//
// - Memory has been alocted to the buffer.
//
// - The width and hight memeber variables have been updated.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleTextBuffer::initialize_buffer ( int width, int height, char ch )
{
	try
	{
		// Check for boundary constraints.

		if ( ( width > 0 ) && ( height > 0 ) )
		{
			// Update member variables.

			this->width  = width;
			this->height = height;

			// Calculate the size of the text bufer.
			// - Size(w,h): s = h ( w + 1 )
			// - We add 1 to the width, to include a new line character at the end of each row in the buffer.

			++width;
			int size { width * height };

			// Initialize the buffer.

			this->text_buffer.clear ();
			this->text_buffer = string ( size, (char) ch );

			// Add new line characters to the end of each row in the buffer.

			for ( int row = 0; row < height; row++ )
			{
				for ( int col = 0; col < width; col++ )
				{
					if ( col == width - 1 )
					{
						int index = row * width + col;

						this->text_buffer [ index ] = CH_NEW_LINE;
					}
				}
			}
		}
		else
		{
			// Compile exception message.

			string exeption_msg;

			if ( ( width <= 0 ) && ( height <= 0 ) ) { exeption_msg = EXEPTION_MESSAGE_01; }
			if ( ( width <= 0 ) && ( height >  0 ) ) { exeption_msg = EXEPTION_MESSAGE_02; }
			if ( ( width >  0 ) && ( height <= 0 ) ) { exeption_msg = EXEPTION_MESSAGE_03; }

			// Throw underflow exception.

			throw ( underflow_error ( exeption_msg ) );
		}
	}
	catch ( overflow_error& exception )
	{
		cout << exception.what () << endl;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - initialize_ascii_union
//
// DESCRIPTION:
//
// - Load the ASCII union lookup table with the rules required to implement the smart overlay funciton.
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
// - N/A
//   
// POST-CONDITIONS:
//
// - The ASCII union look up table has been loaded with the look up rules required to implement the smart overlay function.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleTextBuffer::initialize_ascii_union ()
{
	this->ascii_union_table.push_back ( ASCIIUnion { (char) 0xC5, (char) 0xB3, (char) 0xC4 } );		// '│'  +  '─'  =  '┼'
	this->ascii_union_table.push_back ( ASCIIUnion { (char) 0xCE, (char) 0xBA, (char) 0xCD } );		// '║'  +  '═'  =  '╬'
	this->ascii_union_table.push_back ( ASCIIUnion { (char) 0xD7, (char) 0xBA, (char) 0xC4 } );		// '║'  +  '─'  =  '╫'
	this->ascii_union_table.push_back ( ASCIIUnion { (char) 0xD8, (char) 0xB3, (char) 0xCD } );		// '│'  +  '═'  =  '╪'
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - clear_buffer
//
// DESCRIPTION:
//
// - Clears the text buffer to a specified character.
//
// ARGUMENTS:
//
// - ch
//   The character to set all elements in the buffer to.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - The buffer must already have been initialized.
//   
// POST-CONDITIONS:
//
// - The buffer has been cleared to a specific character, specified by the argument ch.
//
//--------------------------------------------------------------------------------------------------------------------------------------

// Overload 1/2

void ConsoleTextBuffer::clear_buffer ()
{
	clear_buffer ( CH_DEFAULT_BLANK );
}

// Overload 2/2

void ConsoleTextBuffer::clear_buffer ( char ch )
{
	initialize_buffer ( this->width, this->height, ch );
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - draw_char
//
// DESCRIPTION:
//
// - Place a character in the text buffer.
//
// ARGUMENTS:
//
// - ( x, y )
//   The text buffer co-ordinates of the character.
//
// - ch
//   The character to draw.
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
// - The character has been placed in the buffer at the specified coordinates.
// - If the coordinates fall outside the grid, then the character is not drawn.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleTextBuffer::draw_char ( int x, int y, char ch )
{	
	if ( ( x >= 0 ) && ( x < this->width ) && ( y >= 0 ) && ( y < this->height ) )
	{
		// Get text buffer parameters.
		// We add 1 to the width, in order to accomodate for the new line characters as the end of each row.

		int width  = this->width + 1;
		int height = this->height;

		// Calculate the buffer offset index.

		long index = x + y * width;

		// TRansform character if smart overlay is enabled.

		if ( this->smart_overlay_enabled )
		{
			// Retreive the character already on the grid before we write the new one.

			char ch_grid = this->text_buffer [ index ];

			// Transform the character to write, based on the character already on the grid.

			ch = ascii_union ( ch, ch_grid );
		}

		// Write the character to the calculated location.

		this->text_buffer [ index ] = ch;
	}	
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - draw_text
//
// DESCRIPTION:
//
// - Draws a string of horizontal text into the budder.
//
// ARGUMENTS:
//
// - (x, y)
//   Co-ordinates of the left most character of the horizontal string.
//
// - text_direction
//   The direction to write the text.
//
// - text
//   The text to write into the buffer.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - The buffer should already be initiated.
//   
// POST-CONDITIONS:
//
// - The string has been writen to the buffer.
// - If the string falls completely out side the buffer, then nothing is writen to the buffer.
// - If the string falls partialy in the grid, then the string is clipped and the visible portion is writen to the grid.
//
//--------------------------------------------------------------------------------------------------------------------------------------

// Overload 1/2

void ConsoleTextBuffer::draw_text ( int x, int y, string text )
{
	draw_text ( x, y, TextDirection::TD_RIGHT, text );
}

// Overload 2/2

void ConsoleTextBuffer::draw_text ( int x, int y, TextDirection text_direction, string text )
{
	switch (  text_direction )
	{
		case TextDirection::TD_RIGHT:
			draw_text_horizontal_right ( x, y, text );
			break;

		case TextDirection::TD_LEFT:
			draw_text_horizontal_left ( x, y, text );
			break;

		case TextDirection::TD_DOWN:
			draw_text_vertical_down ( x, y, text );
			break;

		case TextDirection::TD_UP:
			draw_text_vertical_up ( x, y, text );
			break;		
	}
}

// Low level text writer: Draw text horizontal-right.
// - Fast version.

void ConsoleTextBuffer::draw_text_horizontal_right ( int x, int y, string text )
{
	// Retrieve data.

	string clipped_text { text };
	int    size         { (int) text.size () };
	int    width        { this->width  };
	int    height       { this->height };

	// Validate boundary constraints.

	if ( ( x + size >= 0 ) && ( x < width ) && ( y >= 0 ) && ( y < height ) )
	{
		// Clip text.

		int clip_size { size };

		if ( x < 0 )
		{
			clip_size    = size + x;
			x            = 0;
			clipped_text = text.substr ( size - clip_size, clip_size );
		}
		else if ( x + size > width )
		{
			clip_size    = width - x;
			clipped_text = text.substr ( 0, clip_size );
		}		

		// write string to the buffer. But only if the clip_size is greater than zero.

		if ( clip_size > 0 )
		{
			for ( int i = 0; i < clip_size; i++ )
			{
				char ch = clipped_text [ i ];
				draw_char ( x + i, y, ch );
			}
		}
	}
}

// Low level text writer: Draw text horizontal-left..

void ConsoleTextBuffer::draw_text_horizontal_left ( int x, int y, string text )
{
	int  size { (int) text.size () };
	char ch   { CH_HASH };

	for ( int i = 0; i < size; i++ )
	{
		ch = text [ i ];
		draw_char ( x - i, y, ch );
	}
}

// Low level text writer: Draw text vertical-up.

void ConsoleTextBuffer::draw_text_vertical_up ( int x, int y, string text )
{
	int  size { (int) text.size () };
	char ch   { CH_HASH };

	for ( int i = 0; i < size; i++ )
	{
		ch = text [ i ];
		draw_char ( x, y - i, ch );
	}
}

// Low level text writer: Draw text vertical-up.

void ConsoleTextBuffer::draw_text_vertical_down ( int x, int y, string text )
{
	int  size { (int) text.size () };
	char ch   { CH_HASH };

	for ( int i = 0; i < size; i++ )
	{
		ch = text [ i ];
		draw_char ( x, y + i, ch );
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - draw_horizontal_line
//
// DESCRIPTION:
//
// - Draw a horizontal line.
//
// ARGUMENTS:
//
// - (x, y)
//   The top,left most coordinate.
//
// - length
//   The length of the line, from (x,y) to the right.
//
// - ch
//   The character to draw.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - The buffer should already be initiated.
//   
// POST-CONDITIONS:
//
// - The line has been writen to the buffer.
// - If the line falls completely out side the buffer, then nothing is writen to the buffer.
// - If the line falls partialy in the grid, then the line is clipped and the visible portion is writen to the grid.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleTextBuffer::draw_horizontal_line ( int x, int y, int length, char ch )
{
	// CLip vertical ordinate.

	if ( ( y >= 0 ) && ( y < this->height ) )
	{
		// Clip horizontal ordinate.

		if ( x < 0 )
		{
			length = length + x;
			x      = 0;
		}
		else if ( x + length > this->width )
		{
			length = this->width - x;
		}	
		
		// Draw the line. But only if the width is greater than zero.

		if ( length > 0 )
		{
			for ( int i = 0; i < length; i++ )
			{
				draw_char ( x + i, y, ch );
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - draw_vertical_line
//
// DESCRIPTION:
//
// - Draw a vertical line.
//
// ARGUMENTS:
//
// - (x, y)
//   The top,left most coordinate.
//
// - length
//   The length of the line, from (x,y) to the bottom.
//
// - ch
//   The character to draw.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - The buffer should already be initiated.
//   
// POST-CONDITIONS:
//
// - The line has been writen to the buffer.
// - If the line falls completely out side the buffer, then nothing is writen to the buffer.
// - If the line falls partialy in the grid, then the line is clipped and the visible portion is writen to the grid.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleTextBuffer::draw_vertical_line ( int x, int y, int length, char ch )
{
	// CLip vertical ordinate.

	if ( ( x >= 0 ) && ( x < this->width ) )
	{
		// Clip horizontal ordinate.

		if ( y < 0 )
		{
			length = length + y;
			y     = 0;
		}
		else if ( y + length > this->height )
		{
			length = this->height - y;
		}	
		
		// Draw the line. But only if the width is greater than zero.

		if ( length > 0 )
		{
			for ( int i = 0; i < length; i++ )
			{
				draw_char ( x, y + i, ch );
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - draw_rectangle
//
// DESCRIPTION:
//
// - Draw an ASCII art rectangle.
//
// ARGUMENTS:
//
// - (x,y)
//   Top left hand corner.
//
// - (width, height)
//   Width and height.
//
// - ch
//   - The character to use to draw the rectangle.
//   - Special characters are used to specify line based rectangles.
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
// - A rectangle has been drawn to the text buffer.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleTextBuffer::draw_rectangle ( int x, int y, int width, int height, char ch )
{
	// Initialize the characters we will use to build the rectangle. We will just use ch by default.

	char top_left     { ch };
	char top_right    { ch };
	char bottom_left  { ch };
	char bottom_right { ch };
	char horizontal   { ch };
	char vertical     { ch };

	// Teansform to specialised charaters, if specified.

	switch ( ch )
	{
		case (char) 0xC5:					// ┼
			top_left     = (char) 0xDA;		// ┌
			top_right    = (char) 0xBF;		// ┐
			bottom_left  = (char) 0xC0;		// └
			bottom_right = (char) 0xD9;		// ┘
			horizontal   = (char) 0xC4;		// ─
			vertical     = (char) 0xB3;		// │
			break;

		case (char) 0xCE:					// ╬
			top_left     = (char) 0xC9;		// ╔
			top_right    = (char) 0xBB;		// ╗
			bottom_left  = (char) 0xC8;		// ╚
			bottom_right = (char) 0xBC;		// ╝
			horizontal   = (char) 0xCD;		// ═
			vertical     = (char) 0xBA;		// ║
			break;

		case (char) 0xD8:					// ╪
			top_left     = (char) 0xD5;		// ╒
			top_right    = (char) 0xB8;		// ╕
			bottom_left  = (char) 0xD4;		// ╘
			bottom_right = (char) 0xBE;		// ╛
			horizontal   = (char) 0xCD;		// ═
			vertical     = (char) 0xB3;		// │
			break;

		case (char) 0xD7:					// ╫
			top_left     = (char) 0xD6;		// ╓
			top_right    = (char) 0xB7;		// ╖
			bottom_left  = (char) 0xD3;		// ╙
			bottom_right = (char) 0xBD;		// ╜
			horizontal   = (char) 0xC4;		// ─
			vertical     = (char) 0xBA;		// ║
			break;
	}

	// Transform coordinates from {(x,y),(width,height)}, to {(x0,y0),(x1,y1)}.

	int x0 = x;
	int y0 = y;
	int x1 = x + width  - 1;
	int y1 = y + height - 1;

	// Draw the rectangle

	draw_horizontal_line ( x0 + 1, y0,     width  - 2, horizontal );		// Top.
	draw_horizontal_line ( x0 + 1, y1,     width  - 2, horizontal );		// Bottom.
	draw_vertical_line   ( x0,     y0 + 1, height - 2, vertical   );		// Left.
	draw_vertical_line   ( x1,     y0 + 1, height - 2, vertical   );		// Right.

	draw_char ( x0, y0, top_left     );										// Top left.
	draw_char ( x1, y0, top_right    );										// Top right.
	draw_char ( x0, y1, bottom_left  );										// Bottom left.
	draw_char ( x1, y1, bottom_right );										// Bottom right.
}
	

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - draw_filled_rectangle
//
// DESCRIPTION:
//
// - Draw an filled ASCII art rectangle.
//
// ARGUMENTS:
//
// - (x,y)
//   Top left hand corner.
//
// - (width, height)
//   Width and height.
//
// - ch
//   - The character to use to draw the rectangle.
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
// - A filled rectangle has been drawn to the text buffer.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleTextBuffer::draw_filled_rectangle ( int x, int y, int width, int height, char ch )
{
	// Draw the rectangle

	for ( int i = 0; i < height; i++ )
	{
		draw_horizontal_line ( x, y + i, width, ch );
	}
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

void ConsoleTextBuffer::draw_buffer ( int x, int y, ConsoleTextBuffer buffer, char transparency_char )
{
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - get_char
//
// DESCRIPTION:
//
// - Retreive the character currently located at the coordinates (x, y) in the text buffer.
//
// ARGUMENTS:
//
// - (x, y)
//   Coordinates of the character to retreieve.
//
// RETURN VALUE:
//
// - The character found at the location specified by the coordinate arguments (x, y)
//
// PRE-CONDITIONS:
//
// - The buffer should be initialized.
//   
// POST-CONDITIONS:
//
// - The character specified by the coordinate arguments (x, y), has been returned.
//
//--------------------------------------------------------------------------------------------------------------------------------------

char ConsoleTextBuffer::get_char ( int x, int y )
{
	// Initialize default character. 
	// - The default character will be returned if x or y are out of bounds.

	char ch { CH_SPACE };	

	// Attempt to retreive the characer, only if x and y are both in bounds.

	if ( ( x >= 0 ) && ( x < this->width ) && ( y >= 0 ) && ( y < this->height ) )
	{
		int width = this->width + 1;	// We add 1 to accomodate for the new line characters at the end of each row in the text buffer.
		int index = x + y * width;

		ch = this->text_buffer [ index ];
	}
	
	// Return the character.

	return ch;
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

string ConsoleTextBuffer::get_text ( int x, int y, int width )
{
	string text { "" };

	for ( int i = 0; i < width; i++ )
	{
		text += get_char ( x + i, y );
	}

	return text;
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

ConsoleTextBuffer ConsoleTextBuffer::get_buffer ( int x, int y, int width, int height )
{
	ConsoleTextBuffer buffer;

	return buffer;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - draw_text_pixel
//
// DESCRIPTION:
//
// - Draw a text art hach-shaded block.
///- color ϵ [0,1,2,3,4], where 0 = 0%, 1 = 25%, 2 = 50%, 3 = 75%, 4 = 100%
//
// ARGUMENTS:
//
// - (x,y)
//   Coordinates to draw block into the text buffer.
//
// - color
//   The indexed numerical value representing the shade to draw the block.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - The text buffer needs to have already been initialized.
//   
// POST-CONDITIONS:
//
// - The text block is drawn to the text buffer.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleTextBuffer::draw_text_pixel ( int x, int y, int color )
{
	// Initialize character to something we will notice if there is an error.

	char ch { '#' };	

	// Calculate the shade to draw.

	switch ( color )
	{
		case 0: ch = CH_BLOCK_0;   break;
		case 1: ch = CH_BLOCK_25;  break;
		case 2: ch = CH_BLOCK_50;  break;
		case 3: ch = CH_BLOCK_75;  break;
		case 4: ch = CH_BLOCK_100; break;
	}

	// Draw character to the text buffer.

	draw_char ( x, y, ch );
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - draw_text_pixel
//
// DESCRIPTION:
//
// - Draw a text art hach-shaded block.
///- color ϵ [0.0..1.0],  where 0.0 = 0%, 0.25 = 25%, 0.5 = 50%, 0.75 = 75%, 1.0 = 100% 
//
// ARGUMENTS:
//
// - (x,y)
//   Coordinates to draw block into the text buffer.
//
// - color
//   The indexed numerical value representing the shade to draw the block.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - The text buffer needs to have already been initialized.
//   
// POST-CONDITIONS:
//
// - The text block is drawn to the text buffer.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleTextBuffer::draw_text_pixel ( int x, int y, double color )	
{
	// Set the shading range. 

	const double range { 4.0 };

	// Calculate the discrete color value, so that we can use the integer overload version of draw_text_pixel.

	int discrete_color { (int) ( color * range ) };

	// Draw the pixel.

	draw_text_pixel ( x, y, discrete_color );
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

void ConsoleTextBuffer::flush ()
{
	//cout << this->text_buffer << endl;

	int size = this->text_buffer.size ();

	fwrite ( this->text_buffer.c_str(), size, 1, stderr );
		
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - save
//
// DESCRIPTION:
//
// - Save the buffer to a text file.
//
// ARGUMENTS:
//
// - file_name
//   The file name of the file to save teh buffer to.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - The text buffer should be initialized.
//   
// POST-CONDITIONS:
//
// - The contents of the text buffer hsa benn writen to a text file.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleTextBuffer::save ( string file_name )
{
	ofstream output_file;

	output_file.open ( file_name );
	
	output_file.write ( (char *) this->text_buffer.c_str(), ( this->width + 1 ) * this->height );	
	
	output_file.close ();
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

void ConsoleTextBuffer::load ( string file_name, int width, int height )
{
	int y { 0 };

	initialize_buffer ( width, height, CH_SPACE );

	ifstream input_file ( file_name, ifstream::in );

	for ( string line; getline ( input_file, line ); )
	{
		draw_text ( 0, y++, line );		
	}
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

char ConsoleTextBuffer::ascii_union ( char ch0, char ch1 )
{
	// Initialize.

	char ch = ch0;

	// Combine characters.

	for ( ASCIIUnion a : this->ascii_union_table )
	{
		if
		(
			( a.x0 == ch0 ) && ( a.x1 == ch1 )
			||
			( a.x0 == ch1 ) && ( a.x1 == ch0 )
		)
		{
			ch = a.y;
			break;
		}
	}

	//REturn result.

	return ch;
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

