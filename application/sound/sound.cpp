
#include "stdafx.h"

#include <iostream>
#include <windows.h>

using namespace std;

int main ( int argc, char* argv[] )
{	
	const int C_FREQUENCY_LIST_SIZE = 16;
	const int C_PERIOD_LIST_SIZE    = 16;

	int f [ C_FREQUENCY_LIST_SIZE ];
	int p [ C_PERIOD_LIST_SIZE ];
	int i { 0 };
	int x { 0 };

	if ( argc == 3 )
	{
		i    = 0;
		f[i] = atoi ( argv [ 1 ] );
		p[i] = atoi ( argv [ 2 ] );

		Beep ( f[i], p[i] );
	}
	else if ( argc == 2 )
	{
		x = atoi ( argv [ 1 ] );
		
		i       = 0;
		f [ i ] =  8000; ++i;
		f [ i ] = 10000; ++i;
		f [ i ] = 12000; ++i;

		i       = 0;
		p [ i ] =  50; ++i;
		p [ i ] = 100; ++i;
		p [ i ] = 200; ++i;		
		
		switch ( x )
		{
			case 0:
				
				Beep ( f[1], p[0] );
				Beep ( f[1], p[0] );
				Beep ( f[2], p[2] );
				break;

			case 1:
				Beep ( f[1], p[0] );
				Beep ( f[1], p[0] );
				Beep ( f[0], p[0] );
				break;

			case 2:
				Beep ( f[0], p[0] );
				Beep ( f[0], p[0] );
				Beep ( f[0], p[0] );				
				break;

			case 3:
				Beep ( f[1], p[0] );
				Beep ( f[1], p[0] );
				Beep ( f[1], p[0] );				
				break;

			default:
				Beep ( f[1], p[1] );
		}
	}
	else
	{
		cout << endl;
		cout << "PROGRAM:       sound.exe"            << endl;
		cout << "VERSION:       1.0"                  << endl;
		cout << "RELEEASE DATE: 2016-04-04"           << endl;
		cout << "AUTHOR:        Rohin A Gosling"      << endl;
		cout << "USAGE:         sound f p"            << endl;
		cout << "               f = Freequency in Hz" << endl;
		cout << "               p = Periiod in ms"    << endl;
	}

	return 0;
}

