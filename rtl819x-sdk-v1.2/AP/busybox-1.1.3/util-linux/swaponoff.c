/* vi: set sw=4 ts=4: */
/*
 * Mini swapon/swapoff implementation for busybox
 *
 * Copyright (C) 1999-2004 by Erik Andersen <andersen@codepoet.org>
 *
 * Licensed under the GPL v2, see the file LICENSE in this tarball.
 */

#include <stdio.h>
#include <mntent.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/swap.h>

#include "busybox.h"

static int swap_enable_disable(const char *device)
{
	int status;
	struct stat st;

	xstat(device, &st);

	/* test for holes */
	if (S_ISREG(st.st_mode))
		if (st.st_blocks * 512 < st.st_size)
			bb_error_msg_and_die("swap file has holes");

	if (bb_applet_name[5] == 'n')
		status = swapon(device, 0);
	else
		status = swapoff(device);

	if (status != 0) {
		bb_perror_msg("%s", device);
		return 1;
	}

	return 0;
}

static int do_em_all(void)
{
	struct mntent *m;
	FILE *f;
	int err;

	f = setmntent("/etc/fstab", "r");
	if (f == NULL)
		bb_perror_msg_and_die("/etc/fstab");

	err = 0;
	while ((m = getmntent(f)) != NULL)
		if (strcmp(m->mnt_type, MNTTYPE_SWAP) == 0)
			err += swap_enable_disable(m->mnt_fsname);

	endmntent(f);

	return err;
}

#define DO_ALL    0x01

int swap_on_off_main(int argc, char **argv)
{
	int ret;

	if (argc == 1)
		bb_show_usage();

	ret = bb_getopt_ulflags(argc, argv, "a");
	if (ret & DO_ALL)
		return do_em_all();

	ret = 0;
	while (*++argv)
		ret += swap_enable_disable(*argv);
	return ret;
}
