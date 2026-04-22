#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/A_DTS/DTS.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<DTS::DTSScene>();

    engine->Run();

    return 0;
}
