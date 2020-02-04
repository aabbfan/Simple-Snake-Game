#ifndef NODE_H_
#define NODE_H_
#include "object.h"

class Node : public Object
{
public:
    Node(int _x, int _y, ColorType _color);
    ~Node() = default;
    Node(const Node&) = default;
    Node(Node&&) = default;

    void setdirection(int _dire) noexcept;
    void setHead() noexcept;
    void cancelHead(ColorType _color_behind_me) noexcept;
    bool isNodeAHead() noexcept;
    ColorType getColor() noexcept;

    virtual void render();

    static const std::string headResourcePath;
    static const std::string purpleBodyResourcePath;
    static const std::string blueBodyReSourcePath;
    static const int pictureDirection;
private:
    bool isHead;
    int direction;  // the direction angle's range is -180
                    // to 180. 0 is the right, 90 is the up.

    ColorType color;
};

#endif