#include <Geode/Geode.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <Geode/modify/MenuLayer.hpp>
#include "Serpent.hpp"

namespace py = pybind11;
using namespace geode::prelude;

//

$execute {
	py::initialize_interpreter();
	Serpent::initModule();
	Serpent::_geode::enums();
	Serpent::_geode::bind();
	Serpent::cocos::enums();
	Serpent::cocos::bind();
	Serpent::robtop::bind();

	py::exec(R"(
def MenuLayer_init(this):
	if not this.init():
		return False
	
	info("Hook reached!")

	return True
)");
	Serpent::hook::initAllHooks();
}