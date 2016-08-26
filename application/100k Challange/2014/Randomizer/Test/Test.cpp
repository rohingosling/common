
#include "stdafx.h"

#include <iostream>

using namespace std;

class Test
{
	public:

	using Integer = long;
};

class Application
{
	public:

	void Run ();
};

int main ( int argc, char* argv [] )
{
	Application application;

	application.Run ();

	system ( "pause" );

	return 0;
}

void Application::Run ()
{
	Test::Integer i = 0;

	cout << "x = " << i << endl;
}


