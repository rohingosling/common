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

#pragma once

#include "stdafx.h"

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

class ConsoleTextBuffer
{
	//--------------------------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	using HorizontalAlignment   = enum { HA_LEFT, HA_CENTER, HA_RIGHT };		// Horizontal text alignment.
	using VerticalAlignment     = enum { VA_TOP, VA_CENTER, VA_BOTTOM };		// Vertical text alignment.
	using HorizontalOrientation = enum { HO_LEFT, HO_RIGHT };					// Horizontal content orientation.
	using VerticalOrientation   = enum { VO_TOP, VO_BOTTOM };					// Vertical content orientation.	
	using TextDirection         = enum { TD_UP, TD_DOWN, TD_LEFT, TD_RIGHT };	// Vertical content orientation.	

private:

	using ASCIIUnion = struct { char y; char x0; char x1; };					// y = f ( x0, x1 )

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Constants
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// Character constants.
		
	static const char CH_NEW_LINE               = (char) 0x0A;
	static const char CH_SPACE                  = (char) 0x20;
	static const char CH_BLOCK                  = (char) 0xFE;
	static const char CH_FULL_BLOCK             = (char) 0xDB;
	static const char CH_BULLET_DOT             = (char) 0xF9;
	static const char CH_DOT                    = (char) 0xFA;
	static const char CH_LINE_SINGLE_VERTICAL   = (char) 0xB3;
	static const char CH_LINE_SINGLE_HORIZONTAL = (char) 0xC4;	
	static const char CH_LINE_SINGLE_CROSS      = (char) 0xC5;
	static const char CH_BLOCK_100              = (char) CH_FULL_BLOCK;
	static const char CH_BLOCK_75               = (char) 0xB2;
	static const char CH_BLOCK_50               = (char) 0xB1;
	static const char CH_BLOCK_25               = (char) 0xB0;
	static const char CH_BLOCK_0                = (char) CH_SPACE;
	static const char CH_HASH                   = (char) 0x23;
	static const char CH_SINGLE_SINGLE          = (char) 0xC5;		// ┼
	static const char CH_DOUBLE_DOUBLE          = (char) 0xCE;		// ╬
	static const char CH_DOUBLE_SINGLE          = (char) 0xD8;		// ╪
	static const char CH_SINGLE_DOUBLE          = (char) 0xD7;		// ╫

	// Default character constants.

	const char CH_DEFAULT_BLANK = CH_SPACE;			// Used as the default blank charcter for white space and clearing the buffer.

private:

	// General parameters

	const int  C_DEFAULT_WIDTH          = 80;
	const int  C_DEFAULT_HEIGHT         = 60;
	const bool C_DEFAULT_SMART_OVERLAY  = true; 
	const char C_HORIZONTAL_BAR_STYLE_1 = 0x01;		// 0x00 = Transparent, 0x01 = High granularity, 0x02 ≤ Character to render.
	const char C_HORIZONTAL_BAR_STYLE_2 = 0x20;
	const char C_VERTICAL_BAR_STYLE_1   = 0x01;		// 0x00 = Transparent, 0x01 = High granularity, 0x02 ≤ Character to render.
	const char C_VERTICAL_BAR_STYLE_2   = 0x20;

	// Messages

	const string EXEPTION_MESSAGE_00 { "EXCEPTION: "                                                          };
	const string EXEPTION_MESSAGE_01 { "width and height both need to be natural numbers, greater than zero." };
	const string EXEPTION_MESSAGE_02 { "width needs to be a natural number, greater than zero."               };
	const string EXEPTION_MESSAGE_03 { "height needs to be a natural number, greater than zero."              };
	const string EXEPTION_MESSAGE_04 { "Co-ordinates out of bounds."                                          };

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Functions.
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// Constructors and destructors

	ConsoleTextBuffer ();
	ConsoleTextBuffer ( int width, int height );
	ConsoleTextBuffer ( int width, int height, char ch );

	~ConsoleTextBuffer ();

	// Drawing functions.
	
	void initialize            ( int width, int height, char ch );	
	void clear_buffer          ();
	void clear_buffer          ( char ch );
	void draw_char             ( int x, int y, char ch );
	void draw_text             ( int x, int y, string text );
	void draw_text             ( int x, int y, TextDirection text_direction, string text );
	void draw_horizontal_line  ( int x, int y, int length, char ch );
	void draw_vertical_line    ( int x, int y, int length, char ch );
	void draw_rectangle        ( int x, int y, int width, int height, char ch );
	void draw_filled_rectangle ( int x, int y, int width, int height, char ch );
	void draw_buffer           ( int x, int y, ConsoleTextBuffer buffer, char transparency_char );	// TODO:

	// Query functions.

	char              get_char   ( int x, int y );
	string            get_text   ( int x, int y, int width );	
	ConsoleTextBuffer get_buffer ( int x, int y, int width, int height );	// TODO:

	// Specialized drawing functions.

	void draw_text_pixel ( int x, int y, int    color );	// color ϵ [0,1,2,3,4], where 0 = 0%, 1 = 25%, 2 = 50%, 3 = 75%, 4 = 100%
	void draw_text_pixel ( int x, int y, double color );	// color ϵ [0.0..1.0],  where 0.0 = 0%, 0.25 = 25%, 0.5 = 50%, 0.75 = 75%, 1.0 = 100% 

	// Input/output functions.

	void flush ();
	void save  ( string file_name );
	void load  ( string file_name,  int width, int height );
	
private:

	// Private utility functions.

	void initialize_buffer          ( int width, int height, char ch );
	void initialize_ascii_union     ();
	char ascii_union                ( char ch0, char ch1 );
	void draw_text_horizontal_right ( int x, int y, string text );
	void draw_text_horizontal_left  ( int x, int y, string text );
	void draw_text_vertical_down    ( int x, int y, string text );
	void draw_text_vertical_up      ( int x, int y, string text );

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Accessors and mutators
	//--------------------------------------------------------------------------------------------------------------------------------------
	
public:

	// Accessors

	string get_text_buffer () { return this->text_buffer; };
	
	// Mutators

	void set_text_buffer ( string text_buffer ) { this->text_buffer = text_buffer; };

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Member data.
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	int  width                 { C_DEFAULT_WIDTH         };
	int  height                { C_DEFAULT_HEIGHT        };
	bool smart_overlay_enabled { C_DEFAULT_SMART_OVERLAY };

	string text_buffer { "" };

private:

	vector <ASCIIUnion> ascii_union_table;	
};


