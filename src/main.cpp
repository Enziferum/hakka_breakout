#include <robot2D/Util/Logger.h>
#include "robot2D/Core/App.h"

#include "game/IntroState.h"
#include "game/MenuState.h"
#include "game/GameState.h"


#include "game/Audio.h"
#include "game/States.h"

void pre_init() {
    logger::debug = true;

    Audio::getInstanse() -> loadFile("res/audio/breakout.wav",
                                     AudioFileID::breakout, AudioType::music);
    Audio::getInstanse() -> play(AudioFileID::breakout, true);
    Audio::getInstanse() -> setVolume(AudioFileID::breakout, 80.f);
}

int main() {
    pre_init();

    robot2D::App my_app{robot2D::vec2u(800, 600),
                        "robot2D Game", true};

    my_app.register_state<IntroState>(States::Intro, my_app);
    my_app.register_state<MenuState>(States::Menu, my_app);
    my_app.register_state<GameState>(States::Game, my_app);
    my_app.setCurrent(States::Game);

    my_app.run();

    return 0;
}
