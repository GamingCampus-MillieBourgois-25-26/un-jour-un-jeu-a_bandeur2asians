#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/A_DTS/DTScene.h"
#include "Scenes/TDS/TDS.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<TDS::TopDownShooter>();


    engine->Run();

    return 0;
}
