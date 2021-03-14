/*********************************************************************
(c) Alex Raag 2021
https://github.com/Enziferum
hakka - Zlib license.
This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.
2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any
source distribution.
*********************************************************************/

#pragma once

#include "hakka/Sprite.h"
#include "hakka/ResourceHandler.h"
#include "State.h"
#include "Level.h"
#include "ParticleEmitter.h"

class GameState: public State{
public:
    using Ptr = std::shared_ptr<GameState>;
public:
    GameState(IStateMachine& machine);
    ~GameState() override;

    void handleEvents(const hakka::Event& event) override;
    void update(float dt) override;
    void render() override;

private:
    void setup();
    void process_collisions(float dt);

    void reset_game();
private:
    hakka::ResourceHandler<hakka::Texture> m_textures;
    hakka::Sprite m_background;

    GameObject m_paddle;
    BallObject m_ball;

    ParticleEmitter m_particleEmitter;

    std::vector<Level> m_levels;
    unsigned int currlevel = 0;

    bool m_keys[1024];
    bool m_keysProcessed[1024];

    int m_lives = 3;
};