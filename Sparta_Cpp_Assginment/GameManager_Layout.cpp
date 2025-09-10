#include "GameManager_Layout.h"
#include "SceneMaker.h"
#include <iostream>

// 생성자: 필요한 모든 화면(Layout) 객체를 만들고 초기 화면을 설정합니다.
GameManager_Layout::GameManager_Layout(ConsoleManager* _C_manager)
    : _C_manager(_C_manager),
    mainMenu_Layout(nullptr),
    CharacterSelect_Layout(nullptr),
    newCharacterMake(nullptr),
    GM_Logic(new GameManager()),
    _su(new StringUpdater({ 10, 2 }))

{
    // CharacterSelect_Layout 화면을 미리 생성해둡니다.
    this->CharacterSelect_Layout = createCharacterSelectionLayout();

    // 메인 메뉴 화면(Layout)을 생성합니다.
    this->mainMenu_Layout = new Layout();

    // 메인 메뉴에 들어갈 버튼들을 만듭니다.
    Button* new_game = new Button(0, 2, "<<NEW_GAME>>", center_center, { 20, 5 }, { 0, 4 }, single_line, White, Gray);
    Button* load_game = new Button(0, 2, "<<LOAD_GAME>>", center_center, { 20, 5 }, { 0, 9 }, double_line, White, Gray);
    Button* next = new Button(0, 2, "<<CREDITS>>", center_center, { 20, 5 }, { 0, 14 }, double_line, White, Gray);
    Button* gameExit = new Button(0, 2, "<<EXIT_GAME>>", center_center, { 20, 5 }, { 0, 19 }, double_line, White, Gray);

    // 람다 함수를 통해 버튼 클릭 시 화면을 전환하는 로직을 추가합니다.
    new_game->SetOnLeftPressed([this]() {
        this->_C_manager->SetCurrentDisplay(this->CharacterSelect_Layout);
        });
    gameExit->SetOnLeftPressed([this]() {
        this->_C_manager->gameExit();
        });

    // 버튼들을 메인 메뉴 화면에 추가합니다.
    mainMenu_Layout->AddButton(new_game);
    mainMenu_Layout->AddButton(load_game);
    mainMenu_Layout->AddButton(next);
    mainMenu_Layout->AddButton(gameExit);

    // 프로그램의 시작 화면을 메인 메뉴로 설정합니다.
    _C_manager->SetCurrentDisplay(mainMenu_Layout);

    // **주의:** 이 클래스(GamaManager_Layout)는 이제 더 이상 ConsoleManager가 직접 관리하는 레이아웃이 아닙니다.
    // 레이아웃을 생성하고 관리하는 역할만 담당합니다.
};

// 소멸자: 힙에 할당한 화면(Layout) 객체들을 모두 해제합니다.
GameManager_Layout::~GameManager_Layout()
{
    // ConsoleManager는 다른 곳에서 관리하므로 여기서 삭제하지 않습니다.
    // _C_manager = nullptr;

    // 메인 메뉴와 캐릭터 선택 화면을 삭제합니다.
    // 각 Layout의 소멸자에서 자신이 소유한 버튼들을 삭제하도록 구현했다고 가정합니다.
    delete mainMenu_Layout;
    delete CharacterSelect_Layout;
    delete newCharacterMake;
    delete GM_Logic;
    delete _su;

    // 삭제 후 포인터를 nullptr로 초기화합니다.
    mainMenu_Layout = nullptr;
    CharacterSelect_Layout = nullptr;
    newCharacterMake = nullptr;
    GM_Logic = nullptr;
    _su = nullptr;
}

// 캐릭터 선택 화면을 생성하는 함수입니다.
Layout* GameManager_Layout::createCharacterSelectionLayout()
{
    Layout* nowLayout = new Layout();

    Button* character = new Button(0, 2, "New_Player", center_center, { 35,10 }, { 5, -20 }, double_line, White, Gray);
    Button* loadPlayer = new Button(0, 2, "Load", center_center, { 35,10 }, { 5, -5 }, double_line, White, Gray);
    Button* deleteSaveFile = new Button(0, 2, "Save_File_Delete", center_center, { 35,10 }, { 5, 10 }, double_line, White, Gray);
    Button* exitMenu = new Button(0, 2, "EXIT", center_center, { 35,10 }, { 5, 25 }, double_line, White, Gray);
    newCharacterMake = createNewCharacterMakeLayout();

    character->SetOnLeftPressed([this]() {
        this->_C_manager->SetCurrentDisplay(this->newCharacterMake);
        });

    nowLayout->AddButton(character);
    nowLayout->AddButton(loadPlayer);
    nowLayout->AddButton(deleteSaveFile);
    nowLayout->AddButton(exitMenu);

    return nowLayout;
}

