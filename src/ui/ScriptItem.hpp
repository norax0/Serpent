#include <Geode/Geode.hpp>

namespace Serpent::ui {
    class ScriptItem : public geode::ModItem {
    private:
        bool init();
    public:
        static ScriptItem* create();
    };
}
