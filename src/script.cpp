#include "Serpent.hpp"
#include <Geode/Geode.hpp>
#include <matjson.hpp>

using namespace Serpent;
using namespace geode::prelude;
namespace py = pybind11;

script* script::wrapper::instance = nullptr;

CREATE_WRAPPER_FOR(instance->mainClass, MenuLayer_init, bool, ARGS(self), MenuLayer* self)
CREATE_WRAPPER_FOR(instance->mainClass, MenuLayer_onMoreGames, void, ARGS(self, p0), MenuLayer* self, cocos2d::CCObject* p0)

std::vector<ui::ScriptItem*> Serpent::scripts;
std::vector<matjson::Value> Serpent::tempScripts;

bool script::CheckMetadata(matjson::Value json) {
    std::vector<std::string> missingKeys;
    if (!json.contains("developer")) {
        missingKeys.push_back("developer");
    } else if (!json.contains("name")) {
        missingKeys.push_back("name");
    } else if (!json.contains("serpent")) {
        missingKeys.push_back("serpent");
    }
    if (missingKeys.empty()) {
        return true;
    } else {
        for (auto& key : missingKeys) {
            log::error("The \"{}\" key is missing for {}", key, ID);
        }
        return false;
    }
}

bool script::loadMetadata(const std::string& str) {
    auto json = matjson::parse(str);
    if (CheckMetadata(json)) {
        name = json["name"].as_string();
        developer = json["developer"].as_string();
        serpentVer = json["serpent"].as_string();
        return true;
    } else {
        return false;
    }
}

std::string script::getScriptJson() {
    auto path = Mod::get()->getConfigDir() / "unzipped" / ID / "script.json";
    auto res = geode::utils::file::readString(path);
    return res.value();
}

void script::initAllHooks() {
    log::info("Enabling hooks for {}", ID);
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::init", "MenuLayer_init", wrapper::MenuLayer_init, geode::base::get() + 0x3130f0, Thiscall, MenuLayer_initHook)
    CREATE_HOOK_WITH_CHECK_FOR(this->mainClass, "MenuLayer::onMoreGames", "MenuLayer_onMoreGames", wrapper::MenuLayer_onMoreGames, geode::base::get() + 0x314da0, Thiscall, MenuLayer_onMoreGamesHook)
}