
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

#ifndef _EVEAPI_CORPORATIONSHEET_HH_
#define _EVEAPI_CORPORATIONSHEET_HH_

#include <QPair>
#include <QString>

#include "abstracteveapidata.hh"

namespace EveApi
{
    class LogoData
    {
    private:
	DataItem _graphicID;
	DataItem _shape1;
	DataItem _shape2;
	DataItem _shape3;
	DataItem _color1;
	DataItem _color2;
	DataItem _color3;
    };

    class CorporationSheetData
    {
    private:
	DataItem _corporationID;
	DataItem _corporationName;
	DataItem _ticker;
	DataItem _ceoID;
	DataItem _ceoName;
	DataItem _stationID;
	DataItem _stationName;
	DataItem _description;
	DataItem _url;
	DataItem _allianceID;
	DataItem _allianceName;
	DataItem _taxRate;
	DataItem _memberCount;
	DataItem _memberLimit;
	DataItem _shares;
	RowSet _divisions;
	RowSet _walletDivisions;
	LogoData _logo;
    };
};


#endif
