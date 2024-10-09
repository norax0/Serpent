#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <Geode/Geode.hpp>

#define CREATE_HOOK_FOR(function, pyfn, wrapperName, address, convention, returnName, body)                \
if (pybind11::globals().contains(pyfn)) {                                                                  \
	auto returnName = Mod::get()->hook(                                                                    \
        reinterpret_cast<void*>(address),                                                                  \
        &wrapperName,                                                                                      \
        function,                                                                                          \
        tulip::hook::TulipConvention::convention                                                           \
    );                                                                                                     \
	body                                                                                                   \
}                                                                                                          \

#define CREATE_HOOK_WITH_CHECK_FOR(function, pyfn, wrapperName, address, convention, returnName)           \
CREATE_HOOK_FOR(function, pyfn, wrapperName, address, convention, returnName,                              \
	if (returnName.isErr()) {                                                                              \
		log::error("Error enabling {} hook.", function);                                                   \
	}                                                                                                      \
)                                                                                                          \

#define GET_PY_FN(fn, type, ...) pybind11::globals()[fn](__VA_ARGS__).cast<type>()                  

namespace Serpent {

	extern pybind11::module m;
	extern std::unordered_map<std::string, intptr_t> methods;


	void initModule();

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

		// mod-specific bindings
		struct serpent {
			static void bind();
		};
	}

	namespace wrappers {
		bool MenuLayer_init(MenuLayer* self);
		void MenuLayer_onMoreGames(MenuLayer* self, cocos2d::CCObject* p0);
	}

	class script {
	public:
		std::string ID;
		script(const std::string& scriptID) : ID(scriptID) {
			wrapper::setParent(this);
		}
		void initAllHooks();
	private:
		struct wrapper {
			static script* instance;

			static void setParent(script* parent) {
				instance = parent;
			}
			static bool MenuLayer_init(MenuLayer* self);
			static void MenuLayer_onMoreGames(MenuLayer* self, cocos2d::CCObject* p0);
		};
	};
}