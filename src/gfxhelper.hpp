#ifndef GFXHELPER_HPP
#define GFXHELPER_HPP
#include "log.hpp"
#include "raylib.h"
#include "types.hpp"
#include <iostream>

/// Visual Debug Elements
/// - Circle ticker changes color on every call
class FLIPPING_CIRCLE
{
      public:
    Color primaryColor = RED;
    Color secondaryColor = YELLOW;
    /// flips between primaryColor and secondaryColor
    void flip();
    /// raylib draw function wrapper
    void draw(i32 x, i32 y, f32 radious);
    FLIPPING_CIRCLE(Color _primaryColor, Color _secondaryColor);

      private:
    bool state = true;
    Color color = primaryColor;
};

#endif  // GFXHELPER_HPP
