#ifndef FOOD_H_
#define FOOD_H_

#include "object.h"
#include <string>
class AudioListener;
class Food : public Object, public std::enable_shared_from_this<Food>
{
public:
    Food();
    ~Food() = default;
    
    static const std::string foodTexturePath;
private:
};
#endif