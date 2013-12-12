// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/sysapps/device_capabilities_new/av_codecs_provider.h"

#include <vector>

#include "testing/gtest/include/gtest/gtest.h"
#include "xwalk/sysapps/device_capabilities_new/device_capabilities.h"

using xwalk::jsapi::device_capabilities::AudioCodec;
using xwalk::jsapi::device_capabilities::VideoCodec;
using xwalk::jsapi::device_capabilities::SystemAVCodecs;
using xwalk::sysapps::AVCodecsProvider;

TEST(XWalkSysAppsDeviceCapabilitiesTest, AVCodecsProvider) {
  AVCodecsProvider* provider = AVCodecsProvider::GetInstance();

  ASSERT_TRUE(provider != NULL);
  EXPECT_EQ(provider, AVCodecsProvider::GetInstance());

  for (unsigned i = 0; i < 1000; ++i) {
    scoped_ptr<SystemAVCodecs> info(provider->av_codecs());
    std::vector<linked_ptr<AudioCodec> > audio_codecs = info->audio_codecs;
    for (size_t i = 0; i < audio_codecs.size(); ++i)
      EXPECT_FALSE(audio_codecs[i]->format.empty());

    std::vector<linked_ptr<VideoCodec> > video_codecs = info->video_codecs;
    for (size_t i = 0; i < video_codecs.size(); ++i)
      EXPECT_FALSE(video_codecs[i]->format.empty());
  }
}
