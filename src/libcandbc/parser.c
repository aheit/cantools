/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_COLON = 258,
     T_SEMICOLON = 259,
     T_SEP = 260,
     T_AT = 261,
     T_PLUS = 262,
     T_MINUS = 263,
     T_BOX_OPEN = 264,
     T_BOX_CLOSE = 265,
     T_PAR_OPEN = 266,
     T_PAR_CLOSE = 267,
     T_COMMA = 268,
     T_ID = 269,
     T_STRING_VAL = 270,
     T_INT_VAL = 271,
     T_DOUBLE_VAL = 272,
     T_VERSION = 273,
     T_INT = 274,
     T_FLOAT = 275,
     T_STRING = 276,
     T_ENUM = 277,
     T_HEX = 278,
     T_BO = 279,
     T_BS = 280,
     T_BU = 281,
     T_SG = 282,
     T_EV = 283,
     T_NS = 284,
     T_NS_DESC = 285,
     T_CM = 286,
     T_BA_DEF = 287,
     T_BA = 288,
     T_VAL = 289,
     T_CAT_DEF = 290,
     T_CAT = 291,
     T_FILTE = 292,
     T_BA_DEF_DEF = 293,
     T_EV_DATA = 294,
     T_ENVVAR_DATA = 295,
     T_SGTYPE = 296,
     T_SGTYPE_VAL = 297,
     T_BA_DEF_SGTYPE = 298,
     T_BA_SGTYPE = 299,
     T_SIG_TYPE_REF = 300,
     T_VAL_TABLE = 301,
     T_SIG_GROUP = 302,
     T_SIG_VALTYPE = 303,
     T_SIGTYPE_VALTYPE = 304,
     T_BO_TX_BU = 305,
     T_BA_DEF_REL = 306,
     T_BA_REL = 307,
     T_BA_DEF_DEF_REL = 308,
     T_BU_SG_REL = 309,
     T_BU_EV_REL = 310,
     T_BU_BO_REL = 311,
     T_SG_MUL_VAL = 312,
     T_DUMMY_NODE_VECTOR = 313
   };
#endif
/* Tokens.  */
#define T_COLON 258
#define T_SEMICOLON 259
#define T_SEP 260
#define T_AT 261
#define T_PLUS 262
#define T_MINUS 263
#define T_BOX_OPEN 264
#define T_BOX_CLOSE 265
#define T_PAR_OPEN 266
#define T_PAR_CLOSE 267
#define T_COMMA 268
#define T_ID 269
#define T_STRING_VAL 270
#define T_INT_VAL 271
#define T_DOUBLE_VAL 272
#define T_VERSION 273
#define T_INT 274
#define T_FLOAT 275
#define T_STRING 276
#define T_ENUM 277
#define T_HEX 278
#define T_BO 279
#define T_BS 280
#define T_BU 281
#define T_SG 282
#define T_EV 283
#define T_NS 284
#define T_NS_DESC 285
#define T_CM 286
#define T_BA_DEF 287
#define T_BA 288
#define T_VAL 289
#define T_CAT_DEF 290
#define T_CAT 291
#define T_FILTE 292
#define T_BA_DEF_DEF 293
#define T_EV_DATA 294
#define T_ENVVAR_DATA 295
#define T_SGTYPE 296
#define T_SGTYPE_VAL 297
#define T_BA_DEF_SGTYPE 298
#define T_BA_SGTYPE 299
#define T_SIG_TYPE_REF 300
#define T_VAL_TABLE 301
#define T_SIG_GROUP 302
#define T_SIG_VALTYPE 303
#define T_SIGTYPE_VALTYPE 304
#define T_BO_TX_BU 305
#define T_BA_DEF_REL 306
#define T_BA_REL 307
#define T_BA_DEF_DEF_REL 308
#define T_BU_SG_REL 309
#define T_BU_EV_REL 310
#define T_BU_BO_REL 311
#define T_SG_MUL_VAL 312
#define T_DUMMY_NODE_VECTOR 313




/* Copy the first part of user declarations.  */
#line 17 "parser.y"

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <dbcModel.h>

/*
 * Define the parameter name of the yyparse() argument
 */
#define YYPARSE_PARAM dbcptr

/* Tell Bison how much stack space is needed. */
#define YYMAXDEPTH 20000



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 37 "parser.y"
{
  number_t                     number;
  double                       double_val;
  string_t                     string;
  object_type_t                object_type;
  signal_t                    *signal;
  node_list_t                 *node_list;
  string_list_t               *string_list;
  mux_info_t                   mux_info;
  signal_list_t               *signal_list;
  string_t                     signal_name;
  string_list_t               *signal_name_list;
  signal_group_t              *signal_group;
  signal_group_list_t         *signal_group_list;
  message_t                   *message;
  message_list_t              *message_list;
  attribute_value_t           *attribute_value;
  attribute_object_class_t     attribute_object_class;
  attribute_rel_t             *attribute_rel;
  attribute_rel_list_t        *attribute_rel_list;
  attribute_definition_t      *attribute_definition;
  attribute_definition_list_t *attribute_definition_list;
  dbc_t                       *dbc;
  envvar_t                    *envvar;
  envvar_list_t               *envvar_list;
  val_map_entry_t             *val_map_entry;
  val_map_t                   *val_map;
  valtable_list_t             *valtable_list;
  valtable_t                  *valtable;
}
/* Line 187 of yacc.c.  */
#line 263 "src/libcandbc/parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 68 "parser.y"

extern int yylex (void);
extern char *yytext;
extern int   yylineno;

void
yyerror (char* msg)
{
  fprintf(stderr,"Error in line %d '%s', symbol '%s'\n",
          yylineno, msg, yytext);
}

/* context dependent object access (TODO: replace by dbc pointer) */
char *current_yacc_file;
dbc_t *current_dbc;
string_t current_attribute;

static attribute_definition_t *
attribute_definition_find(string_t name, attribute_object_class_t aoc)
{
  /* lookup attribute in attribute_definition_list */
  attribute_definition_list_t *adl;
  attribute_definition_t *ret = NULL;

  for(adl = current_dbc->attribute_definition_list;
      adl != NULL;
      adl=adl->next) {
    if(!strcmp(adl->attribute_definition->name,name)) {
      int found;

      switch(adl->attribute_definition->object_type) {
      case ot_network:
      case ot_node:
      case ot_message:
      case ot_signal:
        found = (aoc == aoc_object);
        break;
      case ot_node_signal:
      case ot_node_message:
        found = (aoc == aoc_relation);
        break;
      default:
        found = 0;
      }
      if(found) {
        ret = adl->attribute_definition;
        break;
      }
    }
  }
  return ret;
}

static node_t *node_find(string_t name)
{
  node_list_t *nl;

  for(nl = current_dbc->node_list; nl != NULL; nl = nl->next) {
    if(nl->node->name != NULL) {
      if(!strcmp(nl->node->name, name)) {
        return nl->node;
      }
    }
  }
  return NULL;
}

static message_t *message_find(uint32 id)
{
  message_list_t *ml;

  for(ml = current_dbc->message_list; ml != NULL; ml = ml->next)
    if(ml->message->id == id)
      return ml->message;
  return NULL;
}


