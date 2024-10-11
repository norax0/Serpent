#include "Serpent.hpp"
#include <Geode/Geode.hpp>

using namespace Serpent;
using namespace geode::prelude;
namespace py = pybind11;

//script* script::wrapper::instance = nullptr;

bool script::wrapper::MenuLayer_init(MenuLayer* self) {
    return GET_PY_FN(instance->mainClass, "MenuLayer_init", bool, self);
}

void script::wrapper::MenuLayer_onMoreGames(MenuLayer* self, CCObject* p0) {
    return GET_PY_FN(instance->mainClass, "MenuLayer_onMoreGames", void, self, p0);
}

void script::initAllHooks() {
    log::info("Enabling hooks for {}", ID);
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::init", "MenuLayer_init", wrapper::MenuLayer_init, geode::base::get() + 0x3130f0, Thiscall, MenuLayer_initHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onMoreGames", "MenuLayer_onMoreGames", wrapper::MenuLayer_onMoreGames, geode::base::get() + 0x314da0, Thiscall, MenuLayer_onMoreGamesHook)
}

script* script::wrapper::instance = nullptr;