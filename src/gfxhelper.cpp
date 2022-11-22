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
