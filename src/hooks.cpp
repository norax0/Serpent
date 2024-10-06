#include "Serpent.hpp"

using namespace geode::prelude;

bool MenuLayer_init(MenuLayer* self) {
    return GET_PY_FN("MenuLayer_init", bool, self);
}

void MenuLayer_onMoreGames(MenuLayer* self, CCObject* p0) {
    return GET_PY_FN("MenuLayer_onMoreGames", void, self, p0);
}

namespace Serpent::hook {
    // automatically enable hooks whenever a function is defined as ClassName_function

    void initAllHooks() {
        log::info("Enabling hooks");
        CREATE_HOOK_FOR(MenuLayer::init, MenuLayer_init, geode::base::get() + 0x3130f0, Default)
        CREATE_HOOK_FOR(MenuLayer::onMoreGames, MenuLayer_onMoreGames, geode::base::get() + 0x314da0, Thiscall)
    }
}