#include "ScriptItem.hpp"
#include <Geode/Geode.hpp>

using namespace Serpent::ui;
using namespace geode::prelude;

bool ScriptItem::init(matjson::Value json) {
    if (!CCNode::init()) return false;
    this->setID(fmt::format("script-item/{}", json["id"].as_string()));
    

    auto bg = CCScale9Sprite::create("square02b_small.png");
    bg->setID("background");
    bg->setOpacity(55);
    bg->ignoreAnchorPointForPosition(false);
    bg->setAnchorPoint({0.5f, 0.5f});
    bg->setScale(0.7f);
    this->setContentSize({200, 30});
    bg->setContentSize((m_obContentSize - ccp(6, 0)) / bg->getScale());
    bg->setPosition(m_obContentSize / 2);

    mainContainer = CCNode::create();
    mainContainer->setScale(0.4f);
    mainContainer->setAnchorPoint({0.0f, 0.5f});
    mainContainer->setLayout(
        ColumnLayout::create()
            ->setAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::Even)
            ->setCrossAxisLineAlignment(AxisAlignment::Start)
            ->setGap(0)
    );
    mainContainer->getLayout()->ignoreInvisibleChildren(true);

    mainContainer->setPosition(m_obContentSize.height + 10, m_obContentSize.height / 2);
    mainContainer->setContentSize(ccp(m_obContentSize.width / 2 - m_obContentSize.height, m_obContentSize.height - 5) / mainContainer->getScale());

    title = CCNode::create();
    title->setAnchorPoint({0.5f, 0.5f});
    title->setLayout(
        RowLayout::create()
            ->setDefaultScaleLimits(0.1f, 1.0f)
            ->setAxisAlignment(AxisAlignment::Start)
    );

    mainContainer->addChild(title);

    titleLabel = CCLabelBMFont::create(json["name"].as_string().c_str(), "bigFont.fnt");
    titleLabel->setLayoutOptions(AxisLayoutOptions::create()->setScalePriority(1));

    dev = CCLabelBMFont::create(json["developer"].as_string().c_str(), "goldFont.fnt");
    dev->setLayoutOptions(AxisLayoutOptions::create()->setScaleLimits(std::nullopt, 0.7f));
    title->addChild(dev);

    title->addChild(titleLabel);
    this->addChild(bg);
    this->addChild(mainContainer);
    mainContainer->updateLayout();
    title->updateLayout();
    dev->updateLayout();
    this->updateLayout();
    return true;
}

ScriptItem* ScriptItem::create(matjson::Value json) {
    auto ret = new ScriptItem();
    if (ret->init(json)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}