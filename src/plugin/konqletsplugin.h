#ifndef _KONQLETSPLUGIN_H_
#define _KONQLETSPLUGIN_H_
#ident "$Id: konqletsplugin.h,v 1.1 2004/03/09 14:40:51 symbiont Exp $"
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

#include <qmap.h>
#include <qstringlist.h>
#include <qvaluelist.h>

#include <klibloader.h>
#include <kparts/plugin.h>
#include <kurl.h>

class KHTMLPart;
class KActionMenu;

class KonqletsPlugin : public KParts::Plugin {
    Q_OBJECT

public:
    KonqletsPlugin(QObject *, const char *, const QStringList &);
    ~KonqletsPlugin() {};

protected slots:
    // add callbacks here

signals:
    void executeScript( const QString &script );

private:
    KActionMenu* m_KonqletsMenu;
    KHTMLPart*   m_part;
};

#endif // _KONQLETSPLUGIN_H_ 
