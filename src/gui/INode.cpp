//
// Created by support on 02.04.2021.
//

#include "game/gui/INode.h"

namespace gui {
    INode::INode():
        m_pos(),
        m_pressed(false),
        m_hover(false){}

    INode::~INode() {}

    void INode::onPress(const robot2D::vec2f&) {
    }

    void INode::onHover(const robot2D::vec2f&) {
    }

    void INode::update(float dt) {

    }

    void INode::setPosition(float x, float y) {
        setPosition(robot2D::vec2f(x, y));
    }

    void INode::setPosition(const robot2D::vec2f &pos) {
        m_pos = pos;
    }
}