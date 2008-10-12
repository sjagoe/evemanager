
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

#ifndef _EVEAPI_MEMBERSECURITYDATA_HH_
#define _EVEAPI_MEMBERSECURITYDATA_HH_

namespace EveApi
{
    class Member
    {
    private:
        RowSet _roles;
        RowSet _grantableRoles;
        RowSet _rolesAtHQ;
        RowSet _grantableRolesAtHQ;
        RowSet _rolesAtBase;
        RowSet _grantableRolesAtBase;
        RowSet _rolesAtOther;
        RowSet _grantableRolesAtOther;
        RowSet _titles;
    };

    class MemberSecurityData
    {

    };
};

#endif
