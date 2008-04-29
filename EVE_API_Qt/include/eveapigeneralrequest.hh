
/*
 * Copyright 2007-2008 Simon Jagoe
 *
 * This file is part of EVE_API_Qt.
 *
 * EVE_API_Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EVE_API_Qt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EVE_API_Qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __EVEAPIGENERALREQUEST_HH__
#define __EVEAPIGENERALREQUEST_HH__

#include "eveapirequest.hh"

class EveApiGeneralRequest: public EveApiRequest
{
        Q_OBJECT
    public:
        /*!
        pass the constructor args to the super-class
        */
        EveApiGeneralRequest( const QString& requestType,
                              const QString& dataPath,
                              const int& xmlIndent,
                              const QList<QString>& requiredParams,
                              const QList<QString>& optionalParams,
                              const QList<QString>& fileIDParam,
                              const int& p_type,
                              const QString& host,
                              const quint16& port,
                              const QString & user,
                              const QString & password,
                              QObject* parent = 0 );

    private:
        /*!
        return a QStringList of filesystem directories, relative to the data directory, in which to store cache
        */
        QStringList cachePath( const QString& scope,
                               const QMap<QString, QString>& parameters );
};

#endif
