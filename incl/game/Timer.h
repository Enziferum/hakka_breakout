//
// Created by support on 02.04.2021.
//

#pragma once

#include <functional>
#include <utility>

//todo be based on chrono
class Timer{
public:
    Timer();
    Timer(const float& endTime, bool endless = false);
    ~Timer() = default;

    void update(float dt);
    float elapsed() const;

    void onTick(std::function<void(float dt)>);
    void reset(float to_time = 0.f);
private:
    std::function<void(float)> m_callback;
    float m_end;
    float m_start;
    bool m_endless;
};

