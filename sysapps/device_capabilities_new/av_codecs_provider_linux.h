// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_AV_CODECS_PROVIDER_LINUX_H_
#define XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_AV_CODECS_PROVIDER_LINUX_H_

#include "base/lazy_instance.h"
#include "xwalk/sysapps/device_capabilities_new/av_codecs_provider.h"

namespace xwalk {
namespace sysapps {

class AVCodecsProviderLinux : public AVCodecsProvider {
 public:
  virtual ~AVCodecsProviderLinux();

  virtual scoped_ptr<SystemAVCodecs> av_codecs() const OVERRIDE;

 private:
  AVCodecsProviderLinux();

  friend struct base::DefaultLazyInstanceTraits<AVCodecsProviderLinux>;

  DISALLOW_COPY_AND_ASSIGN(AVCodecsProviderLinux);
};

}  // namespace sysapps
}  // namespace xwalk

#endif  // XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_AV_CODECS_PROVIDER_LINUX_H_
