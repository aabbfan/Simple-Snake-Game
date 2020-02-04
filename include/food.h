#ifndef FOOD_H_
#define FOOD_H_

#include "object.h"
#include <string>
class Food : public Object
{
public:
    Food();
    ~Food() = default;
    
    static const std::string foodTexturePath;
private:
    
};
#endif