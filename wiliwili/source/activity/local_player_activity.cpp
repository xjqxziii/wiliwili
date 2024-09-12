//
// Created by Anonymous on 2024/4/2.
//

#include "activity/local_player_activity.hpp"

#include "view/video_view.hpp"

LocalPlayerActivity::~LocalPlayerActivity() {
    brls::Logger::debug("LocalPlayerActivity: delete");
    this->video->stop();
}

void LocalPlayerActivity::onContentAvailable() {
    this->video->hideOnlineCount();
    this->video->hideDanmakuButton();
    this->video->hideVideoQualityButton();
    this->video->hideSkipOpeningCreditsSetting();
    this->video->hideHighlightLineSetting();
    this->video->hideHistorySetting();
    this->video->hideVideoRelatedSetting();
    this->video->hideDLNAButton();

    this->video->setUrl(this->filepath);
    this->video->setTitle(this->filepath.filename().string());
    MPV_E->fire(MpvEventEnum::RESET);
}
