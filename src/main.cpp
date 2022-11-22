#include "gfxhelper.hpp"
#include "log.hpp"
#include "logic.hpp"
#include "raylib.h"
#include "types.hpp"
#include <iostream>

int main()
{

    log(" --- Init window --- ");
    InitWindow(800, 640, "Tetris");
    SetTargetFPS(1000);
    SetExitKey(KEY_BACKSPACE);

    // remove this area

    // up to this point

    log(" --- Tetris init --- ");
    // main loop
    bool Debug = true;
    f32 time = 0.f;
    // - time stamps
    f32 lastTimelogicTick = 0.f;
    f32 logicTickDurationNormal = 0.5f;   // every 500 ms
    f32 logicTickDurationSpeedUp = 0.1f;  // every 200 ms
    f32 logicTickDuration = logicTickDurationNormal;
    // input
    bool input = false;
    i32 inputX = 0;
    i32 inputR = 0;
    // playing field
    LOGIC::Field *field = new LOGIC::Field(10, 20);
    field->grid->set(5, 15, 8);
    field->Debug = !true;
    // stuck status
    int unmovedTurns = 0;
    // gravity
    i32 maxContinuesMoves = 2;
    i32 continuesMoves = 0;
    // Other
    FLIPPING_CIRCLE gfxLogicTick(YELLOW, RED);
    // debug TODO: Remove
    while(!WindowShouldClose())
    {
        // tick variables
        f32 DeltaTime = GetFrameTime();
        time += DeltaTime;

        // read input
        if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT))
        {
            inputX = IsKeyPressed(KEY_LEFT) ? -1 : 1;
            input = true;
        }
        if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN))
        {
            inputR = IsKeyPressed(KEY_UP) ? -1 : 1;
            input = true;
        }
        logicTickDuration = IsKeyDown(KEY_SPACE) ? logicTickDurationSpeedUp : logicTickDurationNormal;

        // trigger logic tick every logicTickDuration interval
        // or on user input, whichever is sooner
        if(time > lastTimelogicTick + logicTickDuration || input)
        {
            lastTimelogicTick = time;
            if(Debug)
            {
                // - Flip debug circle color every logical tick
                gfxLogicTick.flip();
            }
            unmovedTurns++;
            // tick
            // 1. check if there is an active shape
            // 2. Input
            // 3. Gravity
            // 4. check if stuck (if so then bake it into grid)
            // 5. Solved rows
            // 6. Activations
            // 7. Lose state checka
            // 8. drawing (draw in layers so effects can be applied)
            log("tick");

            // 1. if there is no active shape then make a new random one
            if(field->shape == NULL)
            {
                // TODO: make so added shape is random
                field->shape = new LOGIC::Grid(3, 3);
                field->shape->fill(6);
                field->shape->set(0, 0, 1);
                field->shape->set(1, 0, 2);
                field->shape->set(2, 0, 3);
                field->shape->set(1, 1, 9);
                field->shape->set(0, 2, 0);
                field->shape->set(1, 2, 1);
                field->shape->set(2, 2, 0);

                field->shapeResetPos();
                if(Debug)
                {
                    log(" -+- New shape spawned -+- ");
                }
            }
            // 2. Input
            if(input)
            {
                // X axis
                if(inputX > 0 || inputX < 0)
                {
                    if(Debug)
                    {
                        log(" $ INPUT move [>] or [<] $");
                    }
                    if(field->shape != NULL)
                    {
                        int newPossibleX = field->xShape + inputX;
                        if(field->canFit(newPossibleX, field->yShape))
                        {
                            // if shape can fit in the reqested position
                            field->xShape = newPossibleX;
                            unmovedTurns = 0;
                            continuesMoves++;
                            if(Debug)
                            {
                                field->printWithShape(newPossibleX, field->yShape);
                            }
                        }
                    }
                }
                // Rotation request
                if(inputR > 0 || inputR < 0)
                {
                    if(Debug)
                    {
                        log(" $ INPUT Rotate [C] or [AC] $");
                    }
                    if(field->shape != NULL)
                    {
                        // make temp copy of current shape
                        LOGIC::Grid *tmp_copy = field->shape->copy();
                        // rotate the copy
                        if(inputR == -1)
                        {
                            tmp_copy->rotate(false);
                        }
                        else
                        {
                            tmp_copy->rotate(true);
                        }
                        // check if copy can fit at current shape XY
                        if(field->canFit(field->xShape, field->yShape))
                        {
                            // if shape can fit in the reqested position
                            delete field->shape;
                            field->shape = tmp_copy;
                            continuesMoves++;
                            if(Debug)
                            {
                                log(" * Shape was ROTATED * ");
                                field->printWithShape(field->xShape, field->yShape);
                            }
                        }
                    }
                }
            }

            // 3.Gravity (only if there was no input)
            // - TODO: Input should only be able to skip 2 gravity ticks in a row max
            if(!input || continuesMoves > maxContinuesMoves)
            {
                if(field->shape != NULL)
                {
                    int newPossibleY = field->yShape + 1;
                    if(field->canFit(field->xShape, newPossibleY))
                    {
                        field->yShape = newPossibleY;
                        unmovedTurns = 0;
                        continuesMoves = 0;
                        // Debug print of tick state
                        if(Debug)
                        {
                            log("! After gravity applied !");
                            field->printWithShape(field->xShape, newPossibleY);
                        }
                    }
                }
            }

            // 4. check if stuck (if so then bake it into grid)
            if(unmovedTurns >= 3 && field->shape != NULL && !input)
            {
                // burn shape into grid
                field->burnShapeIntoGrid();

                // remove old shape
                delete field->shape;
                field->shape = NULL;

                // reset unmoved turns status
                unmovedTurns = 0;

                log(" * We are OFFICIALY stuck! * ");
            }

            // - reset input
            inputX = 0;
            inputR = 0;
            input = false;
        }


        // input
        // - debug toggle
        Debug = (IsKeyPressed(KEY_TAB)) ? !Debug : Debug;

        // animation update tick
        // TODO

        // drawing
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if(Debug)
        {
            DrawFPS(10, 10);
            gfxLogicTick.draw(110, 19, 6);
            DrawText(("Frame time: " + std::to_string(DeltaTime)).c_str(), 10, 35, 12, WHITE);
            DrawText(("Time: " + std::to_string(time)).c_str(), 10, 50, 12, WHITE);
        }
        EndDrawing();
    }

    return 0;
}
