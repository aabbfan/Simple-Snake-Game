#include "listener.h"
#include "object.h"

Listener::Listener()
{

}

void Listener::update()
{
    
}

void Listener::attach(std::shared_ptr<Object> _object)
{
    this->object = std::weak_ptr<Object>(_object);
    (this->object).lock()->attach(shared_from_this());
}
