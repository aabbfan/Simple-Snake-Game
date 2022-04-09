#ifndef OBJECT_H_
#define OBJECT_H_
#include "utils.h"
#include "texture.h"
#include <memory>
#include <vector>

class Listener;
class Object
{
public:
    Object(int _x, int _y);
    virtual ~Object() = default;

    void setPos(Pos _position) noexcept;
    void setTex(const std::string&);
    void setRadius(int _radius);
    
    virtual void render();

    void notify();
    void attach(std::shared_ptr<Listener> listener);

    unsigned int getID();
    
    Pos getPos() noexcept;
    Texture& getTexture() noexcept;
    int getRadius() noexcept;
private:
    Pos position;
    Texture texture;
    int radius;
    unsigned int id;

    std::vector<std::weak_ptr<Listener>> listeners;
};

#endif