/****************************************************************************
**
** This file is part of QtCompositor**
**
** Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
**
** Contact:  Nokia Corporation qt-info@nokia.com
**
** You may use this file under the terms of the BSD license as follows:
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**
** Redistributions of source code must retain the above copyright
** notice, this list of conditions and the following disclaimer.
**
** Redistributions in binary form must reproduce the above copyright
** notice, this list of conditions and the following disclaimer in the
** documentation and/or other materials provided with the distribution.
**
** Neither the name of Nokia Corporation and its Subsidiary(-ies) nor the
** names of its contributors may be used to endorse or promote products
** derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include "wloutput.h"
#include <QGuiApplication>
#include <QtGui/QScreen>
#include <QRect>

namespace Wayland {

void Output::output_bind_func(struct wl_client *client, void *data,
                          uint32_t version, uint32_t id)
{
    Q_UNUSED(version);
    Output *output = static_cast<Output *>(data);

    struct wl_resource *resource = wl_client_add_object(client,&wl_output_interface,0,id,data);
    output->registerResource(resource);
    wl_resource_post_event(resource, WL_OUTPUT_GEOMETRY, 0, 0,
                         output->size().width(), output->size().height(),0,"","");

    wl_resource_post_event(resource,WL_OUTPUT_MODE, WL_OUTPUT_MODE_CURRENT|WL_OUTPUT_MODE_PREFERRED,
                           output->size().width(),output->size().height());
}


Output::Output()
    : m_displayId(-1)
    , m_numQueued(0)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    m_geometry = QRect(QPoint(0, 0), screen->availableGeometry().size());
}

void Output::setGeometry(const QRect &geometry)
{
    m_geometry = geometry;
}

} // namespace Wayland
