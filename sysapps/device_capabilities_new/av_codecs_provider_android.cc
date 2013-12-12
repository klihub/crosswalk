// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/sysapps/device_capabilities_new/av_codecs_provider_android.h"

namespace xwalk {
namespace sysapps {

static base::LazyInstance<AVCodecsProviderAndroid>::Leaky
    g_storage_info_provider = LAZY_INSTANCE_INITIALIZER;

AVCodecsProviderAndroid::AVCodecsProviderAndroid() {}

AVCodecsProviderAndroid::~AVCodecsProviderAndroid() {}

scoped_ptr<SystemAVCodecs> AVCodecsProviderAndroid::av_codecs() const {
  NOTIMPLEMENTED();
  return make_scoped_ptr(new SystemAVCodecs);
}

// static
AVCodecsProvider* AVCodecsProvider::GetInstance() {
  return &g_storage_info_provider.Get();
}

}  // namespace sysapps
}  // namespace xwalk
