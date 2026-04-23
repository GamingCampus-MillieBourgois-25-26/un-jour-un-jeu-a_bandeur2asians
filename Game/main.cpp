#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/A_DTS/DTScene.h"
#include "Scenes/TDS/TDS.h"
#include "Scenes/TETRIS_Nolan/Tetris.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<Tetris::TetrisScene>();


    engine->Run();

    return 0;
}