static signal_t *signal_find(uint32 id, string_t name)
{
  message_list_t *ml;
  signal_list_t *sl;

  for(ml = current_dbc->message_list; ml != NULL; ml = ml->next)
    if(ml->message->id == id)
      for(sl = ml->message->signal_list; sl != NULL; sl = sl->next)
        if(sl->signal->name != NULL)
          if(!strcmp(sl->signal->name,name))
            return sl->signal;
  return NULL;
}

static envvar_t *envvar_find(string_t name)
{
  envvar_list_t *el;

  for(el = current_dbc->envvar_list; el != NULL; el = el->next)
    if(el->envvar->name != NULL)
      if(!strcmp(el->envvar->name,name))
        return el->envvar;
  return NULL;
}

/*
 * create a new attribute and append it to the attribute list "al".
 *
 * name - name of the new attribute
 * av   - value of the new attribute
 *
 * if the attribute with the given name is already in
 * current_dbc->attribute_defition_list, the value is cast to the
 * already existing type.
 */
void attribute_append(
  attribute_list_t **al,
  string_t           name,
  attribute_value_t *av)
{
  CREATE(attribute_t,a);
  CREATE(attribute_list_t,al_new);

  /* search for the end of the list and link new node */
  if(*al == NULL) {
    *al = al_new;
  } else {
    attribute_list_t *linkfrom = linkfrom = *al;
    while(linkfrom->next != NULL) {
      linkfrom = linkfrom->next;
    }
    linkfrom ->next = al_new;
  }
  al_new->next = NULL;

  /* look up value type in attribute definition list */
  attribute_definition_t *const ad =
    attribute_definition_find(name, aoc_object);

  if(ad != NULL) {
    /* dynamic cast */
    if(   av->value_type == vt_integer
       && ad->value_type == vt_float) {
      av->value.double_val = (double)av->value.int_val;
      av->value_type = ad->value_type;
    } else if(   av->value_type == vt_integer
              && ad->value_type == vt_hex) {
      av->value.hex_val = (uint32)av->value.int_val;
      av->value_type = ad->value_type;
    } else if(   av->value_type == vt_integer
              && ad->value_type == vt_enum) {
#ifdef CONVERT_INT_TO_ENUM
      int eindex = av->value.int_val;
      string_list_t *el;

      /* goto element eindex in the enum list and set the string */
      for(el = ad->range.enum_list;
          el != NULL;
          el = el->next, eindex--) {
        if(eindex == 0) {
          av->value.enum_val = strdup(el->string);
        }
      }
      av->value_type = ad->value_type;
#endif
    } else if(av->value_type != ad->value_type) {
      fprintf(stderr, "error: unhandled type conversion: %d->%d\n",
              av->value_type,
              ad->value_type);
    }
  }

  /* copy attribute name and value*/
  a->name  = name;
  a->value = av;

  /* fill new list element */
  al_new->attribute = a;
}



