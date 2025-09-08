#pragma once
#include <Windows.h>
#include <functional>
#include "Interaction_Component.h"// to get interaction target
#include "Enum_MouseInput.h"


class MouseInputManager
{
public:
	MouseInputManager(HANDLE input_Handle);

private:
	HANDLE _input_H;// from console manager
	COORD _cursor_coord_on_event;

	MOUSE_EVENT_RECORD _mouse_event_Record;// record mouse events
	INPUT_RECORD _input_Record;//varaible to record the input event
	DWORD _events;// this will store the number of events read//
	bool _isActive;//
	bool _isClickable;//able and disable the click function

	//==== Interaction ====//
	Interactable* _Interaction_targetPtr;
	Enum_MouseInput _input_type;
	
public:
	void Start_MouseInputReading();
	void Pause_MouseInputReading();
	void ActivateMouseInput();
	void DeactivateMouseInput();

	void ActivateMouseClick();// 마우스 클릭 가능하게 함
	void DisableMouseClick();// 마우스 클릭 읽기를 중단함

	void OnRightClick();
	void OnLeftClick();
	// void Hovering();
	void OnHovering_started();
	void OnHovering_ended();

	void SetInteractionTarget(Interactable* newTarget);

	void DetectInteractionTarget();// check if the interactable's coord is matching with mouse cursor's coord and set it as target
	Interactable* GetCurrentInteractionTarget();
	bool CheckTargetValid(Interactable* newTarget);// check if interaction target is valid or not

	~MouseInputManager();

};