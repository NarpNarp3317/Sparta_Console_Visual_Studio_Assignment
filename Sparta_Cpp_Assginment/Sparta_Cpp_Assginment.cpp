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
#include "GameManager_Layout.h"
#include "Shop_Layout.h"

//테스트용 해두는 shop
#include "Shop.h"
#include "Character.h"
Shop shop;
Character player("Test");

using namespace std;

int main()
{
    ConsoleManager* C_manager = new ConsoleManager();
    GameManager_Layout* layout_GM = new GameManager_Layout(C_manager);
    C_manager->Run_Update();// run the console manager

	return 0;
}