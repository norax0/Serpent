#include <Geode/Geode.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <Geode/modify/MenuLayer.hpp>

namespace py = pybind11;

$execute {
	py::initialize_interpreter();
}

class $modify(MenuLayer) {
	void onMoreGames(CCObject*) {

		py::module::import("__main__").def("info", [=](const std::string& str) {
			geode::log::info("{}", str);
		});

		py::exec(R"(
info("hi")
)");
	}
};