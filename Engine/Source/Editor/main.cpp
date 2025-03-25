#include "Editor.h"
#include "Engine.h"

int main(int argc, char* args[])
{
	Taurus::TaurusEngine* engine = new Taurus::TaurusEngine();
	engine->StartEngine();

	Taurus::TaurusEditor* editor = new Taurus::TaurusEditor();
	editor->Initialize(engine);
	editor->Run();
	editor->ShutDown();

	//engine->Run();
	engine->ShutdownEngine();

    return 0;
}