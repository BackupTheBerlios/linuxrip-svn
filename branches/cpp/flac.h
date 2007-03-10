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

#ifndef _FLAC_H
#define _FLAC_H

#include <string>
#include <FLAC++/encoder.h>
#include <sndfile.hh>

#define BUFFER_SIZE 44100*2*75
#define FRAMES_PER_SEC 75
#define MAXLEN 250

class flac : FLAC::Encoder::File {
	public:
		void EncodeFile(std::string in_filename, std::string out_filename);
	private:
		int buffer[BUFFER_SIZE];
		sf_count_t numsamples;
		char tmp[MAXLEN+4];
};

#endif /* _FLAC_H */
