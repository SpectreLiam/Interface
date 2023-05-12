#pragma once
#include "stdafx.h"
#include <xkelib.h>
#include <memory>

struct Interface_console {
	bool m_xdk;
};

struct Interface_client {
	HMODULE m_handle;
	PLDR_DATA_TABLE_ENTRY m_table_entry;
};

class Interface {
public:
	Interface(void* handle);

	Interface_console m_console;
	Interface_client m_client;
};

extern std::unique_ptr<Interface> g_interface;