/* Line 216 of yacc.c.  */
#line 455 "src/libcandbc/parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   287

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNRULES -- Number of states.  */
#define YYNSTATES  287

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   313

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,     7,     8,     9,    33,
      36,    40,    42,    45,    47,    49,    51,    53,    55,    57,
      59,    61,    63,    65,    67,    69,    71,    73,    75,    77,
      79,    81,    83,    85,    87,    89,    91,    93,    95,    97,
      99,   101,   102,   105,   121,   122,   125,   131,   133,   135,
     137,   138,   141,   146,   153,   160,   168,   169,   172,   182,
     183,   186,   191,   196,   201,   203,   205,   206,   209,   216,
     223,   228,   234,   241,   243,   246,   249,   252,   255,   258,
     261,   262,   265,   271,   276,   277,   280,   283,   284,   287,
     294,   295,   298,   302,   308,   314,   320,   327,   328,   331,
     339,   340,   343,   366,   367,   369,   371,   373,   375,   378,
     380,   384,   386,   390,   392,   394,   396,   398,   400,   402,
     404,   406,   408,   410,   412,   413,   416,   420,   421,   424,
     429,   432,   440,   441,   444,   450,   451
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      60,     0,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      67,    68,   117,   114,    62,   115,    63,    94,    64,   121,
      71,    65,    73,    92,    83,    66,    80,    76,    78,    86,
      90,   119,    -1,    18,    15,    -1,    29,     3,    69,    -1,
      70,    -1,    70,    69,    -1,    30,    -1,    31,    -1,    32,
      -1,    33,    -1,    34,    -1,    35,    -1,    36,    -1,    37,
      -1,    38,    -1,    39,    -1,    40,    -1,    41,    -1,    42,
      -1,    43,    -1,    44,    -1,    45,    -1,    46,    -1,    47,
      -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,
      -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,
      -1,    -1,    72,    71,    -1,    28,    14,     3,    16,     9,
      16,     5,    16,    10,    15,    16,    16,    58,   102,     4,
      -1,    -1,    74,    73,    -1,    40,    14,     3,    16,     4,
      -1,    16,    -1,    15,    -1,    17,    -1,    -1,    77,    76,
      -1,    33,    15,    75,     4,    -1,    33,    15,    26,    14,
      75,     4,    -1,    33,    15,    24,    16,    75,     4,    -1,
      33,    15,    27,    16,    14,    75,     4,    -1,    -1,    79,
      78,    -1,    52,    15,    54,    14,    27,    16,    99,    75,
       4,    -1,    -1,    81,    80,    -1,    82,    15,    16,     4,
      -1,    82,    15,    17,     4,    -1,    82,    15,    15,     4,
      -1,    38,    -1,    53,    -1,    -1,    84,    83,    -1,    85,
      15,    19,    16,    16,     4,    -1,    85,    15,    20,   104,
     104,     4,    -1,    85,    15,    21,     4,    -1,    85,    15,
      22,   103,     4,    -1,    85,    15,    23,    16,    16,     4,
      -1,    32,    -1,    32,    26,    -1,    32,    24,    -1,    32,
      27,    -1,    32,    28,    -1,    51,    54,    -1,    51,    56,
      -1,    -1,    87,    86,    -1,    34,    16,    99,    88,     4,
      -1,    34,    14,    88,     4,    -1,    -1,    89,    88,    -1,
      16,    15,    -1,    -1,    91,    90,    -1,    48,    16,    14,
       3,    16,     4,    -1,    -1,    93,    92,    -1,    31,    15,
       4,    -1,    31,    28,    14,    15,     4,    -1,    31,    26,
      14,    15,     4,    -1,    31,    24,    16,    15,     4,    -1,
      31,    27,    16,    14,    15,     4,    -1,    -1,    95,    94,
      -1,    24,    16,    14,     3,    16,    14,    96,    -1,    -1,
      97,    96,    -1,    27,    99,    98,     3,   105,     5,   106,
       6,   111,   112,    11,   107,    13,   108,    12,     9,   109,
       5,   110,    10,    15,   102,    -1,    -1,    14,    -1,    14,
      -1,   101,    -1,    14,    -1,    14,   101,    -1,    14,    -1,
      14,    13,   102,    -1,    15,    -1,    15,    13,   103,    -1,
      17,    -1,    16,    -1,    16,    -1,    16,    -1,   104,    -1,
     104,    -1,   104,    -1,   104,    -1,    16,    -1,     7,    -1,
       8,    -1,    -1,    14,   113,    -1,    26,     3,   113,    -1,
      -1,   116,   115,    -1,    46,    14,    88,     4,    -1,    25,
       3,    -1,    47,    16,    14,    16,     3,   100,     4,    -1,
      -1,   118,   119,    -1,    50,    16,     3,   102,     4,    -1,
      -1,   120,   121,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   343,   343,   354,   356,   358,   361,   365,   343,   379,
     381,   384,   385,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   421,   424,   434,   467,   469,   473,   486,   493,   500,
     509,   511,   515,   525,   536,   547,   570,   573,   584,   617,
     619,   624,   639,   648,   672,   673,   678,   681,   691,   703,
     715,   724,   734,   748,   749,   750,   751,   752,   754,   756,
     761,   763,   768,   787,   809,   812,   822,   833,   835,   847,
     862,   864,   869,   878,   889,   900,   910,   927,   930,   940,
     959,   962,   972,  1004,  1008,  1027,  1028,  1031,  1038,  1048,
    1055,  1065,  1072,  1083,  1084,  1087,  1088,  1090,  1091,  1092,
    1093,  1095,  1098,  1099,  1106,  1109,  1122,  1130,  1133,  1144,
    1155,  1160,  1175,  1178,  1188,  1203,  1205
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_COLON", "T_SEMICOLON", "T_SEP",
  "T_AT", "T_PLUS", "T_MINUS", "T_BOX_OPEN", "T_BOX_CLOSE", "T_PAR_OPEN",
  "T_PAR_CLOSE", "T_COMMA", "T_ID", "T_STRING_VAL", "T_INT_VAL",
  "T_DOUBLE_VAL", "T_VERSION", "T_INT", "T_FLOAT", "T_STRING", "T_ENUM",
  "T_HEX", "T_BO", "T_BS", "T_BU", "T_SG", "T_EV", "T_NS", "T_NS_DESC",
  "T_CM", "T_BA_DEF", "T_BA", "T_VAL", "T_CAT_DEF", "T_CAT", "T_FILTE",
  "T_BA_DEF_DEF", "T_EV_DATA", "T_ENVVAR_DATA", "T_SGTYPE", "T_SGTYPE_VAL",
  "T_BA_DEF_SGTYPE", "T_BA_SGTYPE", "T_SIG_TYPE_REF", "T_VAL_TABLE",
  "T_SIG_GROUP", "T_SIG_VALTYPE", "T_SIGTYPE_VALTYPE", "T_BO_TX_BU",
  "T_BA_DEF_REL", "T_BA_REL", "T_BA_DEF_DEF_REL", "T_BU_SG_REL",
  "T_BU_EV_REL", "T_BU_BO_REL", "T_SG_MUL_VAL", "T_DUMMY_NODE_VECTOR",
  "$accept", "dbc", "@1", "@2", "@3", "@4", "@5", "@6", "version",
  "symbol_section", "symbol_list", "symbol", "envvar_list", "envvar",
  "envvar_data_list", "envvar_data", "attribute_value", "attribute_list",
  "attribute", "attribute_rel_list", "attribute_rel",
  "attribute_definition_default_list", "attribute_definition_default",
  "attribute_definition_object_or_relation", "attribute_definition_list",
  "attribute_definition", "attribute_object_type", "val_list", "val",
  "val_map", "val_map_entry", "sig_valtype_list", "sig_valtype",
  "comment_list", "comment", "message_list", "message", "signal_list",
  "signal", "mux_info", "signal_name", "signal_name_list",
  "space_identifier_list", "comma_identifier_list", "comma_string_list",
  "double_val", "bit_start", "bit_len", "scale", "offset", "min", "max",
  "endianess", "signedness", "space_node_list", "node_list",
  "valtable_list", "valtable", "message_section", "signal_group",
  "signal_group_list", "message_transmitters", "message_transmitter_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    61,    62,    63,    64,    65,    66,    60,    67,
      68,    69,    69,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    71,    71,    72,    73,    73,    74,    75,    75,    75,
      76,    76,    77,    77,    77,    77,    78,    78,    79,    80,
      80,    81,    81,    81,    82,    82,    83,    83,    84,    84,
      84,    84,    84,    85,    85,    85,    85,    85,    85,    85,
      86,    86,    87,    87,    88,    88,    89,    90,    90,    91,
      92,    92,    93,    93,    93,    93,    93,    94,    94,    95,
      96,    96,    97,    98,    98,    99,   100,   101,   101,   102,
     102,   103,   103,   104,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   112,   113,   113,   114,   115,   115,   116,
     117,   118,   119,   119,   120,   121,   121
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,     0,     0,     0,    23,     2,
       3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     2,    15,     0,     2,     5,     1,     1,     1,
       0,     2,     4,     6,     6,     7,     0,     2,     9,     0,
       2,     4,     4,     4,     1,     1,     0,     2,     6,     6,
       4,     5,     6,     1,     2,     2,     2,     2,     2,     2,
       0,     2,     5,     4,     0,     2,     2,     0,     2,     6,
       0,     2,     3,     5,     5,     5,     6,     0,     2,     7,
       0,     2,    22,     0,     1,     1,     1,     1,     2,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     3,     0,     2,     4,
       2,     7,     0,     2,     5,     0,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     9,     0,     0,     0,
       0,     0,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      10,    11,   130,     0,     3,    12,   124,   127,   124,   126,
       0,     4,   127,   125,    84,    97,   128,     0,     0,    84,
       0,     5,    97,    86,   129,    85,     0,   135,    98,     0,
       0,   135,    41,     0,     0,   136,     0,     6,    41,     0,
       0,     0,    44,    42,   100,   109,     0,     0,     0,    90,
      44,     0,    99,   100,     0,   134,     0,     0,     0,    66,
      90,    45,   105,   103,   101,   110,     0,     0,     0,     0,
       0,     0,     0,    73,     0,     7,    66,     0,    91,   104,
       0,     0,     0,    92,     0,     0,     0,     0,    75,    74,
      76,    77,    78,    79,    59,    67,     0,     0,     0,    46,
       0,     0,     0,     0,    64,    65,    50,    59,     0,     0,
       0,     0,     0,     0,   115,     0,     0,    95,    94,     0,
      93,     0,    56,    50,    60,     0,     0,   114,   113,     0,
      70,   111,     0,     0,     0,     0,    96,     0,     0,    80,
      56,    51,     0,     0,     0,     0,     0,     0,    71,     0,
     116,     0,     0,    48,    47,    49,     0,     0,     0,     0,
       0,     0,    87,    80,    57,    63,    61,    62,    68,    69,
     112,    72,     0,     0,     0,     0,     0,    52,     0,    84,
       0,     0,   132,    87,    81,   121,     0,     0,     0,     0,
       0,     0,     0,    84,     0,     0,   132,     8,    88,   122,
     123,     0,     0,    54,    53,     0,     0,    83,     0,     0,
       0,   133,     0,     0,    55,     0,    82,     0,     0,   117,
       0,    43,     0,     0,     0,     0,     0,    89,     0,   118,
       0,    58,   107,     0,   106,     0,   108,   131,     0,   119,
       0,     0,   120,     0,     0,     0,   102
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    47,    55,    67,    82,   134,     5,     8,
      40,    41,    77,    78,    89,    90,   199,   162,   163,   179,
     180,   146,   147,   148,   115,   116,   117,   202,   203,    58,
      59,   222,   223,    99,   100,    61,    62,    92,    93,   120,
     103,   273,   274,    86,   172,   169,   155,   191,   260,   270,
     280,   283,   226,   241,    49,    44,    51,    52,    11,   236,
     237,    71,    72
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -216
static const yytype_int16 yypact[] =
{
    -216,     8,     5,  -216,    34,    16,  -216,    47,    55,    22,
      78,    56,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,    22,  -216,    80,  -216,  -216,    70,    40,    70,  -216,
      73,  -216,    40,  -216,    72,    65,  -216,    75,    87,    72,
      76,  -216,    65,  -216,  -216,  -216,    79,    44,  -216,    92,
      81,    44,    68,    83,    97,  -216,    88,  -216,    68,    89,
      90,    98,    66,  -216,    82,    94,   101,    96,    99,    77,
      66,   102,  -216,    82,    90,  -216,   106,   107,     0,   -26,
      77,  -216,  -216,   103,  -216,  -216,   104,   105,   114,   108,
     109,   110,   111,    11,   -20,  -216,   -26,   112,  -216,  -216,
     116,   117,   124,  -216,   115,   118,   120,   121,  -216,  -216,
    -216,  -216,  -216,  -216,   -31,  -216,    10,   113,   119,  -216,
     127,   128,   122,   134,  -216,  -216,   123,   -31,   125,   126,
      31,   135,   129,   130,  -216,   136,   133,  -216,  -216,   141,
    -216,   132,   100,   123,  -216,    -3,   137,  -216,  -216,    31,
    -216,   138,   145,   139,   142,   144,  -216,    -6,   147,   131,
     100,  -216,   146,   150,   153,   156,   159,   129,  -216,   160,
    -216,   161,   152,  -216,  -216,  -216,   154,   155,   157,   162,
     140,    30,   148,   131,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,   158,   163,    26,    26,   164,  -216,   166,    72,
     102,   165,   143,   148,  -216,  -216,     9,   149,   167,   168,
      26,   170,   172,    72,   169,   171,   143,  -216,  -216,  -216,
    -216,   173,    90,  -216,  -216,   178,   176,  -216,   181,   174,
     175,  -216,    31,   182,  -216,   102,  -216,   177,   179,  -216,
     185,  -216,    26,   184,   196,    31,   197,  -216,   186,  -216,
     190,  -216,   186,   199,  -216,   195,  -216,  -216,    31,  -216,
     200,    31,  -216,   198,   191,    90,  -216
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
     180,  -216,   151,  -216,   183,  -216,  -211,    46,  -216,    32,
    -216,    63,  -216,  -216,    95,  -216,  -216,    12,  -216,   -58,
    -216,   -10,  -216,   187,  -216,   188,  -216,   189,  -216,  -216,
    -215,  -216,   -56,   -94,    27,  -167,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,   192,  -216,   193,  -216,  -216,  -216,
     -19,  -216,   194
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     105,    65,   186,   228,   229,   233,   113,   144,     3,   193,
     194,   195,   182,   183,   184,   108,   239,   240,   196,   245,
     197,   198,   145,     4,   109,   114,   110,   111,   112,   149,
     150,   151,   152,   153,   132,   128,   133,   129,   130,   131,
     262,   193,   194,   195,   219,     7,   220,   167,   168,     6,
       9,   266,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      10,    42,    43,    46,    48,   259,    50,    54,    57,    60,
      63,    64,    66,    69,    70,    73,    76,    74,   269,    79,
      80,    87,    81,    84,    85,    95,    88,    94,    98,    91,
     107,   279,    96,    97,   282,   106,   102,   119,   123,   137,
     121,   122,   138,   125,   124,   127,   126,   136,   139,   154,
     140,   157,   158,   141,   142,   156,   143,   159,   160,   170,
     165,   174,   166,   175,   171,   176,   173,   177,   253,   188,
     205,   187,   178,   185,   206,   189,   161,   207,   190,   192,
     208,   232,   200,   209,   211,   201,   217,   212,   213,   215,
     214,   243,   244,   216,   225,   248,   247,   257,   230,   227,
     231,   234,   254,   249,   252,   256,   261,   250,   267,   258,
     235,   286,   255,   263,   218,   264,   221,   246,   265,   268,
     272,   271,   275,   277,   278,   281,   285,   242,   284,   181,
     164,   135,   204,   238,   210,   224,   276,   251,     0,     0,
       0,    45,     0,     0,     0,     0,     0,     0,     0,    83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      53,     0,     0,     0,     0,    56,     0,     0,     0,     0,
      68,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    75,     0,     0,     0,     0,
       0,     0,     0,   101,     0,     0,     0,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,   118
};

