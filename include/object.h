#ifndef OBJECT_H_
#define OBJECT_H_
#include "utils.h"
#include "texture.h"

enum ObjectEvent
{
    Object_show,
    Object_disppear,
    Object_moved
};

class Object
{
public:
    Object(int _x, int _y);
    virtual ~Object() = default;

    void setPos(Pos _position) noexcept;
    void setTex(const std::string&);
    
    virtual void render();

    void notify(ObjectEvent e);
    Pos getPos() noexcept;
    Texture& getTexture() noexcept;
    int getRadius() noexcept;
private:
    Pos position;
    Texture texture;
    int radius;
};

#endif