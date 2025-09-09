// Sparta_Cpp_Assginment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Layout.h"
#include "GameManager.h"
#include "ConsoleManager.h"
#include "StringUpdater.h"
#include <map>
#include <vector>

//------<<<< 여기에 자신의 layer헤더 넣기
#include "BattleStage_Layout.h"

using namespace std;

int main()
{

	/// 그 외 조원 시작지점(기존)
	GameManager startGame;
	startGame.StartGame();
    return 0;

    //===== Managers ====//

    StringUpdater string_updater({10,2});
    ConsoleManager C_manager;// for the getting max sceen size first so that base frames can know the screen limit

    /*
    
    // generate required displays in here, first and then start the console manager

    Layout GameMenu;// start
    Layout LoadGame;// loading new games
    Layout Character_Selection;
    Layout Lounge_Stage;
    Layout Store;
    Layout Battle_Stage;

    map<string, Layout*> layout_List;
    Layout* _precious_Layout;

    //======== Required Scenes =======// original scene here, delt with pointer

    //=== Layout type ===//
    Scene intermission;// during layout change
    Scene loading;
    Scene victory;
    Scene lost;

    //=== Props ===//
    Scene potion_bottle;
    Scene weapon;// there could be a type but for now, just one

    //=== extra ====//
    Scene x_button;
    Scene skip_button;



    // generate required buttons for game menu
    Button new_game(0, 2, "<<NEW_GAME>>", center_center, {20,5}, {0,4}, single_line, White, Gray);
    new_game.SetOnLeftPressed([&C_manager, &Character_Selection]() { C_manager.SetCurrentDisplay(&Character_Selection); });
    new_game.SetOnLeftReleased([&string_updater](){});// for release trigger

   // gamestart.SetOnHovering_ended([&string_updater]() {string_updater.StringUpdate("not hovering"); });

    Button load_game(0, 2, "<<LOAD_GAME>>", center_center, { 20,5 }, { 0,9 }, double_line,  White, Gray);
   // load.SetOnLeftClick([]() {printf("Load Clicked"); });// add funtio

    Button next(0, 2, "<<CREDITS>>", center_center, { 20,5 }, { 0,14 }, double_line, White, Gray);
    next.SetOnLeftPressed([&string_updater]() {});

	Button gameExit(0, 2, "<<EXIT_GAME>>", center_center, { 20,5 }, { 0,19 }, double_line, White, Gray);
    gameExit.SetOnLeftPressed([&C_manager]() {C_manager.gameExit(); });

    GameMenu.AddButton(&new_game);
    GameMenu.AddButton(&load_game);
    GameMenu.AddButton(&next);
    GameMenu.AddButton(&gameExit);

    //--------------------------------------------------------
 
    Button character(0, 2,"New_Player", center_center, {35,40}, {5,0}, double_line, White, Gray);
    character.SetOnLeftPressed([]() {});

    Button list1 (0, 2, left_center, { 20,5 }, { 40,-10 }, double_line, White, Gray);
    list1.SetOnHovering_started([]() {});
    list1.SetOnHovering_ended([]() {});

    Button list2 (0, 2, left_center, { 20,5 }, {40,0 }, double_line, White, Gray);

    Button list3(0, 2, left_center, { 20,5 }, { 40, 10 }, double_line, White, Gray);

    Character_Selection.AddButton(&character);
    Character_Selection.AddButton(&list1);
    Character_Selection.AddButton(&list2);
    Character_Selection.AddButton(&list3);

    //----------------------------------------------------

    */


    //==========<< Game Start ==========//


    BattleStage_Layout B_layout;

    C_manager.SetCurrentDisplay(& B_layout);// start up display here

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