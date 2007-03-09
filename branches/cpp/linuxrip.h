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

#include <cdio/cdio.h>
#include <cdio/cdda.h>
#include <cdio/paranoia.h>
#include <cdio/cd_types.h>
#include <sndfile.h>

#ifndef _LINUXRIP_H
#define _LINUXRIP_H

#define NUM_SECTORS 1000
/* Do NOT change NUM_TRIES, this will do you no good */
#define NUM_TRIES 2
#define MAX_SPEED 15

#define FRAMES_PER_SEC 75

#define MAXLEN 250

#endif /* _LINUXRIP_H */
