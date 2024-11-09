#include "Serpent.hpp"

using namespace geode::prelude;
using namespace Serpent::ui;

bool ScriptsLayer::setup() {
    scroll = ScrollLayer::create(CCSize(445, 230));
    this->setTitle("Serpent", "bigFont.fnt");

    scroll->setPosition(winSize / 2);
    scroll->m_contentLayer->setLayout(
        ColumnLayout::create()
            ->setAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAutoGrowAxis(250.0f)
            ->setGap(5.0f)
    );

    border = Border::create(scroll, {100, 45, 0, 255}, {445, 230});

    border->setPosition(
        {
            (m_bgSprite->getPositionX() - (m_bgSprite->getContentWidth() * m_bgSprite->getAnchorPoint().x)) + 10,
            m_bgSprite->getPositionY() - 130
        }
    );

    m_mainLayer->addChild(border);

    for (auto& script : Serpent::tempScripts) {
        scroll->m_contentLayer->addChild(ScriptItem::create(script, [&](CCObject* sender) {
            if (static_cast<CCMenuItemToggler*>(sender)->isToggled()) {
                log::info("is toogggled!.");
                Mod::get()->setSavedValue<std::string>("enabled-script", script["id"].as_string());
            }
        }));
    }

    scroll->m_contentLayer->updateLayout();
    scroll->updateLayout();
    scroll->scrollToTop();
    return true;
}

bool ScriptsLayer::init() {
    winSize = CCDirector::get()->getWinSize();
    return Popup::init(winSize.width - 100.0f, 280.0f);
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