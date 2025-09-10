#pragma once
#include "BaseFrame.h"
#include "interaction_Component.h"
#include "Button.h"
#include "Enum_MouseInput.h"
#include "Enum_PopupType.h"
#include <functional>
#include <map>
#include "Str_PopupLayers.h"

using namespace std;

class Popup :public BaseFrame
{
public:
	Popup(PopupType type, PivotPoiontLocation anchor_type, COORD offset, Text_Color texts_color, Text_Color text, Text_Color bg);

private:
	/*
	Popout_Type _pop_type;
	map<int,PopoutLayer> _popout_layers;


	map< int, vector<string>> _texts;// update strings
	//vector for storing more than one line
	// map for skip to next update

	Text_Color _texts_color;// updated strings' color

	function<void()> _onEnter;// layer update
	function<void()> _onExit;// leaving the popout
	*/

	//=== Popout Window ===//
	PopupType _pop_type;
	COORD _default_widh_XY;


	//==== layer ====//

	vector<PopupLayer> _PopupLayers;
	int _current_PopupLayer_index;

	//=== buttons  ====//
	//confirm
	Button* Yes_Button;
	Button* No_Button;

	//info
	Button* Skip_Button;// to next layer of popout

	//value adjustment
	int* _target_value;
	int _value_storage;// to save the value change and set the original value later

	//int _value_adjustment_step;// or just increment decrement per click
	Button* Increment_Button;
	Button* Decrement_Button;
	Button* Confirm_Button;// to finalize the value change
	//exit
	Button* Leave_Button;
	function<void()> _onExit;

	std::vector<Button*> _active_buttons;
	//----------------//

public:
	void AddPopoutLayer(PopupType type, Scene layer_texture);
	void AddCustomPopoutLayer(Scene layer_texture, vector<Button*> buttons, vector<function<void()>> custom_functions);

	void NextLayer();
	//void PreviousLayer();// no going back

	std::vector<Button*> GetCurrentButtons();

	void UpdateLayer();//update current popout
	void LeavePopout();//close

	void SetDefaultButtons();
	void AttachDefaultButtons();

	COORD AdjustPopoutWidth();// checks the containing texture's size and resize the popout window size

	bool IncrementValue();
	bool DecrementValue();
	void SetTargetValue(int* value);
	int GetTargetValue();
	bool ConfirmValueChange();

};