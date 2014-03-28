// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "murphy_resource_manager.h"

#include "xwalk/tizen/browser/browser_mediaplayer_manager.h"

namespace tizen {

MurphyResourceManager::MurphyResourceManager(BrowserMediaPlayerManager* manager)
    : manager_(manager) {
#if 0
  mainloop = g_main_loop_new(NULL, FALSE);
  m_ml = mrp_mainloop_create();
  if (!mrp_mainloop_register_with_ecore(m_ml)) {
    mrp_mainloop_destroy(m_ml);
    m_ml = NULL;
  }
  m_ctx = NULL;
#endif
  m_ml = mrp_mainloop_glib_get(gml_);
}

MurphyResourceManager::~MurphyResourceManager() {
  disconnectFromMurphy();

  if (m_ctx)
    mrp_res_destroy(m_ctx);

#if 0
  if (m_ml) {
    mrp_mainloop_unregister_from_ecore(m_ml);
    mrp_mainloop_destroy(m_ml);
  }
#endif
}

static void state_cb(mrp_res_context_t *cx, mrp_res_error_t err, void *userdata)
{
#if 0
    MurphyResourceManager *m = (MurphyResourceManager *) userdata;
    Vector<MurphyObserver *> observers = m->getObservers();

    if (err != MRP_RES_ERROR_NONE) {
        // TODO: better error handling
        return;
    }

    for (uint i = 0; i < observers.size(); i++) {
        MurphyObserver *observer = observers[i];
        enum MurphyConnectionEvent evt = MURPHY_DISCONNECTED;
        switch(cx->state) {
            case MRP_RES_CONNECTED:
                evt = MURPHY_CONNECTED;
                break;
            case MRP_RES_DISCONNECTED:
                evt = MURPHY_DISCONNECTED;
                break;
        }
        observer->murphyNotify(evt);
    }
#endif
 // m->manager_->MurphyResourceManagerNotify();
}

bool MurphyResourceManager::connectToMurphy()
{
  if (!m_ml)
    return FALSE;

  if (!m_ctx)
    m_ctx = mrp_res_create(m_ml, state_cb, this);

  return m_ctx != NULL;
}

bool MurphyResourceManager::isConnected()
{
  if (!m_ctx)
    return FALSE;

  return m_ctx->state == MRP_RES_CONNECTED;
}


void MurphyResourceManager::disconnectFromMurphy()
{
  if (!m_ctx)
    return;

  mrp_res_destroy(m_ctx);
  m_ctx = NULL;
}

mrp_res_context_t * MurphyResourceManager::getContext()
{
    return m_ctx;
}

#if 0
Vector<MurphyObserver *> & MurphyResourceManager::getObservers()
{
    return m_observers;
}

void MurphyResourceManager::registerObserver(MurphyObserver *obs)
{
    m_observers.append(obs);
}

void MurphyResourceManager::unregisterObserver(MurphyObserver *obs)
{
    size_t i = m_observers.find(obs);
    if (i != notFound)
        m_observers.remove(i);
}
#endif

}
