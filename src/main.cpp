#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include "Serpent.hpp"


namespace py = pybind11;
using namespace geode::prelude;
using namespace Serpent;

void unzipAndExecute(std::filesystem::path scripts) {
	auto unzippedDirRes = geode::utils::file::createDirectory(Mod::get()->getConfigDir() / "unzipped");
	if (unzippedDirRes.isErr()) {
		log::error("There was an error creating the `unzipped` directory: {}", unzippedDirRes.err());
		return;
	}

	auto unzipped = Mod::get()->getConfigDir() / "unzipped";

	for (const auto& script : std::filesystem::directory_iterator(scripts)) {
		if (script.is_directory()) {
			log::info("{} is a folder. will be ignored.", script.path().filename().stem().string());
			continue;
		}
		if (script.path().extension() == ".zip") {
			auto scriptDir = unzipped / script.path().filename().stem();
			log::info("Unzipping {}...", script.path().filename().stem());
			auto zip = geode::utils::file::Unzip::create(script.path());
			if (zip) {
				auto ok = zip->extractAllTo(scriptDir);
				if (ok) {
					log::info("Unzipped {}!", script.path().filename().stem());
					auto scriptjson = matjson::parse(geode::utils::file::readString(scriptDir / "script.json").value());

					Serpent::tempScripts.push_back(scriptjson);

					log::info("Executing {}...", script.path().filename().stem());
					try {
						py::exec(py::str(geode::utils::file::readString(scriptDir / std::filesystem::path(script.path().filename().stem().string() + ".py")).value()));
					} catch (py::error_already_set& e) {
						log::error("{}", e.what());
					}
					
				}
			}
		} else {
			log::warn("a file that doesn't have a .zip extension was found in {}", scripts.string());
		}
	}
}

$on_mod(Loaded) {
	py::initialize_interpreter();
	Serpent::initModule();
	bindings::_geode::enums();
	bindings::_geode::bind();
	bindings::cocos::enums();
	bindings::cocos::bind();
	bindings::robtop::bind();
	bindings::serpent::bind();

	auto ScriptsDirectoryResult = geode::utils::file::createDirectory(Mod::get()->getConfigDir() / "scripts");
	if (ScriptsDirectoryResult.isErr()) {
		log::error("There was an error creating the scripts directory: {}", ScriptsDirectoryResult.err());
		return;
	}

	auto scripts = Mod::get()->getConfigDir() / "scripts";

	unzipAndExecute(scripts);
}

class $modify(LoadingLayer) {
struct Fields {
	int currentScript = -1;
};
	void loadAssets() {
		LoadingLayer::loadAssets();
		m_fields->currentScript += 1;
		int maxSize = Serpent::tempScripts.size();
		auto label = static_cast<CCLabelBMFont*>(this->getChildByID("geode-small-label"));
		label->setString("Serpent: Creating UI");
		if (m_fields->currentScript < maxSize) {
			log::info("{}", Serpent::tempScripts[m_fields->currentScript].dump());
			// for whatever reason creating a ScriptItem using Serpent::tempScripts[m_fields->currentScript] doesnt work, epic!!
			std::string json = fmt::format(R"(
{{
    "serpent": "{}",
    "name": "{}",
    "id": "{}",
    "developer": "{}"
}}
)", Serpent::tempScripts[m_fields->currentScript]["serpent"].as_string(), Serpent::tempScripts[m_fields->currentScript]["name"].as_string(), Serpent::tempScripts[m_fields->currentScript]["id"].as_string(), Serpent::tempScripts[m_fields->currentScript]["developer"].as_string());
			Serpent::scripts.push_back(Serpent::ui::ScriptItem::create(matjson::parse(json), [=](CCObject*) {
				log::info("clicked!!");
			}));
		} else {
			label->setString("Loading game resources");
		}
	}
};

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(CCMenuItemExt::createSpriteExtra(geode::CircleButtonSprite::createWithSprite("PyBtn.png"_spr, 1.0f, CircleBaseColor::Green, CircleBaseSize::MediumAlt), [=](CCObject* sender) {
			ui::ScriptsLayer::create()->show();
		}));
		if (!Loader::get()->isModLoaded("alphalaneous.pages_api") || !Loader::get()->isModLoaded("alphalaneous.vanilla_pages")) {
			menu->updateLayout();
		}
		return true;
	}
};