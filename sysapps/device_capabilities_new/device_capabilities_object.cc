// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/sysapps/device_capabilities_new/device_capabilities_object.h"

#include <string>

#include "xwalk/sysapps/device_capabilities_new/cpu_info_provider.h"
#include "xwalk/sysapps/device_capabilities_new/storage_info_provider.h"

namespace xwalk {
namespace sysapps {

using namespace jsapi::device_capabilities;

DeviceCapabilitiesObject::DeviceCapabilitiesObject() {
  handler_.Register("getCPUInfo",
                    base::Bind(&DeviceCapabilitiesObject::OnGetCPUInfo,
                               base::Unretained(this)));
  handler_.Register("getStorageInfo",
                    base::Bind(&DeviceCapabilitiesObject::OnGetStorageInfo,
                               base::Unretained(this)));
}

DeviceCapabilitiesObject::~DeviceCapabilitiesObject() {}

void DeviceCapabilitiesObject::OnGetCPUInfo(
    scoped_ptr<XWalkExtensionFunctionInfo> info) {
  scoped_ptr<SystemCPU> cpu_info(CPUInfoProvider::GetInstance()->cpu_info());
  info->PostResult(GetCPUInfo::Results::Create(*cpu_info, std::string()));
}

void DeviceCapabilitiesObject::OnGetStorageInfo(
    scoped_ptr<XWalkExtensionFunctionInfo> info) {
  StorageInfoProvider* provider(StorageInfoProvider::GetInstance());

  // Queue the message if the backend is not initialized yet.
  if (!provider->IsInitialized()) {
    provider->AddOnInitCallback(
        base::Bind(&DeviceCapabilitiesObject::OnGetStorageInfo,
                   base::Unretained(this),
                   base::Passed(&info)));
    return;
  }

  scoped_ptr<SystemStorage> storage_info(provider->storage_info());
  info->PostResult(GetStorageInfo::Results::Create(
      *storage_info, std::string()));
}

}  // namespace sysapps
}  // namespace xwalk
