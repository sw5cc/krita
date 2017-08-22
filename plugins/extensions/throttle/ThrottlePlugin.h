/*
 *  Copyright (c) 2017 Boudewijn Rempt <boud@valdyas.org>
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef THROTTLEPLUGIN_H
#define THROTTLEPLUGIN_H

#include <kis_view_plugin.h>

#include <QVariant>

class Throttle;

class ThrottlePlugin : public KisViewPlugin
{
    Q_OBJECT
public:
    ThrottlePlugin(QObject *parent, const QVariantList &);
    ~ThrottlePlugin() override;
private Q_SLOTS:
    void slotActivated();
private:
    Throttle * m_throttle {0};

};

#endif
