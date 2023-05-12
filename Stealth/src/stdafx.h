#pragma once
#define _USE_MATH_DEFINES

#include <xtl.h>
#include <xboxmath.h>
#include <ppcintrinsics.h>
#include <memory>

#define KERNEL_VERSION 0x4497

namespace std {
	template <typename T>
	inline std::unique_ptr<T> make_unique() {
		return std::unique_ptr<T>(new T());
	}

	template <typename T, typename P1>
	inline std::unique_ptr<T> make_unique(P1 p1) {
		return std::unique_ptr<T>(new T(p1));
	}
}



using namespace std;