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



$execute {
    auto base = geode::base::get();
    auto addr = base + 0x3a32d0; // tryPlaceCheckpoint function

    geode::hook::create((void*)addr, +[](long long self) {
        auto original = (void(*)(long long)) geode::hook::getOriginal();

        log::info("[HOOK] tryPlaceCheckpoint BEFORE original");
        original(self);
        log::info("[HOOK] tryPlaceCheckpoint AFTER original");
    });
}
