#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/UndergroundShelter/B4/LabScene.hpp"
#include "Stats/Shared.hpp"
void WinScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("win/winscene.png", 0, 0, w, h, 0, 0));
    Engine::GameEngine::GetInstance().PlayBGM("joannaliaoThemeSong.ogg");
}

void WinScene::Terminate() {
    IScene::Terminate();
}

void WinScene::OnKeyDown(int keyCode)
{
    switch (keyCode)
    {
    case ALLEGRO_KEY_B:
        Engine::GameEngine::GetInstance().ChangeScene("start");
        break;
    default:
        break;
    }
}


