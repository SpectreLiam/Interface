#pragma once
#include "stdafx.h"
#include <xkelib.h>
#include <string>

namespace util {
	DWORD get_proc_address(std::string module_name, DWORD ordinal);
}