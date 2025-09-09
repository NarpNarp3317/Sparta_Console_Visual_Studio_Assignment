#include "ClockTower.h"

int ClockTower::_global_tick = 0;

void ClockTower::Update_Tick()
{
    _global_tick++;
}

int ClockTower::Get_Current_Tick()
{
    return _global_tick;
}

void ClockTower::Reset_ClockTower()
{
    _global_tick = 0;
}