////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project:          Win32 OpenGL Window Manager
// Application Name: OpenGL Template
// Version:          1.0
// Author:           Rohin Gosling
// Year:             2014
//
// Description:
//
// Open GL Window Manager
//
// ┌─────────────┐              ┌─────────────┐              ┌─────────────┐              ┌─────────────┐
// │             │   Draws to   │             │  Copied to   │             │  Shows in    │ Application │
// │   OpenGL    │ ∙∙∙∙∙∙∙∙∙∙∙► │    HGLRC    │ ∙∙∙∙∙∙∙∙∙∙∙► │     HDC     │ ∙∙∙∙∙∙∙∙∙∙∙► │   Window    │
// │             │              │             │              │             │              │             │
// └─────────────┘              └─────────────┘              └─────────────┘              └─────────────┘
//
// 1.  Create a regular Win32 window.
//
//     InitInstance ()  
//
// 2.  Get the Device Context (DC) of the Win32 window..
//
//     InitInstance ()  
//     {
//       Step 1.
//       ...
//       hdc = GetDC ( hwnd );
//     }
//
// 3.  Set the HDC pixel format.
//
//     - Create a PFD (Pixel Format Descriptor)
//     - ChoosePixelFormat ()
//     - SetPixelFormat ()
//
// 4.  Create a rendering context (HGLRC).
//
//     wglCreateContext ()
//
//     - Create a surface for OpenGL to draw on.
//     - The HGLRC uses the same pixel format as the DC (Device Context) 
//       of our window.
//
// 5.  Link the HGLRC to the HDC.
//
//     wglMakeCurrent ()
//
//     - Link the rendering context (HGLRC) to the device context (HDC) of 
//       our window.
//
// 6.  Draw OpenGL graphics to the HGLRC.
//
//     OpenGL outputs it's screen buffer to the HGLRC.
//
// 7.  Perform double buffer swap.
//
//     SwapBuffers ( hdc );	
//
//     - Doulbe buffering is configured in step 2.
//     - Each time we draw to the back buffer of the HDC, we will call 
//       SwapBuffers to send the completed image to the Win32 application window.
//
// REFERENCES:
//
//  - MSDN
//    http://msdn.microsoft.com/en-us/library/ms537556(VS.85).aspx    
//
//  - TURORIAL - Bobobobo’s Weblog.
//    http://bobobobo.wordpress.com/2008/02/11/opengl-in-a-proper-windows-app-no-glut/
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Win32 headers.

#include "stdafx.h"
#include "Minimizer1.h"

// C and C++ headers.

#include <stdio.h>
#include <string.h>
#include <math.h>

// C++11 headers.

#include <string>
#include <iostream>
#include <sstream>

// OpenGL headers.

#include <gl/gl.h>
#include <gl/glu.h>

// OpenGL libraries.

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")


//----------------------------------------------------------------------------------------------------------------------
// Gloabal constants.
//----------------------------------------------------------------------------------------------------------------------

// Data constants.

const int  GC_WIN32_MAX_LOADSTRING = 100;		// String table, string size.
const int  GC_OPENGL_WINDOW_WIDTH  = 1600;		// OpenGL window width.
const int  GC_OPENGL_WINDOW_HEIGHT = 1000;		// OpenGL window height.
const bool GC_DEBUG                = false;		// General purpose debugging mode.

// String literals.

const LPCWSTR GSL_PFD_MODAL_TITLE         = TEXT ( "Pixel Format" );
const LPCWSTR GSL_PFD_MODAL_LABEL         = TEXT ( "Pixel Format ID: " );
const LPCWSTR GSL_PFD_EXEPTION            = TEXT ( "EXCEPTION: ChoosePixelFormat() failed to identify a conforming pixel format." );

//----------------------------------------------------------------------------------------------------------------------
//
// Global Win32 window data.
//
// Note:
//
// - We will only use this for Win32 window data.
// - We will not alow any other global variabeles, asside from one or more
//   string tables where required.
//
//----------------------------------------------------------------------------------------------------------------------

struct Win32Globals
{
	// Global Win 32 variables.

	public:

