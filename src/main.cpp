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

	//auto ScriptsDirectoryResult = geode::utils::file::createDirectory(Mod::get()->getConfigDir() / "scripts");
	//if (ScriptsDirectoryResult.isErr()) {
	//	log::error("There was an error creating the scripts directory: {}", ScriptsDirectoryResult.err());
	//}

	//auto scripts = Mod::get()->getConfigDir() / "scripts";

	//for (const auto& scriptPath : std::filesystem::directory_iterator(scripts)) {
	//	auto scriptResult = geode::utils::file::readString(scriptPath.path());
	//	log::info("\nscript generated: {}", scriptResult.value());
	//	py::exec(scriptResult.value());
	//}

	py::exec(R"(
class testmod_yellowcat98:
	def __init__(self):
		self.script = script("testmod_yellowcat98", self)
		self.script.initAllHooks()

	def MenuLayer_init(self, this):
		if not this.init(): return False
		info("Hook!!!!!!!!!!")
		return True

testmod_yellowcat98()
)");

}