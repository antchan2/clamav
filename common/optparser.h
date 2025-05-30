/*
 *  Copyright (C) 2013-2025 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 *  Copyright (C) 2008-2013 Sourcefire, Inc.
 *
 *  Author: Tomasz Kojm <tkojm@clamav.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 */

#ifndef __OPTPARSER_H
#define __OPTPARSER_H

/* don't share bits! */
// clang-format off
#define OPT_CLAMD           1
#define OPT_FRESHCLAM       2
#define OPT_MILTER          4
#define OPT_CLAMSCAN        8
#define OPT_CLAMDSCAN       16
#define OPT_SIGTOOL         32
#define OPT_CLAMCONF        64
#define OPT_CLAMDTOP        128
#define OPT_CLAMBC          256
#define OPT_CLAMONACC       512
#define OPT_DEPRECATED	    1024

#define CLOPT_TYPE_STRING   1    /* quoted/regular string */
#define CLOPT_TYPE_NUMBER   2    /* raw number */
#define CLOPT_TYPE_SIZE     3    /* number possibly followed by modifiers (K/k, M/m or G/g) */
#define CLOPT_TYPE_BOOL     4    /* boolean */
#define CLOPT_TYPE_SIZE64   5    /* 64-bit number possibly followed by modifiers (K/k, M/m or G/g) */

#ifdef _WIN32

    extern char _DATADIR[MAX_PATH];
    extern char _CONFDIR[MAX_PATH];
    extern char _CERTSDIR[MAX_PATH];
    extern char _CONFDIR_CLAMD[MAX_PATH];
    extern char _CONFDIR_FRESHCLAM[MAX_PATH];
    extern char _CONFDIR_MILTER[MAX_PATH];

    #define OPT_DATADIR           _DATADIR
    #define OPT_CONFDIR           _CONFDIR
    #define OPT_CERTSDIR          _CERTSDIR
    #define OPT_CONFDIR_CLAMD     _CONFDIR_CLAMD
    #define OPT_CONFDIR_FRESHCLAM _CONFDIR_FRESHCLAM
    #define OPT_CONFDIR_MILTER    _CONFDIR_MILTER

#else /* !_WIN32 */

    #define OPT_DATADIR           DATADIR
    #define OPT_CONFDIR           CONFDIR
    #define OPT_CERTSDIR          CERTSDIR
    #define OPT_CONFDIR_CLAMD     CONFDIR PATHSEP "clamd.conf"
    #define OPT_CONFDIR_FRESHCLAM CONFDIR PATHSEP "freshclam.conf"
    #define OPT_CONFDIR_MILTER    CONFDIR PATHSEP "clamav-milter.conf"

#endif
// clang-format on

struct optstruct {
    char *name;
    char *cmd;
    char *strarg;
    long long numarg;
    int enabled;
    int active;
    int flags;
    int idx;
    struct optstruct *nextarg;
    struct optstruct *next;

    char **filename; /* cmdline */
};

struct clam_option {
    const char *name;
    const char *longopt;
    char shortopt;
    int argtype;
    const char *regex;
    long long numarg;
    const char *strarg;
    int flags;
    int owner;
    const char *description;
    const char *suggested;
};

const struct optstruct *optget(const struct optstruct *opts, const char *name);

void optfree(struct optstruct *opts);

struct optstruct *optparse(const char *cfgfile, int argc, char **argv, int verbose, int toolmask, int ignore, struct optstruct *oldopts);
struct optstruct *optadditem(const char *name, const char *arg, int verbose, int toolmask, int ignore, struct optstruct *oldopts);

#endif
