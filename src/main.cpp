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

	auto unzippedDirRes = geode::utils::file::createDirectory(Mod::get()->getConfigDir() / "unzipped");
	if (unzippedDirRes.isErr()) {
		log::error("There was an error creating the `unzipped` directory: {}", unzippedDirRes.err());
		return;
	}

	auto unzipped = Mod::get()->getConfigDir() / "unzipped";

	for (const auto& script : std::filesystem::directory_iterator(scripts)) {
		if (script.path().extension() == ".zip") {
			auto scriptDir = unzipped / script.path().filename().stem();
			log::info("Unzipping {}", script.path().filename().stem());
			auto zip = geode::utils::file::Unzip::create(script.path());
			if (zip) {
				auto ok = zip->extractAllTo(scriptDir);
				if (ok) {
					log::info("Unzipped {}", script.path().filename().stem());
				}
			}
		} else {
			log::warn("a file that doesn't have a .zip extension was found in {}", scripts.string());
		}
	}
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
		this->getChildByID("bottom-menu")->addChild(CCMenuItemExt::createSpriteExtra(geode::CircleButtonSprite::createWithSprite("PyBtn.png"_spr, 1.0f, CircleBaseColor::Green, CircleBaseSize::MediumAlt), [=](CCObject* sender) {
			ui::ScriptsLayer::create()->show();
		}));
		return true;
	}
};