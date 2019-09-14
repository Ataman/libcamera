/* SPDX-License-Identifier: LGPL-2.1-or-later */
/*
 * Copyright (C) 2019, Google Inc.
 *
 * timer.h - Generic timer
 */
#ifndef __LIBCAMERA_TIMER_H__
#define __LIBCAMERA_TIMER_H__

#include <chrono>
#include <cstdint>

#include <libcamera/object.h>
#include <libcamera/signal.h>

namespace libcamera {

class Message;

class Timer : public Object
{
public:
	Timer(Object *parent = nullptr);
	~Timer();

	void start(unsigned int msec) { start(std::chrono::milliseconds(msec)); }
	void start(std::chrono::milliseconds interval);
	void stop();
	bool isRunning() const;

	std::chrono::milliseconds interval() const { return interval_; }
	std::chrono::steady_clock::time_point deadline() const { return deadline_; }

	Signal<Timer *> timeout;

protected:
	void message(Message *msg) override;

private:
	void registerTimer();
	void unregisterTimer();

	std::chrono::milliseconds interval_;
	std::chrono::steady_clock::time_point deadline_;
};

} /* namespace libcamera */

#endif /* __LIBCAMERA_TIMER_H__ */
