// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_STORAGE_INFO_PROVIDER_LINUX_H_
#define XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_STORAGE_INFO_PROVIDER_LINUX_H_

#include "base/lazy_instance.h"
#include "chrome/browser/storage_monitor/removable_storage_observer.h"
#include "xwalk/sysapps/device_capabilities_new/storage_info_provider.h"

namespace xwalk {
namespace sysapps {

class StorageInfoProviderLinux : public StorageInfoProvider,
                                 public RemovableStorageObserver {
 public:
  virtual ~StorageInfoProviderLinux();

  virtual scoped_ptr<SystemStorage> storage_info() const;

  // RemovableStorageObserver implementation.
  virtual void OnRemovableStorageAttached(const StorageInfo& info) OVERRIDE;
  virtual void OnRemovableStorageDetached(const StorageInfo& info) OVERRIDE;

 private:
  StorageInfoProviderLinux();

  // StorageInfoProvider implementation.
  virtual void StartStorageMonitoring() OVERRIDE;
  virtual void StopStorageMonitoring() OVERRIDE;

  friend struct base::DefaultLazyInstanceTraits<StorageInfoProviderLinux>;
};

}  // namespace sysapps
}  // namespace xwalk

#endif  // XWALK_SYSAPPS_DEVICE_CAPABILITIES_NEW_STORAGE_INFO_PROVIDER_LINUX_H_
