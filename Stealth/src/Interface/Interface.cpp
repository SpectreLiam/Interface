#include "Interface.h"

std::unique_ptr<Interface> g_interface;

Interface::Interface(void* handle) {
	m_console.m_xdk = !(*(int*)0x8E038610 & 0x8000);

	m_client.m_handle = (HMODULE)handle;
	XexPcToFileHeader((void*)0x90900000, &m_client.m_table_entry);
}