//
// Created by kertz on 9/6/25.
//
#include <cmath>
#include <string>
#include "Window.hpp"
#include "Image.hpp"

struct MousePosition { double x; double y; };
MousePosition currentMousePos, lastMousePos;

void drawCircle(Image & image,
                const MousePosition pos,
                const double radius,
                const glm::vec4 color){
    double y = pos.y - radius;
    while ( y <= pos.y + radius ) {
        double x = pos.x - radius;
        while ( x <= pos.x + radius ) {
            if ( (pow((x - pos.x), 2) + pow((y - pos.y), 2) ) <= pow(radius, 2) )
                image.SetRGBA(
                  static_cast<int>(std::round(y)),
                   static_cast<int>(std::round(x)),
                    color);
            x += 1;
        }
        y += 1;
    }
}


void drawLine(Image & image,
              MousePosition p1,
              MousePosition p2,
              const double radius,
              const glm::vec4 color){

    if (const int maxWidth = image.GetWidth();
        p1.x < 0 or p1.x > maxWidth or p2.x < 0 or p2.x > maxWidth)
        return;

    if (const int maxHeight = image.GetHeight();
        p1.y < 0 or p1.y > maxHeight or p2.y < 0 or p2.y > maxHeight)
        return;

    const double dx = p2.x - p1.x;
    if(const double dy = p2.y - p1.y; std::abs(dx) >= std::abs(dy)){
        const double m = dy / dx;
        if(dx < 0)
            std::swap(p1, p2);

        double x = p1.x;
        double y = p1.y;
        while (x <= p2.x) {
            drawCircle(image, {x,y}, radius, color);
            ++x;
            y += m;
        }
    } else {
        const double m = dx / dy;

        if(dy < 0)
            std::swap(p1, p2);
        double x = p1.x;
        double y = p1.y;
        while (y <= p2.y) {
            drawCircle(image, {x,y}, radius, color);
            ++y;
            x += m;
        }
    }
}

MousePosition scaleMousePosition(const Window & window, const Image & image, const double x, const double y) {
    const double scale_factor_x = static_cast<double> (image.GetWidth()) / static_cast<double> (window.getBufferSize().width);
    const double scale_factor_y = static_cast<double> (image.GetHeight()) / static_cast<double> (window.getBufferSize().height);
    return {x * scale_factor_x, image.GetHeight() - y * scale_factor_y};
}