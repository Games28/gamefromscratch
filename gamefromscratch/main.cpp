#include "engine.h"



int main()
{
	GameEngine demo;
	if (demo.Construct({ 30,30 }, { 1280,800 }))
	{
		demo.Start();
	}

	return 0;

}




