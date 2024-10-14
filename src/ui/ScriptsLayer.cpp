#include "ScriptsLayer.hpp"
#include "ScriptItem.hpp"

using namespace geode::prelude;
using namespace Serpent::ui;

bool ScriptsLayer::setup() {
    scroll = ScrollLayer::create(CCSize(200, 250));

    scroll->setPosition(winSize / 2);
    scroll->m_contentLayer->setLayout(
        ColumnLayout::create()
            ->setAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAutoGrowAxis(250.0f)
            ->setGap(5.0f)
    );

    border = Border::create(scroll, {100, 45, 0, 255}, {200, 250});

    border->setPosition(
        {
            (m_bgSprite->getPositionX() - (m_bgSprite->getContentWidth() * m_bgSprite->getAnchorPoint().x)) + 10,
            m_bgSprite->getPositionY() - 130
        }
    );

    m_mainLayer->addChild(border);

    scriptView = MDTextArea::create("```print('hello world')```", {m_bgSprite->getContentWidth() - border->getContentWidth() - 20, 250});

    scriptView->setPosition(
        {
            border->getPositionX() + 325,
            border->getPositionY() + 125
        }
    );
    m_mainLayer->addChild(scriptView);


    for (int i = 0; i < 20; i++) {
        auto node = ScriptItem::create(matjson::parse(fmt::format(R"(
{{
	"serpent": "1.0.0",
	"name": "{}",
	"id": "gyatt_yellowcat98",
	"developer": "YellowCat98"
}}
)", i)), [=](CCObject* sender) {
    scriptView->setString(fmt::format("Script number {}", i).c_str());
});
        scroll->m_contentLayer->addChild(node);
        
    }

    scroll->m_contentLayer->updateLayout();
    scroll->updateLayout();
    scroll->scrollToTop();
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