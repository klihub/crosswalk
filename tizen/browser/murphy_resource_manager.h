// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_TIZEN_BROWSER_MURPHY_RESOURCE_MANAGER_H_
#define XWALK_TIZEN_BROWSER_MURPHY_RESOURCE_MANAGER_H_

#include "base/logging.h"
#include <murphy/common.h>
#include <murphy/ecore/ecore-glue.h>
#include <murphy/glib/glib-glue.h>
#include <murphy/plugins/resource-native/libmurphy-resource/resource-api.h>

namespace tizen {
class BrowserMediaPlayerManager;

enum MurphyConnectionEvent {
    MURPHY_DISCONNECTED,
    MURPHY_CONNECTED
};

#if 0
class MurphyObserver {

public:
    MurphyObserver() { };
    virtual ~MurphyObserver() { };

    virtual void murphyNotify(MurphyConnectionEvent evt) = 0;
};
#endif

class MurphyResourceManager {

public:
    MurphyResourceManager(BrowserMediaPlayerManager* manager);
    virtual ~MurphyResourceManager();

    bool connectToMurphy();
    void disconnectFromMurphy();
    bool isConnected();
    mrp_res_context_t * getContext();

#if 0
    void registerObserver(MurphyObserver *obs);
    void unregisterObserver(MurphyObserver *obs);
    Vector<MurphyObserver *> & getObservers();
#endif

private:
    BrowserMediaPlayerManager*  manager_;
    mrp_res_context_t *m_ctx;
    mrp_mainloop_t *m_ml;
    GMainLoop* gml_;
#if 0
    Vector<MurphyObserver *> m_observers;
#endif
};

}

#endif // XWALK_TIZEN_BROWSER_MURPHY_RESOURCE_MANAGER_H_
