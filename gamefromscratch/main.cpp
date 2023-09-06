#include "engine.h"



int main()
{
	GameEngine demo;
	if (demo.Construct({ 100,100 }, { 1280,800 }))
	{
		demo.Start();
	}

	return 0;

}




