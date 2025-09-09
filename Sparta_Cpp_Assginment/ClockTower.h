#pragma once

class ClockTower// this will be the centralized timer for every interactables
{
private:
    static int _global_tick;

public:
    static void Update_Tick();

    static int Get_Current_Tick();

    static void Reset_ClockTower();
};
