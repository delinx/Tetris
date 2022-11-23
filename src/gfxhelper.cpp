#include "gfxhelper.hpp"
#include <raylib.h>

void FLIPPING_CIRCLE::flip()
{
    if(state)
    {
        color = primaryColor;
        state = !state;
    }
    else
    {
        color = secondaryColor;
        state = !state;
    }
}

FLIPPING_CIRCLE::FLIPPING_CIRCLE(Color _primaryColor, Color _secondaryColor)
{
    primaryColor = _primaryColor;
    secondaryColor = _secondaryColor;
};

void FLIPPING_CIRCLE::draw(i32 x, i32 y, f32 radious)
{
    DrawCircle(x, y, radious, color);
}

void Sprite::tick()
{
    if(actualX != x)
    {
        actualX = actualX > x ? actualX - 1 : actualX + 1;
    }
    if(actualY != y)
    {
        actualY = actualY > y ? actualY - 1 : actualY + 1;
    }
}

void Sprite::move(i32 _x, i32 _y)
{
    x = _x;
    y = _y;
}

void Sprite::moveInstant(i32 _x, i32 _y)
{
    x = _x;
    y = _y;
    actualX = _x;
    actualY = _y;
}


Sprite::Sprite(i32 _x, i32 _y, i32 _size, LOGIC::Grid *_grid)
{
    x = _x;
    y = _y;
    actualX = x;
    actualY = y;
    size = _size;
    grid = _grid;

    // TODO: Convert canvas into boxes
}

Sprite::~Sprite()
{
    delete grid;
}

void Sprite::draw()
{
    for(usize gX = 0; gX < grid->WIDTH; gX++)
    {
        for(usize gY = 0; gY < grid->HEIGHT; gY++)
        {
            i32 value = grid->get(gX, gY);
            if(value != 0)
            {
                // gX * size, gY * size
                switch(value)
                {
                    case 1:
                        DrawRectangle(actualX + (gX * size), actualY + (gY * size), size, size, RED);
                        break;
                    case 100:
                        DrawRectangle(actualX + (gX * size), actualY + (gY * size), size, size, Color { 30, 30, 30, 255 });
                        break;
                    case 101:
                        DrawRectangle(actualX + (gX * size), actualY + (gY * size), size, size, Color { 60, 60, 60, 255 });
                        break;
                }
            }
            else
            {
                if(Debug)
                {
                    DrawRectangle(actualX + (gX * size), actualY + (gY * size), size, size, BLACK);
                }
            }
        }
    }
}
