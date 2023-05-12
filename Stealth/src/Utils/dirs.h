#pragma once
#include "stdafx.h"
#include <string>
#include <unordered_map>
#include <xkelib.h>


enum eDirs : int {
	PATH_MOUNT,
	PATH_MAIN,
	PATH_RESOURCE,
	PATH_HDD,
	PATH_USB,
	PATH_LOG,
};

struct dir_buffer {
	char b[MAX_PATH];
};

class dirs {
public:
	dirs();

	bool exists(std::string file);
	bool mount(std::string drive, std::string device, bool both);

	std::string get_system_mount();
	std::vector<std::string> get_files_in_directory(std::string directory, std::string extension);

	// TODO: read/write
public:
	bool m_success;
	std::string m_error;

	std::unordered_map<eDirs, dir_buffer> m_paths;

private:
	HRESULT mount_path(std::string drive, std::string device, std::string sys);
};

extern std::unique_ptr<dirs> g_dirs;