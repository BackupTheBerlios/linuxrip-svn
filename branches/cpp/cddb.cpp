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

#include "cddb.h"

cddb::cddb(int *frame_offsets, int numtracks, int disc_length) {
	conn = cddb_new();
	if (conn == NULL) {
		fprintf(stderr, "out of memory, "
				"unable to create connection structure");
	}

	/* http acces is preferred */
	cddb_http_enable(conn);
	cddb_set_server_port(conn, 80);

	disc = cddb_disc_new();
	if (disc == NULL) {
		fprintf(stderr, "out of memory, unable to create disc");
	} else {
		cddb_disc_set_length(disc, disc_length);
		for (i = 0; i < numtracks; i++) {
			track = cddb_track_new();
			if (track == NULL) {
				fprintf(stderr, "out of memory, unable to create track");
			}
			cddb_track_set_frame_offset(track, frame_offsets[i]);
			cddb_disc_add_track(disc, track);
		}
	}

	/* (2) execute query command */
	matches = cddb_query(conn, disc);
	if (matches == -1) {
		/* something went wrong, print error */
		cddb_error_print(cddb_errno(conn));
	}

	cddb_read(conn, disc);
}

cddb::~cddb() {
	libcddb_shutdown();
}

std::string cddb::GetGenre() {
	return cddb_disc_get_genre(disc);
}

unsigned int cddb::GetYear() {
	return cddb_disc_get_year(disc);
}

std::string cddb::GetTitle(int num) {
	return cddb_track_get_title(cddb_disc_get_track(disc, num));
}

std::string cddb::GetArtist() {
	return cddb_disc_get_artist(disc);
}
