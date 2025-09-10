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
<<<<<<< HEAD
#include "Shop_Layout.h"

//테스트용 해두는 shop
#include "Shop.h"
#include "Character.h"
Shop shop;
Character player("Test");
=======
#include "GameManager_Layout.h"
>>>>>>> Dev

using namespace std;

int main()
{

	/// 그 외 조원 시작지점(기존)
	//GameManager startGame;
	//startGame.StartGame();
 //   return 0;

    //===== Managers ====//

    // ConsoleManager C_manager;// for the getting max sceen size first so that base frames can know the screen limit
    ConsoleManager* C_manager = new ConsoleManager();

    /**/
 
    //----------------------------------------------------

    /**/


    //==========<< Game Start ==========//


    //BattleStage_Layout B_layout;
    Shop_Layout shopLayout;

<<<<<<< HEAD
    C_manager.SetCurrentDisplay(&shopLayout);// start up display here
=======
    GameManager_Layout* layout_GM = new GameManager_Layout(C_manager);
>>>>>>> Dev

    // new_game.SetOnLeftReleased([&string_updater]() {});// for release trigger

    // C_manager->SetCurrentDisplay(layout_GM);// start up display here <-- gamemanager layout에서 해결
    C_manager->Run_Update();// run the console manager


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