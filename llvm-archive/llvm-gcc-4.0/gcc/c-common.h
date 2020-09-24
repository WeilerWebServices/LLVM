/* Definitions for c-common.c.
   Copyright (C) 1987, 1993, 1994, 1995, 1997, 1998,
   1999, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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

#ifndef GCC_C_COMMON_H
#define GCC_C_COMMON_H

#include "splay-tree.h"
#include "cpplib.h"
#include "ggc.h"

/* Usage of TREE_LANG_FLAG_?:
   0: TREE_NEGATED_INT (in INTEGER_CST).
      IDENTIFIER_MARKED (used by search routines).
      DECL_PRETTY_FUNCTION_P (in VAR_DECL)
      STMT_EXPR_NO_SCOPE (in STMT_EXPR)
   1: C_DECLARED_LABEL_FLAG (in LABEL_DECL)
      STMT_IS_FULL_EXPR_P (in _STMT)
      STATEMENT_LIST_STMT_EXPR (in STATEMENT_LIST)
   2: unused
   3: STATEMENT_LIST_HAS_LABEL (in STATEMENT_LIST)
   4: unused
*/

/* Reserved identifiers.  This is the union of all the keywords for C,
   C++, and Objective-C.  All the type modifiers have to be in one
   block at the beginning, because they are used as mask bits.  There
   are 27 type modifiers; if we add many more we will have to redesign
   the mask mechanism.  */

enum rid
{
  /* Modifiers: */
  /* C, in empirical order of frequency.  */
  RID_STATIC = 0,
  RID_UNSIGNED, RID_LONG,    RID_CONST, RID_EXTERN,
  RID_REGISTER, RID_TYPEDEF, RID_SHORT, RID_INLINE,
  RID_VOLATILE, RID_SIGNED,  RID_AUTO,  RID_RESTRICT,

  /* C extensions */
  RID_COMPLEX, RID_THREAD,
  /* APPLE LOCAL private extern */
  RID_PRIVATE_EXTERN,

  /* C++ */
  RID_FRIEND, RID_VIRTUAL, RID_EXPLICIT, RID_EXPORT, RID_MUTABLE,

  /* ObjC */
  RID_IN, RID_OUT, RID_INOUT, RID_BYCOPY, RID_BYREF, RID_ONEWAY,

  /* C */
  RID_INT,     RID_CHAR,   RID_FLOAT,    RID_DOUBLE, RID_VOID,
  RID_ENUM,    RID_STRUCT, RID_UNION,    RID_IF,     RID_ELSE,
  RID_WHILE,   RID_DO,     RID_FOR,      RID_SWITCH, RID_CASE,
  RID_DEFAULT, RID_BREAK,  RID_CONTINUE, RID_RETURN, RID_GOTO,
  RID_SIZEOF,

  /* C extensions */
  RID_ASM,       RID_TYPEOF,   RID_ALIGNOF,  RID_ATTRIBUTE,  RID_VA_ARG,
  RID_EXTENSION, RID_IMAGPART, RID_REALPART, RID_LABEL,      RID_CHOOSE_EXPR,
  RID_TYPES_COMPATIBLE_P,

  /* Too many ways of getting the name of a function as a string */
  RID_FUNCTION_NAME, RID_PRETTY_FUNCTION_NAME, RID_C99_FUNCTION_NAME,

  /* C++ */
  RID_BOOL,     RID_WCHAR,    RID_CLASS,
  RID_PUBLIC,   RID_PRIVATE,  RID_PROTECTED,
  RID_TEMPLATE, RID_NULL,     RID_CATCH,
  RID_DELETE,   RID_FALSE,    RID_NAMESPACE,
  RID_NEW,      RID_OFFSETOF, RID_OPERATOR, 
  RID_THIS,     RID_THROW,    RID_TRUE,     
  RID_TRY,      RID_TYPENAME, RID_TYPEID,   
  RID_USING,

  /* casts */
  RID_CONSTCAST, RID_DYNCAST, RID_REINTCAST, RID_STATCAST,

  /* Objective-C */
  RID_AT_ENCODE,   RID_AT_END,
  RID_AT_CLASS,    RID_AT_ALIAS,     RID_AT_DEFS,
  /* APPLE LOCAL radar 4564694 */
  RID_AT_PACKAGE,  RID_AT_PRIVATE,  RID_AT_PROTECTED, RID_AT_PUBLIC,
  RID_AT_PROTOCOL, RID_AT_SELECTOR,  
  RID_AT_THROW,	   RID_AT_TRY,       RID_AT_CATCH,
  RID_AT_FINALLY,  RID_AT_SYNCHRONIZED,
  RID_AT_INTERFACE,
  /* APPLE LOCAL C* language */
  RID_AT_OPTIONAL, RID_AT_REQUIRED,
  /* APPLE LOCAL C* property (Radar 4436866) */
  RID_AT_PROPERTY,
  /* APPLE LOCAL begin objc new property */
  RID_AT_SYNTHESIZE,
  RID_AT_DYNAMIC,
  /* APPLE LOCAL end objc new property */
  RID_AT_IMPLEMENTATION,
  /* APPLE LOCAL C* property (Radar 4436866, 4591909, 4621020) */
  RID_READONLY, RID_DYNAMIC, RID_GETTER, RID_SETTER, RID_WEAK, RID_IVAR,
  /* APPLE LOCAL objc new property */
  RID_READWRITE, RID_ASSIGN, RID_RETAIN, RID_COPY,
  /* APPLE LOCAL radar 4947014 - objc atomic property */
  RID_NONATOMIC,

  RID_MAX,

  /* APPLE LOCAL begin C* property (Radar 4436866) */
  RID_FIRST_PATTR = RID_READONLY,
  RID_LAST_PATTR = RID_IVAR,
  /* APPLE LOCAL end C* property (Radar 4436866) */
  RID_FIRST_MODIFIER = RID_STATIC,
  RID_LAST_MODIFIER = RID_ONEWAY,

  RID_FIRST_AT = RID_AT_ENCODE,
  RID_LAST_AT = RID_AT_IMPLEMENTATION,
  RID_FIRST_PQ = RID_IN,
  RID_LAST_PQ = RID_ONEWAY
};

