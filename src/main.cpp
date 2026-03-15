#if !defined(GEODE_IS_IOS)
#include <Geode/Geode.hpp>
#include <sabe.persistenceapi/include/PersistenceAPI.hpp>

using namespace geode::prelude;
using namespace persistenceAPI;

void setupKeybinds();

$on_mod(Loaded) {
    setupKeybinds();
}

void setupKeybinds() {
    BindManager::get()->registerBindable({
        "save-game"_spr,
        "Save game",
        "Hotkey for quick saving",
        { Keybind::create(KEY_K) },
        "Play",  // category - required in Geode 5.x
    });
}
#endif
