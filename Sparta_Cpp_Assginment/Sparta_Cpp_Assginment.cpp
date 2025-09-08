// Sparta_Cpp_Assginment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Layout.h"
#include "GameManager.h"
#include "ConsoleManager.h"
#include "StringUpdater.h"

int main()
{

	/// 그 외 조원 시작지점(기존)
	GameManager startGame;
	startGame.StartGame();

     return 0;
    StringUpdater string_updater({10,2});
    ConsoleManager C_manager;// for the getting max sceen size first so that base frames can know the screen limit

    // generate required displays in here, first and then start the console manager

    Layout GameMenu;
    Layout Character_Maker;

    // generate required buttons for game menu
    Button gamestart(0, 2, center_center, { 20,5 }, { 0,-2 }, double_line);
    gamestart.SetOnLeftClick([&string_updater]() {string_updater.StringUpdate("left clicked"); });
    gamestart.SetOnRightClick([&string_updater]() {string_updater.StringUpdate("right clicked"); });
    gamestart.SetOnHovering_started([&string_updater]() {string_updater.StringUpdate("Hoverring"); });

   // gamestart.SetOnHovering_ended([&string_updater]() {string_updater.StringUpdate("not hovering"); });

    Button load(0, 2, center_center, { 20,5 }, { 0,6 }, double_line);
   // load.SetOnLeftClick([]() {printf("Load Clicked"); });// add funtio
   // load.SetOnHovering_started([]() { printf("load hovering\n"); });

    Button next(0, 2, center_center, { 20,5 }, { 0,12 }, double_line);
    next.SetOnLeftClick([&C_manager, &Character_Maker]() { C_manager.SetCurrentDisplay(&Character_Maker); });

	Button gameExit(0, 2, center_center, { 20,5 }, { 0,18 }, double_line);
    gameExit.SetOnLeftClick([&C_manager]() {C_manager.gameExit(); });

    GameMenu.AddButton(&gamestart);
    GameMenu.AddButton(&load);
    GameMenu.AddButton(&next);
    GameMenu.AddButton(&gameExit);

    //--------------------------------------------------------
 
    Button character(0, 2, left_center, { 30,40 }, { 5,0 }, double_line);
    character.SetOnLeftClick([]() {});

    Button list1 (0, 2, left_center, { 20,5 }, { 40,-10 }, double_line);
    list1.SetOnHovering_started([]() {});
    list1.SetOnHovering_ended([]() {});

    Button list2 (0, 2, left_center, { 20,5 }, {40,0 }, double_line);

    Button list3(0, 2, left_center, { 20,5 }, { 40, 10 }, double_line);

    Character_Maker.AddButton(&character);
    Character_Maker.AddButton(&list1);
    Character_Maker.AddButton(&list2);
    Character_Maker.AddButton(&list3);

    //----------------------------------------------------


    C_manager.SetCurrentDisplay(&GameMenu);// start up display here

    C_manager.Run_Update();// run the console manager


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file