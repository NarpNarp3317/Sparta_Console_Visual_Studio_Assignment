#pragma once
#include "BaseFrame.h"
#include "Interaction_Component.h"
#include "Enum_FrameType.h"
#include <functional>// for call function
#include <string>
#include <Windows.h>
#include "Enum_Live_Interactable_state.h"// to use timer function!!!!
#include "ClockTower.h"

using namespace std;

class Button :public BaseFrame, public Interactable
{
public:
	Button(int button_id, int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_style, Text_Color text_color, Text_Color bg_color);
	Button(int button_id, int priority, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_style, Text_Color text_color, Text_Color bg_color);

	Button(int button_id, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, COORD offset, FrameStyle frame_style, Text_Color text_color, Text_Color bg_color);
	Button(int button_id, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, FrameStyle frame_style, Text_Color text_color, Text_Color bg_color);



private:

	int _buttonID;
	bool _isClickable;// to disalbe and able the press 
	bool _isOverlapping;// to toggle the hovering state
	string _lable;

	vector<vector<bool>> _collision_mask;// alpha mask for mouse detection

	//------change the T-Pixel frame with this when the button state is changed

	Scene _idle_texture;
	Scene _pressed_texture;
	Scene _hovering_texture;
	Scene _activate_failed_texture;

	//=== fucntions ===//
	function<void()> _onLeftPressed;// using functions as variable using <functional>
	function<void()> _onLeftReleased;

	function<void()> _onRightPressed;
	function<void()> _onRightReleased;

	function<void()> _onHovering_Started;
	function<void()> _onHovering_Ended;
	


public:

	bool IsDetected(COORD mouse_coord) override;// 
	// when the cursor is in range, detect the mouse cursor and check if the alpha mask is overlapping

	//void GenerateDefaultButton(Scene* newTexture);
	void GenerateDefaultButtonSet();// this will generate defualt buttons with event states

	void SetButtonID(int newId);
	int GetButtonID();

	void FillAlpha();
	std::vector < std::vector<bool>> GetCollisionMask();

	void SetLable(string new_lable);


	//===== Left button ======//
	void SetOnLeftPressed(function<void()> function);
	void OnLeftPressed() override;

	void SetOnLeftReleased(function<void()> function);
	void OnLeftReleased() override;

	//===== Right Button ======//
	void SetOnRightPressed(function<void()> function);
	void OnRightPressed() override;

	void SetOnRightReleased(function<void()> function);
	void OnRightReleased() override;

	//===== Hovering =====//

	void SetOnHovering_started(function<void()> function);
	void OnHovering_started() override;

	void SetOnHovering_ended(function<void()> function);
	void OnHovering_ended() override;

	//===== Invalid Input ======//
	void OnInvalidInput();
	//--------------------------//

	//void I_Live_Update() override;// from interacction component// not now

	~Button();

};