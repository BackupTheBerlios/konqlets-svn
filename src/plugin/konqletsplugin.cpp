#ident "$Id: konqletsplugin.cpp,v 1.1 2004/03/09 14:40:51 symbiont Exp $"
#ident "Copyright (C) 2004 by Jeff Pitman. GPL Software."
/***************************************************************************
 *   Copyright (C) 2004 by Jeff Pitman                                     *
 *   symbiont@berlios.de                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <qfile.h>

#include <kaction.h>
#include <kconfig.h>
#include <kdebug.h>
#include <kgenericfactory.h>
#include <kglobal.h>
#include <khtml_part.h>
#include <kinstance.h>
#include <kpopupmenu.h>
#include <krun.h>
#include <kservice.h>
#include <kstandarddirs.h>

#include "konqletsplugin.h"

K_EXPORT_COMPONENT_FACTORY( libkonqletsplugin, 
                            KGenericFactory<KonqletsPlugin>("konqletsplugin") )

KonqletsPlugin::
KonqletsPlugin(QObject* parent, const char* name, const QStringList &
              ) : KParts::Plugin(parent, name) 
{
    m_part = NULL;
    if(parent && parent->inherits("KHTMLPart")) 
        m_part = static_cast<KHTMLPart*>(parent);

    m_KonqletsMenu = new KActionMenu(i18n("&Konqlets"), "core", actionCollection(), "konqlets");

    m_KonqletsMenu->setDelayed(false);
    m_KonqletsMenu->setEnabled(true);

    //connect(m_KonqletsMenu->popupMenu(), SIGNAL( aboutToShow() ),
     //       this, SLOT( slotAboutToShow() ));
}

//  emit executeScript(script);
//connect(this, SIGNAL( executeScript(const QString &) ),  Why?
//       m_part, SLOT( executeScript(const QString &) ));
//  disconnect(this, SIGNAL( executeScript(const QString &) ), 0, 0);

#include "konqletsplugin.moc"
