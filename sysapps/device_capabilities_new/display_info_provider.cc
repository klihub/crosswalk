// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/sysapps/device_capabilities_new/display_info_provider.h"

#include <vector>
#include "base/strings/string_number_conversions.h"
#include "base/sys_info.h"
#include "ui/gfx/display.h"
#include "ui/gfx/screen.h"

namespace {

// We are calculating the DPI the same way Chromium for
// ChromiumOS. See display_info_provider_chromeos.cc.
const float kDpi96 = 96;

}  // namespace

namespace xwalk {
namespace sysapps {

using xwalk::jsapi::device_capabilities::DisplayUnit;

DisplayInfoProvider::DisplayInfoProvider() {}

DisplayInfoProvider::~DisplayInfoProvider() {}

// static
scoped_ptr<SystemDisplay> DisplayInfoProvider::display_info() {
  scoped_ptr<SystemDisplay> info(new SystemDisplay);

  gfx::Screen* screen = gfx::Screen::GetNativeScreen();
  const int64 primary_display_id = screen->GetPrimaryDisplay().id();
  std::vector<gfx::Display> displays = screen->GetAllDisplays();

  for (std::vector<gfx::Display>::const_iterator it = displays.begin();
      it != displays.end(); ++it) {
    linked_ptr<DisplayUnit> display(make_linked_ptr(new DisplayUnit));

    display->id = base::Int64ToString(it->id());
    // FIXME(YuZhiqiangX): find which field reflects 'name'.
    display->name = "unknown";

    display->is_primary = (it->id() == primary_display_id);
    display->is_internal = it->IsInternal();

    const float dpi = it->device_scale_factor() * kDpi96;
    display->dpi_x = static_cast<unsigned int>(dpi);
    display->dpi_y = static_cast<unsigned int>(dpi);

    display->width = it->bounds().width();
    display->height = it->bounds().height();
    display->avail_width = it->work_area_size().width();
    display->avail_height = it->work_area_size().height();

    info->displays.push_back(display);
  }

  return info.Pass();
}

// static
DisplayInfoProvider* DisplayInfoProvider::GetInstance() {
  return Singleton<DisplayInfoProvider>::get();
}

}  // namespace sysapps
}  // namespace xwalk
