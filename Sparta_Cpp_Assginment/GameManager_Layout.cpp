#include "GameManager_Layout.h"
#include "SceneMaker.h"
#include <iostream>
#include "Logger.h"

GameManager_Layout::GameManager_Layout(ConsoleManager* _C_manager)
    : _C_manager(_C_manager),
    mainMenu_Layout(nullptr),
    CharacterSelect_Layout(nullptr),
    mainLounge(nullptr),
    newCharacterMake(nullptr),
    GM_Logic(new GameManager()),
    _su(new StringUpdater({ 10, 2 }))

{
    // 나중에 쓸 레이아웃 미리 생성
    this->CharacterSelect_Layout = gameStartLayout();
    this->mainMenu_Layout = new Layout();
    this->Credit_Layout = creditLayout();

    // 메인 메뉴 버튼 생성
    Button* new_game = new Button(0, 2, "<<START_GAME>>", center_center, { 20, 5 }, { 0, 4 }, single_line, White, Gray);
    Button* next = new Button(0, 2, "<<CREDITS>>", center_center, { 20, 5 }, { 0, 9 }, double_line, White, Gray);
    Button* gameExit = new Button(0, 2, "<<EXIT_GAME>>", center_center, { 20, 5 }, { 0, 14 }, double_line, White, Gray);

    // 메인 메뉴 이벤트 연결
    new_game->SetOnLeftPressed([this]() {
        this->_C_manager->SetCurrentDisplay(this->CharacterSelect_Layout);
        });

    next->SetOnLeftPressed([this]() {
        this->_C_manager->SetCurrentDisplay(this->Credit_Layout);
        });


    gameExit->SetOnLeftPressed([this]() {
        this->_C_manager->gameExit();
        });

    // 메인 메뉴 등록
    mainMenu_Layout->AddButton(new_game);
    mainMenu_Layout->AddButton(next);
    mainMenu_Layout->AddButton(gameExit);

    // 메인 메뉴 Show
    _C_manager->SetCurrentDisplay(mainMenu_Layout);

    LOG("Load Main Function Complete! PROGRAM START");    
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
    delete mainLounge;
    delete Credit_Layout;

    // 삭제 후 포인터를 nullptr로 초기화합니다.
    mainMenu_Layout = nullptr;
    CharacterSelect_Layout = nullptr;
    newCharacterMake = nullptr;
    GM_Logic = nullptr;
    _su = nullptr;
    mainLounge = nullptr;
    Credit_Layout = nullptr;

    LOG("Delete Main Function Complete! bye bye");
}

