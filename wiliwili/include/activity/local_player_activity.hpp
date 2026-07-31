//
// Created for local video playback support
//

#pragma once

#include <borealis/core/activity.hpp>
#include <borealis/core/bind.hpp>

class VideoView;

class LocalPlayerActivity : public brls::Activity {
public:
    CONTENT_FROM_XML_RES("activity/local_player_activity.xml");

    LocalPlayerActivity(const std::string& filePath);

    void onContentAvailable() override;

    ~LocalPlayerActivity() override;

private:
    std::string filePath;

    BRLS_BIND(VideoView, video, "video");
};
