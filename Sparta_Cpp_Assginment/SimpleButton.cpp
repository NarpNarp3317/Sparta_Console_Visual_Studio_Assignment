#include "SimpleButton.h"




SimpleButton::SimpleButton(int buttonID, int priority, PivotPoiontLocation anchor, COORD width, Text_Color text_color, Text_Color bg_color) 
    : BaseFrame(priority, anchor, width, { 0,0 }, FrameStyle::no_line, text_color, bg_color)
{
    FillAlpha(); // clickable
}

bool SimpleButton::IsDetected(COORD mouse_coord)// return bool by checking if the mouse coord is in range of button(not finding corrd for each)
{
    COORD width = GetWidthXY();
    COORD start = GetPrintStartCoord();

    COORD relative_coord = { mouse_coord.X - start.X, mouse_coord.Y - start.Y };

    if (relative_coord.X < 0 || relative_coord.Y < 0 || relative_coord.X >= width.X || relative_coord.Y >= width.Y)
    {
        return false;
    }

    return _collision_mask[relative_coord.Y][relative_coord.X];//return relative coord of mouse cursor and it will be used
}

void SimpleButton::SetOnLeftPressed(function<void()> function)
{
    _onLeftPressed = function;
}

void SimpleButton::OnLeftPressed()
{
    if (_onLeftPressed != nullptr)  _onLeftPressed();
}

void SimpleButton::SetOnLeftReleased(function<void()> function)
{
    _onLeftReleased = function;
}

void SimpleButton::OnLeftReleased()
{
    if (_onLeftReleased != nullptr)  _onLeftReleased();
}


void SimpleButton::FillAlpha()
{
    _collision_mask.assign(_width_XY.Y, vector<bool>(_width_XY.X, true));
}
