#pragma once
#include "Layout.h"
#include "ConsoleManager.h"
#include "GameManager.h"
#include "StringUpdater.h"
#include "Inventory_Layout.h"

class Shop_Layout;

class Weapon;

class Lounge_Layout
{
public:
	Lounge_Layout(ConsoleManager* _C_manager, StringUpdater* su, GameManager* _GM);
	~Lounge_Layout();

	void makeStatus();
	void updateStatus();
	void makeLayout();
	void setLayout(Layout* _Lay);
	void createSysMsg(string _msg);
	void deleteSysMsg();
	Layout* getLayout();

private:
	ConsoleManager* _C_manager;
	Layout* mainLounge_Layout;
	BattleStage_Layout* mainBattleStage_layout;
	StringUpdater* _su;
	GameManager* GM_Logic;

	Shop_Layout* myShopLayout;
	Inventory_Layout* inventory_Layout;

	void onBtnBattle();
	void onBtnShop();
	void onBtnPlayerStatus();
	void onBtnInventory();
	void onBtnSave();
	void onBtnEXIT();

	Button* lbl_name = nullptr;
	Button* lbl_Lv = nullptr;
	Button* lbl_hp = nullptr;
	Button* lbl_atk = nullptr;
	Button* lbl_exp = nullptr;
	Button* lbl_gold = nullptr;

	Button* lbl_sysMsg = nullptr;
};

