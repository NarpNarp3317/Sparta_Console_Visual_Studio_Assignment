#include "Popup.h"
#include "SceneMaker.h"

Popup::Popup(PopupType type, PivotPoiontLocation anchor_type, COORD offset, Text_Color texts_color, Text_Color text, Text_Color bg)
    : BaseFrame(1, center_center, AdjustPopoutWidth(), offset, double_line, text, bg),
    _pop_type{ type },
    _target_value{ nullptr },
    _value_storage{ -1 },
    _current_PopupLayer_index{ 0 }
{
    // Set up the first/default layer
    AddPopoutLayer(type, _texture);
    UpdateLayer();
}

void Popup::AddPopoutLayer(PopupType type, Scene layer_texture)
{
    PopupLayer layer;// empty struct
    layer.layer_type = type;
    layer.texture = layer_texture;

    // Create default buttons for this layer
    SetDefaultButtons();
    layer.buttons = _active_buttons;

    _PopupLayers.push_back(layer);
}

void Popup::AddCustomPopoutLayer(Scene layer_texture, vector<Button*> buttons, vector<function<void()>> custom_functions)
{
    PopupLayer layer;
    layer.layer_type = Custom;
    layer.texture = layer_texture;
    layer.buttons = buttons;
    layer.custom_functions = custom_functions;

    _PopupLayers.push_back(layer);
}

void Popup::NextLayer()
{
    if (_current_PopupLayer_index + 1 < (int)_PopupLayers.size())
    {
        _current_PopupLayer_index++;
        UpdateLayer();
    }
    else
    {
        // no more layer to popout, leave
        LeavePopout();
    }
}

std::vector<Button*> Popup::GetCurrentButtons()
{
    if (_current_PopupLayer_index < (int)_PopupLayers.size())
    {
        return _PopupLayers[_current_PopupLayer_index].buttons;
    }
    return {};
}

void Popup::UpdateLayer()
{
    if (_current_PopupLayer_index >= (int)_PopupLayers.size()) return;

    PopupLayer& layer = _PopupLayers[_current_PopupLayer_index];
    _texture = layer.texture;
    _active_buttons = layer.buttons; // switch to the buttons of this layer
}

void Popup::LeavePopout()
{
    if (_onExit != nullptr) _onExit();

    _PopupLayers.clear();
    _active_buttons.clear();
    _current_PopupLayer_index = 0;
}

void Popup::SetDefaultButtons()
{
    _active_buttons.clear();// remove posible left over. clean up!

    switch (_pop_type)
    {
    case Confirmation:
        Yes_Button = new Button(1, 1, "Yes", bottom_center, { 5,3 }, { -5,0 }, single_line, White, Black, _default_widh_XY);
        No_Button = new Button(2, 1, "No", bottom_center, { 5,3 }, { 5,0 }, single_line, White, Black, _default_widh_XY);
        Leave_Button = new Button(3, 1, "X", top_right, { 3,3 }, { 0,0 }, single_line, White, Black, _default_widh_XY);

        _active_buttons = { Yes_Button, No_Button, Leave_Button };
        break;

    case ValueChange:
        Increment_Button = new Button(4, 101, "+", top_center, { 5,3 }, { -5,0 }, single_line, White, Black, _default_widh_XY);
        Decrement_Button = new Button(5, 101, "-", top_center, { 5,3 }, { 5,0 }, single_line, White, Black, _default_widh_XY);
        Confirm_Button = new Button(6, 101, "Confirm", bottom_right, { 10,3 }, { -1,-1 }, single_line, White, Black, _default_widh_XY);
        Leave_Button = new Button(7, 101, "X", top_right, { 3,3 }, { 0,0 }, single_line, White, Black, _default_widh_XY);

        _active_buttons = { Increment_Button, Decrement_Button, Confirm_Button, Leave_Button };
        break;

    case Information:
    case Error:
        Skip_Button = new Button(8, 101, "Skip", bottom_right, { 10,3 }, { -1,-1 }, single_line, White, Black, _default_widh_XY);
        Leave_Button = new Button(9, 101, "X", top_center, { 10,3 }, { 0,0 }, single_line, White, Black, _default_widh_XY);

        _active_buttons = { Skip_Button, Leave_Button };
        break;

    default:
        break;
    }
}

void Popup::AttachDefaultButtons()
{
    if (_current_PopupLayer_index >= (int)_PopupLayers.size()) return;// no no condition

    PopupLayer& layer = _PopupLayers[_current_PopupLayer_index];
    layer.buttons.insert(layer.buttons.end(), _active_buttons.begin(), _active_buttons.end());
}

COORD Popup::AdjustPopoutWidth()
{
    // For now, just return a default size. calculation for inserted image goes later fuck

    //... calculating

    //--> after calculation is done, return
    return _default_widh_XY;
}

bool Popup::IncrementValue()
{
    if (_value_storage < 0) return false;

    ++_value_storage;
    return true;
}

bool Popup::DecrementValue()
{
    if (_value_storage < 0) return false;

    --_value_storage;
    return true;
}

void Popup::SetTargetValue(int* value)
{
    if (_target_value != nullptr) return;// if target value goes null, do nothing
    _target_value = value;  
}

int Popup::GetTargetValue()
{
    return _value_storage;
}

bool Popup::ConfirmValueChange()
{
    if (_target_value == nullptr) return false;

    *_target_value = _value_storage;
    return true;
}
