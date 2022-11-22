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
    if(1)
    {
        LOGIC::Field *field = new LOGIC::Field(10, 20);
        field->Debug = true;
        field->shape = new LOGIC::Grid(3, 3);
        field->shape->set(1, 1, 1);
        field->canFit(0, 0);
    }
    // up to this point

    log(" --- Tetris init --- ");
    // main loop
    bool Debug = true;
    f32 time = 0.f;
    // - time stamps
    f32 lastTimelogicTick = 0.f;
    f32 logicTickDuration = 0.5f;  // every 500 ms
    // Other
    FLIPPING_CIRCLE gfxLogicTick(YELLOW, RED);
    while(!WindowShouldClose())
    {
        // tick variables
        f32 DeltaTime = GetFrameTime();
        time += DeltaTime;

        // trigger logic tick every logicTickDuration interval
        if(time > lastTimelogicTick + logicTickDuration)
        {
            lastTimelogicTick = time;
            if(Debug)
            {
                // - Flip debug circle color every logical tick
                gfxLogicTick.flip();
            }
            // tick
            // 1. Gravity
            // 2. Input
            // 3. Solved rows
            // 4. Activations
            // 5. Lose state check
            log("text");
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
