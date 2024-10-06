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
def callback(sender):
	info("HI!!!!")

def MenuLayer_init(this):
	if not this.init(): return False
	director = CCDirector.get()
	winSize = director.getWinSize()
	info("hello")
	menu = this.getChildByID("profile-menu")

	button = CCMenuItemExt.createSpriteExtra(CCSprite.createWithSpriteFrameName("GJ_arrow_01_001.png"), callback)

	if not button:
		error("button is false")
	else:
		info("button is true")
		menu.addChild(button)
	return True
)");
	Serpent::hook::initAllHooks();
}