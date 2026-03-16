#include "CCKeyboardDispatcher.hpp"
#include "Geode/cocos/robtop/keyboard_dispatcher/CCKeyboardDispatcher.h"
#include <hooks/PlayLayer.hpp>
#include <hooks/PauseLayer.hpp>

using namespace geode::prelude;
using namespace persistenceAPI;

// overrides

void PSCCKeyboardDispatcher::removeDelegate(cocos2d::CCKeyboardDelegate* i_delegate) {
    if (s_levelInfoLayerDelegate1 == reinterpret_cast<size_t>(i_delegate)
        || s_levelInfoLayerDelegate2 == reinterpret_cast<size_t>(i_delegate)
        || s_editLevelLayerDelegate1 == reinterpret_cast<size_t>(i_delegate)
        || s_editLevelLayerDelegate2 == reinterpret_cast<size_t>(i_delegate)
    ) {
        return;
    }
    CCKeyboardDispatcher::removeDelegate(i_delegate);
}

bool PSCCKeyboardDispatcher::dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool down, bool isArrowKey) {
    if (down) {
        auto* pl = PlayLayer::get();
        if (pl) {
            auto* ppl = static_cast<PSPlayLayer*>(pl);
            auto keybind = Mod::get()->getSettingValue<keybinds::Keybind>("save-keybind");
            if (keybind.key == key && ppl->canSave() && ppl->startSaveGame()) {
                PSPauseLayer* l_pauseLayer = static_cast<PSPauseLayer*>(CCScene::get()->getChildByID("PauseLayer"));
                if (l_pauseLayer) {
                    if (l_pauseLayer->m_fields->m_saveCheckpointsSprite != nullptr)
                        l_pauseLayer->m_fields->m_saveCheckpointsSprite->setColor({127,127,127});
                    if (l_pauseLayer->m_fields->m_saveCheckpointsSprite != nullptr && l_pauseLayer->m_fields->m_saveCheckpointsSprite->getChildren()->count() > 0)
                        static_cast<CCSprite*>(l_pauseLayer->m_fields->m_saveCheckpointsSprite->getChildren()->objectAtIndex(0))->setColor({127,127,127});
                    if (l_pauseLayer->m_fields->m_saveCheckpointsButton != nullptr)
                        l_pauseLayer->m_fields->m_saveCheckpointsButton->m_bEnabled = false;
                }
                return true;
            }
        }
    }
    return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, isArrowKey);
}
