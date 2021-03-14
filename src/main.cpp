#include "game/App.h"
#include "game/GameState.h"
#include "game/IntroState.h"

enum States{
    Intro = 0,
    Menu = 1,
    Game = 2
};

int main() {
    App app;
    1==1;
    GameState::Ptr game_state = std::make_shared<GameState>(app);
    IntroState::Ptr introState = std::make_shared<IntroState>(app);
    app.addState(States::Intro, introState);
    app.addState(States::Game, game_state);

    app.setCurrentState(States::Game);
    app.run();

    return 0;
}
