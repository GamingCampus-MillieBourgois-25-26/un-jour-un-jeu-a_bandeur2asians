#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/A_DTS/DTScene.h"
#include "Scenes/TDS/TDS.h"
#include "Scenes/TETRIS_Nolan/Tetris.h"
#include "Scenes/Tetris-Mahres/Tetris.h"
#include "Scenes/Bullet-L/BulletHell-M.h"
#include "Scenes/BulletHell/BulletHell.h"



int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    SceneModule* sceneModule = engine->GetModuleManager()->GetModule<SceneModule>();

    // Crée toutes les scènes sans les activer

    
   // sceneModule->CreateScene<TDS::TopDownShooter>();
   //sceneModule->CreateScene<DTS::DTSScene>();

   //sceneModule->CreateScene<TETRIS::TetrisScene>();
   //engine->GetModuleManager()->GetModule<SceneModule>()->SetScene<Tetris_Nolan::TetrisScene>();

   sceneModule->CreateScene<BulletHell::BulletHellScene>();



    engine->Run();

    return 0;
}
