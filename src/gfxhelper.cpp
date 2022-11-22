#include "gfxhelper.hpp"

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


Sprite::Sprite(i32 _x, i32 _y, i32 _width, i32 _height, f32 _rot)
{
    x = _x;
    y = _y;
    actualX = x;
    actualY = y;
    width = _width;
    height = _height;
    rot = _rot;

    Canvas = LoadRenderTexture(_width, _height);
    SetTextureFilter(Canvas.texture, TEXTURE_FILTER_POINT);
}

void Sprite::drawCanvas()
{
    BeginTextureMode(Canvas);
    DrawRectangle(0, 0, width, height, RED);
    EndTextureMode();
}

void Sprite::draw()
{
    DrawTextureEx(Canvas.texture, Vector2 { (f32)actualX, (f32)actualY }, rot, 1.f, WHITE);
}
