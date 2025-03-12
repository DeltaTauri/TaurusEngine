#include "Engine.h"

int main(int argc, char* args[])
{
    Taurus::TaurusEngine* engine = new Taurus::TaurusEngine();
	
	engine->StartEngine();
	engine->Run();
	engine->ShutdownEngine();

    return 0;
}