/* APPLE LOCAL begin objc new property */
#define OBJC_IS_NEW_PATTR_KEYWORD(rid) \
  (((unsigned int) (rid) == RID_SETTER    || \
    (unsigned int) (rid) == RID_GETTER    || \
    (unsigned int) (rid) == RID_READONLY  || \
    (unsigned int) (rid) == RID_READWRITE || \
    (unsigned int) (rid) == RID_ASSIGN    || \
    (unsigned int) (rid) == RID_RETAIN    || \
    /* APPLE LOCAL begin radar 4947014 - objc atomic property */  \
    (unsigned int) (rid) == RID_COPY	  || \
    (unsigned int) (rid) == RID_NONATOMIC))
    /* APPLE LOCAL end radar 4947014 - objc atomic property */  \
/* APPLE LOCAL end objc new property */

/* APPLE LOCAL begin C* property (Radar 4436866) */
#define OBJC_IS_PATTR_KEYWORD(rid) \
  ((unsigned int) (rid) >= (unsigned int) RID_FIRST_PATTR && \
  (unsigned int) (rid) <= (unsigned int) RID_LAST_PATTR)
/* APPLE LOCAL end C* property (Radar 4436866) */

#define OBJC_IS_AT_KEYWORD(rid) \
  ((unsigned int) (rid) >= (unsigned int) RID_FIRST_AT && \
   (unsigned int) (rid) <= (unsigned int) RID_LAST_AT)

/* APPLE LOCAL begin objc new property */
#define OBJC_IS_NEW_AT_KEYWORD(rid) \
  (((OBJC_IS_AT_KEYWORD(rid) || \
    (unsigned int) (rid) == RID_AT_SYNTHESIZE || \
    (unsigned int) (rid) == RID_DYNAMIC)))
/* APPLE LOCAL end objc new property */

#define OBJC_IS_PQ_KEYWORD(rid) \
  ((unsigned int) (rid) >= (unsigned int) RID_FIRST_PQ && \
   (unsigned int) (rid) <= (unsigned int) RID_LAST_PQ)

/* The elements of `ridpointers' are identifier nodes for the reserved
   type names and storage classes.  It is indexed by a RID_... value.  */
extern GTY ((length ("(int) RID_MAX"))) tree *ridpointers;

/* Standard named or nameless data types of the C compiler.  */

enum c_tree_index
{
    CTI_WCHAR_TYPE,
    CTI_SIGNED_WCHAR_TYPE,
    CTI_UNSIGNED_WCHAR_TYPE,
    CTI_WINT_TYPE,
    CTI_SIGNED_SIZE_TYPE, /* For format checking only.  */
    CTI_UNSIGNED_PTRDIFF_TYPE, /* For format checking only.  */
    CTI_INTMAX_TYPE,
    CTI_UINTMAX_TYPE,
    CTI_WIDEST_INT_LIT_TYPE,
    CTI_WIDEST_UINT_LIT_TYPE,

    CTI_CHAR_ARRAY_TYPE,
    /* APPLE LOCAL pascal strings */
    CTI_PASCAL_STRING_TYPE,    /* for Pascal strings */
    CTI_WCHAR_ARRAY_TYPE,
    CTI_INT_ARRAY_TYPE,
    CTI_STRING_TYPE,
    CTI_CONST_STRING_TYPE,

    /* Type for boolean expressions (bool in C++, int in C).  */
    CTI_TRUTHVALUE_TYPE,
    CTI_TRUTHVALUE_TRUE,
    CTI_TRUTHVALUE_FALSE,

    CTI_DEFAULT_FUNCTION_TYPE,

    /* These are not types, but we have to look them up all the time.  */
    CTI_FUNCTION_NAME_DECL,
    CTI_PRETTY_FUNCTION_NAME_DECL,
    CTI_C99_FUNCTION_NAME_DECL,
    CTI_SAVED_FUNCTION_NAME_DECLS,
    
    CTI_VOID_ZERO,

    CTI_NULL,

    CTI_MAX
};

#define C_RID_CODE(id)	(((struct c_common_identifier *) (id))->node.rid_code)

/* Identifier part common to the C front ends.  Inherits from
   tree_identifier, despite appearances.  */
struct c_common_identifier GTY(())
{
  struct tree_common common;
  struct cpp_hashnode node;
};

#define wchar_type_node			c_global_trees[CTI_WCHAR_TYPE]
#define signed_wchar_type_node		c_global_trees[CTI_SIGNED_WCHAR_TYPE]
#define unsigned_wchar_type_node	c_global_trees[CTI_UNSIGNED_WCHAR_TYPE]
#define wint_type_node			c_global_trees[CTI_WINT_TYPE]
#define signed_size_type_node		c_global_trees[CTI_SIGNED_SIZE_TYPE]
#define unsigned_ptrdiff_type_node	c_global_trees[CTI_UNSIGNED_PTRDIFF_TYPE]
#define intmax_type_node		c_global_trees[CTI_INTMAX_TYPE]
#define uintmax_type_node		c_global_trees[CTI_UINTMAX_TYPE]
#define widest_integer_literal_type_node c_global_trees[CTI_WIDEST_INT_LIT_TYPE]
#define widest_unsigned_literal_type_node c_global_trees[CTI_WIDEST_UINT_LIT_TYPE]

#define truthvalue_type_node		c_global_trees[CTI_TRUTHVALUE_TYPE]
#define truthvalue_true_node		c_global_trees[CTI_TRUTHVALUE_TRUE]
#define truthvalue_false_node		c_global_trees[CTI_TRUTHVALUE_FALSE]

#define char_array_type_node		c_global_trees[CTI_CHAR_ARRAY_TYPE]
/* APPLE LOCAL pascal strings */
#define pascal_string_type_node 	c_global_trees[CTI_PASCAL_STRING_TYPE]
#define wchar_array_type_node		c_global_trees[CTI_WCHAR_ARRAY_TYPE]
#define int_array_type_node		c_global_trees[CTI_INT_ARRAY_TYPE]
#define string_type_node		c_global_trees[CTI_STRING_TYPE]
#define const_string_type_node		c_global_trees[CTI_CONST_STRING_TYPE]