static const yytype_int16 yycheck[] =
{
      94,    59,   169,   214,   215,   220,    32,    38,     0,    15,
      16,    17,    15,    16,    17,    15,     7,     8,    24,   230,
      26,    27,    53,    18,    24,    51,    26,    27,    28,    19,
      20,    21,    22,    23,    54,    24,    56,    26,    27,    28,
     255,    15,    16,    17,    14,    29,    16,    16,    17,    15,
       3,   262,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      25,     3,    26,     3,    14,   252,    46,    14,    16,    24,
      15,     4,    16,    14,    50,     3,    28,    16,   265,    16,
       3,     3,    14,    14,    14,     4,    40,    13,    31,    27,
       3,   278,    16,    14,   281,     9,    14,    14,     4,     3,
      16,    16,     5,    14,    16,    14,    16,    15,     4,    16,
      15,     4,     4,    15,    14,    16,    15,    15,     4,     4,
      15,     5,    16,    10,    15,     4,    16,    15,   242,     4,
       4,    13,    52,    16,     4,    16,    33,     4,    16,    15,
       4,   219,    15,     4,     4,    34,     4,     6,    16,    14,
      16,     4,     4,    16,    16,   233,     4,     3,    14,    16,
      14,    16,     4,    14,    11,     4,     4,    16,     4,    14,
      47,   285,    16,    16,    54,    16,    48,    27,    13,     3,
      14,     4,    12,     4,     9,     5,    15,    58,    10,   163,
     147,   116,   180,   223,   187,   203,   272,   236,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    -1,    -1,    -1,    -1,   100
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    60,    61,     0,    18,    67,    15,    29,    68,     3,
      25,   117,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      69,    70,     3,    26,   114,    69,     3,    62,    14,   113,
      46,   115,   116,   113,    14,    63,   115,    16,    88,    89,
      24,    94,    95,    15,     4,    88,    16,    64,    94,    14,
      50,   120,   121,     3,    16,   121,    28,    71,    72,    16,
       3,    14,    65,    71,    14,    14,   102,     3,    40,    73,
      74,    27,    96,    97,    13,     4,    16,    14,    31,    92,
      93,    73,    14,    99,    96,   102,     9,     3,    15,    24,
      26,    27,    28,    32,    51,    83,    84,    85,    92,    14,
      98,    16,    16,     4,    16,    14,    16,    14,    24,    26,
      27,    28,    54,    56,    66,    83,    15,     3,     5,     4,
      15,    15,    14,    15,    38,    53,    80,    81,    82,    19,
      20,    21,    22,    23,    16,   105,    16,     4,     4,    15,
       4,    33,    76,    77,    80,    15,    16,    16,    17,   104,
       4,    15,   103,    16,     5,    10,     4,    15,    52,    78,
      79,    76,    15,    16,    17,    16,   104,    13,     4,    16,
      16,   106,    15,    15,    16,    17,    24,    26,    27,    75,
      15,    34,    86,    87,    78,     4,     4,     4,     4,     4,
     103,     4,     6,    16,    16,    14,    16,     4,    54,    14,
      16,    48,    90,    91,    86,    16,   111,    16,    75,    75,
      14,    14,    88,    99,    16,    47,   118,   119,    90,     7,
       8,   112,    58,     4,     4,    75,    27,     4,    88,    14,
      16,   119,    11,   102,     4,    16,     4,     3,    14,   104,
     107,     4,    99,    16,    16,    13,    75,     4,     3,   104,
     108,     4,    14,   100,   101,    12,   101,     4,     9,   104,
     109,     5,   104,   110,    10,    15,   102
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 343 "parser.y"
    {
        CREATE(network_t, network);
        current_dbc = (dbc_t *)dbcptr;
        current_dbc->network = network;
        current_dbc->network->comment = NULL;
        current_dbc->network->attribute_list = NULL;
      }
    break;

  case 3:
#line 354 "parser.y"
    { current_dbc->node_list = (yyvsp[(5) - (5)].node_list); }
    break;

  case 4:
#line 356 "parser.y"
    { current_dbc->valtable_list = (yyvsp[(7) - (7)].valtable_list); }
    break;

  case 5:
#line 358 "parser.y"
    { current_dbc->message_list = (yyvsp[(9) - (9)].message_list); }
    break;

  case 6:
#line 361 "parser.y"
    { current_dbc->envvar_list  = (yyvsp[(12) - (12)].envvar_list); }
    break;

  case 7:
#line 365 "parser.y"
    { current_dbc->attribute_definition_list = (yyvsp[(16) - (16)].attribute_definition_list); }
    break;

  case 8:
#line 372 "parser.y"
    {
        current_dbc->version            = (yyvsp[(2) - (23)].string);
        current_dbc->signal_group_list  = (yyvsp[(23) - (23)].signal_group_list);
	current_dbc->attribute_rel_list = (yyvsp[(20) - (23)].attribute_rel_list);
      }
    break;

  case 9:
#line 379 "parser.y"
    { (yyval.string) = (yyvsp[(2) - (2)].string); }
    break;

  case 41:
#line 421 "parser.y"
    {
      (yyval.envvar_list) = NULL;
    }
    break;

  case 42:
#line 425 "parser.y"
    {
      CREATE(envvar_list_t,list);
      list->envvar = (yyvsp[(1) - (2)].envvar);
      list->next   = (yyvsp[(2) - (2)].envvar_list);
      (yyval.envvar_list) = list;
    }
    break;

  case 43:
#line 449 "parser.y"
    {
      CREATE(envvar_t, envvar);

      envvar->name    = (yyvsp[(2) - (15)].string);
      envvar->envtype = (envtype_t)(yyvsp[(4) - (15)].number);
      envvar->min     = (yyvsp[(6) - (15)].number);
      envvar->max     = (yyvsp[(8) - (15)].number);
      envvar->unit    = (yyvsp[(10) - (15)].string);
      envvar->max     = (yyvsp[(11) - (15)].number);
      envvar->index   = (yyvsp[(12) - (15)].number);
      envvar->access  = (accesstype_t)(yyvsp[(13) - (15)].number);
      envvar->node_list = (yyvsp[(14) - (15)].string_list);
      envvar->val_map = NULL;
      envvar->comment = NULL;
      (yyval.envvar) = envvar;
    }
    break;

  case 46:
#line 476 "parser.y"
    {
        free((yyvsp[(2) - (5)].string));
      }
    break;

  case 47:
#line 487 "parser.y"
    {
      CREATE(attribute_value_t, av);
      av->value_type    = vt_integer; /* preliminary value type */
      av->value.int_val = (yyvsp[(1) - (1)].number);
      (yyval.attribute_value) = av;
    }
    break;

  case 48:
#line 494 "parser.y"
    {
      CREATE(attribute_value_t, av);
      av->value_type = vt_string;
      av->value.string_val = (yyvsp[(1) - (1)].string);
      (yyval.attribute_value) = av;
    }
    break;

  case 49:
#line 501 "parser.y"
    {
      CREATE(attribute_value_t, av);
      av->value_type = vt_float;
      av->value.double_val = (yyvsp[(1) - (1)].double_val);
      (yyval.attribute_value) = av;
    }
    break;

  case 52:
#line 516 "parser.y"
    {
      if(current_dbc->network != NULL) {
        attribute_append(&current_dbc->network->attribute_list,(yyvsp[(2) - (4)].string),(yyvsp[(3) - (4)].attribute_value));
      } else {
        fprintf(stderr,"error: network not found\n");
        free((yyvsp[(2) - (4)].string));
        attribute_value_free((yyvsp[(3) - (4)].attribute_value));
      }
    }
    break;

  case 53:
#line 526 "parser.y"
    {
      node_t *const node = node_find((yyvsp[(4) - (6)].string));
      if(node != NULL) {
        attribute_append(&node->attribute_list,(yyvsp[(2) - (6)].string),(yyvsp[(5) - (6)].attribute_value));
      } else {
        fprintf(stderr,"error: node %s not found\n", (yyvsp[(4) - (6)].string));
        attribute_value_free((yyvsp[(5) - (6)].attribute_value));
      }
      free((yyvsp[(4) - (6)].string));
    }
    break;

  case 54:
#line 537 "parser.y"
    {
      message_t *const message = message_find((yyvsp[(4) - (6)].number));
      if(message != NULL) {
        attribute_append(&message->attribute_list,(yyvsp[(2) - (6)].string),(yyvsp[(5) - (6)].attribute_value));
      } else {
        fprintf(stderr,"error: message %d not found\n", (yyvsp[(4) - (6)].number));
        attribute_value_free((yyvsp[(5) - (6)].attribute_value));
        free((yyvsp[(2) - (6)].string));
      }
    }
    break;

  case 55:
#line 554 "parser.y"
    {
      signal_t *const signal = signal_find((yyvsp[(4) - (7)].number),(yyvsp[(5) - (7)].string));

      if(signal != NULL) {
        attribute_append(&signal->attribute_list,(yyvsp[(2) - (7)].string),(yyvsp[(6) - (7)].attribute_value));
      } else {
        fprintf(stderr,"error: signal %d (%s) not found\n", (yyvsp[(4) - (7)].number), (yyvsp[(5) - (7)].string));
        attribute_value_free((yyvsp[(6) - (7)].attribute_value));
        free((yyvsp[(2) - (7)].string));
      }
      free((yyvsp[(5) - (7)].string));
    }
    break;

  case 56:
#line 570 "parser.y"
    {
      (yyval.attribute_rel_list) = NULL;
    }
    break;

  case 57:
#line 574 "parser.y"
    {
      CREATE(attribute_rel_list_t,list);
      list->attribute_rel = (yyvsp[(1) - (2)].attribute_rel);
      list->next          = (yyvsp[(2) - (2)].attribute_rel_list);
      (yyval.attribute_rel_list) = list;
    }
    break;

  case 58:
#line 593 "parser.y"
    {
      node_t *node = node_find((yyvsp[(4) - (9)].string));
      message_t *message = message_find((yyvsp[(6) - (9)].number));
      signal_t *signal = signal_find((yyvsp[(6) - (9)].number),(yyvsp[(7) - (9)].signal_name));

      if(   (node != NULL)
         && (message != NULL)
         && (signal != NULL)) {
        CREATE(attribute_rel_t,attribute_rel);
        attribute_rel->name             = (yyvsp[(2) - (9)].string);
        attribute_rel->node             = node;
        attribute_rel->message          = message;
        attribute_rel->signal           = signal;
        attribute_rel->attribute_value  = (yyvsp[(8) - (9)].attribute_value);
        (yyval.attribute_rel) = attribute_rel;
      } else {
        free((yyvsp[(2) - (9)].string));
        attribute_value_free((yyvsp[(8) - (9)].attribute_value));
        (yyval.attribute_rel) = NULL;
      }
      free((yyvsp[(4) - (9)].string));
      free((yyvsp[(7) - (9)].signal_name));
    }
    break;

  case 61:
#line 626 "parser.y"
    {
      attribute_definition_t *const ad = attribute_definition_find((yyvsp[(2) - (4)].string), (yyvsp[(1) - (4)].attribute_object_class));
      free((yyvsp[(2) - (4)].string));
      if(ad != NULL) {
        switch(ad->value_type) {
        case vt_integer: ad->default_value.int_val = (yyvsp[(3) - (4)].number); break;
        case vt_hex:     ad->default_value.hex_val = (uint32)(yyvsp[(3) - (4)].number); break;
        case vt_float:   ad->default_value.double_val = (double)(yyvsp[(3) - (4)].number); break;
        default:
          break;
        }
      }
    }
    break;

  case 62:
#line 641 "parser.y"
    {
      attribute_definition_t *const ad = attribute_definition_find((yyvsp[(2) - (4)].string), (yyvsp[(1) - (4)].attribute_object_class));
      free((yyvsp[(2) - (4)].string));
      if(ad != NULL && ad->value_type == vt_float) {
        ad->default_value.double_val = (yyvsp[(3) - (4)].double_val);
      }
    }
    break;

  case 63:
#line 650 "parser.y"
    {
      attribute_definition_t *const ad = attribute_definition_find((yyvsp[(2) - (4)].string), (yyvsp[(1) - (4)].attribute_object_class));
      if(ad != NULL) {
        switch(ad->value_type) {
        case vt_string:
          ad->default_value.string_val = (yyvsp[(3) - (4)].string);
          break;
        case vt_enum:
          ad->default_value.enum_val = (yyvsp[(3) - (4)].string);
          break;
        default:
          break;
        }
      } else {
        fprintf(stderr,"error: attribute %s not found\n", (yyvsp[(2) - (4)].string));
        free((yyvsp[(3) - (4)].string));
      }
      free((yyvsp[(2) - (4)].string));
    }
    break;

  case 64:
#line 672 "parser.y"
    { (yyval.attribute_object_class) = aoc_object; }
    break;

  case 65:
#line 673 "parser.y"
    { (yyval.attribute_object_class) = aoc_relation; }
    break;

  case 66:
#line 678 "parser.y"
    {
      (yyval.attribute_definition_list) = NULL;
    }
    break;

  case 67:
#line 682 "parser.y"
    {
      CREATE(attribute_definition_list_t,list);
      list->attribute_definition = (yyvsp[(1) - (2)].attribute_definition);
      list->next                 = (yyvsp[(2) - (2)].attribute_definition_list);
      (yyval.attribute_definition_list) = list;
    }
    break;

  case 68:
#line 693 "parser.y"
    {
      CREATE(attribute_definition_t,ad);
      ad->object_type           = (yyvsp[(1) - (6)].object_type);
      ad->name                  = (yyvsp[(2) - (6)].string);
      ad->value_type            = vt_integer;
      ad->range.int_range.min   = (sint32)(yyvsp[(4) - (6)].number);
      ad->range.int_range.max   = (sint32)(yyvsp[(5) - (6)].number);
      ad->default_value.int_val = 0;
      (yyval.attribute_definition) = ad;
    }
    break;

  case 69:
#line 705 "parser.y"
    {
      CREATE(attribute_definition_t,ad);
      ad->object_type              = (yyvsp[(1) - (6)].object_type);
      ad->name                     = (yyvsp[(2) - (6)].string);
      ad->value_type               = vt_float;
      ad->range.double_range.min   = (yyvsp[(4) - (6)].double_val);
      ad->range.double_range.max   = (yyvsp[(5) - (6)].double_val);
      ad->default_value.double_val = 0;
      (yyval.attribute_definition) = ad;
    }
    break;

  case 70:
#line 716 "parser.y"
    {
      CREATE(attribute_definition_t,ad);
      ad->object_type              = (yyvsp[(1) - (4)].object_type);
      ad->name                     = (yyvsp[(2) - (4)].string);
      ad->value_type               = vt_string;
      ad->default_value.string_val = NULL;
      (yyval.attribute_definition) = ad;
    }
    break;

  case 71:
#line 725 "parser.y"
    {
      CREATE(attribute_definition_t,ad);
      ad->object_type            = (yyvsp[(1) - (5)].object_type);
      ad->name                   = (yyvsp[(2) - (5)].string);
      ad->value_type             = vt_enum;
      ad->range.enum_list        = (yyvsp[(4) - (5)].string_list);
      ad->default_value.enum_val = NULL;
      (yyval.attribute_definition) = ad;
    }
    break;

  case 72:
#line 735 "parser.y"
    {
      CREATE(attribute_definition_t,ad);
      ad->object_type           = (yyvsp[(1) - (6)].object_type);
      ad->name                  = (yyvsp[(2) - (6)].string);
      ad->value_type            = vt_hex;
      ad->range.hex_range.min   = (uint32)(yyvsp[(4) - (6)].number);
      ad->range.hex_range.max   = (uint32)(yyvsp[(5) - (6)].number);
      ad->default_value.hex_val = 0;
      (yyval.attribute_definition) = ad;
    }
    break;

  case 73:
#line 748 "parser.y"
    { (yyval.object_type) = ot_network; }
    break;

  case 74:
#line 749 "parser.y"
    { (yyval.object_type) = ot_node; }
    break;

  case 75:
#line 750 "parser.y"
    { (yyval.object_type) = ot_message; }
    break;

  case 76:
#line 751 "parser.y"
    { (yyval.object_type) = ot_signal; }
    break;

  case 77:
#line 752 "parser.y"
    { (yyval.object_type) = ot_envvar; }
    break;

  case 78:
#line 754 "parser.y"
    { (yyval.object_type) = ot_node_signal; }
    break;

  case 79:
#line 756 "parser.y"
    { (yyval.object_type) = ot_node_message; }
    break;

  case 82:
#line 769 "parser.y"
    {
      signal_t *const signal = signal_find((yyvsp[(2) - (5)].number),(yyvsp[(3) - (5)].signal_name));

      if(signal != NULL) {
        if(signal->val_map == NULL) {
          signal->val_map = (yyvsp[(4) - (5)].val_map);
        } else {
          fprintf(stderr,
                  "error: duplicate val_map for signal %lu (%s)\n", (yyvsp[(2) - (5)].number), (yyvsp[(3) - (5)].signal_name));
          val_map_free((yyvsp[(4) - (5)].val_map));
        }
      } else {
        fprintf(stderr,"error: signal %lu (%s) not found\n", (yyvsp[(2) - (5)].number), (yyvsp[(3) - (5)].signal_name));
        val_map_free((yyvsp[(4) - (5)].val_map));
      }
      free((yyvsp[(3) - (5)].signal_name));
    }
    break;

  case 83:
#line 788 "parser.y"
    {
      envvar_t *const envvar = envvar_find((yyvsp[(2) - (4)].string));

      if(envvar != NULL) {
        if(envvar->val_map == NULL) {
          envvar->val_map = (yyvsp[(3) - (4)].val_map);
        } else {
          fprintf(stderr,
                  "error: duplicate val_map for environment variable %s\n", (yyvsp[(2) - (4)].string));
          val_map_free((yyvsp[(3) - (4)].val_map));
        }
      } else {
        fprintf(stderr,"error: environment variable %s not found\n", (yyvsp[(2) - (4)].string));
        val_map_free((yyvsp[(3) - (4)].val_map));
      }
      free((yyvsp[(2) - (4)].string));
    }
    break;

  case 84:
#line 809 "parser.y"
    {
      (yyval.val_map) = NULL;
    }
    break;

  case 85:
#line 813 "parser.y"
    {
      CREATE(val_map_t, val_map);
      val_map->val_map_entry = (yyvsp[(1) - (2)].val_map_entry);
      val_map->next          = (yyvsp[(2) - (2)].val_map);
      (yyval.val_map) = val_map;
    }
    break;

  case 86:
#line 823 "parser.y"
    {
      CREATE(val_map_entry_t, val_map_entry);
      val_map_entry->index = (yyvsp[(1) - (2)].number);
      val_map_entry->value = (yyvsp[(2) - (2)].string);
      (yyval.val_map_entry) = val_map_entry;
    }
    break;

  case 89:
#line 848 "parser.y"
    {
      signal_t *const s = signal_find((yyvsp[(2) - (6)].number),(yyvsp[(3) - (6)].string));
      free((yyvsp[(3) - (6)].string));
      if(s != NULL) {
        switch((yyvsp[(5) - (6)].number)) {
        case 1: s->signal_val_type = svt_float; break;
        case 2: s->signal_val_type = svt_double; break;
        }
      }
    }
    break;

  case 92:
#line 870 "parser.y"
    {
      if(current_dbc->network != NULL) {
	current_dbc->network->comment =
	  string_merge(current_dbc->network->comment, (yyvsp[(2) - (3)].string));
      } else {
	string_free((yyvsp[(2) - (3)].string));
      }
    }
    break;

  case 93:
#line 879 "parser.y"
    {
      envvar_t *const envvar = envvar_find((yyvsp[(3) - (5)].string));
      if(envvar != NULL) {
	envvar->comment = string_merge(envvar->comment, (yyvsp[(4) - (5)].string));
      } else {
        fprintf(stderr,"error: environment variable %s not found\n", (yyvsp[(3) - (5)].string));
	string_free((yyvsp[(4) - (5)].string));
      }
      string_free((yyvsp[(3) - (5)].string));
    }
    break;

  case 94:
#line 890 "parser.y"
    {
      node_t *const node = node_find((yyvsp[(3) - (5)].string));
      if(node != NULL) {
	node->comment = string_merge(node->comment, (yyvsp[(4) - (5)].string));
      } else {
        fprintf(stderr,"error: node %s not found\n", (yyvsp[(3) - (5)].string));
        string_free((yyvsp[(4) - (5)].string));
      }
      string_free((yyvsp[(3) - (5)].string));
    }
    break;

  case 95:
#line 901 "parser.y"
    {
      message_t *const message = message_find((yyvsp[(3) - (5)].number));
      if(message != NULL) {
	message->comment = string_merge(message->comment, (yyvsp[(4) - (5)].string));
      } else {
        fprintf(stderr,"error: message %s not found\n", (yyvsp[(3) - (5)].number));
        string_free((yyvsp[(4) - (5)].string));
      }
    }
    break;

  case 96:
#line 911 "parser.y"
    {
      signal_t *const signal = signal_find((yyvsp[(3) - (6)].number), (yyvsp[(4) - (6)].string));
      if(signal != NULL) {
	signal->comment = string_merge(signal->comment, (yyvsp[(5) - (6)].string));
      } else {
        fprintf(stderr,"error: signal %d (%s) not found\n", (yyvsp[(3) - (6)].number), (yyvsp[(4) - (6)].string));
        string_free((yyvsp[(5) - (6)].string));
      }
      string_free((yyvsp[(4) - (6)].string));
    }
    break;

  case 97:
#line 927 "parser.y"
    {
      (yyval.message_list) = NULL;
    }
    break;

  case 98:
#line 931 "parser.y"
    {
      CREATE(message_list_t,list);
      list->message = (yyvsp[(1) - (2)].message);
      list->next    = (yyvsp[(2) - (2)].message_list);
      (yyval.message_list) = list;
    }
    break;

  case 99:
#line 941 "parser.y"
    {
      CREATE(message_t, m);
      m->id               = (yyvsp[(2) - (7)].number);
      m->name             = (yyvsp[(3) - (7)].string);
      m->len              = (yyvsp[(5) - (7)].number);
      m->sender           = (yyvsp[(6) - (7)].string);
      m->signal_list      = (yyvsp[(7) - (7)].signal_list);
      m->comment          = NULL;
      m->attribute_list   = NULL;
      m->transmitter_list = NULL;
      (yyval.message) = m;
    }
    break;

  case 100:
#line 959 "parser.y"
    {
      (yyval.signal_list) = NULL;
    }
    break;

  case 101:
#line 963 "parser.y"
    {
      CREATE(signal_list_t,list);
      list->signal = (yyvsp[(1) - (2)].signal);
      list->next   = (yyvsp[(2) - (2)].signal_list);
      (yyval.signal_list) = list;
    }
    break;

  case 102:
#line 977 "parser.y"
    {
      CREATE(signal_t, signal);
      signal->name       = (yyvsp[(2) - (22)].signal_name);
      signal->mux_type   = (yyvsp[(3) - (22)].mux_info).mux_type;
      signal->mux_value  = (yyvsp[(3) - (22)].mux_info).mux_value;
      signal->bit_start  = (yyvsp[(5) - (22)].number);
      signal->bit_len    = (yyvsp[(7) - (22)].number);
      signal->endianess  = (yyvsp[(9) - (22)].number);
      signal->signedness = (yyvsp[(10) - (22)].number);
      signal->scale      = (yyvsp[(12) - (22)].double_val);
      signal->offset     = (yyvsp[(14) - (22)].double_val);
      signal->min        = (yyvsp[(17) - (22)].double_val);
      signal->max        = (yyvsp[(19) - (22)].double_val);
      signal->unit       = (yyvsp[(21) - (22)].string);
      signal->signal_val_type = svt_integer;
      signal->receiver_list   = (yyvsp[(22) - (22)].string_list);
      signal->comment         = NULL;
      signal->attribute_list  = NULL;
      signal->val_map         = NULL;
      (yyval.signal) = signal;
    }
    break;

  case 103:
#line 1004 "parser.y"
    {
      (yyval.mux_info).mux_type = m_signal;
      (yyval.mux_info).mux_value = 0;
    }
    break;

  case 104:
#line 1009 "parser.y"
    {
      switch((yyvsp[(1) - (1)].string)[0]) {
      case 'M':
        (yyval.mux_info).mux_type  = m_multiplexor;
        (yyval.mux_info).mux_value = 0;
        break;
      case 'm':
        (yyval.mux_info).mux_type  = m_multiplexed;
        (yyval.mux_info).mux_value = strtoul((yyvsp[(1) - (1)].string)+1, NULL, 10);
        break;
      default:
        /* error: unknown mux type */
        break;
      }
      free((yyvsp[(1) - (1)].string));
    }
    break;

  case 105:
#line 1027 "parser.y"
    { (yyval.signal_name) = (string_t)(yyvsp[(1) - (1)].string); }
    break;

  case 106:
#line 1028 "parser.y"
    { (yyval.signal_name_list) = (string_list_t *)(yyvsp[(1) - (1)].string_list); }
    break;

  case 107:
#line 1032 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (1)].string);
      list->next   = NULL;
      (yyval.string_list) = list;
    }
    break;

  case 108:
