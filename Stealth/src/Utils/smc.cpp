#include "smc.h"
#include <xkelib.h>

namespace smc {
	bool is_tray_open() {
		BYTE msg[0x10];
		BYTE resp[0x10];
		msg[0] = 0xA;

		HalSendSMCMessage(msg, resp);
		return (resp[1] == 0x60);
	}
};