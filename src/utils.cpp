#include "utils.h"

int formatAngle(int angle)
{
    while (angle > 180)
    {
        angle -= 360;
    }

    while (angle < - 180)
    {
        angle += 360;
    }
    return angle;
}
