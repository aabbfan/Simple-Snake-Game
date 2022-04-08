#ifndef COLLISIONLISTENER_H_
#define COLLISIONLISTENER_H_
#include "listener.h"
#include <list>
#include <memory>

class Object;
class Game;
class CollisionListener : public Listener
{
public:
    CollisionListener(Game* _game);
    ~CollisionListener() = default;
    
    void checkCollide(std::shared_ptr<Object> obj);
    void addOnCheckObject(std::shared_ptr<Object> obj);
    void removeCheckObject(std::shared_ptr<Object> obj);

    virtual void update() override;
private:
    std::list<std::shared_ptr<Object>> onCheckObjects;

    bool isCollide(std::shared_ptr<Object> obj_1, std::shared_ptr<Object> obj_2);
    void checkCollideWall(std::shared_ptr<Object> obj);
    void clearData();

    Game* game;
};

#endif