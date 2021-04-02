//
// Created by support on 02.04.2021.
//

#pragma once

#include <vector>
#include "INode.h"

#include <robot2D/Core/Event.h>

namespace gui {
    class Gui final:  public robot2D::Drawable{
    public:
        Gui();
        ~Gui() = default;

        void handleEvents(const robot2D::Event& event);
        void update(float dt);
        void pack(INode::Ptr node);
    protected:
        void draw(robot2D::RenderTarget& target,
                  robot2D::RenderStates states) const override;

    private:
        std::vector<INode::Ptr> m_nodes;
    };
}