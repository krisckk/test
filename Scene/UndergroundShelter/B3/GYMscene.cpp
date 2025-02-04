#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Resources.hpp"
#include "Engine/Sprite.hpp"
#include "UI/Component/Label.hpp"
#include "Maincharacter/Maincharacter.hpp"
#include "Scene/UndergroundShelter/B4/LibraryScene.hpp"
#include "Scene/UndergroundShelter/B4/LabScene.hpp"
#include "Scene/UndergroundShelter/B4/StorageRoom.hpp"
#include "RestRoom.hpp"
#include "GYMscene.hpp"
#include "DataRoom.hpp"
#include "Stats/Shared.hpp"
int use_barbell = 0;
bool get_coin = false;
bool coin_picked = false;
bool up = false;
void GYMscene::Initialize(){
    Shared::GYMscene = true;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::LOG(Engine::INFO) << "GYM scene create";
    PoetFont = al_load_font("Resource/fonts/PoetsenOne.ttf", 30, 0);
    BIGFont = al_load_font("Resource/fonts/PoetsenOne.ttf", 150, 0);
    BARBELL = al_load_bitmap("Resource/images/UndergroundShelter/B3/GYMscene/barbell.png");
    COIN = al_load_bitmap("Resource/images/UndergroundShelter/B3/GYMscene/coin.png");
    AddNewObject(new Engine::Image("UndergroundShelter/LabGeneralBackground.png", 0, 0, w, h, 0, 0));
    AddNewObject(new Engine::Image("2Ddooropened.png", 1550, h - 460, 300, 360, 0.5, 0));
    AddNewObject(new Engine::Image("2Ddooropened.png", 0, h - 460, 300, 360, 0, 0));
    AddNewObject(new Engine::Image("UndergroundShelter/B3/GYMscene/running_machine.png", 600, 620, 300, 210, 0, 0));
    AddNewObject(new Engine::Image("Gold.png", 1100, 750, 80, 60, 0, 0));

    if(Shared::previousStage == "DiningRoom") MC = new Maincharacter("MCRightStop.png", 1450, 680, 32, 200);
    else if(Shared::previousStage == "DataRoom") MC = new Maincharacter("MCRightStop.png", 20, 680, 32, 200);
    if (!MC) {
        Engine::LOG(Engine::ERROR) << "Failed to create Maincharacter object";
        return;
    }
    AddNewObject(MC);
}

void GYMscene::Terminate(){
    Engine::LOG(Engine::INFO) << "GYMscene Terminated";
    MC = nullptr; 
    al_destroy_font(PoetFont);
    al_destroy_font(BIGFont);
    IScene::Terminate();
}

