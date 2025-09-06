#pragma once
#include "BaseFrame.h"
#include "interaction_Component.h"
#include <functional>// for call function
#include <string>
#include <Windows.h>

class Button :public BaseFrame, public Interactable
{
public:
	Button(int button_id, int priority, PivotPoiontLocation anchor_type, COORD width, COORD offset);
	Button(int button_id, int priority, PivotPoiontLocation anchor_type, COORD width);

	Button(int button_id, int priority, string lable, PivotPoiontLocation anchor_type, COORD width, COORD offset);
	Button(int button_id, int priority, string lable, PivotPoiontLocation anchor_type, COORD width);



private:

	int _id;

	function<void()> _onLeftClick;// using functions as variable using <functional>
	function<void()> _onRightClick;
	function<void()> _onHovering;

	string _lable;


public:

	bool IsDetected(COORD mouse_coord);// when the cursor is in range, detect the mouse cursor and check if the alpha mask is overlapping

	void SetOnLeftClick(function<void()> function);
	void OnLeftClick() override;

	void SetOnRightClick(function<void()> function);
	void OnRightClick() override;

	void SetOnHovering(function<void()> function);
	void OnHovering() override;

	void OnInvalidInput();

	void SetLable(string new_lable);

	COORD GetMouseCoord();

	~Button();

};