#line 1039 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (2)].string);
      list->next   = (yyvsp[(2) - (2)].string_list);
      (yyval.string_list) = list;
    }
    break;

  case 109:
#line 1049 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (1)].string);
      list->next   = NULL;
      (yyval.string_list) = list;
    }
    break;

  case 110:
#line 1056 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (3)].string);
      list->next   = (yyvsp[(3) - (3)].string_list);
      (yyval.string_list) = list;
    }
    break;

  case 111:
#line 1066 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (1)].string);
      list->next   = NULL;
      (yyval.string_list) = list;
    }
    break;

  case 112:
#line 1073 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (3)].string);
      list->next   = (yyvsp[(3) - (3)].string_list);
      (yyval.string_list) = list;
    }
    break;

  case 113:
#line 1083 "parser.y"
    { (yyval.double_val) = (yyvsp[(1) - (1)].double_val);        }
    break;

  case 114:
#line 1084 "parser.y"
    { (yyval.double_val) = (double)(yyvsp[(1) - (1)].number); }
    break;

  case 115:
#line 1087 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (1)].number); }
    break;

  case 116:
#line 1088 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (1)].number); }
    break;

  case 117:
#line 1090 "parser.y"
    { (yyval.double_val) = (yyvsp[(1) - (1)].double_val); }
    break;

  case 118:
