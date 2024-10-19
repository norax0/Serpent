#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <Geode/modify/MenuLayer.hpp>
#include "Serpent.hpp"
#include "ui/ScriptsLayer.hpp"
#include "ui/ScriptItem.hpp"

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

					log::info("Now setting up Visual scripts (so you can view them in the script view)");
					auto scriptjson = matjson::parse(geode::utils::file::readString(scriptDir / "script.json").value());
					auto scriptString = geode::utils::file::readString(scriptDir / std::filesystem::path(script.path().filename().stem().string() + ".py")).value();
					Serpent::scripts.push_back(new Serpent::visualScripts(scriptjson["name"].as_string(), scriptjson["developer"].as_string(), scriptString, scriptjson["id"].as_string()));

					log::info("Now Executing {}...", script.path().filename().stem());
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

$execute {
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
/*
	py::exec(R"(
class testmod_yellowcat98:
	def __init__(self):
		self.script = script("testmod_yellowcat98", self)
		self.script.initAllHooks()

	def MenuLayer_init(self, this):
		if not this.init(): return False
		info("Hook!!!!!!!!!!")
		return True

if __name__ == "__main__":
	testmod_yellowcat98()
)");*/

}

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