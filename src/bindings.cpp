#include "Serpent.hpp"

namespace py = pybind11;
using namespace geode::prelude;

py::module Serpent::m;

void Serpent::initModule() {
	Serpent::m = py::module::import("__main__");
}

// geode

void Serpent::bindings::_geode::bind() {
	py::class_<Notification>(m, "Notification")
		.def_static("create", static_cast<Notification* (*)(const std::string&, NotificationIcon, float)>(&Notification::create), py::arg("text"), py::arg("icon") = NotificationIcon::None, py::arg("time") = geode::NOTIFICATION_DEFAULT_TIME, py::return_value_policy::reference)
		.def("show", &Notification::show)
		.def("cancel", &Notification::cancel)
		.def("hide", &Notification::hide);
	
	m.def("info", [=](const std::string& str) {
		log::info("{}", str);
	});

	m.def("debug", [=](const std::string& str) {
		log::debug("{}", str);
	});

	m.def("warn", [=](const std::string& str) {
		geode::log::warn("{}", str);
	});

	m.def("error", [=](const std::string& str) {
		geode::log::error("{}", str);
	});
}

void Serpent::bindings::_geode::enums() {
	py::enum_<NotificationIcon>(m, "NotificationIcon")
		.value("None", NotificationIcon::None)
		.value("Loading", NotificationIcon::Loading)
		.value("Success", NotificationIcon::Success)
		.value("Warning", NotificationIcon::Warning)
		.value("Error", NotificationIcon::Error)
		.value("Info", NotificationIcon::Info);
}

// cocos