#line 1091 "parser.y"
    { (yyval.double_val) = (yyvsp[(1) - (1)].double_val); }
    break;

  case 119:
#line 1092 "parser.y"
    { (yyval.double_val) = (yyvsp[(1) - (1)].double_val); }
    break;

  case 120:
#line 1093 "parser.y"
    { (yyval.double_val) = (yyvsp[(1) - (1)].double_val); }
    break;

  case 121:
#line 1095 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (1)].number); }
    break;

  case 122:
#line 1098 "parser.y"
    { (yyval.number) = 0; }
    break;

  case 123:
#line 1099 "parser.y"
    { (yyval.number) = 1; }
    break;

  case 124:
#line 1106 "parser.y"
    {
      (yyval.node_list) = NULL;
    }
    break;

  case 125:
#line 1110 "parser.y"
    {
      CREATE(node_list_t,list);
      CREATE(node_t,node);
      node->name = (yyvsp[(1) - (2)].string);
      node->comment = NULL;
      node->attribute_list = NULL;
      list->node = node;
      list->next = (yyvsp[(2) - (2)].node_list);
      (yyval.node_list) = list;
    }
    break;

  case 126:
#line 1123 "parser.y"
    {
      (yyval.node_list) = (yyvsp[(3) - (3)].node_list);
    }
    break;

  case 127:
