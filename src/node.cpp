#include "node.h"

const std::string Node::headResourcePath = "./resources/head.png";
const std::string Node::purpleBodyResourcePath = "./resources/body_purple.png";
const std::string Node::blueBodyReSourcePath = "./resources/body_blue.png";
const int Node::pictureDirection = 90;

Node::Node(int _x, int _y, ColorType _color)
            : Object(_x, _y)
            , color(_color), isHead(false)
{

}

void Node::setHead() noexcept
{
    isHead = true;
    setTex(headResourcePath);
}

void Node::cancelHead(ColorType _color_behind_me) noexcept
{
    isHead = false;
    color = (ColorType)((_color_behind_me + 1) % 2);
    
    switch (color)
    {
    case purple:
        setTex(purpleBodyResourcePath);
        break;
    
    case blue:
        setTex(blueBodyReSourcePath);
        break;
    default:
        setTex(purpleBodyResourcePath);
    }
}

ColorType Node::getColor() noexcept
{
    return color;
}

bool Node::isNodeAHead() noexcept
{
    return isHead;
}

void Node::setdirection(int _dire) noexcept
{
    direction = _dire;
}

void Node::render()
{
    getTexture().render(getPos().x, getPos().y, nullptr, pictureDirection - direction);
}
