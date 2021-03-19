#include <iostream>
#include "hakka/App.h"

#include "game/GameState.h"
#include "game/IntroState.h"
//demo state
#include "game/EcsState.h"
#include "game/Audio.h"

enum States{
    Intro = 1,
    Game = 2,
    Menu = 3,
    Pause = 4,
    Ecs = 5
};


int main() {
    Audio::getInstanse() -> loadFile("res/audio/breakout.wav",
                                     "breakout", AudioType::music);
    Audio::getInstanse() -> play("breakout", true);
    Audio::getInstanse() -> setVolume("breakout", 80.f);

    hakka::App my_app;

    my_app.register_state<IntroState>(States::Intro, my_app);
    my_app.register_state<GameState>(States::Game, my_app);

    my_app.setCurrent(States::Intro);

    my_app.run();

    return 0;
}
