/*
 *  Copyright (c) 2015 Boudewijn Rempt <boud@valdyas.org>
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
#include <KritaVersionWrapper.h>

#include <kritaversion.h>
#include <kritagitversion.h>

QString KritaVersionWrapper::versionString(bool checkGit)
{
    QString kritaVersion(KRITA_VERSION_STRING);
    QString version = kritaVersion;

    if (checkGit) {
#ifdef KRITA_GIT_SHA1_STRING
        QString gitVersion(KRITA_GIT_SHA1_STRING);
        version = QString("%1 (git %2)").arg(kritaVersion).arg(gitVersion).toLatin1();
#endif
    }
    return version;
}

