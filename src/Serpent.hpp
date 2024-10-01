#include <pybind11/pybind11.h>

namespace Serpent {
    struct geode {
        static void bind(pybind11::module& m);
        static void enums(pybind11::module& m);
    };

    struct cocos {
        static void bind(pybind11::module& m);
        static void enums(pybind11::module& m);
    };

    struct robtop {
        static void bind(pybind11::module& m);
        static void enums(pybind11::module& m);
    };
}