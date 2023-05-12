#pragma once
#include "stdafx.h"
#include <string>

#define LOG(fmt, ...) logger::print("", fmt, ##__VA_ARGS__);
#define LOG_ERROR(fmt, ...) logger::print("Error", fmt, ##__VA_ARGS__);
#define LOG_WARN(fmt, ...) logger::print("Warning", fmt, ##__VA_ARGS__);
#define LOG_DEV(fmt, ...) logger::print("Dev", fmt, ##__VA_ARGS__);

#define LOG_DASHBOARD(fmt, ...) logger::print("Dashboard", fmt, ##__VA_ARGS__);
#define LOG_HUD(fmt, ...) logger::print("Dashboard", fmt, ##__VA_ARGS__);


namespace logger {
	void init();
	void print(std::string type, const char* fmt, ...);
	void print_dev(std::string type, const char* fmt, ...);
};