#line 1130 "parser.y"
    {
      (yyval.valtable_list) = NULL;
    }
    break;

  case 128:
#line 1134 "parser.y"
    {
      CREATE(valtable_list_t, valtable_list);
      CREATE(valtable_t, valtable);
      valtable_list->next     = (yyvsp[(2) - (2)].valtable_list);
      valtable_list->valtable = (yyvsp[(1) - (2)].valtable);
      (yyval.valtable_list) = valtable_list;
    }
    break;

  case 129:
#line 1145 "parser.y"
    {
      CREATE(valtable_t, valtable);
      valtable->name    = (yyvsp[(2) - (4)].string);
      valtable->comment = NULL;
      valtable->val_map = (yyvsp[(3) - (4)].val_map);
      (yyval.valtable) = valtable;
    }
    break;

  case 131:
#line 1162 "parser.y"
    {
      CREATE(signal_group_t,sg);
      sg->id   = (yyvsp[(2) - (7)].number);
      sg->name = (yyvsp[(3) - (7)].string);
      /* TODO: meaning of $4? */
      sg->signal_name_list = (yyvsp[(6) - (7)].signal_name_list);
      (yyval.signal_group) = sg;
    }
    break;

  case 132:
#line 1175 "parser.y"
    {
      (yyval.signal_group_list) = NULL;
    }
    break;

  case 133:
#line 1179 "parser.y"
    {
      CREATE(signal_group_list_t,list);
      list->signal_group = (yyvsp[(1) - (2)].signal_group);
      list->next         = (yyvsp[(2) - (2)].signal_group_list);
      (yyval.signal_group_list) = list;
    }
    break;

  case 134:
#line 1190 "parser.y"
    {
      message_t *const message = message_find((yyvsp[(2) - (5)].number));
      if(message != NULL) {
	/* duplicate list: new one replaces old one */
	string_list_free(message->transmitter_list);
	message->transmitter_list = (yyvsp[(4) - (5)].string_list);
      } else {
        fprintf(stderr,"error: message %d not found\n", (yyvsp[(2) - (5)].number));
	string_list_free((yyvsp[(4) - (5)].string_list));
      }
    }
    break;


/* Line 1267 of yacc.c.  */
#line 2802 "src/libcandbc/parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



