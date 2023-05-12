#include "Init.h"
#include "Interface.h"
#include "utils/dirs.h"
#include "utils/log.h"

namespace init {
	void entry(void* handle) {
		g_interface = std::make_unique<Interface>(handle);

		g_dirs = std::make_unique<dirs>();
		if (!g_dirs->m_success) {
			LOG_ERROR("%s", g_dirs->m_error.c_str());
			return;
		}
	}
}