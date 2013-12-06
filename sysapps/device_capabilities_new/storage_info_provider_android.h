// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_STORAGE_INFO_PROVIDER_ANDROID_H_
#define XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_STORAGE_INFO_PROVIDER_ANDROID_H_

#include "base/lazy_instance.h"
#include "xwalk/sysapps/device_capabilities_new/storage_info_provider.h"

namespace xwalk {
namespace sysapps {

class StorageInfoProviderAndroid : public StorageInfoProvider {
 public:
  virtual ~StorageInfoProviderAndroid();

  virtual scoped_ptr<SystemStorage> storage_info() const;

 private:
  StorageInfoProviderAndroid();

  // StorageInfoProvider implementation.
  virtual void StartStorageMonitoring() OVERRIDE;
  virtual void StopStorageMonitoring() OVERRIDE;

  friend struct base::DefaultLazyInstanceTraits<StorageInfoProviderAndroid>;
};

}  // namespace sysapps
}  // namespace xwalk

#endif  // XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_STORAGE_INFO_PROVIDER_ANDROID_H_
