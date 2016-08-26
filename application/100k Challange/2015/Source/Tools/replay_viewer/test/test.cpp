#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void test ()
{
	vector <string> v;
	int i;

	v = vector <string> ( 10 );
	i = int ( 3 );
	v [ i ] = "Hello World!";
	v [ i ][ v [ i ].length() - 1 ] = 'X';

	cout << endl;
	cout << "i       = " << i       << endl;
	cout << "v [ i ] = " << v [ i ] << endl;
}

int main ( int argc, char* argv[] )
{
	test ();

	return 0;
}


