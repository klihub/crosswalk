// Copyright (c 2013 Intel Corporation. All rights reserved.
// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/sysapps/device_capabilities_new/av_codecs_provider_linux.h"

extern "C" {
#include <libavcodec/avcodec.h>
}  // extern "C"

#include <set>
#include <string>

#include "base/path_service.h"
#include "content/public/common/content_paths.h"
#include "media/base/media.h"
#include "media/ffmpeg/ffmpeg_common.h"
#include "media/filters/ffmpeg_glue.h"

namespace xwalk {
namespace sysapps {

static base::LazyInstance<AVCodecsProviderLinux>::Leaky
    g_storage_info_provider = LAZY_INSTANCE_INITIALIZER;

AVCodecsProviderLinux::AVCodecsProviderLinux() {
  base::FilePath media_path;
  PathService::Get(content::DIR_MEDIA_LIBS, &media_path);
  media::InitializeMediaLibrary(media_path);
  media::FFmpegGlue::InitializeFFmpeg();
}

AVCodecsProviderLinux::~AVCodecsProviderLinux() {}

scoped_ptr<SystemAVCodecs> AVCodecsProviderLinux::av_codecs() const {
  scoped_ptr<SystemAVCodecs> av_codecs(new SystemAVCodecs);

  // Get a list of supported codecs.
  AVCodec* codec = NULL;
  while ((codec = av_codec_next(codec))) {
    if (codec->type == AVMEDIA_TYPE_AUDIO) {
      // Ensure the codec is supported by converting an FFmpeg audio codec ID
      // into its corresponding supported codec id.
      if (media::CodecIDToAudioCodec(codec->id)) {
        linked_ptr<AudioCodec> audio_codec(new AudioCodec);
        audio_codec->format = std::string(codec->name);
        av_codecs->audio_codecs.push_back(audio_codec);
      }
    } else if (codec->type == AVMEDIA_TYPE_VIDEO) {
      // Ensure the codec is supported by converting an FFmpeg video codec ID
      // into its corresponding supported codec id.
      if (media::CodecIDToVideoCodec(codec->id)) {
        linked_ptr<VideoCodec> video_codec(new VideoCodec);
        video_codec->format = std::string(codec->name);
        // FIXME(qjia7): find how to get hwAccel value
        video_codec->hw_accel = false;
        video_codec->encode = av_codec_is_encoder(codec) != 0;
        av_codecs->video_codecs.push_back(video_codec);
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
