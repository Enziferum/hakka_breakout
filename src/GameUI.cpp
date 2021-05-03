/*********************************************************************
(c) Alex Raag 2021
https://github.com/Enziferum
robot2D - Zlib license.
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
#include <robot2D/Util/Logger.h>
#include <robot2D/Graphics/RenderTarget.h>
#include <robot2D/Graphics/RenderStates.h>

#include <game/GameUI.hpp>
#include <game/MessageIDs.hpp>
#include <game/FileManager.hpp>


GameUI::GameUI() {
    setup();
}

void GameUI::setup() {
    m_fonts.loadFromFile(ResourceIDs::Font, "res/fonts/game_font.ttf");

    m_livesText.setText("Lives:");
    m_livesText.setPos(robot2D::vec2f(50, 10));
    m_livesText.setFont(m_fonts.get(ResourceIDs::Font));
}

void GameUI::handleMessage(const Message& msg) {
    if(msg.id == messageIDs::LivesUpdate){
        auto data = msg.unpack<LivesEvent>();
        const auto text = "Lives: " + std::to_string(data.new_lives);
        m_livesText.setText(text);
    }
}

void GameUI::update(float dt) {

}

void GameUI::draw(robot2D::RenderTarget& target, robot2D::RenderStates states) const {
    target.draw(m_livesText);
}


