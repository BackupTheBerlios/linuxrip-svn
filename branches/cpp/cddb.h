/* 
	Linuxrip, not doing a whole lot yet.
	Copyright (C) 2007 madman2003(madman2003@gmail.com)

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef _CDDB_H
#define _CDDB_H

#include <string>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cddb/cddb.h>

class cddb {
	public:
		cddb(int *frame_offsets, int numtracks, int disc_length);

		~cddb();

		std::string GetGenre();

		unsigned int GetYear();

		std::string GetTitle(int num);

		std::string GetArtist();

	private:
		cddb_disc_t *disc;
		cddb_track_t *track;
		cddb_conn_t *conn;
		int i, matches;
};

#endif /* _CDDB_H */
