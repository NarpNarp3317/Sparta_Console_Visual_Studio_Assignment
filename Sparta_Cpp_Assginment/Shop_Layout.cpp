#include "Shop_Layout.h"
#include "SceneMaker.h"
#include "Shop.h"
#include "Character.h"

extern Shop shop;
extern Character player;

Shop_Layout::Shop_Layout()
    : Layout()

    {
        // ====== Health Potion ======
        Button* buyHpBtn = new Button(0, 1, "Buy HP Potion", left_center, { 20,5 }, { -25,-10 }, double_line, White, Gray);
        buyHpBtn->SetOnLeftPressed([] {
            shop.BuyItemByIndex(player, 0); // HealthPotion index = 0
            });
        AddButton(buyHpBtn);

        Button* sellHpBtn = new Button(0, 1, "Sell HP Potion", left_center, { 20,5 }, { 25,-10 }, double_line, White, Gray);
        sellHpBtn->SetOnLeftPressed([] {
            shop.SellItemByIndex(player, 0);
            });
        AddButton(sellHpBtn);

        // ====== Attack Boost ======
        Button* buyAtkBtn = new Button(0, 1, "Buy ATK Boost", left_center, { 20,5 }, { -25,0 }, double_line, White, Gray);
        buyAtkBtn->SetOnLeftPressed([] {
            shop.BuyItemByIndex(player, 1); // AttackBoost index = 1
            });
        AddButton(buyAtkBtn);

        Button* sellAtkBtn = new Button(0, 1, "Sell ATK Boost", left_center, { 20,5 }, { 25,0 }, double_line, White, Gray);
        sellAtkBtn->SetOnLeftPressed([] {
            shop.SellItemByIndex(player, 1);
            });
        AddButton(sellAtkBtn);

        // ====== Iron Sword ======
        Button* buySwordBtn = new Button(0, 1, "Buy Iron Sword", left_center, { 20,5 }, { -25,10 }, double_line, White, Gray);
        buySwordBtn->SetOnLeftPressed([] {
            shop.BuyItemByIndex(player, 2); // Weapon index = 2
            });
        AddButton(buySwordBtn);

        Button* sellSwordBtn = new Button(0, 1, "Sell Iron Sword", left_center, { 20,5 }, { 25,10 }, double_line, White, Gray);
        sellSwordBtn->SetOnLeftPressed([] {
            shop.SellItemByIndex(player, 2);
            });
        AddButton(sellSwordBtn);


	//===== Extra ====//

	Scene newScene;

	SceneMaker::PrepareCanvas(&newScene, { 20,20 });// Scene maker로 이미지 만들어서 버튼 이미지를 바꿀수 있음. 반드시 크기는 버튼의 크기와 같아야 함
	//프레임 만들기, 색채우기, 색반전시키기, 글자 여러줄 넣기등 있음

	// 만들어낸 이미지를 버튼에 넣기는 잠시 미루기



		//----> 팝업창 작업중
		// 
		//----> popup 창이 필요하다면 여기에 필요로하는 기능과 글을 적어둘 것
		// 선택가능한 팝업창 기능 1.글자 표시+끄기 2. 다음으로 넘기기, 2. 대상 값(int)올리기 내리기








};
