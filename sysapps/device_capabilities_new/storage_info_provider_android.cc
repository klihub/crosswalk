// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/sysapps/device_capabilities_new/storage_info_provider_android.h"

namespace xwalk {
namespace sysapps {

static base::LazyInstance<StorageInfoProviderAndroid>::Leaky
    g_storage_info_provider = LAZY_INSTANCE_INITIALIZER;

StorageInfoProviderAndroid::StorageInfoProviderAndroid() {
  MarkInitialized();
}

StorageInfoProviderAndroid::~StorageInfoProviderAndroid() {}

scoped_ptr<SystemStorage> StorageInfoProviderAndroid::storage_info() const {
  NOTIMPLEMENTED();
  return make_scoped_ptr(new SystemStorage);
}

void StorageInfoProviderAndroid::StartStorageMonitoring() {
  NOTIMPLEMENTED();
}

void StorageInfoProviderAndroid::StopStorageMonitoring() {
  NOTIMPLEMENTED();
}

// static
StorageInfoProvider* StorageInfoProvider::GetInstance() {
  return &g_storage_info_provider.Get();
}

}  // namespace sysapps
}  // namespace xwalk
