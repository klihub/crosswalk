// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/sysapps/device_capabilities_new/device_capabilities_object.h"

#include <string>

#include "xwalk/sysapps/device_capabilities_new/cpu_info_provider.h"
#include "xwalk/sysapps/device_capabilities_new/display_info_provider.h"
#include "xwalk/sysapps/device_capabilities_new/memory_info_provider.h"
#include "xwalk/sysapps/device_capabilities_new/storage_info_provider.h"

namespace xwalk {
namespace sysapps {

using namespace jsapi::device_capabilities;

DeviceCapabilitiesObject::DeviceCapabilitiesObject() {
  handler_.Register("getCPUInfo",
                    base::Bind(&DeviceCapabilitiesObject::OnGetCPUInfo,
                               base::Unretained(this)));
  handler_.Register("getDisplayInfo",
                    base::Bind(&DeviceCapabilitiesObject::OnGetDisplayInfo,
                               base::Unretained(this)));
  handler_.Register("getMemoryInfo",
                    base::Bind(&DeviceCapabilitiesObject::OnGetMemoryInfo,
                               base::Unretained(this)));
  handler_.Register("getStorageInfo",
                    base::Bind(&DeviceCapabilitiesObject::OnGetStorageInfo,
                               base::Unretained(this)));
}

DeviceCapabilitiesObject::~DeviceCapabilitiesObject() {
  if (StorageInfoProvider::GetInstance()->HasObserver(this))
    StorageInfoProvider::GetInstance()->RemoveObserver(this);

  if (DisplayInfoProvider::GetInstance()->HasObserver(this))
    DisplayInfoProvider::GetInstance()->RemoveObserver(this);
}

void DeviceCapabilitiesObject::StartEvent(const std::string& type) {
  if (type == "storageattach" || type == "storagedetach") {
    if (!StorageInfoProvider::GetInstance()->HasObserver(this))
      StorageInfoProvider::GetInstance()->AddObserver(this);
  } else if (type == "displayconnect" || type == "displaydisconnect") {
    if (!DisplayInfoProvider::GetInstance()->HasObserver(this))
      DisplayInfoProvider::GetInstance()->AddObserver(this);
  }
}

void DeviceCapabilitiesObject::StopEvent(const std::string& type) {
  if (type == "storageattach" || type == "storagedetach") {
    if (!IsEventActive("storageattach") && !IsEventActive("storagedetach"))
      StorageInfoProvider::GetInstance()->RemoveObserver(this);
  } else if (type == "displayconnect" || type == "displaydisconnect") {
    if (!IsEventActive("displayconnect") && !IsEventActive("displaydisconnect"))
      DisplayInfoProvider::GetInstance()->RemoveObserver(this);
  }
}

void DeviceCapabilitiesObject::OnDisplayConnected(const DisplayUnit& display) {
  scoped_ptr<base::ListValue> eventData(new base::ListValue);
  eventData->Append(display.ToValue().release());

  DispatchEvent("displayconnect", eventData.Pass());
}

void DeviceCapabilitiesObject::OnDisplayDisconnected(
    const DisplayUnit& display) {
  scoped_ptr<base::ListValue> eventData(new base::ListValue);
  eventData->Append(display.ToValue().release());

  DispatchEvent("displaydisconnect", eventData.Pass());
}

void DeviceCapabilitiesObject::OnStorageAttached(const StorageUnit& storage) {
  scoped_ptr<base::ListValue> eventData(new base::ListValue);
  eventData->Append(storage.ToValue().release());

  DispatchEvent("storageattach", eventData.Pass());
}

void DeviceCapabilitiesObject::OnStorageDetached(const StorageUnit& storage) {
  scoped_ptr<base::ListValue> eventData(new base::ListValue);
  eventData->Append(storage.ToValue().release());

  DispatchEvent("storagedetach", eventData.Pass());
}

void DeviceCapabilitiesObject::OnGetCPUInfo(
    scoped_ptr<XWalkExtensionFunctionInfo> info) {
  scoped_ptr<SystemCPU> cpu_info(CPUInfoProvider::GetInstance()->cpu_info());
  info->PostResult(GetCPUInfo::Results::Create(*cpu_info, std::string()));
}

void DeviceCapabilitiesObject::OnGetDisplayInfo(
    scoped_ptr<XWalkExtensionFunctionInfo> info) {
  scoped_ptr<SystemDisplay> display_info(DisplayInfoProvider::display_info());
  info->PostResult(GetDisplayInfo::Results::Create(*display_info,
                                                   std::string()));
}

void DeviceCapabilitiesObject::OnGetMemoryInfo(
    scoped_ptr<XWalkExtensionFunctionInfo> info) {
  scoped_ptr<SystemMemory> memory_info(
      MemoryInfoProvider::GetInstance()->memory_info());
  info->PostResult(GetMemoryInfo::Results::Create(*memory_info, std::string()));
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
