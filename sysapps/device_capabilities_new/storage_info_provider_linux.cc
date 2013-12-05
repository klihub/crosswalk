// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/sysapps/device_capabilities_new/storage_info_provider_linux.h"

#include <string>
#include <vector>
#include "base/bind_helpers.h"
#include "base/message_loop/message_loop.h"
#include "base/strings/utf_string_conversions.h"
#include "chrome/browser/storage_monitor/storage_monitor.h"

using namespace xwalk::jsapi::device_capabilities; // NOLINT

namespace {

linked_ptr<StorageUnit> makeStorageUnit(const StorageInfo& storage) {
  linked_ptr<StorageUnit> storage_unit(make_linked_ptr(new StorageUnit));

  storage_unit->id = storage.device_id();
  storage_unit->name = base::UTF16ToUTF8(storage.name());
  storage_unit->capacity = storage.total_size_in_bytes();

  if (StorageInfo::IsRemovableDevice(storage_unit->id))
    storage_unit->type = ToString(STORAGE_UNIT_TYPE_REMOVABLE);
  else if (StorageInfo::IsMassStorageDevice(storage_unit->id))
    storage_unit->type = ToString(STORAGE_UNIT_TYPE_FIXED);
  else
    storage_unit->type = ToString(STORAGE_UNIT_TYPE_UNKNOWN);

  return storage_unit;
}

}  // namespace

namespace xwalk {
namespace sysapps {

static base::LazyInstance<StorageInfoProviderLinux>::Leaky
    g_storage_info_provider = LAZY_INSTANCE_INITIALIZER;

StorageInfoProviderLinux::StorageInfoProviderLinux() {
  StorageMonitor* monitor = StorageMonitor::GetInstance();

  monitor->EnsureInitialized(
      base::Bind(&StorageInfoProvider::MarkInitialized,
                 base::Unretained(this)));
}

StorageInfoProviderLinux::~StorageInfoProviderLinux() {}

scoped_ptr<SystemStorage> StorageInfoProviderLinux::storage_info() const {
  scoped_ptr<SystemStorage> info(new SystemStorage);

  StorageMonitor* monitor = StorageMonitor::GetInstance();
  DCHECK(monitor->IsInitialized());

  std::vector<StorageInfo> storages = monitor->GetAllAvailableStorages();
  for (std::vector<StorageInfo>::const_iterator it = storages.begin();
      it != storages.end(); ++it) {
    info->storages.push_back(makeStorageUnit(*it));
  }

  return info.Pass();
}

void StorageInfoProviderLinux::OnRemovableStorageAttached(
    const StorageInfo& info) {
  NotifyStorageAttached(*makeStorageUnit(info));
}

void StorageInfoProviderLinux::OnRemovableStorageDetached(
    const StorageInfo& info) {
  NotifyStorageDetached(*makeStorageUnit(info));
}

void StorageInfoProviderLinux::StartStorageMonitoring() {
  StorageMonitor::GetInstance()->AddObserver(this);
}

void StorageInfoProviderLinux::StopStorageMonitoring() {
  StorageMonitor::GetInstance()->RemoveObserver(this);
}

// static
StorageInfoProvider* StorageInfoProvider::GetInstance() {
  return &g_storage_info_provider.Get();
}

}  // namespace sysapps
}  // namespace xwalk
