/********************************************************************
* Copyright (C) PanteR
*-------------------------------------------------------------------
*
* QDBFRedactor is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* QDBFRedactor is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Panther Commander; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor,
* Boston, MA 02110-1301 USA
*-------------------------------------------------------------------
* Project:		QDBFRedactor
* Author:		PanteR
* Contact:		panter.dsd@gmail.com
*******************************************************************/

#ifndef DBFRECORD_H
#define DBFRECORD_H

#include "dbfredactorcore.h"

namespace DBFRedactorCore {

class DBFRecord {
public:
	DBFRecord ();
	DBFRecord (const char *data, int16 length);
	DBFRecord (const DBFRecord &f);

	DBFRecord& operator= (const DBFRecord &f);

	~DBFRecord ();

	void clear ();
	bool isEmpty () const;
	bool isValid () const;


	const char* data () const
	{return m_data;}

	void setData (const char *data, int16 length);

private:
	char *m_data;
	int16 m_length;
};
}

#endif //DBFRECORD_H