	TCHAR     szTitle       [ GC_WIN32_MAX_LOADSTRING ];	// Window class name.
	TCHAR     szWindowClass [ GC_WIN32_MAX_LOADSTRING ];	// Window title bar text. Usualy the applicaiton name.
	HINSTANCE hInst;										// Application instance handle.
	HWND      hWnd;											// Window handle.
	HDC       hdc;											// Device context handle.
	HGLRC     hglrc;										// OpenGL rendering context handle.
	int       windowWidth;									// Client width of Win32 window.
	int       windowHeight;									// Client height of Win32 window.

	// Singleton configuration.

	public:

	static Win32Globals* instance;	// Create the single instance.

	// Constructors.

	Win32Globals ( ) {}		// default constructor.
	Win32Globals ( const Win32Globals & source ) {}		// Disable copy constructor.
	Win32Globals ( Win32Globals      && source ) {}		// Disable move constructor.

	// Public singleton management functions.

	public:

	// Return the single instance, if it has been correctly created.

	Win32Globals* GetInstance ( )
	{
		if ( this->instance == nullptr )
		{
			this->instance = new Win32Globals ( );
		}

		return this->instance;
	}
};


//----------------------------------------------------------------------------------------------------------------------
// Declare our global Win32 data singleton. 
//----------------------------------------------------------------------------------------------------------------------

Win32Globals g;

//----------------------------------------------------------------------------------------------------------------------
// Function prototype, forward declerations.
//----------------------------------------------------------------------------------------------------------------------

// Win32.

ATOM				MyRegisterClass			( HINSTANCE hInstance );
BOOL				InitInstance			( HINSTANCE, int );
LRESULT CALLBACK	WndProc					( HWND, UINT, WPARAM, LPARAM );
INT_PTR CALLBACK	About					( HWND, UINT, WPARAM, LPARAM );
BOOL                CreateWin32Window       ( HINSTANCE, int );

// OpenGL.

void				InitializePixelFormat	();
void                mainLoop				();
void				renderScene				();
void                drawShape				();


//----------------------------------------------------------------------------------------------------------------------
// Win32 application entry point.
//----------------------------------------------------------------------------------------------------------------------

int APIENTRY _tWinMain
(
	_In_		HINSTANCE hInstance,		// Current instance of the application. 
	_In_opt_	HINSTANCE hPrevInstance,	// Handle to the previous instance of the application.
	_In_		LPTSTR    lpCmdLine,		// Application console command line, excluding the applicaton name.
	_In_		int       nCmdShow			// Window display state command.
)
{
	UNREFERENCED_PARAMETER ( hPrevInstance );
	UNREFERENCED_PARAMETER ( lpCmdLine );

 	// TODO: Place code here.

	MSG		msg;
	HACCEL	hAccelTable;

	// Initialize global strings

	if ( !GC_DEBUG )
	{
		LoadString ( hInstance, IDS_APP_TITLE, g.szTitle, GC_WIN32_MAX_LOADSTRING );
	}
	else
	{
		LoadString ( hInstance, IDS_APP_TITLE_DEBUG, g.szTitle, GC_WIN32_MAX_LOADSTRING );
	}
	
	LoadString      ( hInstance, IDC_MINIMIZER1, g.szWindowClass, GC_WIN32_MAX_LOADSTRING );

	// Register a standard Win32 winodow class.

	MyRegisterClass ( hInstance );

	// Perform application initialization:

	if ( !InitInstance ( hInstance, nCmdShow ) )
	{	
		return FALSE;
	}

	hAccelTable = LoadAccelerators ( hInstance, MAKEINTRESOURCE ( IDC_MINIMIZER1 ) );

	// Main message loop:

	while ( GetMessage ( &msg, NULL, 0, 0 ) )
	{
		if ( !TranslateAccelerator ( msg.hwnd, hAccelTable, &msg ) )
		{
			TranslateMessage	( &msg );
			DispatchMessage		( &msg );
		}
	}

	return (int) msg.wParam;
}


//----------------------------------------------------------------------------------------------------------------------
//
// FUNCTION:    MyRegisterClass()
//
// DESCRIPTION: Registers the window class.
//
//----------------------------------------------------------------------------------------------------------------------