void Serpent::bindings::cocos::bind() {
	py::class_<CCObject>(m, "CCObject")
		.def("release", &CCObject::release)
		.def("retain", &CCObject::retain)
		.def("copy", &CCObject::copy, py::return_value_policy::reference)
		.def("autorelease", &CCObject::autorelease, py::return_value_policy::reference)
		.def("getTag", &CCObject::getTag)
		.def("setTag", &CCObject::setTag, py::arg("nTag"))
		.def("setObjType", &CCObject::setObjType, py::arg("type"))
		.def("isEqual", &CCObject::isEqual, py::arg("pObject"));
	
	py::class_<CCPoint>(m, "CCPoint")
		.def(py::init<float, float>())
		.def_readwrite("x", &CCPoint::x)
		.def_readwrite("y", &CCPoint::y);
	
	py::class_<CCSize>(m, "CCSize")
		.def(py::init<float, float>())
		.def_readwrite("height", &CCSize::height)
		.def_readwrite("width", &CCSize::width);
	
	py::class_<CCRect>(m, "CCRect")
		.def_readwrite("origin", &CCRect::origin)
		.def_readwrite("size", &CCRect::size)
		.def("intersectsRect", py::overload_cast<CCRect const&>(&CCRect::intersectsRect, py::const_));
	
	py::class_<ccColor3B>(m, "ccColor3B")
		.def(py::init<>())
		.def_readwrite("r", &ccColor3B::r)
		.def_readwrite("g", &ccColor3B::g)
		.def_readwrite("g", &ccColor3B::b);

	py::class_<CCDirector>(m, "CCDirector")
		.def_static("get", py::overload_cast<>(&CCDirector::get), py::return_value_policy::reference)
		.def("getWinSize", py::overload_cast<>(&CCDirector::getWinSize));
	
	py::class_<CCNode, CCObject>(m, "CCNode")
		.def_static("create", &CCNode::create, py::return_value_policy::reference)
		.def("init", &CCNode::init)
		.def("description", &CCNode::description)
		.def("setZOrder", &CCNode::setZOrder, py::arg("zOrder"))
		.def("getZOrder", &CCNode::getZOrder)
		.def("setVertexZ", &CCNode::setVertexZ, py::arg("vertexZ"))
		.def("getVertexZ", &CCNode::getVertexZ)
		.def("setScaleX", &CCNode::setScaleX)
		.def("getScaleY", &CCNode::getScaleY)
		.def("setScale", py::overload_cast<float, float>(&CCNode::setScale), py::arg("scaleX"), py::arg("scaleY"))
		.def("setPosition", py::overload_cast<CCPoint const&>(&CCNode::setPosition), py::arg("position"))
		.def("getPosition", py::overload_cast<>(&CCNode::getPosition))
		.def("setPositionX", py::overload_cast<float>(&CCNode::setPositionX), py::arg("x"))
		.def("getPositionX", py::overload_cast<>(&CCNode::getPositionX))
		.def("setPositionY", py::overload_cast<float>(&CCNode::setPositionY), py::arg("y"))
		.def("getPositionY", py::overload_cast<>(&CCNode::getPositionY))
		.def("setSkewX", py::overload_cast<float>(&CCNode::setSkewX), py::arg("fSkewX"))
		.def("getSkewX", py::overload_cast<>(&CCNode::getSkewX))
		.def("setSkewY", py::overload_cast<float>(&CCNode::setSkewY), py::arg("fSkewY"))
		.def("getSkewY", py::overload_cast<>(&CCNode::getSkewY))
		.def("setAnchorPoint", py::overload_cast<CCPoint const&>(&CCNode::setAnchorPoint), py::arg("anchorPoint"))
		.def("getAnchorPoint", py::overload_cast<>(&CCNode::getAnchorPoint))
		.def("getAnchorPointInPoint", py::overload_cast<>(&CCNode::getAnchorPointInPoints))
		.def("setContentSize", py::overload_cast<const CCSize&>(&CCNode::setContentSize), py::arg("contentSize"))
		.def("getContentSize", py::overload_cast<>(&CCNode::getContentSize, py::const_), py::return_value_policy::reference)
		.def("getScaledContentSize", py::overload_cast<>(&CCNode::getScaledContentSize))
		.def("setVisible", py::overload_cast<bool>(&CCNode::setVisible))
		.def("isVisible", py::overload_cast<>(&CCNode::isVisible))
		.def("setRotation", py::overload_cast<float>(&CCNode::setRotation), py::arg("fRotation"))
		.def("getRotation", py::overload_cast<>(&CCNode::getRotation))
		.def("setRotationX", py::overload_cast<float>(&CCNode::setRotationX), py::arg("fRotaionX")) // the arg name was misspelt in the docs, i wanted to use the same arg names as the ones in the docs so uhh have fun with rotaion
		.def("getRotationX", py::overload_cast<>(&CCNode::getRotationX))
		.def("setRotationY", py::overload_cast<float>(&CCNode::setRotationY), py::arg("fRotationY"))
		.def("getRotationY", py::overload_cast<>(&CCNode::getRotationY))
		.def("addChild", py::overload_cast<CCNode*>(&CCNode::addChild), py::arg("child"))
		.def("addChild", py::overload_cast<CCNode*, int>(&CCNode::addChild), py::arg("child"), py::arg("zOrder"))
		.def("addChild", py::overload_cast<CCNode*, int, int>(&CCNode::addChild), py::arg("child"), py::arg("zOrder"), py::arg("tag"))
		.def("getChildByTag", py::overload_cast<int>(&CCNode::getChildByTag), py::arg("tag"), py::return_value_policy::reference)
		.def("getParent", py::overload_cast<>(&CCNode::getParent))
		.def("removeFromParent", py::overload_cast<>(&CCNode::removeFromParent))
		.def("removeFromParentAndCleanup", py::overload_cast<bool>(&CCNode::removeFromParentAndCleanup), py::arg("cleanup"))
		.def("removeChild", py::overload_cast<CCNode*, bool>(&CCNode::removeChild), py::arg("child"), py::arg("cleanup"))
		.def("removeChildByTag", py::overload_cast<int, bool>(&CCNode::removeChildByTag), py::arg("tag"), py::arg("cleanup"))
		.def("removeAllChildren", py::overload_cast<>(&CCNode::removeAllChildren))
		.def("removeAllChildrenAndCleanup", py::overload_cast<bool>(&CCNode::removeAllChildrenWithCleanup), py::arg("cleanup")) // binded as 2 separate functions (wanted to bind removeAllChildrenWithCleanup only, but didnt want to cause confusion)
		.def("getID", py::overload_cast<>(&CCNode::getID))
		.def("setID", py::overload_cast<std::string const&>(&CCNode::setID), py::arg("id"))
		.def("getChildByID", py::overload_cast<std::string const&>(&CCNode::getChildByID), py::arg("id"), py::return_value_policy::reference)
		.def("getChildByIDRecursive", py::overload_cast<std::string const&>(&CCNode::getChildByIDRecursive), py::arg("id"), py::return_value_policy::reference)
		.def("removeChildByID", py::overload_cast<std::string const&>(&CCNode::removeChildByID), py::arg("id"));
	
	py::class_<CCRGBAProtocol>(m, "CCRGBAProtocol")
		.def("setColor", py::overload_cast<ccColor3B const&>(&CCRGBAProtocol::setColor), py::arg("color"))
		.def("getColor", py::overload_cast<>(&CCRGBAProtocol::getColor))
		.def("getDisplayedColor", py::overload_cast<>(&CCRGBAProtocol::getDisplayedColor))
		.def("setOpacity", py::overload_cast<GLubyte>(&CCRGBAProtocol::setOpacity), py::arg("opacity"))
		.def("getOpacity", py::overload_cast<>(&CCRGBAProtocol::getOpacity));
	
	py::class_<CCLayer, CCNode>(m, "CCLayer")
		.def_static("create", py::overload_cast<>(&CCLayer::create), py::return_value_policy::reference);
	
	py::class_<CCLayerRGBA, CCLayer, CCRGBAProtocol>(m, "CCLayerRGBA")
		.def_static("create", py::overload_cast<>(&CCLayerRGBA::create), py::return_value_policy::reference);

	py::class_<CCNodeRGBA, CCNode, CCRGBAProtocol>(m, "CCNodeRGBA")
		.def_static("create", py::overload_cast<>(&CCNodeRGBA::create), py::return_value_policy::reference);
	
	py::class_<CCTexture2D, CCObject>(m, "CCTexture2D")
		.def(py::init<>());
	
	py::class_<CCTextureProtocol>(m, "CCTextureProtocol")
		.def("getTexture", &CCTextureProtocol::getTexture)
		.def("setTexture", &CCTextureProtocol::setTexture);
	
	py::class_<CCSprite, CCNodeRGBA, CCTextureProtocol>(m, "CCSprite")
		.def_static("create", py::overload_cast<const char*>(&CCSprite::create), py::arg("pszFileName"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<>(&CCSprite::create), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<const char*, CCRect const&>(&CCSprite::create), py::arg("pszFileName"), py::arg("rect"), py::return_value_policy::reference)
		.def_static("createWithSpriteFrameName", py::overload_cast<const char*>(&CCSprite::createWithSpriteFrameName), py::arg("pszSpriteFrameName"), py::return_value_policy::reference);
	
	py::class_<CCSpriteBatchNode, CCNode, CCTextureProtocol>(m, "CCSpriteBatchNode")
		.def_static("create", py::overload_cast<char const*>(&CCSpriteBatchNode::create), py::arg("fileImage"), py::return_value_policy::reference);
	
	py::class_<CCLabelProtocol>(m, "CCLabelProtocol")
		.def("setString", py::overload_cast<char const*>(&CCLabelProtocol::setString), py::arg("label"))
		.def("getString", py::overload_cast<>(&CCLabelProtocol::getString));

	py::class_<CCLabelBMFont, CCSpriteBatchNode, CCLabelProtocol, CCRGBAProtocol>(m, "CCLabelBMFont")
		.def_static("create", py::overload_cast<char const*, char const*>(&CCLabelBMFont::create), py::arg("str"), py::arg("fntFile"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<>(&CCLabelBMFont::create), py::return_value_policy::reference);
	
	py::class_<CCMenu, CCLayerRGBA>(m, "CCMenu")
		.def_static("create", py::overload_cast<>(&CCMenu::create));
	
	py::class_<CCMenuItem, CCNodeRGBA>(m, "CCMenuItem")
		.def_static("create", py::overload_cast<>(&CCMenuItem::create))
		.def_static("create", py::overload_cast<CCObject*, SEL_MenuHandler>(&CCMenuItem::create), py::arg("rec"), py::arg("selector"));
	
	py::class_<CCMenuItemSprite, CCMenuItem>(m, "CCMenuItemSprite")
		.def_static("create", py::overload_cast<CCNode*, CCNode*, CCNode*>(&CCMenuItemSprite::create), py::arg("normalSprite"), py::arg("selectedSprite"), py::arg("disabledSprite"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<CCNode*, CCNode*, CCNode*, CCObject*, SEL_MenuHandler>(&CCMenuItemSprite::create), py::arg("normalSprite"), py::arg("selectedSprite"), py::arg("disabledSprite"), py::arg("target"), py::arg("selector"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<CCNode*, CCNode*, CCObject*, SEL_MenuHandler>(&CCMenuItemSprite::create), py::arg("normalSprite"), py::arg("selectedSprite"), py::arg("target"), py::arg("selector")), py::return_value_policy::reference;
	
	py::class_<CCMenuItemSpriteExtra, CCMenuItemSprite>(m, "CCMenuItemSpriteExtra")
		.def_static("create", py::overload_cast<CCNode*, CCNode*, CCObject*, SEL_MenuHandler>(&CCMenuItemSpriteExtra::create), py::arg("sprite"), py::arg("disabledSprite"), py::arg("target"), py::arg("callback"), py::return_value_policy::reference)
		.def_static("create", py::overload_cast<CCNode*, CCObject*, SEL_MenuHandler>(&CCMenuItemSpriteExtra::create), py::arg("sprite"), py::arg("target"), py::arg("callback"));
	
	py::class_<CCMenuItemExt>(m, "CCMenuItemExt")
		.def_static("createSpriteExtra", [](CCNode* sprite, std::function<void(CCMenuItemSpriteExtra* sender)>&& callback) {
			return CCMenuItemExt::createSpriteExtra(sprite, callback);
		}, py::return_value_policy::reference);
}


void Serpent::bindings::cocos::enums() {
	py::enum_<CCObjectType>(m, "CCObjectType") // i actualy dont know why this exists but ill just bind it for the 2 people that want it!
		.value("PlayLayer", CCObjectType::PlayLayer)
		.value("LevelEditorLayer", CCObjectType::LevelEditorLayer)
		.value("GameObject", CCObjectType::GameObject)
		.value("MenuLayer", CCObjectType::MenuLayer);
}

void Serpent::bindings::robtop::bind() {
	py::class_<GooglePlayDelegate>(m, "GooglePlayDelegate")	
		.def("googlePlaySignedIn", py::overload_cast<>(&GooglePlayDelegate::googlePlaySignedIn));

	py::class_<MenuLayer, CCLayer, GooglePlayDelegate>(m, "MenuLayer")
		.def_static("scene", py::overload_cast<bool>(&MenuLayer::scene))
		.def("init", py::overload_cast<>(&MenuLayer::init));
}