#define default_function_type		c_global_trees[CTI_DEFAULT_FUNCTION_TYPE]

#define function_name_decl_node		c_global_trees[CTI_FUNCTION_NAME_DECL]
#define pretty_function_name_decl_node	c_global_trees[CTI_PRETTY_FUNCTION_NAME_DECL]
#define c99_function_name_decl_node		c_global_trees[CTI_C99_FUNCTION_NAME_DECL]
#define saved_function_name_decls	c_global_trees[CTI_SAVED_FUNCTION_NAME_DECLS]

/* A node for `((void) 0)'.  */
#define void_zero_node                  c_global_trees[CTI_VOID_ZERO]

/* The node for C++ `__null'.  */
#define null_node                       c_global_trees[CTI_NULL]

extern GTY(()) tree c_global_trees[CTI_MAX];

/* In a RECORD_TYPE, a sorted array of the fields of the type, not a
   tree for size reasons.  */
struct sorted_fields_type GTY(())
{
  int len;
  tree GTY((length ("%h.len"))) elts[1];
};

/* Mark which labels are explicitly declared.
   These may be shadowed, and may be referenced from nested functions.  */
#define C_DECLARED_LABEL_FLAG(label) TREE_LANG_FLAG_1 (label)

/* Flag strings given by __FUNCTION__ and __PRETTY_FUNCTION__ for a
   warning if they undergo concatenation.  */
#define C_ARTIFICIAL_STRING_P(NODE) TREE_LANG_FLAG_0 (NODE)

typedef enum c_language_kind
{
  clk_c		= 0,		/* C90, C94 or C99 */
  clk_objc	= 1,		/* clk_c with ObjC features.  */
  clk_cxx	= 2,		/* ANSI/ISO C++ */
  clk_objcxx	= 3		/* clk_cxx with ObjC features.  */
}
c_language_kind;

/* To test for a specific language use c_language, defined by each
   front end.  For "ObjC features" or "not C++" use the macros.  */
extern c_language_kind c_language;

#define c_dialect_cxx()		(c_language & clk_cxx)
#define c_dialect_objc()	(c_language & clk_objc)

/* Information about a statement tree.  */

struct stmt_tree_s GTY(()) {
  /* The current statement list being collected.  */
  tree x_cur_stmt_list;

  /* In C++, Nonzero if we should treat statements as full
     expressions.  In particular, this variable is no-zero if at the
     end of a statement we should destroy any temporaries created
     during that statement.  Similarly, if, at the end of a block, we
     should destroy any local variables in this block.  Normally, this
     variable is nonzero, since those are the normal semantics of
     C++.

     However, in order to represent aggregate initialization code as
     tree structure, we use statement-expressions.  The statements
     within the statement expression should not result in cleanups
     being run until the entire enclosing statement is complete.

     This flag has no effect in C.  */
  int stmts_are_full_exprs_p;
};

typedef struct stmt_tree_s *stmt_tree;

/* Global state pertinent to the current function.  Some C dialects
   extend this structure with additional fields.  */

struct c_language_function GTY(()) {
  /* While we are parsing the function, this contains information
     about the statement-tree that we are building.  */
  struct stmt_tree_s x_stmt_tree;
};

/* When building a statement-tree, this is the current statement list
   being collected.  It's TREE_CHAIN is a back-pointer to the previous
   statement list.  */

#define cur_stmt_list (current_stmt_tree ()->x_cur_stmt_list)

/* Language-specific hooks.  */

/* Callback that determines if it's ok for a function to have no
   noreturn attribute.  */
extern int (*lang_missing_noreturn_ok_p) (tree);

/* If non-NULL, this function is called after a precompile header file
   is loaded.  */
extern void (*lang_post_pch_load) (void);

extern void push_file_scope (void);
extern void pop_file_scope (void);
extern int yyparse (void);
extern stmt_tree current_stmt_tree (void);
extern tree push_stmt_list (void);
extern tree pop_stmt_list (tree);
extern tree add_stmt (tree);
extern void push_cleanup (tree, tree, bool);

extern int c_expand_decl (tree);

extern int field_decl_cmp (const void *, const void *);
extern void resort_sorted_fields (void *, void *, gt_pointer_operator, 
                                  void *);
extern bool has_c_linkage (tree decl);

/* Switches common to the C front ends.  */

/* Nonzero if prepreprocessing only.  */

extern int flag_preprocess_only;

/* Zero means that faster, ...NonNil variants of objc_msgSend...
   calls will be used in ObjC; passing nil receivers to such calls
   will most likely result in crashes.  */
extern int flag_nil_receivers;

/* Nonzero means that we will allow new ObjC exception syntax (@throw,
   @try, etc.) in source code.  */
extern int flag_objc_exceptions;

/* Nonzero means that we generate NeXT setjmp based exceptions.  */
extern int flag_objc_sjlj_exceptions;

/* Nonzero means that code generation will be altered to support
   "zero-link" execution.  This currently affects ObjC only, but may
   affect other languages in the future.  */
extern int flag_zero_link;

/* Nonzero means emit an '__OBJC, __image_info' for the current translation
   unit.  It will inform the ObjC runtime that class definition(s) herein
   contained are to replace one(s) previously loaded.  */
extern int flag_replace_objc_classes;

/* Nonzero means don't output line number information.  */

extern char flag_no_line_commands;

/* Nonzero causes -E output not to be done, but directives such as
   #define that have side effects are still obeyed.  */

extern char flag_no_output;

/* Nonzero means dump macros in some fashion; contains the 'D', 'M' or
   'N' of the command line switch.  */

extern char flag_dump_macros;

/* Nonzero means pass #include lines through to the output.  */

extern char flag_dump_includes;

/* Nonzero means process PCH files while preprocessing.  */

extern bool flag_pch_preprocess;

/* The file name to which we should write a precompiled header, or
   NULL if no header will be written in this compile.  */

extern const char *pch_file;

