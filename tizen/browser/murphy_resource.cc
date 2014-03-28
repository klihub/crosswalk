// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/tizen/browser/murphy_resource.h"

#include "xwalk/tizen/browser/browser_mediaplayer_manager.h"

namespace tizen {

static void res_cb(mrp_res_context_t *ctx, const mrp_res_resource_set_t *rs,
        void *userdata)
{
#if 0
    MurphyResource *resource = (MurphyResource *) userdata;
    if (!resource)
        return;
    Vector<MurphyResourceObserver *> observers = resource->getObservers();

    for (uint i = 0; i < observers.size(); i++) {
        MurphyResourceObserver *observer = observers[i];
        enum MurphyResourceState evt = MURPHY_RESOURCE_AVAILABLE;
        switch(rs->state) {
            case MRP_RES_RESOURCE_ACQUIRED:
                evt = MURPHY_RESOURCE_AVAILABLE;
                break;
            case MRP_RES_RESOURCE_AVAILABLE:
                evt = MURPHY_RESOURCE_AVAILABLE;
                break;
            case MRP_RES_RESOURCE_LOST:
                evt = MURPHY_RESOURCE_LOST;
               break;
            case MRP_RES_RESOURCE_PENDING:
                evt = MURPHY_RESOURCE_PENDING;
                break;
        }
        observer->murphyResourceNotify(evt);
    }
#endif
}

MurphyResource::MurphyResource(
    BrowserMediaPlayerManager* manager,
    MurphyResourceManager *resource_manager)
    : manager_(manager),
      resource_manager_(resource_manager) {
    mrp_res_context_t *ctx = resource_manager_->getContext();
    if (!ctx)
        return;

    m_rset_ = mrp_res_create_resource_set(ctx, "browser", res_cb, NULL);
    if (!m_rset_)
        return;

    m_resource_ = mrp_res_create_resource(ctx, m_rset_, "audio_playback", TRUE, FALSE);
}

void MurphyResource::acquireResource()
{
    if (!resource_manager_ || !m_rset_)
        return;

    // Call acquire
    mrp_res_acquire_resource_set(resource_manager_->getContext(), m_rset_);
}

void MurphyResource::releaseResource()
{
    if (!resource_manager_ || !m_rset_)
        return;

    // Call release
    mrp_res_release_resource_set(resource_manager_->getContext(), m_rset_);
}

#if 0
void MurphyResource::registerObserver(MurphyResourceObserver *obs)
{
    m_observers.append(obs);
}

void MurphyResource::unregisterObserver(MurphyResourceObserver *obs)
{
    size_t i = m_observers.find(obs);
    if (i != notFound)
        m_observers.remove(i);
}

Vector<MurphyResourceObserver *> & MurphyResource::getObservers() {
    return m_observers;
}
#endif

MurphyResourceState MurphyResource::getResourceState()
{
    if (!m_rset_)
        return MURPHY_RESOURCE_LOST;

    switch(m_rset_->state) {
        case MRP_RES_RESOURCE_ACQUIRED:
            return MURPHY_RESOURCE_ACQUIRED;
        case MRP_RES_RESOURCE_AVAILABLE:
            return MURPHY_RESOURCE_AVAILABLE;
        case MRP_RES_RESOURCE_LOST:
            return MURPHY_RESOURCE_LOST;
        case MRP_RES_RESOURCE_PENDING:
            return MURPHY_RESOURCE_PENDING;
    }
    return MURPHY_RESOURCE_LOST;
}


MurphyResource::~MurphyResource()
{
    releaseResource();

    if (!resource_manager_ || !m_rset_)
        return;
    // Delete resource set (and the resource inside it)
    mrp_res_delete_resource_set(resource_manager_->getContext(), m_rset_);
}

}
