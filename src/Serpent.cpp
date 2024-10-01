#include "Serpent.hpp"

namespace py = pybind11;
using namespace geode::prelude;

void Serpent::_geode::bind(py::module& m) {
    py::class_<Notification>(m, "Notification")
        .def_static("create", static_cast<Notification* (*)(const std::string&, NotificationIcon, float)>(&Notification::create), py::arg("text"), py::arg("icon") = NotificationIcon::None, py::arg("time") = geode::NOTIFICATION_DEFAULT_TIME, py::return_value_policy::reference)
        .def("show", &Notification::show)
        .def("cancel", &Notification::cancel)
        .def("hide", &Notification::hide);
}

void Serpent::_geode::enums(py::module& m) {
    py::enum_<NotificationIcon>(m, "NotificationIcon")
        .value("None", NotificationIcon::None)
        .value("Loading", NotificationIcon::Loading)
        .value("Success", NotificationIcon::Success)
        .value("Warning", NotificationIcon::Warning)
        .value("Error", NotificationIcon::Error)
        .value("Info", NotificationIcon::Info);
}