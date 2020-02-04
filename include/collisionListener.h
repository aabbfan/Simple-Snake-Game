#ifndef COLLISIONLISTENER_H_
#define COLLISIONLISTENER_H_
#include "listener.h"
#include <list>

class CollisionListener : public Listener
{
public:
    CollisionListener();
    ~CollisionListener() = default;
    
    void checkCollide(Object* obj);
    void addOnCheckObject(Object* obj);
    void removeCheckObject(Object* obj);

    virtual bool isAccept(ListenEventType e) noexcept override;
    virtual void work(ListenEventType e, std::vector<void*> argv) override;
    static CollisionListener* getInstance();
private:
    std::list<Object*> onCheckObjects;
    static CollisionListener* coll;

    bool isCollide(Object* obj_1, Object* obj_2);
    void checkCollideWall(Object* obj);
    void clearData();
};

#endif