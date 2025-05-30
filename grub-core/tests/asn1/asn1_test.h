/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2020 IBM Corporation
 *  Copyright (C) 2024 Free Software Foundation, Inc.
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBTASN1_WRAP_TESTS_H
#define LIBTASN1_WRAP_TESTS_H

#include <libtasn1.h>
#include <grub/err.h>
#include <grub/mm.h>
#include <grub/misc.h>
#include <grub/types.h>

extern int test_CVE_2018_1000654 (void);

extern int test_object_id_encoding (void);

extern int test_object_id_decoding (void);

extern int test_octet_string (void);

extern int test_overflow (void);

extern int test_reproducers (void);

extern int test_simple (void);

extern int test_strings (void);

#endif