/* Nonzero if an ISO standard was selected.  It rejects macros in the
   user's namespace.  */

extern int flag_iso;

/* Nonzero if -undef was given.  It suppresses target built-in macros
   and assertions.  */

extern int flag_undef;

/* Nonzero means don't recognize the non-ANSI builtin functions.  */

extern int flag_no_builtin;

/* Nonzero means don't recognize the non-ANSI builtin functions.
   -ansi sets this.  */

extern int flag_no_nonansi_builtin;

/* Nonzero means give `double' the same size as `float'.  */

extern int flag_short_double;

/* Nonzero means give `wchar_t' the same size as `short'.  */

extern int flag_short_wchar;

/* APPLE LOCAL begin lvalue cast */
/* Nonzero means allow assignment, increment or decrement of casts of
   lvalues (e.g., '((foo *)p)++') if both the lvalue and its cast are
   of POD type with identical size and alignment.  */
extern int flag_lvalue_cast_assign;
/* APPLE LOCAL end lvalue cast */

/* Nonzero means allow Microsoft extensions without warnings or errors.  */
extern int flag_ms_extensions;

/* Nonzero means don't recognize the keyword `asm'.  */

extern int flag_no_asm;

/* APPLE LOCAL begin CW asm blocks */
#include "config/asm.h"
/* APPLE LOCAL end CW asm blocks */

/* Nonzero means give string constants the type `const char *', as mandated
   by the standard.  */

extern int flag_const_strings;

/* Nonzero means to treat bitfields as signed unless they say `unsigned'.  */

extern int flag_signed_bitfields;

/* Nonzero means warn about deprecated conversion from string constant to
   `char *'.  */

extern int warn_write_strings;

/* Warn about #pragma directives that are not recognized.  */      

extern int warn_unknown_pragmas; /* Tri state variable.  */  

/* Warn about format/argument anomalies in calls to formatted I/O functions
   (*printf, *scanf, strftime, strfmon, etc.).  */

extern int warn_format;

/* APPLE LOCAL begin disable_typechecking_for_spec_flag */
/* This makes type conflicts a warning, instead of an error,
   to work around some problems with SPEC.  */

extern int disable_typechecking_for_spec_flag;
/* APPLE LOCAL end disable_typechecking_for_spec_flag */

/* C/ObjC language option variables.  */


/* Nonzero means allow type mismatches in conditional expressions;
   just make their values `void'.  */

extern int flag_cond_mismatch;

/* Nonzero means enable C89 Amendment 1 features.  */

extern int flag_isoc94;

/* Nonzero means use the ISO C99 dialect of C.  */

extern int flag_isoc99;

/* Nonzero means that we have builtin functions, and main is an int.  */

extern int flag_hosted;

/* Warn if main is suspicious.  */

extern int warn_main;


/* ObjC language option variables.  */


/* Open and close the file for outputting class declarations, if
   requested (ObjC).  */

extern int flag_gen_declaration;

/* Generate code for GNU or NeXT runtime environment.  */

extern int flag_next_runtime;

/* APPLE LOCAL begin mainline */
/* Generate special '- .cxx_construct' and '- .cxx_destruct' methods
   to initialize any non-POD ivars in ObjC++ classes.  */

extern int flag_objc_call_cxx_cdtors;
/* APPLE LOCAL end mainline */
/* APPLE LOCAL begin radar 2848255 */
extern int flag_objc_zerocost_exceptions;
bool objc2_valid_objc_catch_type (tree);
tree objc2_build_throw_call (tree);
/* APPLE LOCAL end radar 2848255 */

/* Tells the compiler that this is a special run.  Do not perform any
   compiling, instead we are to test some platform dependent features
   and output a C header file with appropriate definitions.  */

extern int print_struct_values;

/* ???.  Undocumented.  */

extern const char *constant_string_class_name;


/* C++ language option variables.  */


/* Nonzero means don't recognize any extension keywords.  */

extern int flag_no_gnu_keywords;

/* Nonzero means do emit exported implementations of functions even if
   they can be inlined.  */

extern int flag_implement_inlines;

/* Nonzero means that implicit instantiations will be emitted if needed.  */

extern int flag_implicit_templates;

/* Nonzero means that implicit instantiations of inline templates will be
   emitted if needed, even if instantiations of non-inline templates
   aren't.  */

extern int flag_implicit_inline_templates;

/* Nonzero means generate separate instantiation control files and
   juggle them at link time.  */

extern int flag_use_repository;

/* Nonzero if we want to issue diagnostics that the standard says are not
   required.  */

extern int flag_optional_diags;

/* Nonzero means we should attempt to elide constructors when possible.  */

extern int flag_elide_constructors;

/* Nonzero means that member functions defined in class scope are
   inline by default.  */

extern int flag_default_inline;

/* Controls whether compiler generates 'type descriptor' that give
   run-time type information.  */

extern int flag_rtti;

/* Nonzero if we want to conserve space in the .o files.  We do this
   by putting uninitialized data and runtime initialized data into
   .common instead of .data at the expense of not flagging multiple
   definitions.  */

extern int flag_conserve_space;

/* Nonzero if we want to obey access control semantics.  */

extern int flag_access_control;

/* Nonzero if we want to check the return value of new and avoid calling
   constructors if it is a null pointer.  */

extern int flag_check_new;

/* Nonzero if we want the new ISO rules for pushing a new scope for `for'
   initialization variables.
   0: Old rules, set by -fno-for-scope.
   2: New ISO rules, set by -ffor-scope.
   1: Try to implement new ISO rules, but with backup compatibility
   (and warnings).  This is the default, for now.  */

extern int flag_new_for_scope;

/* Nonzero if we want to emit defined symbols with common-like linkage as
   weak symbols where possible, in order to conform to C++ semantics.
   Otherwise, emit them as local symbols.  */

extern int flag_weak;

/* 0 means we want the preprocessor to not emit line directives for
   the current working directory.  1 means we want it to do it.  -1
   means we should decide depending on whether debugging information
   is being emitted or not.  */

extern int flag_working_directory;

