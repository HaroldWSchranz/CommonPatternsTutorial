/* @brief multithreaded_application.h
	Custom tick() implementation.
*/
#pragma once
#ifndef MULTITHREADED_APPLICATION_H
#define MULTITHREADED_APPLICATION_H

#include "base_application.h"
#include <thread>
#include <mutex>

class multithreaded_application : public base_application
{
private:
	std::thread m_render_thread;
	std::mutex m_render_data_mutex;
public:
	multithreaded_application();
	//multithreaded_application() = default;
	void tick() override;
};
#endif // !MULTITHREADED_APPLICATION_H

