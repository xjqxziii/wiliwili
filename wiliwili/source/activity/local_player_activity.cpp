//
// Created for local video playback support
//

#include <filesystem>

#include <borealis/core/application.hpp>
#include <borealis/views/applet_frame.hpp>

#include "activity/local_player_activity.hpp"
#include "view/video_view.hpp"
#include "view/mpv_core.hpp"
#include "view/button_close.hpp"

using namespace brls::literals;

LocalPlayerActivity::LocalPlayerActivity(const std::string& filePath) : filePath(filePath) {
    brls::Logger::debug("create LocalPlayerActivity: {}", filePath);
}

void LocalPlayerActivity::onContentAvailable() {
    // Set the video title to the filename
    std::filesystem::path path(filePath);
    std::string filename = path.filename().string();
    this->video->setTitle(filename);

    // Hide Bilibili-specific OSD features
    this->video->hideDanmakuButton();
    this->video->hideDLNAButton();
    this->video->hideVideoQualityButton();
    this->video->hideHistorySetting();
    this->video->hideVideoRelatedSetting();
    this->video->hideSubtitleSetting();
    this->video->hideSkipOpeningCreditsSetting();
    this->video->hideHighlightLineSetting();
    this->video->hideOSDLockButton();

    // Disable close-on-EOF so the player stays open after video ends
    this->video->disableCloseOnEndOfFile();

    // Load the local file into mpv
    // For local files, we don't need referrer/network-timeout options
    MPVCore::instance().setUrl(filePath);

    // Register keyboard shortcuts
    this->video->registerCommonActions(this);

    // Register back button to close this activity
    this->registerAction(
        "cancel", brls::ControllerButton::BUTTON_B,
        [this](brls::View* view) -> bool {
            // Stop playback and close
            MPVCore::instance().stop();
            brls::Application::popActivity(brls::TransitionAnimation::NONE);
            return true;
        },
        true);

    brls::Logger::info("LocalPlayerActivity: playing {}", filePath);
}

LocalPlayerActivity::~LocalPlayerActivity() {
    brls::Logger::debug("del LocalPlayerActivity");
    MPVCore::instance().stop();
}
