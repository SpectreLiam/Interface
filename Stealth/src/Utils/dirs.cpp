#include "dirs.h"
#include "Interface/Interface.h"

std::unique_ptr<dirs> g_dirs;

bool create_directories(std::vector<std::string> directories) {
	for (std::size_t i = 0; i < directories.size(); i++) {
		if (!CreateDirectoryA(directories[i].c_str(), nullptr)) {
			if (GetLastError() != ERROR_ALREADY_EXISTS)
				return false;
		}
	}

	return true;
}

dirs::dirs() {
	sprintf_s(m_paths[PATH_MOUNT].b, "INTERFACE:");
	sprintf_s(m_paths[PATH_HDD].b, "HDD:");
	sprintf_s(m_paths[PATH_USB].b, "USB:");
	sprintf_s(m_paths[PATH_MAIN].b, "%s\\Interface", m_paths[PATH_MOUNT].b);
	sprintf_s(m_paths[PATH_RESOURCE].b, "%s\\Resource", m_paths[PATH_MAIN].b);
	sprintf_s(m_paths[PATH_LOG].b, "%s\\xbHive.log", m_paths[PATH_MAIN].b);

	m_success = mount("INTERFACE:", get_system_mount(), true);
	if (!m_success) {
		m_error = "Failed to mount Interface";
		return;
	}

	m_success = mount("HDD:", "\\Device\\Harddisk0\\Partition1", true);
	if (!m_success) {
		m_error = "Failed to mount HDD partition";
		return;
	}

	mount("USB:", "\\Device\\Mass0\\", true);

	std::vector<std::string> directories;
	directories.push_back(m_paths[PATH_MAIN].b);
	directories.push_back(m_paths[PATH_RESOURCE].b);

	m_success = create_directories(directories);

	if (!m_success)
		m_error = "Failed to create directories";
}

HRESULT dirs::mount_path(std::string drive, std::string device, std::string sys) {
	STRING device_name, link_name;

	char destination[MAX_PATH];
	sprintf_s(destination, sys.c_str(), drive.c_str());
	RtlInitAnsiString(&device_name, device.c_str());
	RtlInitAnsiString(&link_name, destination);
	ObDeleteSymbolicLink(&link_name);
	return (HRESULT)ObCreateSymbolicLink(&link_name, &device_name);
}

bool dirs::mount(std::string drive, std::string device, bool both) {
	if (both)
		return SUCCEEDED(mount_path(drive, device, "\\System??\\%s")) && SUCCEEDED(mount_path(drive, device, "\\??\\%s"));

	if (KeGetCurrentProcessType() == PROC_SYSTEM)
		return SUCCEEDED(mount_path(drive, device, "\\System??\\%s"));

	return SUCCEEDED(mount_path(drive, device, "\\??\\%s"));
}

std::string dirs::get_system_mount() {
	std::wstring ws = g_interface->m_client.m_table_entry->FullDllName.Buffer;
	std::string full_name(begin(ws), end(ws));

	ws = g_interface->m_client.m_table_entry->BaseDllName.Buffer;
	std::string base_name(begin(ws), end(ws));

	auto pos = full_name.find(base_name);
	if (pos != std::string::npos)
		full_name.erase(pos, base_name.length());

	return full_name;
}

bool dirs::exists(std::string file) {
	if (GetFileAttributes(file.c_str()) == -1)
		if (GetLastError() == ERROR_FILE_NOT_FOUND || GetLastError() == ERROR_PATH_NOT_FOUND)
			return false;

	return true;
}

std::vector<std::string> dirs::get_files_in_directory(std::string directory, std::string extension) {
	return std::vector<std::string>();
}