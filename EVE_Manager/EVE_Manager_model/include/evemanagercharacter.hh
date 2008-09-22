/*
 * Copyright 2008 Simon Jagoe
 *
 * This file is part of EVE_Manager.
 *
 * EVE_Manager is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EVE_Manager is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EVE_Manager.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _em_model_EVEMANAGERCHARACTER_HH__
#define _em_model_EVEMANAGERCHARACTER_HH__

#include <QMap>
#include <QObject>
#include <QString>

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

class EveApi;

namespace em_model
{
    class EveManagerRequestor;

    class EveManagerCharacter: public QObject
    {
	Q_OBJECT;
    public:
	/*!
	  Create the character and all related model instances
	 */
	EveManagerCharacter( shared_ptr<EveApi>& api, QObject* parent=0 );

    public slots:
// 	/*!
// 	  Fetch the wallet transactions for this character
// 	 */
// 	void walletTransactions( void* beforeTransID );

// 	/*!
// 	  Fetch the wallet journal for this character
// 	 */
// 	void walletJournal( void* beforeRefID );

// 	/*!
// 	  Fetch the skill tree for this character
// 	 */
// 	void skillTree();

	/*!
	  Fetch the current training skill for this character
	 */
	void skillInTraining();

    private:
	//! The EVE_API instance used to get API data
	shared_ptr<EveApi> _api;

	//! Map requestors to requestIDs
	QMap<shared_ptr<EveManagerRequestor>, QString> _requestorMap;
    };
};


#endif
