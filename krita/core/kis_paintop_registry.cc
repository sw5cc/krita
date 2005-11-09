/*
 *  Copyright (c) 2004 Boudewijn Rempt <boud@valdyas.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include <qpixmap.h>

#include <kdebug.h>
#include <kinstance.h>
#include <kglobal.h>
#include <klocale.h>
#include <kstandarddirs.h>
#include <kparts/plugin.h>
#include <kservice.h>
#include <ktrader.h>
#include <kparts/componentfactory.h>

#include "kis_generic_registry.h"
#include "kis_types.h"
#include "kis_paintop_registry.h"
#include "kis_paintop.h"
#include "kis_id.h"
#include "kis_debug_areas.h"

KisPaintOpRegistry * KisPaintOpRegistry::m_singleton = 0;

KisPaintOpRegistry::KisPaintOpRegistry()
{
    Q_ASSERT(KisPaintOpRegistry::m_singleton == 0);
    KisPaintOpRegistry::m_singleton = this;

    KTrader::OfferList offers = KTrader::self() -> query(QString::fromLatin1("Krita/Paintop"),
                                                         QString::fromLatin1("(Type == 'Service') and "
                                                                             "([X-KDE-Version] == 2)"));

    KTrader::OfferList::ConstIterator iter;

    for(iter = offers.begin(); iter != offers.end(); ++iter)
    {
        KService::Ptr service = *iter;
        int errCode = 0;
        KParts::Plugin* plugin =
             KParts::ComponentFactory::createInstanceFromService<KParts::Plugin> ( service, this, 0, QStringList(), &errCode);
        if ( plugin )
            kdDebug() << "found plugin " << service -> property("Name").toString() << "\n";
    }

}

KisPaintOpRegistry::~KisPaintOpRegistry()
{
}

KisPaintOpRegistry* KisPaintOpRegistry::instance()
{
    if(KisPaintOpRegistry::m_singleton == 0)
    {
        KisPaintOpRegistry::m_singleton = new KisPaintOpRegistry();
        Q_CHECK_PTR(KisPaintOpRegistry::m_singleton);
    }
    return KisPaintOpRegistry::m_singleton;
}

KisPaintOp * KisPaintOpRegistry::paintOp(const KisID & id, KisPainter * painter) const
{
    KisPaintOpFactorySP f = get(id);
    if (f) {
        return f -> createOp(painter);
    }
    else {
        return 0;
    }
}

KisPaintOp * KisPaintOpRegistry::paintOp(const QString & id, KisPainter * painter) const
{
    return paintOp(KisID(id, ""), painter);
}

bool KisPaintOpRegistry::userVisible(const KisID & id) const
{

    KisPaintOpFactorySP f = get(id);
    if (!f) {
        kdDebug(DBG_AREA_REGISTRY) << "No paintop " << id.id() << "\n";
        return false;
    }

    return f->userVisible();

}

QPixmap KisPaintOpRegistry::getPixmap(const KisID & id) const
{
    KisPaintOpFactorySP f = get(id);

    if (!f) {
        kdDebug(DBG_AREA_REGISTRY) << "No paintop " << id.id() << "\n";
        return QPixmap();
    }

    QString pname = f->pixmap();

    if (pname.isEmpty() /*|| pname.isNull() || pname == ""*/) {
        return QPixmap();
    }

    QString fname = KGlobal::dirs()->findResource("kis_images", pname);

    return QPixmap(fname);
}

#include "kis_paintop_registry.moc"