ATOM MyRegisterClass ( HINSTANCE hInstance )
{
	WNDCLASS wc;

	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hbrBackground = ( HBRUSH ) GetStockObject ( DKGRAY_BRUSH );
	wc.hCursor       = LoadCursor ( NULL, IDC_ARROW );
	wc.hIcon         = LoadIcon ( NULL, IDI_APPLICATION );
	wc.hInstance     = hInstance;
	wc.lpfnWndProc   = WndProc;
	wc.lpszClassName = g.szWindowClass;
	wc.lpszMenuName  = MAKEINTRESOURCE ( IDC_MINIMIZER1 );
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	return RegisterClass ( &wc );
}

//----------------------------------------------------------------------------------------------------------------------
//
// FUNCTION:     InitInstance(HINSTANCE, int)
//
// DESCRIPTION:  Saves instance handle and creates main window
//
// COMMENTS:
//
//   In this function, we save the instance handle in a global variable and
//   create and display the main program window.
//
//----------------------------------------------------------------------------------------------------------------------

BOOL InitInstance ( HINSTANCE hInstance, int nCmdShow )
{	
	// And save the handle to our apllciation.

	g.hInst = hInstance;

	// Create a new Win32 window.

	if ( CreateWin32Window ( hInstance, nCmdShow ) )
	{
		// Show the window.

		ShowWindow   ( g.hWnd, nCmdShow );
		UpdateWindow ( g.hWnd );

		// Get and save the device context (DC) for the window that we have just created.

		g.hdc = GetDC ( g.hWnd );

		// Configure the pixel format.

		InitializePixelFormat ( );
		
		// Create a rendering context for OpenGL.

		g.hglrc = wglCreateContext ( g.hdc );

		// Link the rendering context (HGLRC) to the device context (HDC) of our window.

		wglMakeCurrent ( g.hdc, g.hglrc );

		// Launch main loop.

		mainLoop ();

		// Return with success.

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//  FUNCTION:
//
//  - WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  INPUT ARGUMENTS:
//
//  - WM_COMMAND:	Process the application menu.
//  - WM_PAINT:		Paint the main window.
//  - WM_DESTROY:	Post a quit message and return.
//
//  OUTPUT ARGUMENTS:
//
//  - N/A
//
//  DESCRIPTION:
//
//  - Processes messages for the main window.
//
//  REFERENCES:
//
//  - MSDN
//    http://msdn.microsoft.com/en-us/library/bb384843.aspx
//
//----------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	int			wmId;
	int			wmEvent;
	PAINTSTRUCT	ps;
	HDC			hdc;

	switch ( message )
	{
		case WM_CREATE:
		{	
		}
		break;

		case WM_COMMAND:
		{
			wmId = LOWORD ( wParam );
			wmEvent = HIWORD ( wParam );

			// Parse the menu selections:

			switch ( wmId )
			{
				case IDM_ABOUT:
				{
					DialogBox ( g.hInst, MAKEINTRESOURCE ( IDD_ABOUTBOX ), hWnd, About );
				}
				break;

				case IDM_EXIT:
				{
					DestroyWindow ( hWnd );
				}
				break;

				default:
				{
					return DefWindowProc ( hWnd, message, wParam, lParam );
				}

			} // switch
		}
		break;

		case WM_PAINT:
		{
			hdc = BeginPaint ( hWnd, &ps );

			// Do Win32 drawing here.

			EndPaint ( hWnd, &ps );
		}
		break;

		case WM_DESTROY:
		{
			// Disable the rendering context.

			wglMakeCurrent ( NULL, NULL );

			// Delete the rendering context (HGLRC).

			wglDeleteContext ( g.hglrc );

			// Release the window's device context (DC).

			ReleaseDC ( g.hWnd, g.hdc );

			// Post Win32 exit message.

			PostQuitMessage ( 0 );
		}
		break;

		default:
		{
			return DefWindowProc ( hWnd, message, wParam, lParam );
		}

	} // switch

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------
//
// Message handler for about box.
//
//----------------------------------------------------------------------------------------------------------------------

INT_PTR CALLBACK About ( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	UNREFERENCED_PARAMETER ( lParam );

	switch ( message )
	{
		case WM_INITDIALOG:
			return (INT_PTR) TRUE;

		case WM_COMMAND:
			if ( LOWORD ( wParam ) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog ( hDlg, LOWORD ( wParam ) );
				return ( INT_PTR )TRUE;
			}
			break;
	}

	return (INT_PTR) FALSE;
}

//----------------------------------------------------------------------------------------------------------------------
//
//  FUNCTION: BOOL CreateWin32Window ( HINSTANCE hInstance, int nCmdShow )
//
//  PURPOSE:  Create a new Win32 window.
//
//  DESCRIPTIN:
// 
//    Create a standard Win32 window.
//
//----------------------------------------------------------------------------------------------------------------------

BOOL CreateWin32Window ( HINSTANCE hInstance, int nCmdShow )
{
	// Get the screen width and height.

	long screenWidth  = GetSystemMetrics ( SM_CXSCREEN );
	long screenHeight = GetSystemMetrics ( SM_CYSCREEN );

	// Create a Win32 RECT to specify the position and dimentions of our drawing canvas.

	RECT rect;
	long width  = GC_OPENGL_WINDOW_WIDTH;
	long height = GC_OPENGL_WINDOW_HEIGHT;
	long top    = screenHeight / 2 - height / 2;	// Center window verticaly on screen.
	long left   = screenWidth / 2  - width / 2;		// Center window horizontaly on screen.

	SetRect ( &rect, left, top, left + width, top + height );

	// Save the drawing canvas dimentions to our global Win32 data store.

	g.windowWidth  = rect.right  - rect.left;
	g.windowHeight = rect.bottom - rect.top;

	// Set the total Win32 window size, to conform to the desired size of our client window dimentions.
	//
	// ┌──────────────┐ ∙ ∙ ∙ ┐	
	// ├──────────────┤       │
	// │┌────────────┐│ ∙ ┐   │<-- Win32 Window.
	// ││            ││   │<--│--- Client windows (OpenGLdrawing surface).
	// │└────────────┘│ ∙ ┘   │
	// └──────────────┘ ∙ ∙ ∙ ┘

	AdjustWindowRect ( &rect, WS_OVERLAPPEDWINDOW, false );

	// Create the window using the dimentions we have just specified.

	// Create a Win32 window.

	g.hWnd = CreateWindow
	(
		g.szWindowClass,			// Win32 window class name.
		g.szTitle,					// Window title text.
		WS_OVERLAPPEDWINDOW,		// Window style.
		rect.left,					// left.
		rect.top,					// Top.
		rect.right - rect.left,		// Width.
		rect.bottom - rect.top,		// Height.
		NULL,						// Parent window.
		NULL,						// Menu.
		hInstance,					// Application instance handle.
		NULL						// MDI parameter.
	);

	// return with an error if we are unable to create the window.

	if ( !g.hWnd )
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//----------------------------------------------------------------------------------------------------------------------
//
//  FUNCTION: void InitializePixelFormat ()
//
//  PURPOSE:  Configures the pixel format for use with OpenGL.
//
//  DESCRIPTIN:
// 
//  1. Create a pixel format descriptor (PFD), that meets our 'desired' 
//     requirments.
//
//  2. Call ChoosePixelFormat(), to let windows slect the ID of an appropriate 
//     pixel format, that most closely aproaches the paramters of the desired 
//     pixel format we originaly specified in step 1.
//
//  3. Next, we call call SetPixelFormat() to actualy set the pixel format, using
//     the integer ID returned by ChoosePixelFormat() in step 2.
//
//  NOTE:
//
//  - We use the security enhanced _stprintf_s version of the depreciated versions sprintf.
//
//  REFERENCES:
//
//  - MSDN
//    http://msdn.microsoft.com/en-us/library/ms537556(VS.85).aspx    
//
//  - TURORIAL - Bobobobo’s Weblog.
//    http://bobobobo.wordpress.com/2008/02/11/opengl-in-a-proper-windows-app-no-glut/
//
//----------------------------------------------------------------------------------------------------------------------

void InitializePixelFormat ()
{
	// Step 1: Create a pixel format descriptor, for our desired pixel format.
	//
	// - Initialize all fields to zero.
	// - We will only populate the fields we need, and leave the rest set to zero.

	PIXELFORMATDESCRIPTOR pfd = { 0 };

	pfd.nSize      = sizeof ( PIXELFORMATDESCRIPTOR );	// Size of the PFD struct.
	pfd.nVersion   = 1;									// Microsoft recomend setting the version to 1.
	pfd.iPixelType = PFD_TYPE_RGBA;						// Pixel vector structure: RGBA = (Red, Green, Blue, Alpha)
	pfd.cColorBits = 24;								// Color depth: 24 bit == 8 bits red, 8 bits green, 8 bits blue.
	pfd.cDepthBits = 32;								// Pixel depth, excluding alpha layer.

	// Configure PFD flags.

	pfd.dwFlags = PFD_SUPPORT_OPENGL					// Select graphics platform (OpenGL or DirectX).
		          |
		          PFD_DOUBLEBUFFER						// Enable double buffering.
		          |
		          PFD_DRAW_TO_WINDOW;					// Specify target surface (Application window vs. bitmap image).


	// Step 2: Select best pixel format that aproaches our  desired pixel format.
	//
	// - chosenPixelFormat returns an integer that indexes pixel formats known by windows.
	// - chosenPixelFormat returns 0 if there was an error, if it is unable to find a suitable pixel format.
	
	int chosenPixelFormat = ChoosePixelFormat ( g.hdc, &pfd );
	
	if ( chosenPixelFormat == 0 )
	{
		FatalAppExitW ( NULL, GSL_PFD_EXEPTION );		
	}
	else
	{
		// Show us the pixel format that has been selected.

		if ( GC_DEBUG )
		{
			TCHAR textBuffer [ GC_WIN32_MAX_LOADSTRING ];
			_stprintf_s ( textBuffer, _T ( "Pixel Format ID: %d" ), chosenPixelFormat );
			MessageBox  ( g.hWnd, textBuffer, GSL_PFD_MODAL_TITLE, MB_OK );
		}

		// Step 3: Set the pixel format using the pixel format given to us by Windows through chosenPixelFormat.

		int result = SetPixelFormat ( g.hdc, chosenPixelFormat, &pfd );


		// Show us if the configuration failed to set.

		if ( result == NULL )
		{
			FatalAppExit ( NULL, GSL_PFD_EXEPTION );
		}
	}
}


//----------------------------------------------------------------------------------------------------------------------
//
//  FUNCTION: void drawTestScene ()
//
//  PURPOSE:  To test that the OpenGL configuration has been successful.
//
//  DESCRIPTIN:
//
//    Draw a test scene.
//
//----------------------------------------------------------------------------------------------------------------------

void mainLoop ( void )
{
	renderScene ( );
}

//----------------------------------------------------------------------------------------------------------------------
//
//  FUNCTION: void renderScene ()
//
//  PURPOSE:  renders the scene.
//
//  DESCRIPTIN:
//
//    Draw a test scene.
//
//----------------------------------------------------------------------------------------------------------------------

void renderScene ( )
{
	// Clear the screen.

	glClearColor ( 0.0, 0.0, 0.0, 0.0 );
	glShadeModel ( GLU_FLAT );

	// Configure view port.

	glViewport ( 0, 0, g.windowWidth, g.windowHeight );

	// Configure the projection matrix

	glMatrixMode   ( GL_PROJECTION );
	glLoadIdentity ( );
	gluPerspective ( 45.0, ( float ) g.windowWidth / ( float ) g.windowHeight, 1, 1000 );

	// Configure the viewing transformation.

	glMatrixMode   ( GL_MODELVIEW );
	glLoadIdentity ();

	gluLookAt
	(
		0, 0, 10,
		0, 0, 0,
		0, 1, 0
	);


	// draw a shape.

	drawShape ();

	// Swap buffers.

	SwapBuffers ( g.hdc );
}

//----------------------------------------------------------------------------------------------------------------------
//
//  FUNCTION: void drawTestScene ()
//
//  PURPOSE:  To test that the OpenGL configuration has been successful.
//
//  DESCRIPTIN:
//
//    Draw a test scene.
//
//----------------------------------------------------------------------------------------------------------------------

void drawShape ( )
{
	glColor3f ( 1.0, 1.0, 1.0 );
	glBegin ( GL_POLYGON );

		GLfloat width  =  1.0;
		GLfloat height =  1.0;
		GLfloat dx     = -0.5;
		GLfloat dy     = -0.5;
		GLfloat x      =  width  + dx;
		GLfloat y      =  height + dy;
		GLfloat z      = 0.0;

		glVertex3f (  x,  y, z );
		glVertex3f (  x, -y, z );
		glVertex3f ( -x, -y, z );
		glVertex3f ( -x,  y, z );

	glEnd ();

	glFlush ();

}

