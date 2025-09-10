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

	SceneMaker::PrepareCanvas(&newScene, { 20,20 });// Scene maker�� �̹��� ���� ��ư �̹����� �ٲܼ� ����. �ݵ�� ũ��� ��ư�� ũ��� ���ƾ� ��
	//������ �����, ��ä���, ��������Ű��, ���� ������ �ֱ�� ����

	// ���� �̹����� ��ư�� �ֱ�� ��� �̷��



		//----> �˾�â �۾���
		// 
		//----> popup â�� �ʿ��ϴٸ� ���⿡ �ʿ���ϴ� ��ɰ� ���� ����� ��
		// ���ð����� �˾�â ��� 1.���� ǥ��+���� 2. �������� �ѱ��, 2. ��� ��(int)�ø��� ������








};