/* Nonzero to use __cxa_atexit, rather than atexit, to register
   destructors for local statics and global objects.  */

extern int flag_use_cxa_atexit;

/* APPLE LOCAL begin mainline 2006-02-24 4086777 */
/* Nonzero to use __cxa_get_exception_ptr in the C++ exception-handling
   logic.  */

extern int flag_use_cxa_get_exception_ptr;

/* APPLE LOCAL end mainline 2006-02-24 4086777 */
/* Nonzero means make the default pedwarns warnings instead of errors.
   The value of this flag is ignored if -pedantic is specified.  */

extern int flag_permissive;

/* Nonzero means to implement standard semantics for exception
   specifications, calling unexpected if an exception is thrown that
   doesn't match the specification.  Zero means to treat them as
   assertions and optimize accordingly, but not check them.  */

extern int flag_enforce_eh_specs;

/* APPLE LOCAL begin structor thunks */
/* Nonzero if we prefer to clone con/de/structors.
   Alternative is to gen multiple tiny thunk-esque things that
   call/jump to a unified con/de/structor.  This is a classic
   size/speed tradeoff.  */
extern int flag_clone_structors;
/* APPLE LOCAL end structor thunks */

/* APPLE LOCAL begin private extern  Radar 2872481 --ilr */
/* Nonzero if -fpreprocessed specified.  This is needed by init_reswords()
   so that it can make __private_extern__ have the same rid code as extern
   when -fpreprocessed is specified.  Normally there is a -D on the command
   line for this.  But if -fpreprocessed was specified then macros aren't
   expanded.  So we fake the token value out using the rid code.  */
extern int flag_preprocessed;
/* APPLE LOCAL end private extern  Radar 2872481 --ilr */

/* Nonzero (the default) means to generate thread-safe code for
   initializing local statics.  */

extern int flag_threadsafe_statics;

/* Nonzero means warn about implicit declarations.  */

extern int warn_implicit;

/* Warn about using __null (as NULL in C++) as sentinel.  For code compiled
   with GCC this doesn't matter as __null is guaranteed to have the right
   size.  */

extern int warn_strict_null_sentinel;

/* Maximum template instantiation depth.  This limit is rather
   arbitrary, but it exists to limit the time it takes to notice
   infinite template instantiations.  */

extern int max_tinst_depth;

/* Nonzero means the expression being parsed will never be evaluated.
   This is a count, since unevaluated expressions can nest.  */

extern int skip_evaluation;

/* C types are partitioned into three subsets: object, function, and
   incomplete types.  */
#define C_TYPE_OBJECT_P(type) \
  (TREE_CODE (type) != FUNCTION_TYPE && TYPE_SIZE (type))

#define C_TYPE_INCOMPLETE_P(type) \
  (TREE_CODE (type) != FUNCTION_TYPE && TYPE_SIZE (type) == 0)

#define C_TYPE_FUNCTION_P(type) \
  (TREE_CODE (type) == FUNCTION_TYPE)

/* For convenience we define a single macro to identify the class of
   object or incomplete types.  */
#define C_TYPE_OBJECT_OR_INCOMPLETE_P(type) \
  (!C_TYPE_FUNCTION_P (type))

/* Attribute table common to the C front ends.  */
extern const struct attribute_spec c_common_attribute_table[];
extern const struct attribute_spec c_common_format_attribute_table[];

/* Pointer to function to lazily generate the VAR_DECL for __FUNCTION__ etc.
   ID is the identifier to use, NAME is the string.
   TYPE_DEP indicates whether it depends on type of the function or not
   (i.e. __PRETTY_FUNCTION__).  */

extern tree (*make_fname_decl) (tree, int);

extern tree identifier_global_value (tree);
extern void record_builtin_type (enum rid, const char *, tree);
extern tree build_void_list_node (void);
extern void start_fname_decls (void);
extern void finish_fname_decls (void);
extern const char *fname_as_string (int);
extern tree fname_decl (unsigned, tree);

extern void check_function_arguments (tree, tree);
extern void check_function_arguments_recurse (void (*)
					      (void *, tree,
					       unsigned HOST_WIDE_INT),
					      void *, tree,
					      unsigned HOST_WIDE_INT);
extern void check_function_format (tree, tree);
extern void set_Wformat (int);
extern tree handle_format_attribute (tree *, tree, tree, int, bool *);
extern tree handle_format_arg_attribute (tree *, tree, tree, int, bool *);
extern int c_common_handle_option (size_t code, const char *arg, int value);
extern bool c_common_missing_argument (const char *opt, size_t code);
extern tree c_common_type_for_mode (enum machine_mode, int);
extern tree c_common_type_for_size (unsigned int, int);
extern tree c_common_unsigned_type (tree);
extern tree c_common_signed_type (tree);
extern tree c_common_signed_or_unsigned_type (int, tree);
extern tree c_common_truthvalue_conversion (tree);
extern void c_apply_type_quals_to_decl (int, tree);
extern tree c_sizeof_or_alignof_type (tree, enum tree_code, int);
extern tree c_alignof_expr (tree);
/* Print an error message for invalid operands to arith operation CODE.
   NOP_EXPR is used as a special case (see truthvalue_conversion).  */
extern void binary_op_error (enum tree_code);
extern tree fix_string_type (tree);
struct varray_head_tag;
extern void constant_expression_warning (tree);
extern tree convert_and_check (tree, tree);
extern void overflow_warning (tree);
extern void unsigned_conversion_warning (tree, tree);
extern bool c_determine_visibility (tree);

#define c_sizeof(T)  c_sizeof_or_alignof_type (T, SIZEOF_EXPR, 1)
#define c_alignof(T) c_sizeof_or_alignof_type (T, ALIGNOF_EXPR, 1)

/* Subroutine of build_binary_op, used for comparison operations.
   See if the operands have both been converted from subword integer types
   and, if so, perhaps change them both back to their original type.  */
extern tree shorten_compare (tree *, tree *, tree *, enum tree_code *);

extern tree pointer_int_sum (enum tree_code, tree, tree);
extern unsigned int min_precision (tree, int);

