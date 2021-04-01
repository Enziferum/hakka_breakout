#include <iostream>
#include "robot2D/Core/App.h"

#include "game/GameState.h"
#include "game/IntroState.h"

#include "game/Audio.h"
#include "game/States.h"


int main() {
    Audio::getInstanse() -> loadFile("res/audio/breakout.wav",
                                     AudioFileID::breakout, AudioType::music);
    Audio::getInstanse() -> play(AudioFileID::breakout, true);
    Audio::getInstanse() -> setVolume(AudioFileID::breakout, 80.f);

    robot2D::App my_app{robot2D::vec2u(800, 600),
                        "robot2D Game", true};

    my_app.register_state<IntroState>(States::Intro, my_app);
    my_app.register_state<GameState>(States::Game, my_app);


    my_app.run();

    return 0;
}
