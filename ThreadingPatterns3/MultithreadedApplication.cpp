#include "MultiThreadedApplication.h"
#include <iostream>

MultithreadedApplication::MultithreadedApplication()
{
    m_renderThread = std::thread([&] {
        while (true)
        {
            if (m_readyToRender)
            {
                m_culling.Execute();
                m_renderer.Execute();
            }
        }
    });

    m_pathfindingThread = std::thread([&] {
        while (true)
        {
            m_pathfinding.Execute();
        }
    });
}

void MultithreadedApplication::Tick()
{
    m_input.Execute();
    m_gameLogic.Execute();
    m_physics.Execute();

    m_readyToRender = false;
    m_updateRenderData.Execute();
    m_readyToRender = true;
}
