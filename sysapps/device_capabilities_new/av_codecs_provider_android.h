// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_AV_CODECS_PROVIDER_ANDROID_H_
#define XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_AV_CODECS_PROVIDER_ANDROID_H_

#include "base/lazy_instance.h"
#include "xwalk/sysapps/device_capabilities_new/av_codecs_provider.h"

namespace xwalk {
namespace sysapps {

class AVCodecsProviderAndroid : public AVCodecsProvider {
 public:
  virtual ~AVCodecsProviderAndroid();

  virtual scoped_ptr<SystemAVCodecs> av_codecs() const OVERRIDE;

 private:
  AVCodecsProviderAndroid();

  friend struct base::DefaultLazyInstanceTraits<AVCodecsProviderAndroid>;

  DISALLOW_COPY_AND_ASSIGN(AVCodecsProviderAndroid);
};

}  // namespace sysapps
}  // namespace xwalk

#endif  // XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_AV_CODECS_PROVIDER_ANDROID_H_
