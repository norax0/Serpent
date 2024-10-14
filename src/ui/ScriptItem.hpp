#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/ui/General.hpp>
#include "Serpent.hpp"

namespace Serpent::ui {
    class ScriptItem : public cocos2d::CCNode {
    private:
        cocos2d::extension::CCScale9Sprite* bg;
        cocos2d::CCNode* title;
        cocos2d::CCNode* mainContainer;
        cocos2d::CCLabelBMFont* titleLabel;
        cocos2d::CCMenu* devContainer;
        cocos2d::CCLabelBMFont* dev;
        cocos2d::CCMenu* viewMenu;
        bool init(matjson::Value json, std::function<void(cocos2d::CCObject*)> onButton);
    public:
        static ScriptItem* create(matjson::Value, std::function<void(cocos2d::CCObject*)> onButton);
    };
}
