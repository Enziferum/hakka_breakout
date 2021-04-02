//
// Created by support on 02.04.2021.
//

#pragma once

#include <memory>
#include <robot2D/Core/Vector2.h>
#include <robot2D/Graphics/Drawable.h>

namespace gui{

    class INode: public robot2D::Drawable{
    public:
        using Ptr = std::shared_ptr<INode>;
    public:
        INode();
        virtual ~INode() = 0;

        void setPosition(float x, float y);
        void setPosition(const robot2D::vec2f& pos);

        virtual void onPress(const robot2D::vec2f&);
        virtual void onHover(const robot2D::vec2f&);
        virtual void update(float dt);
    protected:
        void draw(robot2D::RenderTarget &target, robot2D::RenderStates states)
        const override = 0;

    protected:
        robot2D::vec2f m_pos;
        bool m_pressed;
        bool m_hover;
    };

}
