///
/// Created by Kris on 2024/6/10
///

#ifndef WINSCENE_HPP
#define WINSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class WinScene final : public Engine::IScene {
    private:
    public:
        explicit WinScene() = default;
        void Initialize() override;
        void Terminate() override;
        void OnKeyDown(int keycode) override;
        std::string GetName() const override { return "Win"; }
};


#endif
