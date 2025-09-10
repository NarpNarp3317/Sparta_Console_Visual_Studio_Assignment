#pragma once
#include "Layout.h"
#include "ConsoleManager.h"
#include "GameManager.h"
#include "StringUpdater.h"


class Lounge_Layout
{
public:
	Lounge_Layout(ConsoleManager* _C_manager, StringUpdater* su, GameManager* _GM);
	~Lounge_Layout();

	void makeLayout();
	void setLayout(Layout* _Lay);
	Layout* getLayout();

private:
	ConsoleManager* _C_manager;
	Layout* mainLounge_Layout;
	StringUpdater* _su;
	GameManager* GM_Logic;


	void onBtnBattle();
	void onBtnShop();
	void onBtnPlayerStatus();
	void onBtnInventory();
	void onBtnSave();
	void onBtnEXIT();
};