/* Add qualifiers to a type, in the fashion for C.  */
extern tree c_build_qualified_type (tree, int);

/* Build tree nodes and builtin functions common to both C and C++ language
   frontends.  */
extern void c_common_nodes_and_builtins (void);

extern void set_builtin_user_assembler_name (tree decl, const char *asmspec);

extern void disable_builtin_function (const char *);

extern tree build_va_arg (tree, tree);

extern unsigned int c_common_init_options (unsigned int, const char **);
extern bool c_common_post_options (const char **);
extern bool c_common_init (void);
extern void c_common_finish (void);
extern void c_common_parse_file (int);
extern HOST_WIDE_INT c_common_get_alias_set (tree);
extern void c_register_builtin_type (tree, const char*);
extern bool c_promoting_integer_type_p (tree);
extern int self_promoting_args_p (tree);
extern tree strip_array_types (tree);
extern tree strip_pointer_operator (tree);
extern HOST_WIDE_INT c_common_to_target_charset (HOST_WIDE_INT);

/* APPLE LOCAL begin IMA built-in decl merging fix (radar 3645899) */
extern bool builtin_function_disabled_p (const char *);
/* APPLE LOCAL end */
/* APPLE LOCAL define this sensibly in all languages */
extern bool c_flag_no_builtin (void);

/* This is the basic parsing function.  */
extern void c_parse_file (void);
/* This is misnamed, it actually performs end-of-compilation processing.  */
extern void finish_file	(void);


/* These macros provide convenient access to the various _STMT nodes.  */

/* Nonzero if this statement should be considered a full-expression,
   i.e., if temporaries created during this statement should have
   their destructors run at the end of this statement.  (In C, this
   will always be false, since there are no destructors.)  */
#define STMT_IS_FULL_EXPR_P(NODE) TREE_LANG_FLAG_1 ((NODE))

/* Nonzero if a given STATEMENT_LIST represents the outermost binding
   if a statement expression.  */
#define STATEMENT_LIST_STMT_EXPR(NODE) \
  TREE_LANG_FLAG_1 (STATEMENT_LIST_CHECK (NODE))

/* Nonzero if a label has been added to the statement list.  */
#define STATEMENT_LIST_HAS_LABEL(NODE) \
  TREE_LANG_FLAG_3 (STATEMENT_LIST_CHECK (NODE))

/* WHILE_STMT accessors. These give access to the condition of the
   while statement and the body of the while statement, respectively.  */
#define WHILE_COND(NODE)        TREE_OPERAND (WHILE_STMT_CHECK (NODE), 0)
#define WHILE_BODY(NODE)        TREE_OPERAND (WHILE_STMT_CHECK (NODE), 1)

/* DO_STMT accessors. These give access to the condition of the do
   statement and the body of the do statement, respectively.  */
#define DO_COND(NODE)           TREE_OPERAND (DO_STMT_CHECK (NODE), 0)
#define DO_BODY(NODE)           TREE_OPERAND (DO_STMT_CHECK (NODE), 1)

/* APPLE LOCAL begin C* language */
/* Used as a flag to indicate synthesized inner do-while loop of a 
   foreach statement.  Used for generation of break/continue statement 
   of the loop. */
#define DO_FOREACH(NODE)           TREE_OPERAND (DO_STMT_CHECK (NODE), 2)
/* APPLE LOCAL end C* language */

/* EXPR_STMT accessor. This gives the expression associated with an
   expression statement.  */
#define EXPR_STMT_EXPR(NODE)    TREE_OPERAND (EXPR_STMT_CHECK (NODE), 0)

/* FOR_STMT accessors. These give access to the init statement,
   condition, update expression, and body of the for statement,
   respectively.  */
#define FOR_INIT_STMT(NODE)     TREE_OPERAND (FOR_STMT_CHECK (NODE), 0)
#define FOR_COND(NODE)          TREE_OPERAND (FOR_STMT_CHECK (NODE), 1)
#define FOR_EXPR(NODE)          TREE_OPERAND (FOR_STMT_CHECK (NODE), 2)
#define FOR_BODY(NODE)          TREE_OPERAND (FOR_STMT_CHECK (NODE), 3)

#define SWITCH_STMT_COND(NODE)	TREE_OPERAND (SWITCH_STMT_CHECK (NODE), 0)
#define SWITCH_STMT_BODY(NODE)	TREE_OPERAND (SWITCH_STMT_CHECK (NODE), 1)
#define SWITCH_STMT_TYPE(NODE)	TREE_OPERAND (SWITCH_STMT_CHECK (NODE), 2)

/* STMT_EXPR accessor.  */
#define STMT_EXPR_STMT(NODE)    TREE_OPERAND (STMT_EXPR_CHECK (NODE), 0)

/* Nonzero if this statement-expression does not have an associated scope.  */
#define STMT_EXPR_NO_SCOPE(NODE) \
   TREE_LANG_FLAG_0 (STMT_EXPR_CHECK (NODE))

/* COMPOUND_LITERAL_EXPR accessors.  */
#define COMPOUND_LITERAL_EXPR_DECL_STMT(NODE)		\
  TREE_OPERAND (COMPOUND_LITERAL_EXPR_CHECK (NODE), 0)
#define COMPOUND_LITERAL_EXPR_DECL(NODE)			\
  DECL_EXPR_DECL (COMPOUND_LITERAL_EXPR_DECL_STMT (NODE))

#define DEFTREECODE(SYM, NAME, TYPE, LENGTH) SYM,

enum c_tree_code {
  C_DUMMY_TREE_CODE = LAST_AND_UNUSED_TREE_CODE,
#include "c-common.def"
  LAST_C_TREE_CODE
};

#undef DEFTREECODE

#define c_common_stmt_codes				\
   EXPR_STMT,		FOR_STMT,			\
   WHILE_STMT,		DO_STMT,			\
   BREAK_STMT,		CONTINUE_STMT,	SWITCH_STMT

/* TRUE if a code represents a statement.  The front end init
   langhook should take care of initialization of this array.  */
extern bool statement_code_p[MAX_TREE_CODES];

#define STATEMENT_CODE_P(CODE) statement_code_p[(int) (CODE)]

