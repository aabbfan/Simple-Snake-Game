#include "collisionListener.h"
#include "object.h"
#include "food.h"
#include "mainwindow.h"
#include "game.h"

CollisionListener::CollisionListener(Game* _game) : Listener(), game(_game)
{
}

void CollisionListener::addOnCheckObject(std::shared_ptr<Object> obj)
{
    if (!obj) return;
    for (auto i : onCheckObjects)
    {
        if ( i->getID() == obj->getID()) return;
    }
    
    onCheckObjects.push_back(obj);
}

void CollisionListener::removeCheckObject(std::shared_ptr<Object> obj)
{
    if (!obj) return;
    for (auto it = onCheckObjects.begin(); it != onCheckObjects.end(); it++)
    {
        if ((*it)->getID() == obj->getID())
        {
            onCheckObjects.erase(it);
            return;
        }
    }
}

void CollisionListener::checkCollide(std::shared_ptr<Object> obj)
{
    if (obj == nullptr) return;

    checkCollideWall(obj);

    for (auto i : onCheckObjects)
    {
        if (i == obj) continue; 
        if (isCollide(i, obj) == true)
        {
            std::shared_ptr<Food> tmp = std::dynamic_pointer_cast<Food>(i);
            game->snakeCollideFood(tmp);
            break;
        }
    }
}

void CollisionListener::checkCollideWall(std::shared_ptr<Object> obj)
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
        game->setGameLost();
    }
}

bool CollisionListener::isCollide(std::shared_ptr<Object> obj_1, std::shared_ptr<Object> obj_2)
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

void CollisionListener::update()
{
    checkCollide(object);
}

void CollisionListener::clearData()
{
    onCheckObjects.clear();
}
