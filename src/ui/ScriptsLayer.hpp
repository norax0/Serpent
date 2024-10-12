#include <Geode/Geode.hpp>


namespace Serpent::ui {
    class ScriptsLayer : public geode::Popup<> {
    public:
        static ScriptsLayer* create();
    private:
        bool setup() override;
        bool init();
        cocos2d::CCSize winSize;
    };
}
