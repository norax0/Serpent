#include "ScriptsLayer.hpp"

using namespace geode::prelude;
using namespace Serpent::ui;

bool ScriptsLayer::setup() {
    auto scroll = ScrollLayer::create(CCSize(100, 200));
    auto idk = MapPackCell::create();
    scroll->setPosition(winSize / 2);
    scroll->m_contentLayer->setLayout(
        ColumnLayout::create()
            ->setAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAutoGrowAxis(195.0f)
            ->setGap(0.0f)
    );
    
    m_mainLayer->addChild(scroll);
    scroll->m_contentLayer->addChild(idk);
    scroll->m_contentLayer->updateLayout();
    return true;
}

bool ScriptsLayer::init() {
    winSize = CCDirector::get()->getWinSize();
    return Popup::init(winSize.width - 100, 280.0f);
}

ScriptsLayer* ScriptsLayer::create() {
    auto ret = new ScriptsLayer();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}