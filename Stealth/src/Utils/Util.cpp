#include "util.h"

namespace util {
	DWORD get_proc_address(std::string module_name, DWORD ordinal) {
		HANDLE proc, handle;

		if (!NT_SUCCESS(XexGetModuleHandle((char*)module_name.c_str(), &handle)))
			return 0;

		if (!NT_SUCCESS(XexGetProcedureAddress(handle, ordinal, &proc)))
			return 0;

		return (DWORD)proc;
	}
};