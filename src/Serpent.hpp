#include <pybind11/pybind11.h>

namespace Serpent {

	extern pybind11::module m;

	void initModule();
	struct _geode { // prefixed with _ so compiler/YOU doesnt/dont get confused between Serpent::geode and geode ns
		static void bind();
		static void enums();
	};

	struct cocos {
		static void bind();
		static void enums();
	};

	struct robtop {
		static void bind();
		static void enums();
	};
}