#define INIT_STATEMENT_CODES(STMT_CODES)			\
  do {								\
    unsigned int i;						\
    memset (&statement_code_p, 0, sizeof (statement_code_p));	\
    for (i = 0; i < ARRAY_SIZE (STMT_CODES); i++)		\
      statement_code_p[STMT_CODES[i]] = true;			\
  } while (0)

extern int stmts_are_full_exprs_p (void);
extern int anon_aggr_type_p (tree);

/* For a VAR_DECL that is an anonymous union, these are the various
   sub-variables that make up the anonymous union.  */
#define DECL_ANON_UNION_ELEMS(NODE) DECL_ARGUMENTS ((NODE))

/* In a FIELD_DECL, nonzero if the decl was originally a bitfield.  */
#define DECL_C_BIT_FIELD(NODE) \
  (DECL_LANG_FLAG_4 (FIELD_DECL_CHECK (NODE)) == 1)
#define SET_DECL_C_BIT_FIELD(NODE) \
  (DECL_LANG_FLAG_4 (FIELD_DECL_CHECK (NODE)) = 1)
#define CLEAR_DECL_C_BIT_FIELD(NODE) \
  (DECL_LANG_FLAG_4 (FIELD_DECL_CHECK (NODE)) = 0)

extern void emit_local_var (tree);
extern tree do_case (tree, tree);
extern tree build_stmt (enum tree_code, ...);
extern tree build_case_label (tree, tree, tree);
extern tree build_continue_stmt (void);
extern tree build_break_stmt (void);

/* These functions must be defined by each front-end which implements
   a variant of the C language.  They are used in c-common.c.  */

extern tree build_unary_op (enum tree_code, tree, int);
extern tree build_binary_op (enum tree_code, tree, tree, int);
extern int lvalue_p (tree);
extern tree default_conversion (tree);

/* Given two integer or real types, return the type for their sum.
   Given two compatible ANSI C types, returns the merged type.  */

extern tree common_type (tree, tree);

extern tree decl_constant_value (tree);

/* Handle increment and decrement of boolean types.  */
extern tree boolean_increment (enum tree_code, tree);

extern int case_compare (splay_tree_key, splay_tree_key);

extern tree c_add_case_label (splay_tree, tree, tree, tree, tree);

extern void c_do_switch_warnings (splay_tree, tree);

extern tree build_function_call (tree, tree);

extern tree finish_label_address_expr (tree);

/* Same function prototype, but the C and C++ front ends have
   different implementations.  Used in c-common.c.  */
extern tree lookup_label (tree);

extern int vector_types_convertible_p (tree t1, tree t2);

extern rtx c_expand_expr (tree, rtx, enum machine_mode, int, rtx *);

extern tree c_staticp (tree);

extern void init_c_lex (void);

extern void c_cpp_builtins (cpp_reader *);

/* Positive if an implicit `extern "C"' scope has just been entered;
   negative if such a scope has just been exited.  */
extern GTY(()) int pending_lang_change;

/* Information recorded about each file examined during compilation.  */

struct c_fileinfo
{
  int time;	/* Time spent in the file.  */

  /* Flags used only by C++.
     INTERFACE_ONLY nonzero means that we are in an "interface" section
     of the compiler.  INTERFACE_UNKNOWN nonzero means we cannot trust
     the value of INTERFACE_ONLY.  If INTERFACE_UNKNOWN is zero and
     INTERFACE_ONLY is zero, it means that we are responsible for
     exporting definitions that others might need.  */
  short interface_only;
  short interface_unknown;
};

struct c_fileinfo *get_fileinfo (const char *);
extern void dump_time_statistics (void);

extern bool c_dump_tree (void *, tree);

extern void c_warn_unused_result (tree *);

extern void verify_sequence_points (tree);

extern tree fold_offsetof (tree);

/* Places where an lvalue, or modifiable lvalue, may be required.
   Used to select diagnostic messages in lvalue_or_else and
   readonly_error.  */
enum lvalue_use {
  lv_assign,
  lv_increment,
  lv_decrement,
  lv_addressof,
  lv_asm
};

/* APPLE LOCAL non lvalue assign */
extern int lvalue_or_else (tree *, enum lvalue_use);

extern int complete_array_type (tree *, tree, bool);

/* In c-gimplify.c  */
extern void c_genericize (tree);
extern int c_gimplify_expr (tree *, tree *, tree *);
extern tree c_build_bind_expr (tree, tree);

/* In c-pch.c  */
extern void pch_init (void);
extern int c_common_valid_pch (cpp_reader *pfile, const char *name, int fd);
extern void c_common_read_pch (cpp_reader *pfile, const char *name, int fd,
			       const char *orig);
extern void c_common_write_pch (void);
extern void c_common_no_more_pch (void);
extern void c_common_pch_pragma (cpp_reader *pfile);
/* APPLE LOCAL begin mainline 4.1 2005-06-17 3988498 */
extern void c_common_print_pch_checksum (FILE *f);

/* In *-checksum.c */
extern const unsigned char executable_checksum[16];

/* APPLE LOCAL end mainline 4.1 2005-06-17 3988498 */
extern void builtin_define_with_value (const char *, const char *, int);
extern void c_stddef_cpp_builtins (void);
extern void fe_file_change (const struct line_map *);
extern void c_parse_error (const char *, enum cpp_ttype, tree);

/* Objective-C / Objective-C++ entry points.  */

/* The following ObjC/ObjC++ functions are called by the C and/or C++
   front-ends; they all must have corresponding stubs in stub-objc.c.  */
