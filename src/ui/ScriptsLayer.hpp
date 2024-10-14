#pragma once
#include <Geode/Geode.hpp>
#include "Serpent.hpp"

namespace Serpent::ui {
    class ScriptsLayer : public geode::Popup<> {
    public:
        static ScriptsLayer* create();
    private:
        bool setup() override;
        bool init();
        geode::ScrollLayer* scroll;
        geode::Border* border;
        geode::MDTextArea* scriptView;
        cocos2d::CCSize winSize;
    };
}
