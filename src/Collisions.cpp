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
#include <cmath>
#include "game/Collisions.h"

float length(const hakka::vec2f& vec){
    return std::sqrt(vec.x * vec.x
                        + vec.y * vec.y);
}

float clamp(float value, float min, float max){
    return std::max(min, std::min(max, value));
}

hakka::vec2f normalize(const hakka::vec2f& vec){
    hakka::vec2f res;

    float inv_len = 1.f / length(vec);
    res.x = vec.x * inv_len;
    res.y = vec.y * inv_len;

    return res;
}

float dot(const hakka::vec2f& left, const hakka::vec2f& right){
    float x = left.x * right.x;
    float y = left.y * right.y;
    return x + y;
}

Direction find_direction(const hakka::vec2f& vec){
    hakka::vec2f compass[] = {
            hakka::vec2f(0.0f, 1.0f),	// up
            hakka::vec2f(1.0f, 0.0f),	// right
            hakka::vec2f(0.0f, -1.0f),	// down
            hakka::vec2f(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;

    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = dot(normalize(vec), compass[i]);
        if (dot_product > max) {
            max = dot_product;
            best_match = i;
        }
    }

    Direction direction;
    if(best_match == 0)
        direction = Direction::up;
    if(best_match == 1)
        direction = Direction::right;
    if(best_match == 2)
        direction = Direction::down;
    if(best_match == 3)
        direction = Direction::left;

    return direction;
}

bool checkCollision(const GameObject &lob, const GameObject &rob) {
    bool collisionX = lob.m_pos.x + lob.m_size.x >= rob.m_pos.x
            && rob.m_pos.x + rob.m_size.x >= lob.m_pos.x;
    bool collisionY = lob.m_pos.y + lob.m_size.y >= rob.m_pos.y
                      && rob.m_pos.y + rob.m_size.y >= lob.m_pos.y;

    return collisionX && collisionY;
}

Collision checkCollision(const BallObject& lob, const GameObject& rob) {
    hakka::vec2f center(lob.m_pos.x + lob.radius,
                        lob.m_pos.y + lob.radius);

    hakka::vec2f aabb_half_extents(rob.m_size.x / 2.f,
                                   rob.m_size.y / 2.f);
    hakka::vec2f aabb_center(rob.m_pos.x + aabb_half_extents.x,
                             rob.m_pos.y + aabb_half_extents.y);
    hakka::vec2f distance = center - aabb_center;
    hakka::vec2f clamped;
    clamped.x = clamp(distance.x, -aabb_half_extents.x, aabb_half_extents.x);
    clamped.y = clamp(distance.y, -aabb_half_extents.y, aabb_half_extents.y);

    hakka::vec2f closest = aabb_center + clamped;
    distance = closest - center;

    if (length(distance) <= lob.radius)
        return std::make_tuple(true, find_direction(distance), distance);
    else
        return std::make_tuple(false, Direction::up, hakka::vec2f());
}
