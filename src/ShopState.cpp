/*********************************************************************
(c) Alex Raag 2021
https://github.com/Enziferum
robot2D_game - Zlib license.
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

#include <game/ShopState.hpp>

ShopState::ShopState(robot2D::IStateMachine &machine, AppContext<ContextID> &context):
State(machine),
m_context(context)
{
    setup();
}

void ShopState::setup() {
    load_resources();
}

void ShopState::load_resources() {

}

void ShopState::handleEvents(const robot2D::Event &event) {
    m_gui.handleEvents(event);
}

void ShopState::update(float dt) {

}

void ShopState::render() {
    m_window.draw(m_gui);
}

