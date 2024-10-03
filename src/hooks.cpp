#include "Serpent.hpp"

using namespace geode::prelude;

bool MenuLayer_init(MenuLayer* self) {
    return pybind11::globals()["MenuLayer_init"](self).cast<bool>();
}

namespace Serpent::hook {
    // automatically enabels hook whenever a function is defined as ClassName_function
    // @note[short] doesnt work for all functions.
    void initAllHooks() {
        log::info("Enabling hooks");
        if (pybind11::globals().contains("MenuLayer_init")) {
            auto result = Mod::get()->hook(
                reinterpret_cast<void*>(geode::base::get() + 0x3130f0),
                &MenuLayer_init,
                "MenuLayer::init",
                tulip::hook::TulipConvention::Thiscall
            );

            if (result.isErr()) {
                log::error("An error occured enabling hook for MenuLayer::init: {}", result.err());
            }
        }
    }
}