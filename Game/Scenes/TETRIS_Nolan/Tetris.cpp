#include "Tetris.h"
#include "TETRIS_Nolan/TetrisGame.h"
#include "WindowModule.h"

Tetris_Nolan::TetrisScene::TetrisScene() : Scene("Tetris")
{
    WindowModule* window = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>();
    window->SetSize({ 640u, 680u });
    window->SetTitle("Tetris");

    GameObject* game = CreateGameObject("TetrisGame");
    game->SetPosition({ 0.f, 0.f });
    game->CreateComponent<Tetris::TetrisGame>();
}