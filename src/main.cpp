#include <Geode/Geode.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <Geode/modify/MenuLayer.hpp>
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

	py::exec(R"(
def MenuLayer_init(this):
	if not this.init():
		return False
	
	sprite = CCSprite.createWithSpriteFrameName("GJ_arrow_01_001.png")
	sprite.setID("sprite-from-python-cool")
	this.addChild(sprite)

	return True

def MenuLayer_onMoreGames(this, sender):
	info("MenuLayer::onMoreGames hook SUCCESS")
)");
	Serpent::hook::initAllHooks();
}