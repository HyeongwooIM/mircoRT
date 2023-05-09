#include "scene.h"

t_canvas    canvas(int  width, int height)
{
    t_canvas canvas;

    canvas.width = width;
    canvas.height = height;
    canvas.aspect_ratio = (double)width / (double)height;
    // canvas.aspect_ratio = (double)-0.9;
    return (canvas);
}