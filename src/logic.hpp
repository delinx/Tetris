#ifndef LOGIC_HPP
#define LOGIC_HPP
#include "log.hpp"
#include "types.hpp"
#include <iostream>

class LOGIC
{
      public:
    /// 2D array ofi32s with X/Y getters and setters
    struct Grid
    {
        u32 WIDTH;
        u32 HEIGHT;
        i32 *grid;

        /// make a newi32 array of X*Y size
        Grid(u32 width, u32 height);
        ~Grid();

        /// set XY to giveni32
        void set(u32 x, u32 y, i32 value);

        /// get XY value
        i32 get(u32 x, u32 y);

        /// override array with value
        void fill(i32 num);

        /// replace old value with new value
        void mask(i32 oldInt, i32 newInt);

        /// prints grids' values as rows and columns
        void print();
    };

    struct Field
    {
        bool Debug = false;
        Grid *grid = NULL;
        Grid *shape = NULL;
        Field(u32 width, u32 height);
        ~Field();

        /// check if shape can fit in the XY position of grid
        bool canFit(i32 x, i32 y);
        /// attemps to move shape with gravity on grid
        void gravityTick();
        /// debug print grid + shape
        void printWithShape(i32 x, i32 y);

        // i32 findSolvedRow();
    };
};

#endif  // LOGIC_HPP
