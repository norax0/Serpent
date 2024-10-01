#include <Geode/Geode.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;

$execute {
	py::initialize_interpreter();
}