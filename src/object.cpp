#include "object.h"
#include "collisionListener.h"
#include <iostream>

Object::Object(int _x, int _y)
        : position{_x, _y}
{

}

void Object::setTex(const std::string& path)
{
    texture.loadFromFile(path);
    radius = texture.getHeight() / 2;
}

void Object::setPos(Pos _position) noexcept
{
    position = _position;
}

void Object::render()
{
    texture.render(position.x, position.y);
}

Pos Object::getPos() noexcept
{
    return position;
}

Texture& Object::getTexture() noexcept
{
    return texture;
}

int Object::getRadius() noexcept
{
    return radius;
}

void Object::notify(ObjectEvent e)
{
    if (e == Object_moved)
    {
        for (auto i : g_ListenerList)
        {
            if (i->isAccept(checkCollision) == false) continue;
            i->work(ListenEventType::checkCollision, { (void*)this });
        }
    }

    if (e == Object_show)
    {
        for (auto i : g_ListenerList)
        {
            if (i->isAccept(addOnCheckCollisonObject) == false) continue;
            i->work(ListenEventType::addOnCheckCollisonObject, { (void*)this });
        }
    }

    if (e == Object_disppear)
    {
        for (auto i : g_ListenerList)
        {
            if (i->isAccept(removeOnCheckCollisionObject) == false) continue;
            i->work(ListenEventType::removeOnCheckCollisionObject, { (void*)this });
        }
    }
}
