//
// Created by support on 02.04.2021.
//

#pragma once

namespace gui {
    class BounceAnimation{
    public:
        BounceAnimation();
        ~BounceAnimation() = default;

        void update(float dt);
        void play();
        void pause();
    private:
    };
}
