#ifndef LISTENER_H_
#define LISTENER_H_

#include <memory>

class Object;
class Listener : public std::enable_shared_from_this<Listener>
{
public:
    Listener();
    void attach(std::shared_ptr<Object> object);
    virtual ~Listener() = default;

    virtual void update();

protected:
    std::weak_ptr<Object> object;
};

#endif