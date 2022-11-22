#include "logic.hpp"

LOGIC::Grid::Grid(u32 width, u32 height)
{
    WIDTH = width;
    HEIGHT = height;
    grid = new i32[WIDTH * HEIGHT];
    for(usize i = 0; i < WIDTH * HEIGHT; i++)
    {
        grid[i] = 0;
    }
}
LOGIC::Grid::~Grid()
{
    delete[] grid;
}

void LOGIC::Grid::set(u32 x, u32 y, i32 value)
{
    grid[x + WIDTH * y] = value;
}

i32 LOGIC::Grid::get(u32 x, u32 y)
{
    return grid[x + WIDTH * y];
}

void LOGIC::Grid::fill(i32 num)
{
    for(usize i = 0; i < WIDTH * HEIGHT; i++)
    {
        grid[i] = num;
    }
}

void LOGIC::Grid::mask(i32 oldInt, i32 newInt)
{
    for(usize i = 0; i < WIDTH * HEIGHT; i++)
    {
        if(grid[i] == oldInt)
        {
            grid[i] = newInt;
        }
    }
}

void LOGIC::Grid::print()
{
    std::string buffer = "=== DEBUG print of grid === \n";
    for(u32 h = 0; h < HEIGHT; h++)
    {
        for(u32 w = 0; w < WIDTH; w++)
        {
            buffer += static_cast<char>(48 + get(w, h));
        }
        buffer += "\n";
    }

    log(buffer);
}

LOGIC::Field::Field(u32 width, u32 height)
{
    grid = new LOGIC::Grid(width, height);
}

LOGIC::Field::~Field()
{
    delete grid;
}

bool LOGIC::Field::canFit(i32 x, i32 y)
{
    // TODO: Cells above field should be valid for the shape to applear into field

    if(shape == NULL || grid == NULL)
    {
        // one of essential parts is NULL
        return false;
    }

    if(Debug)
    {
        log(" *** \n canFit shape: ");
        shape->print();
        log("canFit grid: ");
        grid->print();
    }
    // check if shape values of not 0 is within bounds of field
    for(usize shapeY = 0; shapeY < shape->WIDTH; shapeY++)
    {
        for(usize shapeX = 0; shapeX < shape->HEIGHT; shapeX++)
        {
            i32 value = shape->get((u32)shapeX, (u32)shapeY);
            // logsl(value);
            if(value != 0)
            {
                // check if cell can fit in X axis of field
                if((i32)shapeX + x >= 0 && (i32)shapeX + x < (i32)grid->WIDTH)
                {
                }
                else
                {
                    if(Debug)
                    {
                        log(" X (" + std::to_string(value) + ") " + std::to_string(shapeX) + ":" + std::to_string(shapeY) + " of shape does not fit within grid " + std::to_string(x) + ":" + std::to_string(y));
                    }
                    return false;
                }

                // check if cell can fit in Y axis of field
                if((i32)shapeY + y < (i32)grid->HEIGHT)
                {
                }
                else
                {
                    if(Debug)
                    {
                        log("Y (" + std::to_string(value) + ") " + std::to_string(shapeX) + ":" + std::to_string(shapeY) + " of shape does not fit within grid " + std::to_string(x) + ":" + std::to_string(y));
                    }
                    return false;
                }

                // check if cell of grid underneath is empty
                if(grid->get((u32)shapeX + (u32)x, (u32)shapeY + (u32)y) == 0)
                {
                }
                else
                {
                    if(Debug)
                    {
                        log("Y (" + std::to_string(value) + ") " + std::to_string(shapeX) + ":" + std::to_string(shapeY) + " of shape does not fit because cell is not empty " + std::to_string(x + (i32)shapeX) + ":" + std::to_string(y + (i32)shapeY) + "(" + std::to_string(grid->get((u32)shapeX + (u32)x, (u32)shapeY + (u32)y)) + ")");
                    }
                    return false;
                }
            }
        }
    }

    if(Debug)
    {
        log("***\n");
    }
    return false;
}
