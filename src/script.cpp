#include "Serpent.hpp"
#include <Geode/Geode.hpp>
#include <matjson.hpp>
#include "wrapper.hpp"

using namespace Serpent;
using namespace geode::prelude;
namespace py = pybind11;

script* wrapper::instance = nullptr;
std::vector<std::string> wrapper::enabledHooks = {};

std::vector<ui::ScriptItem*> Serpent::scripts;
std::vector<matjson::Value> Serpent::tempScripts;

script::script(const std::string& scriptID, pybind11::object obj) : ID(scriptID), mainClass(obj) {
	wrapper::setParent(this);
	if (loadMetadata(getScriptJson())) {
		log::info("Loaded metadata for script {}!", ID);
	} else {
		log::error("Failed to load metadata for script {}.", ID);
	}
}

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
    auto json = matjson::parse(str).unwrap();
    if (CheckMetadata(json)) {
        name = json["name"].asString().unwrap();
        developer = json["developer"].asString().unwrap();
        serpentVer = json["serpent"].asString().unwrap();
        return true;
    } else {
        return false;
    }
}

std::string script::getScriptJson() {
    auto path = Mod::get()->getConfigDir() / "unzipped" / ID / "script.json";
    auto res = geode::utils::file::readString(path);
    return res.unwrap();
}