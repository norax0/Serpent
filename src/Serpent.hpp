#pragma once
#include <pybind11/pybind11.h>


#define CREATE_WRAPPER_FOR(function, pyfn, type, class_, ...)                     \
type pyfn(class_ self, __VA_ARGS__) {                                             \
	pybind11::object fn = pybind11::globals()[#pyfn];                       	  \
	return fn(self, ##__VA_ARGS__).cast<type>();                            	  \
}                                                                                 \

#define CREATE_HOOK_FOR(function, pyfn, address, convention)          \
if (pybind11::globals().contains(#pyfn)) {                            \
    auto result = Mod::get()->hook(                                   \
        reinterpret_cast<void*>(address),                             \
        &pyfn,                                                        \
        #function,                                                    \
        tulip::hook::TulipConvention::convention                      \
    );                                                                \
}                                                                     \

#define GET_PY_FN(fn, type, ...) pybind11::globals()[fn](__VA_ARGS__).cast<type>()                  

namespace Serpent {

	extern pybind11::module m;

	void initModule();

	namespace hook {
		void initAllHooks();
	}

	namespace bindings {
		struct _geode { // prefixed with _ so compiler/YOU doesnt/dont get confused between Serpent::geode and geode ns
			static void bind();
			static void enums();
		};

		struct cocos {
			static void bind();
			static void enums();
		};

		struct robtop {
			static void bind();
			static void enums();
		};
	}
}