Layout* GameManager_Layout::createNewCharacterMakeLayout()
{
    Layout* nowLayout = new Layout();
        
    Button* btn_a = new Button(0, 2, "a", left_center, { 7, 3 }, { 40, -10 }, single_line, White, Gray);
    Button* btn_b = new Button(0, 2, "b", left_center, { 7, 3 }, { 50, -10 }, single_line, White, Gray);
    Button* btn_c = new Button(0, 2, "c", left_center, { 7, 3 }, { 60, -10 }, single_line, White, Gray);
    Button* btn_d = new Button(0, 2, "d", left_center, { 7, 3 }, { 70, -10 }, single_line, White, Gray);
    Button* btn_e = new Button(0, 2, "e", left_center, { 7, 3 }, { 80, -10 }, single_line, White, Gray);
    Button* btn_f = new Button(0, 2, "f", left_center, { 7, 3 }, { 90, -10 }, single_line, White, Gray);
    Button* btn_g = new Button(0, 2, "g", left_center, { 7, 3 }, { 100, -10 }, single_line, White, Gray);
    Button* btn_h = new Button(0, 2, "h", left_center, { 7, 3 }, { 110, -10 }, single_line, White, Gray);
    Button* btn_i = new Button(0, 2, "i", left_center, { 7, 3 }, { 120, -10 }, single_line, White, Gray);
    Button* btn_j = new Button(0, 2, "j", left_center, { 7, 3 }, { 130, -10 }, single_line, White, Gray);
    Button* btn_k = new Button(0, 2, "k", left_center, { 7, 3 }, { 140, -10 }, single_line, White, Gray);
    Button* btn_l = new Button(0, 2, "l", left_center, { 7, 3 }, { 150, -10 }, single_line, White, Gray);
    Button* btn_m = new Button(0, 2, "m", left_center, { 7, 3 }, { 40, -5 }, single_line, White, Gray);
    Button* btn_n = new Button(0, 2, "n", left_center, { 7, 3 }, { 50, -5 }, single_line, White, Gray);
    Button* btn_o = new Button(0, 2, "o", left_center, { 7, 3 }, { 60, -5 }, single_line, White, Gray);
    Button* btn_p = new Button(0, 2, "p", left_center, { 7, 3 }, { 70, -5 }, single_line, White, Gray);
    Button* btn_q = new Button(0, 2, "q", left_center, { 7, 3 }, { 80, -5 }, single_line, White, Gray);
    Button* btn_r = new Button(0, 2, "r", left_center, { 7, 3 }, { 90, -5 }, single_line, White, Gray);
    Button* btn_s = new Button(0, 2, "s", left_center, { 7, 3 }, { 100, -5 }, single_line, White, Gray);
    Button* btn_t = new Button(0, 2, "t", left_center, { 7, 3 }, { 110, -5 }, single_line, White, Gray);
    Button* btn_u = new Button(0, 2, "u", left_center, { 7, 3 }, { 120, -5 }, single_line, White, Gray);
    Button* btn_v = new Button(0, 2, "v", left_center, { 7, 3 }, { 130, -5 }, single_line, White, Gray);
    Button* btn_w = new Button(0, 2, "w", left_center, { 7, 3 }, { 140, -5 }, single_line, White, Gray);
    Button* btn_x = new Button(0, 2, "x", left_center, { 7, 3 }, { 150, -5 }, single_line, White, Gray);
    Button* btn_y = new Button(0, 2, "y", left_center, { 7, 3 }, { 40, 0 }, single_line, White, Gray);
    Button* btn_z = new Button(0, 2, "z", left_center, { 7, 3 }, { 50, 0 }, single_line, White, Gray);
    Button* btn_del = new Button(0, 2, "del", left_center, { 15, 3 }, { 60, 0 }, single_line, White, Gray);
    Button* btn_ok = new Button(0, 2, "OK", left_center, { 15, 3 }, { 120, 0 }, single_line, White, Gray);
    Button* btn_exit = new Button(0, 2, "EXIT", left_center, { 15, 3 }, { 140, 0 }, single_line, White, Gray);



    btn_a->SetOnLeftPressed([this]() {
        this->addPlayerName("a");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_b->SetOnLeftPressed([this]() {
        this->addPlayerName("b");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_c->SetOnLeftPressed([this]() {
        this->addPlayerName("c");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_d->SetOnLeftPressed([this]() {
        this->addPlayerName("d");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_e->SetOnLeftPressed([this]() {
        this->addPlayerName("e");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_f->SetOnLeftPressed([this]() {
        this->addPlayerName("f");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_g->SetOnLeftPressed([this]() {
        this->addPlayerName("g");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_h->SetOnLeftPressed([this]() {
        this->addPlayerName("h");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_i->SetOnLeftPressed([this]() {
        this->addPlayerName("i");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_j->SetOnLeftPressed([this]() {
        this->addPlayerName("j");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_k->SetOnLeftPressed([this]() {
        this->addPlayerName("k");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_l->SetOnLeftPressed([this]() {
        this->addPlayerName("l");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_m->SetOnLeftPressed([this]() {
        this->addPlayerName("m");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_n->SetOnLeftPressed([this]() {
        this->addPlayerName("n");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_o->SetOnLeftPressed([this]() {
        this->addPlayerName("o");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_p->SetOnLeftPressed([this]() {
        this->addPlayerName("p");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_q->SetOnLeftPressed([this]() {
        this->addPlayerName("q");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_r->SetOnLeftPressed([this]() {
        this->addPlayerName("r");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_s->SetOnLeftPressed([this]() {
        this->addPlayerName("s");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_t->SetOnLeftPressed([this]() {
        this->addPlayerName("t");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_u->SetOnLeftPressed([this]() {
        this->addPlayerName("u");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_v->SetOnLeftPressed([this]() {
        this->addPlayerName("v");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_w->SetOnLeftPressed([this]() {
        this->addPlayerName("w");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_x->SetOnLeftPressed([this]() {
        this->addPlayerName("x");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_y->SetOnLeftPressed([this]() {
        this->addPlayerName("y");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_z->SetOnLeftPressed([this]() {
        this->addPlayerName("z");
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_del->SetOnLeftPressed([this]() {
        this->removePlayerName();
        this->_su->StringUpdate("Player Name : " + s_playerName);
        });
    btn_ok->SetOnLeftPressed([this]() {
        if(s_playerName != "")
            this->makePlayerStart();
        else
            this->_su->StringUpdate("Player Name Input Please");
        });
    btn_exit->SetOnLeftPressed([this]() {
        this->s_playerName = ""; // 나갈시 이름 초기화
        this->_C_manager->SetCurrentDisplay(this->CharacterSelect_Layout);
        });

    nowLayout->AddButton(btn_a);
    nowLayout->AddButton(btn_b);
    nowLayout->AddButton(btn_c);
    nowLayout->AddButton(btn_d);
    nowLayout->AddButton(btn_e);
    nowLayout->AddButton(btn_f);
    nowLayout->AddButton(btn_g);
    nowLayout->AddButton(btn_h);
    nowLayout->AddButton(btn_i);
    nowLayout->AddButton(btn_j);
    nowLayout->AddButton(btn_k);
    nowLayout->AddButton(btn_l);
    nowLayout->AddButton(btn_m);
    nowLayout->AddButton(btn_n);
    nowLayout->AddButton(btn_o);
    nowLayout->AddButton(btn_p);
    nowLayout->AddButton(btn_q);
    nowLayout->AddButton(btn_r);
    nowLayout->AddButton(btn_s);
    nowLayout->AddButton(btn_t);
    nowLayout->AddButton(btn_u);
    nowLayout->AddButton(btn_v);
    nowLayout->AddButton(btn_w);
    nowLayout->AddButton(btn_x);
    nowLayout->AddButton(btn_y);
    nowLayout->AddButton(btn_z);
    nowLayout->AddButton(btn_del);
    nowLayout->AddButton(btn_ok);
    nowLayout->AddButton(btn_exit);

    return nowLayout;
}

void GameManager_Layout::addPlayerName(string _s)
{
    s_playerName += _s;
}

void GameManager_Layout::removePlayerName()
{
    if (!s_playerName.empty()) {
        s_playerName.pop_back();
    }
}
void GameManager_Layout::makePlayerStart()
{
    this->GM_Logic->makePlayer(s_playerName);
}