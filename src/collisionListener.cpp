#include "collisionListener.h"
#include "object.h"
#include "mainwindow.h"

CollisionListener* CollisionListener::coll = new CollisionListener();

CollisionListener::CollisionListener() : Listener()
{
}

void CollisionListener::addOnCheckObject(Object* obj)
{
    if (obj == nullptr) return;
    for (auto i : onCheckObjects)
    {
        if (i == obj) return;
    }
    
    onCheckObjects.push_back(obj);
}

void CollisionListener::removeCheckObject(Object* obj)
{
    if (obj == nullptr) return;
    for (auto it = onCheckObjects.begin(); it != onCheckObjects.end(); it++)
    {
        if (*it == obj)
        {
            onCheckObjects.erase(it);
            return;
        }
    }
}

CollisionListener* CollisionListener::getInstance()
{
    if (coll == nullptr)
    {
        coll = new CollisionListener();
    }
    return coll;
}

void CollisionListener::checkCollide(Object* obj)
{
    if (obj == nullptr) return;

    checkCollideWall(obj);

    for (auto i : onCheckObjects)
    {
        if (i == obj) continue; 
        if (isCollide(i, obj) == true)
        {
            notify(ListenEventType::collideFood, { i });
            break;
        }
    }
}

void CollisionListener::checkCollideWall(Object* obj)
{
    bool tmp_ = false;
    if (obj->getPos().x <= 0 || obj->getPos().x >= mainwindow->getWidth())
    {
        tmp_ = true;
    }

    if (obj->getPos().y <= 0 || obj->getPos().y >= mainwindow->getHeight())
    {
        tmp_ = true;
    }
    
    if (tmp_ == true)
    {
        notify(ListenEventType::collideWall, { });
    }
}

bool CollisionListener::isCollide(Object* obj_1, Object* obj_2)
{
    int distance = 0;
    
    int tmp_;
    tmp_ = (obj_1->getPos().x - obj_2->getPos().x);
    distance += tmp_ * tmp_;

    tmp_ = (obj_1->getPos().y - obj_2->getPos().y);
    distance += tmp_ * tmp_;

    int min_distance = obj_1->getRadius() + obj_2->getRadius();
    min_distance *= min_distance;

    if (min_distance >= distance)
    {
        return true;
    }
    return false;
}

bool CollisionListener::isAccept(ListenEventType e) noexcept
{
    if (e == checkCollision)
    {
        return true;
    }
    
    if (e == addOnCheckCollisonObject)
    {
        return true;
    }

    if (e == removeOnCheckCollisionObject) return true;

    if (e == gameOver) return true;

    return false;
}

void CollisionListener::work(ListenEventType e, std::vector<void*> argv)
{
    if (e == ListenEventType::checkCollision && argv.size() == 1)
    {
        Object* tmp_ = (Object*)argv[0];
        checkCollide(tmp_);
    }

    if (e == ListenEventType::addOnCheckCollisonObject && argv.size() == 1)
    {
        Object* tmp_ = (Object*)argv[0];
        addOnCheckObject(tmp_);
    }

    if (e == ListenEventType::removeOnCheckCollisionObject && argv.size() == 1)
    {
        Object* tmp_ = (Object*)argv[0];
        removeCheckObject(tmp_);
    }

    if (e == ListenEventType::gameOver && argv.empty())
    {
        clearData();
    }
}

void CollisionListener::clearData()
{
    onCheckObjects.clear();
}
