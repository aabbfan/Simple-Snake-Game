#ifndef GAMELISTENER_H_
#define GAMELISTENER_H_

#include "listener.h"

class Game;
class GameListener : public Listener
{
public:
    GameListener();
    ~GameListener() = default;

    static GameListener* getInstance();
    void bindGame(Game* _game) noexcept;
    bool isGameBinded() noexcept;

    virtual bool isAccept(ListenEventType e) noexcept override;
    virtual void work(ListenEventType e, std::vector<void*> argv) override;
private:
    Game* game;
    static GameListener* ptr_gameListener;
};
#endif