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

#include <iostream>
#include <utility>
#include <ctime>
//todo own keys
#include <GLFW/glfw3.h>

#include "game/GameState.h"
#include "game/Collisions.h"

constexpr float speed = 500.f;

GameState::GameState(IStateMachine& machine):
    State(machine), m_keys(), m_keysProcessed() {
    setup();
}

GameState::~GameState() {}


void GameState::setup() {

    srand( time(0) );

    //load textures
    m_textures.loadFromFile("background", "res/textures/background.jpg");
    m_textures.loadFromFile("face","res/textures/awesomeface.png", true);
    m_textures.loadFromFile("block", "res/textures/block.png");
    m_textures.loadFromFile("block_solid", "res/textures/block_solid.png");
    m_textures.loadFromFile("paddle", "res/textures/paddle.png", true);
    m_textures.loadFromFile("particle", "res/textures/particle.png", true);

    m_particleEmitter.setTexture(const_cast<hakka::Texture &>(m_textures.get("particle")));
    auto size = m_window.get_size();

    //load levels
    Level one;
    Level two;
    Level three;
    Level four;

    one.loadLevel("res/levels/1.lvl", hakka::vec2f(size.x, size.y / 2), m_textures);
    two.loadLevel("res/levels/2.lvl", hakka::vec2f(size.x, size.y / 2), m_textures);
    three.loadLevel("res/levels/3.lvl", hakka::vec2f(size.x, size.y / 2), m_textures);
    four.loadLevel("res/levels/4.lvl", hakka::vec2f(size.x, size.y / 2), m_textures);

    m_levels.push_back(one);
    m_levels.push_back(two);
    m_levels.push_back(three);
    m_levels.push_back(four);

    m_background.setTexture(m_textures.get("background"));
    m_background.setPosition(hakka::vec2f(0.f, 0.f));
    m_background.setScale(hakka::vec2f(size.x, size.y));

    m_paddle.m_sprite.setTexture(m_textures.get("paddle"));
    hakka::vec2f paddle_size(100.f, 20.f);
    m_paddle.setPos(hakka::vec2f(size.x / 2.f - paddle_size.x / 2,
                    size.y - paddle_size.y));
    m_paddle.setSize(paddle_size);

    const float ball_radius = 12.5f;

    hakka::vec2f ballPos =  hakka::vec2f(paddle_size.x / 2.0f - ball_radius + m_paddle.m_pos.x,
                                                    -ball_radius * 2.0f + m_paddle.m_pos.y);
    m_ball.m_sprite.setTexture(m_textures.get("face"));
    m_ball.velocity = hakka::vec2f(100.0f, -350.0f);
    m_ball.border = size.y;
    m_ball.radius = ball_radius;
    m_ball.setPos(ballPos);

    m_ball.setSize(hakka::vec2f(ball_radius * 2.f, ball_radius * 2.f));
}

void GameState::process_collisions(float dt) {
    for(auto& box: m_levels[currlevel].getTiles()){
        if(box.m_destroyed)
            continue;
        auto collision = checkCollision(m_ball, box);
        //collide
        if(std::get<0>(collision)){
            if(!box.m_solid)
                box.m_destroyed = true;

            auto dir = std::get<1>(collision);
            auto vec = std::get<2>(collision);

            if(dir == Direction::left || dir == Direction::right){
                m_ball.velocity.x = -m_ball.velocity.x;
                float penetration = m_ball.radius - std::abs(vec.x);
                if (dir == Direction::left)
                    m_ball.m_pos.x += penetration;
                else
                    m_ball.m_pos.x -= penetration;
            }
            else {
                m_ball.velocity.y = -m_ball.velocity.y;
                float penetration = m_ball.radius - std::abs(vec.y) ;
                if (dir == Direction::up)
                    m_ball.m_pos.y -= penetration;
                else
                    m_ball.m_pos.y += penetration;
            }
        }

        collision = checkCollision(m_ball, m_paddle);
        if(!m_ball.stuck && std::get<0>(collision)){
            float centerBoard = m_paddle.m_pos.x + m_paddle.m_size.x / 2.0f;
            float distance = (m_ball.m_pos.x + m_ball.radius) - centerBoard;
            float percentage = distance / (m_paddle.m_size.x / 2.0f);
            // then move accordingly

            float strength = 2.0f;
            hakka::vec2f oldVelocity = m_ball.velocity;
            m_ball.velocity.x = 100.f * percentage * strength;
            m_ball.velocity.y = -1.0f * std::abs(-m_ball.velocity.y);
            m_ball.velocity = normalize(m_ball.velocity) * length(oldVelocity);
        }
    }
}

void GameState::handleEvents(const hakka::Event& event) {

    if(event.type == hakka::Event::KeyPressed){
        m_keys[event.key.code] = true;
    }

    if(event.type == hakka::Event::KeyReleased){
        m_keys[event.key.code] = false;
        m_keysProcessed[event.key.code] = false;
    }


    if(event.type == hakka::Event::MouseButton){
        if(event.mouse.btn == hakka::Event::MouseButtonEvent::left){
            hakka::vec2f mouse_pos(event.mouse.x, event.mouse.y);
            std::cout << event.mouse.x << ":" << event.mouse.y << std::endl;
        }
    }

}

void GameState::update(float dt) {
    float velocity = dt * speed;

    // update input //
    if(m_keys[GLFW_KEY_A]) {
        if (m_paddle.m_pos.x >= 0.f) {
            m_paddle.m_pos.x -= velocity;
            m_paddle.m_sprite.setPosition(m_paddle.m_pos);
            if (m_ball.stuck) {
                m_ball.m_pos.x -= velocity;
                m_ball.m_sprite.setPosition(m_ball.m_pos);
            }
        }
    }

    if(m_keys[GLFW_KEY_D]) {
        if (m_paddle.m_pos.x <= 640 - m_paddle.m_size.x) {
            m_paddle.m_pos.x += velocity;
            m_paddle.m_sprite.setPosition(m_paddle.m_pos);

            if (m_ball.stuck) {
                m_ball.m_pos.x += velocity;
                m_ball.m_sprite.setPosition(m_ball.m_pos);
            }

        }
    }

    if(m_keys[GLFW_KEY_SPACE]){
        m_ball.stuck = false;
    }
    // update input //

    m_ball.move(dt);
    process_collisions(dt);
    m_particleEmitter.update(dt, 2, m_ball, hakka::vec2f(6.25f,
                                                         6.25f));

    //need reset level
    if(m_ball.m_pos.y >= 640)
        reset_game();
}

void GameState::render() {
    m_window.draw(m_background);
    m_window.draw(m_levels[currlevel]);
    m_window.draw(m_paddle);
    m_window.draw(m_particleEmitter);
    m_window.draw(m_ball);
}

void GameState::reset_game() {
    if(m_lives == 0){
        m_machine.pushState(0);
        m_lives = 3;
        return;
    }

    --m_lives;

    auto size = m_window.get_size();
    hakka::vec2f paddle_size(100.f, 20.f);
    const float ball_radius = 12.5f;
    m_paddle.setPos(hakka::vec2f(size.x / 2.f - paddle_size.x / 2,
                                 size.y - paddle_size.y));
    hakka::vec2f ballPos = hakka::vec2f(paddle_size.x / 2.0f - ball_radius + m_paddle.m_pos.x,
                                         -ball_radius * 2.0f + m_paddle.m_pos.y);
    m_ball.stuck = true;
    m_ball.setPos(ballPos);

}