// 게임 시작 함수
Layout* GameManager_Layout::gameStartLayout()
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

    loadPlayer->SetOnLeftPressed([this]() {
        this->loadPlayerData();
        });

    deleteSaveFile->SetOnLeftPressed([this]() {
        this->loadPlayerData();
        if(this->GM_Logic->deletePlayer())
            this->_su->StringUpdate("Player Save Data Delete!");
        else
            this->_su->StringUpdate("Player Save Data Delete fail...!");
        });

    exitMenu->SetOnLeftPressed([this]() {
        this->_C_manager->SetCurrentDisplay(this->mainMenu_Layout);

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
    this->mainLounge = new Lounge_Layout(_C_manager, _su, GM_Logic);
    this->_C_manager->SetCurrentDisplay(this->mainLounge->getLayout());
}

void GameManager_Layout::loadPlayerData()
{
    this->GM_Logic->makePlayer("TEMP_PLAYER");
    if (GM_Logic->loadPlayer())
    {
        this->mainLounge = new Lounge_Layout(_C_manager, _su, GM_Logic);
        this->_C_manager->SetCurrentDisplay(this->mainLounge->getLayout());
    }

    else // save 없을 시
    {
        this->mainLounge = new Lounge_Layout(_C_manager, _su, GM_Logic);
        this->_C_manager->SetCurrentDisplay(this->newCharacterMake);
    }
}

Layout* GameManager_Layout::creditLayout()
{
    Layout* rtrLayout = new Layout();
    Button* btnRtn = new Button(0, 2, "<<BACK>>", center_center, { 20, 5 }, { 0, 70 }, single_line, White, Gray);

    short nameWidth = 20;
    short jobWidth = 50;
    short commenWidth = 100;

    Button* lbl_name = new Button(0, 2, "<<NAME>>", left_center, { 20, 5 }, { nameWidth, -50 }, single_line, White, Gray);
    Button* lbl_job = new Button(0, 2, "<<JOB>>", left_center, { 50, 5 }, { jobWidth, -50 }, double_line, White, Gray);
    Button* lbl_comment = new Button(0, 2, "<<COMMENT>>", left_center, { 50, 5 }, { commenWidth, -50 }, double_line, White, Gray);

    btnRtn->SetOnLeftPressed([this]() {
        this->_C_manager->SetCurrentDisplay(this->mainMenu_Layout);
        });

    /// 이름 가나다순 정렬입니다...
    // 이름은 스펠링을 정확히 몰라 한글로 적어놨습니다. 실제론 깨지니 영어로 편집 부탁드립니다.
    // 세민
    Button* lbl_name1 = new Button(0, 2, "<<박세민(Leader)>>", left_center, { 20, 5 }, { nameWidth, -30 }, single_line, White, Gray);
    Button* lbl_job1 = new Button(0, 2, "<<JOB>>", left_center, { 50, 5 }, { jobWidth, -30 }, double_line, White, Gray);
    Button* lbl_comment1 = new Button(0, 2, "<<Comment>>", left_center, { 50, 5 }, { commenWidth, -30 }, double_line, White, Gray);
    // 무표
    Button* lbl_name2 = new Button(0, 2, "<<Yi_Moo_Pyo>>", left_center, { 20, 5 }, { nameWidth, -20 }, single_line, White, Gray);
    Button* lbl_job2 = new Button(0, 2, "<<CharacteMake_Save_Load>>", left_center, { 50, 5 }, { jobWidth, -20 }, double_line, White, Gray);
    Button* lbl_comment2 = new Button(0, 2, "<<Happy_Happy_Happy>>", left_center, { 50, 5 }, { commenWidth, -20 }, double_line, White, Gray);
    // 종혁
    Button* lbl_name3 = new Button(0, 2, "<<이종혁>>", left_center, { 20, 5 }, { nameWidth, -10 }, single_line, White, Gray);
    Button* lbl_job3 = new Button(0, 2, "<<JOB>>", left_center, { 50, 5 }, { jobWidth, -10 }, double_line, White, Gray);
    Button* lbl_comment3 = new Button(0, 2, "<<Comment>>", left_center, { 50, 5 }, { commenWidth, -10 }, double_line, White, Gray);
    // 기혁
    Button* lbl_name4 = new Button(0, 2, "<<조기혁>>", left_center, { 20, 5 }, { nameWidth, 0 }, single_line, White, Gray);
    Button* lbl_job4 = new Button(0, 2, "<<JOB>>", left_center, { 50, 5 }, { jobWidth, 0 }, double_line, White, Gray);
    Button* lbl_comment4 = new Button(0, 2, "<<Comment>>", left_center, { 50, 5 }, { commenWidth, 0 }, double_line, White, Gray);
    // 정석
    Button* lbl_name5 = new Button(0, 2, "<<현정석>>", left_center, { 20, 5 }, { nameWidth, 10 }, single_line, White, Gray);
    Button* lbl_job5 = new Button(0, 2, "<<JOB>>", left_center, { 50, 5 }, { jobWidth, 10 }, double_line, White, Gray);
    Button* lbl_comment5 = new Button(0, 2, "<<Comment>>", left_center, { 50, 5 }, { commenWidth, 10 }, double_line, White, Gray);


    rtrLayout->AddButton(btnRtn);
    rtrLayout->AddButton(lbl_name);
    rtrLayout->AddButton(lbl_comment);
    rtrLayout->AddButton(lbl_job);

    rtrLayout->AddButton(lbl_name1);
    rtrLayout->AddButton(lbl_job1);
    rtrLayout->AddButton(lbl_comment1);

    rtrLayout->AddButton(lbl_name2);
    rtrLayout->AddButton(lbl_job2);
    rtrLayout->AddButton(lbl_comment2);

    rtrLayout->AddButton(lbl_name3);
    rtrLayout->AddButton(lbl_job3);
    rtrLayout->AddButton(lbl_comment3);

    rtrLayout->AddButton(lbl_name4);
    rtrLayout->AddButton(lbl_job4);
    rtrLayout->AddButton(lbl_comment4);

    rtrLayout->AddButton(lbl_name5);
    rtrLayout->AddButton(lbl_job5);
    rtrLayout->AddButton(lbl_comment5);

    return rtrLayout;
}