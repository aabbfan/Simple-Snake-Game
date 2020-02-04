#include "gameListener.h"
#include "game.h"
#include <iostream>

GameListener* GameListener::ptr_gameListener = new GameListener();

GameListener::GameListener()
{
    game = nullptr;
}

GameListener* GameListener::getInstance()
{
    return ptr_gameListener;
}

void GameListener::bindGame(Game* _game) noexcept
{
    if (_game == nullptr) return;
    game = _game;
}

bool GameListener::isGameBinded() noexcept
{
    return !(game == nullptr);
}

bool GameListener::isAccept(ListenEventType e) noexcept
{
    if (e == ListenEventType::collideWall) return true;
    if (e == ListenEventType::collideFood) return true;
    return false;
}

void GameListener::work(ListenEventType e, std::vector<void*> argv)
{
    if (e == ListenEventType::collideWall && argv.empty())
    {
        if (game != nullptr) 
        {
            notify(ListenEventType::gameOver, { });
            game->setGameLost();
        }
        game = nullptr;
    }

    if (e == ListenEventType::collideFood && argv.size() == 1)
    {
        if (game != nullptr && argv[0] != nullptr)
        {
            game->snakeCollideFood((Food*)argv[0]);
        }
    }
}
