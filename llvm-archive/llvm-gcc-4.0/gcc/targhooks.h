/* Default target hook functions.
   Copyright (C) 2003, 2004, 2005 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

extern void default_external_libcall (rtx);

extern enum machine_mode default_cc_modes_compatible (enum machine_mode,
						      enum machine_mode);

extern bool default_return_in_memory (tree, tree);
/* APPLE LOCAL radar 4781080 */
extern bool default_objc_fpreturn_msgcall (tree, bool);

extern rtx default_expand_builtin_saveregs (void);
extern void default_setup_incoming_varargs (CUMULATIVE_ARGS *, enum machine_mode, tree, int *, int);
extern rtx default_builtin_setjmp_frame_value (void);
extern bool default_pretend_outgoing_varargs_named (CUMULATIVE_ARGS *);
/* APPLE LOCAL begin Altivec */
extern bool default_skip_vec_args (tree, int, int*);
/* APPLE LOCAL end Altivec */

extern enum machine_mode default_eh_return_filter_mode (void);
extern unsigned HOST_WIDE_INT default_shift_truncation_mask
  (enum machine_mode);
/* APPLE LOCAL begin mainline */
extern tree default_stack_protect_guard (void);
extern tree default_external_stack_protect_fail (void);
extern tree default_hidden_stack_protect_fail (void);
/* APPLE LOCAL end mainline */

extern tree default_cxx_guard_type (void);
extern tree default_cxx_get_cookie_size (tree);

extern bool hook_pass_by_reference_must_pass_in_stack
  (CUMULATIVE_ARGS *, enum machine_mode mode, tree, bool);
extern bool hook_callee_copies_named
  (CUMULATIVE_ARGS *ca, enum machine_mode, tree, bool);

extern void default_unwind_emit (FILE *, rtx);

extern bool default_scalar_mode_supported_p (enum machine_mode);

/* These are here, and not in hooks.[ch], because not all users of
   hooks.h include tm.h, and thus we don't have CUMULATIVE_ARGS.  */

extern bool hook_bool_CUMULATIVE_ARGS_false (CUMULATIVE_ARGS *);
extern bool hook_bool_CUMULATIVE_ARGS_true (CUMULATIVE_ARGS *);

extern bool hook_bool_CUMULATIVE_ARGS_mode_tree_bool_false
  (CUMULATIVE_ARGS *, enum machine_mode, tree, bool);
extern bool hook_bool_CUMULATIVE_ARGS_mode_tree_bool_true
  (CUMULATIVE_ARGS *, enum machine_mode, tree, bool);
extern int hook_int_CUMULATIVE_ARGS_mode_tree_bool_0
  (CUMULATIVE_ARGS *, enum machine_mode, tree, bool);
/* APPLE LOCAL begin mainline 2005-04-14 */
extern const char *hook_invalid_arg_for_unprototyped_fn
  (tree, tree, tree);
/* APPLE LOCAL end mainline 2005-04-14 */
/* APPLE LOCAL begin 4375453 */
extern bool vector_alignment_reachable (tree, bool);
extern bool default_vector_alignment_reachable (tree, bool);
/* APPLE LOCAL end 4375453 */
/* APPLE LOCAL begin mainline 2006-02-17 4356747 stack realign */
extern rtx default_internal_arg_pointer (void);
/* APPLE LOCAL end mainline 2006-02-17 4356747 stack realign */
