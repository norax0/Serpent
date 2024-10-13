#include "ScriptsLayer.hpp"
#include "ScriptItem.hpp"

using namespace geode::prelude;
using namespace Serpent::ui;

bool ScriptsLayer::setup() {
    auto scroll = ScrollLayer::create(CCSize(200, 200));
    auto idk = ScriptItem::create(matjson::parse(R"(
{
	"serpent": "1.0.0",
	"name": "Test",
	"id": "testmod_yellowcat98",
	"version": "v1.0.0",
	"developer": "YellowCat98"
}
)"));

    auto idk2 = ScriptItem::create(matjson::parse(R"(
{
	"serpent": "1.0.0",
	"name": "Gyatt!",
	"id": "gyatt_yellowcat98",
	"developer": "YellowCat98"
}
)"));
    scroll->setPosition(winSize / 2);
    scroll->m_contentLayer->setLayout(
        ColumnLayout::create()
            ->setAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAutoGrowAxis(195.0f)
            ->setGap(5.0f)
    );
    
    m_mainLayer->addChild(scroll);
    scroll->m_contentLayer->addChild(idk);
    scroll->m_contentLayer->addChild(idk2);
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