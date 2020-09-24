/* APPLE LOCAL begin mainline 2005-04-06 4071679 */
/* Darwin host-specific hook definitions.
   Copyright (C) 2003, 2004, 2005 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 2, or (at your
   option) any later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING.  If not, write to the
   Free Software Foundation, 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA.  */

extern void * darwin_gt_pch_get_address (size_t sz, int fd);
extern int darwin_gt_pch_use_address (void *addr, size_t sz, int fd, 
				      size_t off);

#undef HOST_HOOKS_GT_PCH_GET_ADDRESS
#define HOST_HOOKS_GT_PCH_GET_ADDRESS darwin_gt_pch_get_address
#undef HOST_HOOKS_GT_PCH_USE_ADDRESS
#define HOST_HOOKS_GT_PCH_USE_ADDRESS darwin_gt_pch_use_address
/* APPLE LOCAL end mainline 2005-04-06 4071679 */
