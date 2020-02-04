#include "food.h"
#include "mainwindow.h"
#include <cstdlib>

const std::string Food::foodTexturePath = "./resources/food.png";

Food::Food() : Object(0, 0)
{
    setTex(foodTexturePath);

    // create the position
    int height = mainwindow->getHeight();
    int width = mainwindow->getWidth();
    int x = std::rand() % (width - 1);
    int y = std::rand() % (height - 1);
    Pos tmp_ = {x, y};
    setPos(tmp_);

}