void GYMscene::Draw() const{
    IScene::Draw();
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    if (MC -> Position.x >= 20 && MC -> Position.x <= 150){
        al_draw_filled_triangle(MC -> Position.x + 200, 700, MC -> Position.x + 200, 740, MC -> Position.x + 170, 720, al_map_rgb(255, 255, 255));
        al_draw_filled_rounded_rectangle(MC -> Position.x + 200, 680, MC -> Position.x + 400, 800, 10, 10, al_map_rgb(255, 255, 255));
        al_draw_text(PoetFont, al_map_rgb(0, 0, 0), MC -> Position.x + 230, 700, 0, "Press E to ");
        al_draw_text(PoetFont, al_map_rgb(0, 0, 0), MC -> Position.x + 230, 740, 0, "Enter");
    }
    if (MC -> Position.x >= 1350 && MC -> Position.x <= 1600){
        al_draw_filled_triangle(MC -> Position.x - 55, 700, MC -> Position.x - 55, 740, MC -> Position.x - 10, 720, al_map_rgb(255, 255, 255));
        al_draw_filled_rounded_rectangle(MC -> Position.x - 350, 680, MC -> Position.x - 50, 800, 10, 10, al_map_rgb(255, 255, 255));
        al_draw_text(PoetFont, al_map_rgb(0, 0, 0), MC -> Position.x - 310, 710, 0, "Press E to Back");
    }
    if (MC -> Position.x >= 980 && MC -> Position.x <= 1180 && !Shared::Gold){
        al_draw_filled_triangle(MC -> Position.x - 55, 700, MC -> Position.x - 55, 740, MC -> Position.x - 10, 720, al_map_rgb(255, 255, 255));
        al_draw_filled_rounded_rectangle(MC -> Position.x - 350, 680, MC -> Position.x - 50, 800, 10, 10, al_map_rgb(255, 255, 255));
        al_draw_text(PoetFont, al_map_rgb(0, 0, 0), MC -> Position.x - 310, 700, 0, "Press P to");
        al_draw_text(PoetFont, al_map_rgb(0, 0, 0), MC -> Position.x - 310, 740, 0, "Pick Up");
    }
    if  (MC -> Position.x >= 980 && MC -> Position.x <= 1180 && Shared::Gold){
        al_draw_filled_triangle(MC -> Position.x - 55, 700, MC -> Position.x - 55, 740, MC -> Position.x - 10, 720, al_map_rgb(255, 255, 255));
        al_draw_filled_rounded_rectangle(MC -> Position.x - 350, 680, MC -> Position.x - 50, 800, 10, 10, al_map_rgb(255, 255, 255));
        al_draw_text(PoetFont, al_map_rgb(0, 0, 0), MC -> Position.x - 310, 700, 0, "This is heavy");
        al_draw_text(PoetFont, al_map_rgb(0, 0, 0), MC -> Position.x - 310, 740, 0, "as fu...");
    }

    if  (MC -> Position.x >= 240 && MC -> Position.x <= 350 && !get_coin){
        al_draw_filled_triangle(MC -> Position.x + 200, 700, MC -> Position.x + 200, 740, MC -> Position.x + 170, 720, al_map_rgb(255, 255, 255));
        al_draw_filled_rounded_rectangle(MC -> Position.x + 200, 680, MC -> Position.x + 500, 800, 10, 10, al_map_rgb(255, 255, 255));
        al_draw_text(PoetFont, al_map_rgb(0, 0, 0), MC -> Position.x + 240, 700, 0, "Press I to");
        al_draw_text(PoetFont, al_map_rgb(0, 0, 0), MC -> Position.x + 240, 740, 0, "Interact"); 
    }

    if  (MC -> Position.x >= 140 && MC -> Position.x <= 200 && get_coin && !coin_picked){
        al_draw_filled_triangle(MC -> Position.x + 200, 700, MC -> Position.x + 200, 740, MC -> Position.x + 170, 720, al_map_rgb(255, 255, 255));
        al_draw_filled_rounded_rectangle(MC -> Position.x + 200, 680, MC -> Position.x + 500, 800, 10, 10, al_map_rgb(255, 255, 255));
        al_draw_text(PoetFont, al_map_rgb(0, 0, 0), MC -> Position.x + 240, 700, 0, "Press P to");
        al_draw_text(PoetFont, al_map_rgb(0, 0, 0), MC -> Position.x + 240, 740, 0, "Pick up"); 
    }

    if (up) al_draw_scaled_bitmap(BARBELL, 0, 0, 460, 319, 330, 740, 120, 90, 0);
    else al_draw_scaled_bitmap(BARBELL, 0, 0, 460, 319, 330, 790, 120, 90, 0);

    if (get_coin && !Shared::coin){
        al_draw_scaled_bitmap(COIN, 0, 0, 618, 618, 270, 785, 40, 40, 0);
    }
}

void GYMscene::OnKeyDown(int keyCode){
    switch(keyCode){
        case ALLEGRO_KEY_A:
            MC -> MoveLeft(1.0f/ 60.0f);
            break;
        case ALLEGRO_KEY_D:
            MC -> MoveRight(1.0f/ 60.0f);
            break;
        case ALLEGRO_KEY_E:
            if(MC -> Position.x >= 20 && MC -> Position.x <= 150) Engine::GameEngine::GetInstance().ChangeScene("DataRoom");
            if(MC -> Position.x >= 1400) Engine::GameEngine::GetInstance().ChangeScene("DiningRoom");
            break;
        case ALLEGRO_KEY_B:
            Engine::GameEngine::GetInstance().ChangeScene("Backpack");
            break;
        case ALLEGRO_KEY_P:
            if(MC -> Position.x >= 980 && MC -> Position.x <= 1180) Shared::Gold = true;
            if  (MC -> Position.x >= 140 && MC -> Position.x <= 200 && get_coin)
            {
                coin_picked = true;
                Shared::coin = true;
            }
            break;
        case ALLEGRO_KEY_I:
            if(MC -> Position.x >= 240 && MC -> Position.x <= 350) 
            {
                use_barbell++;
                up = true;
            } 
            if (use_barbell >= 5)
                get_coin = true;
            break;
        case ALLEGRO_KEY_ESCAPE:
            Engine::GameEngine::GetInstance().ChangeScene("PauseScene");
            break;
        case ALLEGRO_KEY_M:
            Engine::GameEngine::GetInstance().ChangeScene("Map");
            break;
        default:
            break;
    }
}
void GYMscene::OnKeyUp(int keyCode){
    switch (keyCode) {
        case ALLEGRO_KEY_A:
            MC->Stop();
            break;
        case ALLEGRO_KEY_D:
            MC->Stop();
            break;
        case ALLEGRO_KEY_I:
            if(MC -> Position.x >= 240 && MC -> Position.x <= 350 && up) 
                up = false;
            break;
        default:
            break;
    }
}
