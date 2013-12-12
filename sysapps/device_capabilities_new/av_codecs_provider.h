// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_AV_CODECS_PROVIDER_H_
#define XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_AV_CODECS_PROVIDER_H_

#include "xwalk/sysapps/device_capabilities_new/device_capabilities.h"

namespace xwalk {
namespace sysapps {

using jsapi::device_capabilities::AudioCodec;
using jsapi::device_capabilities::VideoCodec;
using jsapi::device_capabilities::SystemAVCodecs;

class AVCodecsProvider {
 public:
  static AVCodecsProvider* GetInstance();

  virtual ~AVCodecsProvider() {}

  virtual scoped_ptr<SystemAVCodecs> av_codecs() const = 0;

 protected:
  AVCodecsProvider() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(AVCodecsProvider);
};

}  // namespace sysapps
}  // namespace xwalk

#endif  // XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_AV_CODECS_PROVIDER_H_