extern tree objc_is_class_name (tree);
extern tree objc_is_object_ptr (tree);
extern void objc_check_decl (tree);
/* APPLE LOCAL radar 4281748 */
extern void objc_check_global_decl (tree);
extern int objc_is_reserved_word (tree);
/* APPLE LOCAL 4154928 */
extern tree objc_common_type (tree, tree);
/* APPLE LOCAL 4330422 */
extern tree objc_non_volatilized_type (tree);
/* APPLE LOCAL radar 4697411 */
extern void objc_volatilize_component_ref (tree, tree);
/* APPLE LOCAL begin mainline */
/* Prototype for 'objc_comptypes' removed.  */
extern bool objc_compare_types (tree, tree, int, tree);
/* APPLE LOCAL radar 4229905 */
extern bool objc_have_common_type (tree, tree, int, tree);
/* APPLE LOCAL radar 4133425 */
extern bool objc_diagnose_private_ivar (tree);
/* APPLE LOCAL radar 4507230 */
bool objc_type_valid_for_messaging (tree);
extern void objc_volatilize_decl (tree);
extern bool objc_type_quals_match (tree, tree);
extern tree objc_rewrite_function_call (tree, tree);
/* APPLE LOCAL end mainline */
extern tree objc_message_selector (void);
extern tree objc_lookup_ivar (tree, tree);
extern void objc_clear_super_receiver (void);
extern int objc_is_public (tree, tree);
extern tree objc_is_id (tree);
extern void objc_declare_alias (tree, tree);
extern void objc_declare_class (tree);
extern void objc_declare_protocols (tree);
extern tree objc_build_message_expr (tree);
extern tree objc_finish_message_expr (tree, tree, tree);
extern tree objc_build_selector_expr (tree);
extern tree objc_build_protocol_expr (tree);
extern tree objc_build_encode_expr (tree);
extern tree objc_build_string_object (tree);
extern tree objc_get_protocol_qualified_type (tree, tree);
extern tree objc_get_class_reference (tree);
extern tree objc_get_class_ivars (tree);
/* APPLE LOCAL begin radar 4291785 */
extern tree objc_get_interface_ivars (tree);
extern void objc_detect_field_duplicates (tree);
/* APPLE LOCAL end radar 4291785 */
/* APPLE LOCAL radar 4548636 */
extern void objc_start_class_interface (tree, tree, tree, tree);
extern void objc_start_category_interface (tree, tree, tree);
extern void objc_start_protocol (tree, tree);
extern void objc_continue_interface (void);
extern void objc_finish_interface (void);
extern void objc_start_class_implementation (tree, tree);
extern void objc_start_category_implementation (tree, tree);
/* APPLE LOCAL radar 4533974 - ObjC new protocol */
extern void objc_protocol_implementation (tree);
/* APPLE LOCAL radar 4592503 */
extern void objc_checkon_weak_attribute (tree);
extern void objc_continue_implementation (void);
extern void objc_finish_implementation (void);
extern void objc_set_visibility (int);
extern void objc_set_method_type (enum tree_code);
extern tree objc_build_method_signature (tree, tree, tree);
/* APPLE LOCAL begin radar 3803157 - objc attribute */
extern bool objc_method_decl (enum tree_code);
extern void objc_add_method_declaration (tree, tree);
extern void objc_start_method_definition (tree, tree);
/* APPLE LOCAL end radar 3803157 - objc attribute */
extern void objc_finish_method_definition (tree);
extern void objc_add_instance_variable (tree);
extern tree objc_build_keyword_decl (tree, tree, tree);
extern tree objc_build_throw_stmt (tree);
extern void objc_begin_try_stmt (location_t, tree);
/* APPLE LOCAL LOCAL mainline */
extern tree objc_finish_try_stmt (void);
extern void objc_begin_catch_clause (tree);
extern void objc_finish_catch_clause (void);
extern void objc_build_finally_clause (location_t, tree);
/* APPLE LOCAL mainline */
extern tree objc_build_synchronized (location_t, tree, tree);
extern int objc_static_init_needed_p (void);
extern tree objc_generate_static_init_call (tree);
/* APPLE LOCAL mainline */
extern tree objc_generate_write_barrier (tree, enum tree_code, tree);
/* APPLE LOCAL begin radar 4426814 */
extern tree objc_generate_weak_read (tree);
extern void objc_remove_weak_read (tree*);
/* APPLE LOCAL end radar 4426814 */

/* APPLE LOCAL begin C* language */
extern void objc_set_method_opt (int);
void objc_finish_foreach_loop (location_t, tree, tree, tree, tree);
tree objc_build_component_ref (tree, tree);
tree objc_build_foreach_components (tree, tree*, tree*, tree*, 
				    tree*, tree*, tree*);
/* APPLE LOCAL end C* language */
/* APPLE LOCAL begin C* property (Radar 4436866) */
void objc_set_property_attr (int, tree);
void objc_add_property_variable (tree);
tree objc_build_getter_call (tree, tree);
tree objc_build_setter_call (tree, tree);
/* APPLE LOCAL end C* property (Radar 4436866) */
/* APPLE LOCAL radar 4712269 */
tree objc_build_incr_decr_setter_call (enum tree_code, tree, tree);
/* APPLE LOCAL objc new property */
void objc_declare_property_impl (int, tree);

/* APPLE LOCAL ObjC new abi */
extern tree objc_v2_build_ivar_ref (tree datum, tree component);

/* APPLE LOCAL C* warnings to easy porting to new abi */
void diagnose_selector_cast (tree cast_type, tree sel_exp);

/* APPLE LOCAL begin radar 4441049 */
tree objc_v2_component_ref_field_offset (tree);
tree objc_v2_bitfield_ivar_bitpos (tree);
/* APPLE LOCAL end radar 4441049 */

/* APPLE LOCAL radar 4985544 */
bool objc_check_format_nsstring (tree, unsigned HOST_WIDE_INT, bool *);

/* The following are provided by the C and C++ front-ends, and called by
   ObjC/ObjC++.  */
extern void *objc_get_current_scope (void);
extern void objc_mark_locals_volatile (void *);

/* In c-ppoutput.c  */
extern void init_pp_output (FILE *);
extern void preprocess_file (cpp_reader *);
extern void pp_file_change (const struct line_map *);
extern void pp_dir_change (cpp_reader *, const char *);

/* APPLE LOCAL begin AltiVec */
/* The following function will convert expressions into
   vector initializers.  */
extern tree vector_constructor_from_expr (tree, tree);
/* APPLE LOCAL end AltiVec */

#endif /* ! GCC_C_COMMON_H */
