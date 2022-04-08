#include "object.h"
#include "listener.h"

Object::Object(int _x, int _y)
        : position{_x, _y}
{
    static int tmp_id = 0;
    id = ++tmp_id;
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

void Object::notify()
{
    for (auto i : listeners)
    {
        i->update();
    }
}

void Object::attach(std::shared_ptr<Listener> listener)
{
    listeners.push_back(listener);
}

unsigned int Object::getID()
{
    return id;
}

void Object::setRadius(int _radius)
{
    radius = _radius;
}
