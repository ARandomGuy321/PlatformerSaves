#if defined(PS_DEBUG)
#include "debug.hpp"

#if defined(PS_SEPARATORS)
void writeSeparator(std::string i_string, Stream& o_stream) {
    o_stream.write(i_string.data(),i_string.length());
}

void readSeparator(std::string o_string, Stream& i_stream) {
    i_stream.ignore(o_string.length());
}
#endif
#endif


#include <Geode/Geode.hpp>
using namespace geode::prelude;

static void (*orig_tryPlace)(long long);

void hook_tryPlace(long long self) {
    log::info("[HOOK] BEFORE tryPlaceCheckpoint");

    orig_tryPlace(self);

    log::info("[HOOK] AFTER tryPlaceCheckpoint");
}

$on_mod(Loaded) {
    auto base = geode::base::get();
    auto addr = base + 0x3a32d0;

    orig_tryPlace = reinterpret_cast<void(*)(long long)>(addr);

    Mod::get()->hook(reinterpret_cast<void*>(addr), reinterpret_cast<void*>(&hook_tryPlace));
}
