// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/sysapps/device_capabilities_new/av_codecs_provider_android.h"
#include "media/base/android/media_codec_bridge.h"
#include "base/strings/string_util.h"

#include <set>
#include <string>

namespace xwalk {
namespace sysapps {

const char* const kAudioCodecs[] = {"ALAC", "MP3", "AMRNB", "AMRWB", "AAC", "G711", "VORBIS", "WMA", "FLAC", "OPUS"};
const char* const kVideoCodecs[] = {"H263", "H264", "MPEG4", "AVC", "WMV", "VP8", "Theora"};

static base::LazyInstance<AVCodecsProviderAndroid>::Leaky
    g_storage_info_provider = LAZY_INSTANCE_INITIALIZER;

AVCodecsProviderAndroid::AVCodecsProviderAndroid() {}

AVCodecsProviderAndroid::~AVCodecsProviderAndroid() {}

scoped_ptr<SystemAVCodecs> AVCodecsProviderAndroid::av_codecs() const {
  scoped_ptr<SystemAVCodecs> av_codecs(new SystemAVCodecs);
  std::vector<media::MediaCodecBridge::CodecsInfo> codecs_info;
  media::MediaCodecBridge::GetCodecsInfo(&codecs_info);

  for (size_t i = 0; i < codecs_info.size(); ++i) {
    bool handled = false;
    std::string codec_name = StringToUpperASCII(codecs_info[i].name);
    for (size_t i = 0; i < arraysize(kAudioCodecs); ++i) {
      if (string16::npos != codec_name.find(kAudioCodecs[i])) {
        linked_ptr<AudioCodec> audio_codec(new AudioCodec);
        audio_codec->format = std::string(kAudioCodecs[i]);
        av_codecs->audio_codecs.push_back(audio_codec);
        handled = true;
        break;
      }
    }

    if (handled)
      continue;

    for (size_t i = 0; i < arraysize(kVideoCodecs); ++i) {
      if (string16::npos != codec_name.find(kVideoCodecs[i])) {
        linked_ptr<VideoCodec> video_codec(new VideoCodec);
        video_codec->format = std::string(kVideoCodecs[i]);
        av_codecs->video_codecs.push_back(video_codec);
        handled = true;
        break;
      }
    }
  }

  return av_codecs.Pass();
}

// static
AVCodecsProvider* AVCodecsProvider::GetInstance() {
  return &g_storage_info_provider.Get();
}

}  // namespace sysapps
}  // namespace xwalk
