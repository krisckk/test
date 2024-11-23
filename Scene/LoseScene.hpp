///
/// Created by Kris on 2024/6/10
///

#ifndef LOSESCENE_HPP
#define LOSESCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class LoseScene final : public Engine::IScene {
    private:
    public:
        explicit LoseScene() = default;
        void Initialize() override;
        void Terminate() override;
        void OnKeyDown(int keycode) override;
        std::string GetName() const override { return "Lose"; }
};


#endif
