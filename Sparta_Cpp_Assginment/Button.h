#pragma once
#include "BaseFrame.h"
#include "Interaction_Component.h"
#include "Enum_FrameType.h"
#include <functional>// for call function
#include <string>
#include <Windows.h>

class Button :public BaseFrame, public Interactable
{
public:
	Button(int button_id, int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_style);
	Button(int button_id, int priority, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_style);

	Button(int button_id, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_style);
	Button(int button_id, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_style);



private:

	int _id;
	bool _isOverlapping;// to toggle the hovering state

	std::vector<std::vector<bool>> _collision_mask;// alpha mask for mouse detection

	//------change the T-Pixel frame with this when the button state is changed

	std::vector < std::vector<T_Pixel>> _idle_texture;
	std::vector < std::vector<T_Pixel>> _pressed_texture;
	std::vector < std::vector<T_Pixel>> _hovering_texture;


	function<void()> _onLeftClick;// using functions as variable using <functional>
	function<void()> _onRightClick;
	function<void()> _onHovering_Started;
	function<void()> _onHovering_Ended;
	string _lable;


public:

	bool IsDetected(COORD mouse_coord);// when the cursor is in range, detect the mouse cursor and check if the alpha mask is overlapping


	void SetButtonID(int newId);
	int GetButtonID();

	void SetOnLeftClick(function<void()> function);
	void OnLeftClick() override;

	void SetOnRightClick(function<void()> function);
	void OnRightClick() override;

	void SetOnHovering_started(function<void()> function);
	void OnHovering_started() override;

	void SetOnHovering_ended(function<void()> function);
	void OnHovering_ended() override;

	void OnInvalidInput();

	void FillAlpha();
	std::vector < std::vector<bool>> GetCollisionMask();

	void SetLable(string new_lable);

	~Button();

};