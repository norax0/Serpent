#include <Geode/Geode.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <Geode/modify/MenuLayer.hpp>
#include "Serpent.hpp"

namespace py = pybind11;

$execute {
	py::initialize_interpreter();
	Serpent::initModule();
	Serpent::_geode::enums();
	Serpent::_geode::bind();
}

class $modify(MenuLayer) {
	void onMoreGames(CCObject*) {

		py::exec(R"(
notif = Notification.create("Hello!!!")
notif.show()
)");
	}
};