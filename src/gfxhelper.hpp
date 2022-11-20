#ifndef GFXHELPER_HPP
#define GFXHELPER_HPP
#include "log.hpp"
#include "raylib.h"
#include <iostream>

/// Visual Debug Elements
/// - Circle ticker changes color on every call
class FLIPPING_CIRCLE
{
      public:
    Color primaryColor = RED;
    Color secondaryColor = YELLOW;
    void flip();
    void draw(int x, int y, float radious);
    FLIPPING_CIRCLE(Color _primaryColor, Color _secondaryColor);

      private:
    bool state = true;
    Color color;
};

#endif  // GFXHELPER_HPP
