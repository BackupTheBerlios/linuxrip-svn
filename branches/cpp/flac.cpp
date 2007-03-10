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

#include "flac.h"

void flac::EncodeFile(std::string in_filename, std::string out_filename) {
	sprintf(tmp, "%s.wav", in_filename.c_str());
	SndfileHandle wavread(tmp);
	set_channels(2);
	set_sample_rate(44100);
	set_bits_per_sample(16);
	sprintf(tmp, "%s.flac", out_filename.c_str());
	init(tmp);

	numsamples = BUFFER_SIZE;
	while ( numsamples > 0 ) {
		numsamples = wavread.read(&(buffer[0]), BUFFER_SIZE);
		process_interleaved(&(buffer[0]), numsamples/2);
	}

	printf("Encoding of file: %s.wav is done\n", in_filename.c_str());
}
