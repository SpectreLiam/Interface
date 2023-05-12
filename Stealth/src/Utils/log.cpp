#include "log.h"
#include "dirs.h"
#include <fstream>
#include <time.h>

char g_buffer[0x500];

void logger::init() {
	remove(g_dirs->m_paths[PATH_LOG].b);
}

void logger::print(std::string type, const char* fmt, ...) {
	memset(g_buffer, 0, sizeof(g_buffer));

	va_list va_l;
	va_start(va_l, fmt);
	vsprintf(g_buffer, fmt, va_l);
	va_end(va_l);

	time_t raw_time;
	time(&raw_time);

	tm time;
	localtime_s(&time, &raw_time);

	char time_str[0x80];
	strftime(time_str, 0x80, "%d.%m.%Y %X", &time);

	char print_str[0x1000];
	if (type.empty()) sprintf_s(print_str, "[%s] %s\n", time_str, g_buffer);
	else sprintf_s(print_str, "[%s][%s] %s\n", time_str, type.c_str(), g_buffer);

	std::ofstream output(g_dirs->m_paths[PATH_LOG].b, std::ios::app);
	if (output.good()) {
		output << print_str;
		output.close();
	}
}

void logger::print_dev(std::string type, const char* fmt, ...) {
	memset(g_buffer, 0, sizeof(g_buffer));

	va_list va_l;
	va_start(va_l, fmt);
	vsprintf(g_buffer, fmt, va_l);
	va_end(va_l);

	time_t raw_time;
	time(&raw_time);

	tm time;
	localtime_s(&time, &raw_time);

	char time_str[0x80];
	strftime(time_str, 0x80, "%d.%m.%Y %X", &time);

	char print_str[0x1000];
	if (type.empty()) sprintf_s(print_str, "[%s] %s\n", time_str, g_buffer);
	else sprintf_s(print_str, "[%s][%s] %s\n", time_str, type.c_str(), g_buffer);

	std::ofstream output(g_dirs->m_paths[PATH_LOG].b, std::ios::app);
	if (output.good()) {
		output << print_str;
		output.close();
	}

	DbgPrint(print_str);
}