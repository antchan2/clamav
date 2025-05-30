/*
 *  Copyright (C) 2013-2025 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 *  Copyright (C) 2007-2013 Sourcefire, Inc.
 *
 *  Authors: Tomasz Kojm
 *
 *  Summary: Code to parse Clamav CVD database format.
 *
 *  Acknowledgements: ClamAV untar code is based on a public domain minitar utility
 *                    by Charles G. Waldman.
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

#ifndef __CVD_H
#define __CVD_H

#include <stdio.h>
#include <zlib.h>
#include "clamav.h"

struct cli_dbio {
    gzFile gzs;
    FILE *fs;
    unsigned int size, bread;
    char *buf, *bufpt, *readpt;
    unsigned int usebuf, bufsize, readsize;
    unsigned int chkonly;
    void *hashctx;
};

typedef enum cvd_type {
    // unknown / uninitialized
    CVD_TYPE_UNKNOWN,
    // signed signature archive
    CVD_TYPE_CVD,
    // unsigned signature archive that was updated from a CVD or CUD
    CVD_TYPE_CLD,
    // unsigned signature archive
    CVD_TYPE_CUD,
} cvd_type;

cl_error_t cli_cvdload(struct cl_engine *engine, unsigned int *signo, unsigned int options, cvd_type dbtype, const char *filename, void *sign_verifier, unsigned int chkonly);
cl_error_t cli_cvdunpack_and_verify(const char *file, const char *dir, bool dont_verify, void *verifier);

#endif
