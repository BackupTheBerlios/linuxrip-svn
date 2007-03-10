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

#include "linuxrip.h"
#include "cddb.h"
#include "flac.h"

/*
 * This class deals with ripping and storing it as wav.
 */

class cdio {
	public:
		cdio() {
			/* See if we can find a device with a loaded CD-DA in it. */
			ppsz_cd_drives = cdio_get_devices_with_cap(NULL, CDIO_FS_AUDIO, false);

			if (ppsz_cd_drives) {
				/* Found such a CD-ROM with a CD-DA loaded. Use the first drive in the list. */
				d = cdio_cddap_identify(*ppsz_cd_drives, 1, NULL);
			} else {
				printf("Unable find or access a CD-ROM drive with an audio CD in it.\n");
			}

			/* Don't need a list of CD's with CD-DA's any more. */
			if (ppsz_cd_drives) cdio_free_device_list(ppsz_cd_drives);

			/* We'll set for verbose paranoia messages. */
			if (d) cdio_cddap_verbose_set(d, CDDA_MESSAGE_PRINTIT, CDDA_MESSAGE_PRINTIT);

			if ( d && cdio_cddap_open(d) != 0 ) {
				printf("Unable to open disc.\n");
			}
		}

		~cdio() {
			cdio_cddap_close(d);
			cdio_paranoia_free(p);
			sf_close(sf);
		}

		bool RipTrack(track_t i_track, std::string filename) {
			InitWavWriter(filename);
			p = cdio_paranoia_init(d);

			/* Restrict speed */
			if (cdda_speed_set(d, MAX_SPEED) != DRIVER_OP_SUCCESS) {
				printf("Unable to set speed\n");
			}

			i_first_lsn = cdio_cddap_track_firstsector(d, i_track);

			if ( -1 == i_first_lsn ) {
				printf("Trouble getting starting LSN\n");
			} else {
				i_last_lsn = cdio_cddap_track_lastsector(d, i_track);

				printf("Reading track %d from LSN %ld to LSN %ld\n", i_track, 
				(long int) i_first_lsn, (long int) i_last_lsn);

				/* Set reading mode for full paranoia, but allow skipping sectors. */
				paranoia_modeset(p, PARANOIA_MODE_FULL^PARANOIA_MODE_NEVERSKIP);

				if (RipAttempt() == 1) {
					printf("Ripping failed\n");
				}
			}
		}

		int GetTracks() {
			return cdio_cddap_tracks(d);
		}

		lba_t GetLba(track_t i_track) {
			return cdio_lsn_to_lba(cdio_cddap_track_firstsector(d, i_track));
		}

		int GetLength() {
			return cdio_cddap_disc_lastsector(d)/FRAMES_PER_SEC;
		}
	private:
		/* cdio variables */
		cdrom_drive_t *d; /* Place to store handle given by cd-paranoia. */
		char **ppsz_cd_drives; /* List of all drives with a loaded CDDA in it. */
		cdrom_paranoia_t *p;
		lsn_t i_first_lsn, i_last_lsn, i_cursor;
		char *psz_err, *psz_mes;
		bool failed;
		uint num_samples, written_samples, counter;
		short readbuf[NUM_SECTORS*CDIO_CD_FRAMESIZE_RAW/2], readbuf2[NUM_SECTORS*CDIO_CD_FRAMESIZE_RAW/2];

		/* libsndfile variables */
		SNDFILE *sf;
		SF_INFO fileinfo;

		int RipAttempt() {
			for ( i_cursor = i_first_lsn; i_cursor <= i_last_lsn; ) {
				for ( int i = 0; i < NUM_TRIES; i++) {
					paranoia_seek(p, i_cursor, SEEK_SET);
					for ( int j = 0; j < NUM_SECTORS && j <= (i_last_lsn - i_cursor); j++ ) {
						/* read a sector */
						int16_t *p_readbuf = cdio_paranoia_read(p, NULL);
						int16_t *buf_pointer;
						psz_err = cdio_cddap_errors(d);
						psz_mes = cdio_cddap_messages(d);
						if (psz_mes || psz_err)
							printf("%s%s\n", psz_mes ? psz_mes: "", psz_err ? psz_err: "");
						if (psz_err) free(psz_err);
						if (psz_mes) free(psz_mes);
						if( !p_readbuf ) {
							printf("paranoia read error. Stopping.\n");
							break;
						} else {
							/* Transport data to actual buffer */
							if ( i == 0 ) {
								for ( buf_pointer = p_readbuf, counter = (CDIO_CD_FRAMESIZE_RAW/2)*j; buf_pointer != NULL && counter < (CDIO_CD_FRAMESIZE_RAW/2)*(j+1); buf_pointer++, counter++ ) {
									readbuf[counter] = *buf_pointer;
								}
							} else {
								for ( buf_pointer = p_readbuf, counter = (CDIO_CD_FRAMESIZE_RAW/2)*j; buf_pointer != NULL && counter < (CDIO_CD_FRAMESIZE_RAW/2)*(j+1); buf_pointer++, counter++ ) {
									readbuf2[counter] = *buf_pointer;
								}
							}
						}
						num_samples = counter;
					}
				}
				failed = false;
				for (int i = 0; i < num_samples ; i++) {
					if (readbuf[i] != readbuf2[i]) {
						failed = true;
					}
				}
				if (!failed) {
					i_cursor += NUM_SECTORS;
					written_samples = WriteToFile();
					if (written_samples != num_samples) return 1;
				}
			}
			return 0;
		}

		int InitWavWriter(std::string filename) {
			fileinfo.samplerate = 44100;
			fileinfo.channels = 2;
			fileinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
			char tmp[MAXLEN+4];
			sprintf(tmp, "%s.wav", filename.c_str());

			sf = sf_open(tmp, SFM_WRITE, &fileinfo);
			if (sf == NULL) return 1;
		}

		int WriteToFile() {
			return sf_write_short(sf, &(readbuf[0]), num_samples);
		}
};

int main() {
	cdio Ripper;
	flac Encoder;
	int tracks = Ripper.GetTracks();
	std::string filename[tracks+1];

	/* Prepare cddb information */
	int frames[tracks];
	for (int i=0; i<tracks; i++) {
		frames[i] = Ripper.GetLba(i+1);
	}

	cddb TrackInfo(&(frames[0]), tracks, Ripper.GetLength());

	/* Does nothing for the moment */
	//if (mkdir("test", 0755) == 0 ) {
		mkdir("test", 0755);
		chdir("test");
		for (int i=1; i<=tracks; i++) {
			char tmp[MAXLEN];
			sprintf(&(tmp[0]), "%02d - %s", i, TrackInfo.GetTitle(i-1).c_str());
			filename[i] = tmp;
			Ripper.RipTrack(i, tmp);
			Encoder.EncodeFile(tmp, tmp);
		}
	//}
	return 0;
}
