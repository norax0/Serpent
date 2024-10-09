#include <Geode/Geode.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CCSprite.hpp>
#include "Serpent.hpp"

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
	}

	auto scripts = Mod::get()->getConfigDir() / "scripts";

	for (const auto& scriptPath : std::filesystem::directory_iterator(scripts)) {
		auto scriptResult = geode::utils::file::readString(scriptPath.path());
		py::exec(scriptResult.value());
	}
/*
	py::exec(R"(
script = script("testmod_yellowcat98")

def callback(sender):
	info(script.ID)

def testmod_yellowcat98_MenuLayer_init(this):
	if not this.init(): return False
	director = CCDirector.get()
	winSize = director.getWinSize()
	info("hello")
	menu = this.getChildByID("bottom-menu")

	button = CCMenuItemExt.createSpriteExtra(CCSprite.createWithSpriteFrameName("GJ_arrow_01_001.png"), callback)

	if not button:
		error("button is false")
	else:
		info("button is true")
		menu.addChild(button)
	return True

def testmod_yellowcat98_MenuLayer_onMoreGames(this):
	info("hi")

script.initAllHooks()
script.initAllHooks()
)");
*/
}