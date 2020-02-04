#ifndef LISTENER_H_
#define LISTENER_H_

#include <vector>

enum ListenEventType
{
    checkCollision,
    collideWall,
    addOnCheckCollisonObject,
    collideFood,
    removeOnCheckCollisionObject,
    gameOver
};

class Object;
class Listener
{
public:
    Listener();
    virtual ~Listener() = default;

    void notify(ListenEventType e, std::vector<void*> argv);
    virtual bool isAccept(ListenEventType e) noexcept;
    virtual void work(ListenEventType e, std::vector<void*> argv);
};

extern std::vector<Listener*> g_ListenerList;
#endif