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

void LOGIC::Grid::rotate(bool clockwise)
{
    Grid *tmpGrid = new Grid(WIDTH, HEIGHT);

    for(unsigned int Sx = 0; Sx < WIDTH; Sx++)
    {
        for(unsigned int Sy = 0; Sy < HEIGHT; Sy++)
        {
            tmpGrid->set(Sx, Sy, get(Sy, Sx));
        }
    }

    // Mirror each column (i.e. switch index [i][j] to [i][size-j])
    //
    // Mirror columns for anti-clockwise
    // Mirror rows for clockwise
    for(unsigned int Sx = 0; Sx < WIDTH; Sx++)
    {
        for(unsigned int Sy = 0; Sy < HEIGHT; Sy++)
        {
            if(!clockwise)
            {
                set(Sx, Sy, tmpGrid->get(Sx, HEIGHT - 1 - Sy));
            }
            else
            {
                set(Sx, Sy, tmpGrid->get(WIDTH - 1 - Sx, Sy));
            }
        }
    }

    delete tmpGrid;
}
LOGIC::Grid *LOGIC::Grid::copy()
{
    Grid *tmp = new Grid(WIDTH, HEIGHT);

    for(int i = 0; i < WIDTH * HEIGHT; i++)
    {
        tmp->grid[i] = grid[i];
    }

    return tmp;
}


void LOGIC::Grid::checkFill(i32 v1, i32 v2)
{
    bool _colorChecker = false;
    for(usize y = 0; y < HEIGHT; y++)
    {
        for(usize x = 0; x < WIDTH; x++)
        {
            if(_colorChecker)
            {
                set((u32)x, (u32)y, v1);
            }
            else
            {
                set((u32)x, (u32)y, v2);
            }
            _colorChecker = !_colorChecker;
        }
        _colorChecker = !_colorChecker;
    }
}

void LOGIC::Field::shapeResetPos()
{
    yShape = -3;
    xShape = grid->WIDTH / 2 + 1;
}

LOGIC::Field::Field(u32 width, u32 height)
{
    grid = new LOGIC::Grid(width, height);
    shapeResetPos();

    // list of all possible shapes in the neutral rotation
    // 0         1       2       3       4       5       6
    // . . . .   . . .   . . .   . X .   X X X   . . X   X . .
    // X X X X   . O X   X O .   X O X   X 0 X   X O X   X O X
    // . .o. .   X X .   . X X   . . .   X X X   . . .   . . .
    // . . . .
    Shapes[0] = new Grid(4, 4);
    Shapes[0]->set(0, 1, 1);
    Shapes[0]->set(1, 1, 1);
    Shapes[0]->set(2, 1, 1);
    Shapes[0]->set(3, 1, 1);
    Shapes[1] = new Grid(3, 3);
    Shapes[1]->set(1, 1, 1);
    Shapes[1]->set(2, 1, 1);
    Shapes[1]->set(0, 2, 1);
    Shapes[1]->set(1, 2, 1);
    Shapes[2] = new Grid(3, 3);
    Shapes[2]->set(0, 1, 1);
    Shapes[2]->set(1, 1, 1);
    Shapes[2]->set(1, 2, 1);
    Shapes[2]->set(2, 2, 1);
    Shapes[3] = new Grid(3, 3);
    Shapes[3]->set(1, 0, 1);
    Shapes[3]->set(0, 1, 1);
    Shapes[3]->set(1, 1, 1);
    Shapes[3]->set(2, 1, 1);
    Shapes[4] = new Grid(3, 3);
    Shapes[4]->fill(1);
    Shapes[5] = new Grid(3, 3);
    Shapes[5]->set(2, 0, 1);
    Shapes[5]->set(0, 1, 1);
    Shapes[5]->set(1, 1, 1);
    Shapes[5]->set(2, 1, 1);
    Shapes[6] = new Grid(3, 3);
    Shapes[6]->set(0, 0, 1);
    Shapes[6]->set(0, 1, 1);
    Shapes[6]->set(1, 1, 1);
    Shapes[6]->set(2, 1, 1);
}

LOGIC::Field::~Field()
{
    delete grid;
    if(shape != NULL)
    {
        delete shape;
    }
}


LOGIC::Grid *LOGIC::Field::getRandomShape()
{
    srand((unsigned int)(time(NULL) + rand()));
    int rnd = rand() % 7;
    return Shapes[rnd];
}


bool LOGIC::Field::canFit(i32 x, i32 y)
{
    return canFitShape(x, y, shape);
}

bool LOGIC::Field::canFitShape(i32 x, i32 y, Grid *_shape)
{
    // TODO: Cells above field should be valid for the shape to applear into field

    if(_shape == NULL || grid == NULL)
    {
        // one of essential parts is NULL
        return false;
    }

    if(Debug)
    {
        log(" *** \n canFit shape: ");
        _shape->print();
        log("canFit grid: ");
        grid->print();
    }
    // check if shape values of not 0 is within bounds of field
    for(usize shapeY = 0; shapeY < _shape->HEIGHT; shapeY++)
    {
        for(usize shapeX = 0; shapeX < _shape->WIDTH; shapeX++)
        {
            i32 value = _shape->get((u32)shapeX, (u32)shapeY);
            // logsl(value);
            if(value != 0)
            {
                // check if cell can fit in X axis of field
                if((i32)shapeX + x >= 0 && (i32)shapeX + x < (i32)grid->WIDTH)
                {
                    // log(shapeX);
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

                // check if cell of grid underneath cell of shape is empty
                // if we are above 0 Y then skip check
                if(y + (i32)shapeY >= 0)
                {
                    if(grid->get((u32)shapeX + (u32)x, y + (i32)shapeY) == 0)
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
    }

    if(Debug)
    {
        log("***\n");
    }
    return true;
}


void LOGIC::Field::burnShapeIntoGrid()
{
    for(usize shapeY = 0; shapeY < shape->HEIGHT; shapeY++)
    {
        for(usize shapeX = 0; shapeX < shape->WIDTH; shapeX++)
        {
            i32 value = shape->get((u32)shapeX, (u32)shapeY);
            if(value != 0 && (i32)shapeY + yShape >= 0)
            {
                grid->set((i32)shapeX + xShape, (i32)shapeY + yShape, value);
            }
        }
    }
}

void LOGIC::Field::printWithShape(i32 x, i32 y)
{
    Grid *tmpGrid = new Grid(grid->WIDTH, grid->HEIGHT);

    // copy grid to tmpGrid
    for(usize gridY = 0; gridY < grid->HEIGHT; gridY++)
    {
        for(usize gridX = 0; gridX < grid->WIDTH; gridX++)
        {
            i32 value = grid->get(gridX, gridY);
            tmpGrid->set(gridX, gridY, value);
        }
    }

    for(usize shapeY = 0; shapeY < shape->HEIGHT; shapeY++)
    {
        for(usize shapeX = 0; shapeX < shape->WIDTH; shapeX++)
        {
            i32 value = shape->get((u32)shapeX, (u32)shapeY);
            if(value != 0 && (i32)shapeY + y >= 0)
            {
                tmpGrid->set((i32)shapeX + x, (i32)shapeY + y, value);
            }
        }
    }

    tmpGrid->print();

    delete tmpGrid;
}
