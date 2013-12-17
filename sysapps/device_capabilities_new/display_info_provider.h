// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_DISPLAY_INFO_PROVIDER_H_
#define XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_DISPLAY_INFO_PROVIDER_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/singleton.h"
#include "xwalk/sysapps/device_capabilities_new/device_capabilities.h"

namespace xwalk {
namespace sysapps {

using jsapi::device_capabilities::SystemDisplay;

class DisplayInfoProvider {
 public:
  static DisplayInfoProvider* GetInstance();

  ~DisplayInfoProvider();

  static scoped_ptr<SystemDisplay> display_info();

 private:
  DisplayInfoProvider();

  friend struct DefaultSingletonTraits<DisplayInfoProvider>;

  DISALLOW_COPY_AND_ASSIGN(DisplayInfoProvider);
};

}  // namespace sysapps
}  // namespace xwalk

#endif  // XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_DISPLAY_INFO_PROVIDER_H_
