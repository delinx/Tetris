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

    if(shape == NULL)
    {
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
                log(value);
                log(shapeX);
                log(shapeY);
            }
        }
    }

    if(Debug)
    {
        log("***\n");
    }
    return false;
}
