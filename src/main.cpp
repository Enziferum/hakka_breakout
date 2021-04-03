//#define CONSOLE
#ifndef CONSOLE
    #include <windows.h>
#endif

#include <robot2D/Util/Logger.h>
#include "robot2D/Core/App.h"
#include <robot2D/Util/ResourceHandler.h>

#include "game/IntroState.h"
#include "game/MenuState.h"
#include "game/GameState.h"


#include "game/Audio.h"
#include "game/States.h"

namespace {
    enum Icon{
        Default
    };
}

void pre_init() {
    logger::debug = true;

    Audio::getInstanse() -> loadFile("res/audio/breakout.wav",
                                     AudioFileID::breakout, AudioType::music);
    Audio::getInstanse() -> play(AudioFileID::breakout, true);
    Audio::getInstanse() -> setVolume(AudioFileID::breakout, 80.f);
}

void run() {
    pre_init();

    robot2D::App my_app{robot2D::vec2u(800, 600),
                        "robot2D Game", true};

    my_app.register_state<IntroState>(States::Intro, my_app);
    my_app.register_state<MenuState>(States::Menu, my_app);
    my_app.register_state<GameState>(States::Game, my_app);
    my_app.setCurrent(States::Game);

    robot2D::ResourceHandler<robot2D::Texture, Icon> g_icons;
    g_icons.loadFromFile(Icon::Default, "res/textures/icon.png", true);

    std::vector<robot2D::Texture> icons = {g_icons.get(Icon::Default)};

    my_app.setIcon(icons);

    my_app.run();
}


#ifdef CONSOLE
int main()
#else
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevIns, LPSTR lpszArgument, int iShow)
#endif
{
    run();
    return 0;
}