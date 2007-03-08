/*
 * Not much yet.
 */

#include <cdio/cdio.h>
#include <cdio/cdda.h>
#include <cdio/paranoia.h>
#include <cdio/cd_types.h>
#include <sndfile.h>
#include <cddb/cddb.h>

#define NUM_SECTORS 1000
/* Do NOT change NUM_TRIES, this will do you no good */
#define NUM_TRIES 2
#define MAX_SPEED 15

#define FRAMES_PER_SEC 75

#define MAXLEN 250
