/* @brief multithreaded_application.cpp
	Custom tick() implementation.
*/
#include "multithreaded_application.h"

multithreaded_application::multithreaded_application() : m_waiting_to_write(false)
{
	m_render_thread = std::thread([&]
	{
			while (true)
			{
				if (!m_waiting_to_write)
				{
					m_render_data_mutex.lock();
					m_culling.execute();
					m_renderer.execute();
					m_render_data_mutex.unlock();
				}
			}
	});
}


/* @brief Ordered custom tick() implementation.
*/
void multithreaded_application::tick()
{
	m_waiting_to_write = true;
	m_render_data_mutex.lock();

	m_waiting_to_write = false;
	m_update_render_data.execute();
	m_render_data_mutex.unlock();

	// Game mechanics
	m_input.execute();
	m_game_logic.execute();
	m_physics.execute();
	m_pathfinding.execute();
}
