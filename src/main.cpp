#include "log.hpp"
#include "raylib.h"
#include <iostream>

int main()
{

    log(" --- Init window --- ");
    InitWindow(800, 640, "Tetris");
    SetTargetFPS(1000);
    SetExitKey(KEY_BACKSPACE);

    log(" --- Tetris init --- ");
    // main loop
    bool Debug = true;
    float time = 0.f;
    // - time stamps
    float lastTimelogicTick = 0.f;
    float logicTickDuration = 0.5f;  // every 500 ms
    // Other
    bool c_logicTick = true;
    Color c_logicTickColor = RED;
    while(!WindowShouldClose())
    {
        // tick variables
        float DeltaTime = GetFrameTime();
        time += DeltaTime;

        // trigger logic tick every logicTickDuration interval
        if(time > lastTimelogicTick + logicTickDuration)
        {
            lastTimelogicTick = time;
            if(Debug)
            {
                if(c_logicTick)
                {
                    c_logicTickColor = RED;
                    c_logicTick = !c_logicTick;
                }
                else
                {
                    c_logicTickColor = YELLOW;
                    c_logicTick = !c_logicTick;
                }
            }
        }
        // - Flip debug tick circle color every tick
        if(Debug)
        {
            DrawCircle(120, 18, 5, c_logicTickColor);
        }

        // input
        // - debug toggle
        if(IsKeyPressed(KEY_TAB))
        {
            Debug = !Debug;
        }

        // drawing
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if(Debug)
        {
            DrawFPS(10, 10);
            DrawText(("Frame time: " + std::to_string(DeltaTime)).c_str(), 10, 35, 12, WHITE);
            DrawText(("Time: " + std::to_string(time)).c_str(), 10, 50, 12, WHITE);
        }
        EndDrawing();
    }

    return 0;
}
