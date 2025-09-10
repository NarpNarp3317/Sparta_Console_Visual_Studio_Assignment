#pragma once
#include "Layout.h"
#include "ConsoleManager.h"
#include "GameManager.h"
#include "StringUpdater.h"

class GameManager_Layout : public Layout
{
public:
	GameManager_Layout(ConsoleManager* _C_manager);
	~GameManager_Layout();
	void setConsoleManager(ConsoleManager* manager) { _C_manager = manager; }
	void getconsoleManager(ConsoleManager** manager) { *manager = _C_manager; }

	Layout* createCharacterSelectionLayout();
	Layout* createNewCharacterMakeLayout();

private:
	ConsoleManager* _C_manager;
	Layout* mainMenu_Layout;
	Layout* CharacterSelect_Layout;
	Layout* newCharacterMake;
	StringUpdater* _su;
	GameManager* GM_Logic;
	string s_playerName = "";

private:
	void addPlayerName(string _s);
	void removePlayerName();
	void makePlayerStart();
};

