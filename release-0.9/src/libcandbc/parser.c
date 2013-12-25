/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 17 "parser.y"

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <dbcModel.h>
#include <math.h>

/*
 * Define the parameter name of the yyparse() argument
 */
#define YYPARSE_PARAM dbcptr

/* Tell Bison how much stack space is needed. */
#define YYMAXDEPTH 20000



/* Line 189 of yacc.c  */
#line 93 "src/libcandbc/parser.c"

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
     T_DUMMY_NODE_VECTOR = 313,
     T_NAN = 314
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
#define T_NAN 314




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 37 "parser.y"

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



/* Line 214 of yacc.c  */
#line 280 "src/libcandbc/parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */

/* Line 264 of yacc.c  */
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



/* Line 264 of yacc.c  */
#line 473 "src/libcandbc/parser.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   280

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  138
/* YYNRULES -- Number of states.  */
#define YYNSTATES  288

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

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
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,     7,     8,     9,    33,
      36,    39,    43,    45,    48,    50,    52,    54,    56,    58,
      60,    62,    64,    66,    68,    70,    72,    74,    76,    78,
      80,    82,    84,    86,    88,    90,    92,    94,    96,    98,
     100,   102,   104,   105,   108,   124,   125,   128,   134,   136,
     138,   140,   141,   144,   149,   156,   163,   171,   172,   175,
     185,   186,   189,   194,   199,   204,   206,   208,   209,   212,
     219,   226,   231,   237,   244,   246,   249,   252,   255,   258,
     261,   264,   265,   268,   274,   279,   280,   283,   286,   287,
     290,   297,   298,   301,   305,   311,   317,   323,   330,   331,
     334,   342,   343,   346,   369,   370,   372,   374,   376,   378,
     381,   383,   387,   389,   393,   395,   397,   399,   401,   403,
     405,   407,   409,   411,   413,   415,   417,   418,   421,   425,
     426,   429,   434,   437,   445,   446,   449,   455,   456
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      68,    69,   118,   115,    63,   116,    64,    95,    65,   122,
      72,    66,    74,    93,    84,    67,    81,    77,    79,    87,
      91,   120,    -1,    18,    15,    -1,    29,     3,    -1,    29,
       3,    70,    -1,    71,    -1,    71,    70,    -1,    30,    -1,
      31,    -1,    32,    -1,    33,    -1,    34,    -1,    35,    -1,
      36,    -1,    37,    -1,    38,    -1,    39,    -1,    40,    -1,
      41,    -1,    42,    -1,    43,    -1,    44,    -1,    45,    -1,
      46,    -1,    47,    -1,    48,    -1,    49,    -1,    50,    -1,
      51,    -1,    52,    -1,    53,    -1,    54,    -1,    55,    -1,
      56,    -1,    57,    -1,    -1,    73,    72,    -1,    28,    14,
       3,    16,     9,    16,     5,    16,    10,    15,    16,    16,
      58,   103,     4,    -1,    -1,    75,    74,    -1,    40,    14,
       3,    16,     4,    -1,    16,    -1,    15,    -1,    17,    -1,
      -1,    78,    77,    -1,    33,    15,    76,     4,    -1,    33,
      15,    26,    14,    76,     4,    -1,    33,    15,    24,    16,
      76,     4,    -1,    33,    15,    27,    16,    14,    76,     4,
      -1,    -1,    80,    79,    -1,    52,    15,    54,    14,    27,
      16,   100,    76,     4,    -1,    -1,    82,    81,    -1,    83,
      15,    16,     4,    -1,    83,    15,    17,     4,    -1,    83,
      15,    15,     4,    -1,    38,    -1,    53,    -1,    -1,    85,
      84,    -1,    86,    15,    19,    16,    16,     4,    -1,    86,
      15,    20,   105,   105,     4,    -1,    86,    15,    21,     4,
      -1,    86,    15,    22,   104,     4,    -1,    86,    15,    23,
      16,    16,     4,    -1,    32,    -1,    32,    26,    -1,    32,
      24,    -1,    32,    27,    -1,    32,    28,    -1,    51,    54,
      -1,    51,    56,    -1,    -1,    88,    87,    -1,    34,    16,
     100,    89,     4,    -1,    34,    14,    89,     4,    -1,    -1,
      90,    89,    -1,    16,    15,    -1,    -1,    92,    91,    -1,
      48,    16,    14,     3,    16,     4,    -1,    -1,    94,    93,
      -1,    31,    15,     4,    -1,    31,    28,    14,    15,     4,
      -1,    31,    26,    14,    15,     4,    -1,    31,    24,    16,
      15,     4,    -1,    31,    27,    16,    14,    15,     4,    -1,
      -1,    96,    95,    -1,    24,    16,    14,     3,    16,    14,
      97,    -1,    -1,    98,    97,    -1,    27,   100,    99,     3,
     106,     5,   107,     6,   112,   113,    11,   108,    13,   109,
      12,     9,   110,     5,   111,    10,    15,   103,    -1,    -1,
      14,    -1,    14,    -1,   102,    -1,    14,    -1,    14,   102,
      -1,    14,    -1,    14,    13,   103,    -1,    15,    -1,    15,
      13,   104,    -1,    17,    -1,    59,    -1,    16,    -1,    16,
      -1,    16,    -1,   105,    -1,   105,    -1,   105,    -1,   105,
      -1,    16,    -1,     7,    -1,     8,    -1,    -1,    14,   114,
      -1,    26,     3,   114,    -1,    -1,   117,   116,    -1,    46,
      14,    89,     4,    -1,    25,     3,    -1,    47,    16,    14,
      16,     3,   101,     4,    -1,    -1,   119,   120,    -1,    50,
      16,     3,   103,     4,    -1,    -1,   121,   122,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   344,   344,   355,   357,   359,   362,   366,   344,   380,
     383,   384,   387,   388,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   424,   427,   437,   470,   472,   476,   489,   496,
     503,   512,   514,   518,   528,   539,   550,   573,   576,   587,
     620,   622,   627,   642,   651,   675,   676,   681,   684,   694,
     706,   718,   727,   737,   751,   752,   753,   754,   755,   757,
     759,   764,   766,   771,   790,   812,   815,   825,   836,   838,
     850,   865,   867,   872,   881,   892,   903,   913,   930,   933,
     943,   962,   965,   975,  1007,  1011,  1030,  1031,  1034,  1041,
    1051,  1058,  1068,  1075,  1086,  1087,  1088,  1091,  1092,  1094,
    1095,  1096,  1097,  1099,  1102,  1103,  1110,  1113,  1126,  1134,
    1137,  1147,  1158,  1163,  1178,  1181,  1191,  1206,  1208
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
  "T_NAN", "$accept", "dbc", "$@1", "$@2", "$@3", "$@4", "$@5", "$@6",
  "version", "symbol_section", "symbol_list", "symbol", "envvar_list",
  "envvar", "envvar_data_list", "envvar_data", "attribute_value",
  "attribute_list", "attribute", "attribute_rel_list", "attribute_rel",
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    62,    63,    64,    65,    66,    67,    61,    68,
      69,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    72,    73,    74,    74,    75,    76,    76,
      76,    77,    77,    78,    78,    78,    78,    79,    79,    80,
      81,    81,    82,    82,    82,    83,    83,    84,    84,    85,
      85,    85,    85,    85,    86,    86,    86,    86,    86,    86,
      86,    87,    87,    88,    88,    89,    89,    90,    91,    91,
      92,    93,    93,    94,    94,    94,    94,    94,    95,    95,
      96,    97,    97,    98,    99,    99,   100,   101,   102,   102,
     103,   103,   104,   104,   105,   105,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   113,   114,   114,   115,   116,
     116,   117,   118,   119,   120,   120,   121,   122,   122
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,     0,     0,     0,    23,     2,
       2,     3,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     2,    15,     0,     2,     5,     1,     1,
       1,     0,     2,     4,     6,     6,     7,     0,     2,     9,
       0,     2,     4,     4,     4,     1,     1,     0,     2,     6,
       6,     4,     5,     6,     1,     2,     2,     2,     2,     2,
       2,     0,     2,     5,     4,     0,     2,     2,     0,     2,
       6,     0,     2,     3,     5,     5,     5,     6,     0,     2,
       7,     0,     2,    22,     0,     1,     1,     1,     1,     2,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     2,     3,     0,
       2,     4,     2,     7,     0,     2,     5,     0,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     9,     0,     0,    10,
       0,     0,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      11,    12,   132,     0,     3,    13,   126,   129,   126,   128,
       0,     4,   129,   127,    85,    98,   130,     0,     0,    85,
       0,     5,    98,    87,   131,    86,     0,   137,    99,     0,
       0,   137,    42,     0,     0,   138,     0,     6,    42,     0,
       0,     0,    45,    43,   101,   110,     0,     0,     0,    91,
      45,     0,   100,   101,     0,   136,     0,     0,     0,    67,
      91,    46,   106,   104,   102,   111,     0,     0,     0,     0,
       0,     0,     0,    74,     0,     7,    67,     0,    92,   105,
       0,     0,     0,    93,     0,     0,     0,     0,    76,    75,
      77,    78,    79,    80,    60,    68,     0,     0,     0,    47,
       0,     0,     0,     0,    65,    66,    51,    60,     0,     0,
       0,     0,     0,     0,   117,     0,     0,    96,    95,     0,
      94,     0,    57,    51,    61,     0,     0,   116,   114,   115,
       0,    71,   112,     0,     0,     0,     0,    97,     0,     0,
      81,    57,    52,     0,     0,     0,     0,     0,     0,    72,
       0,   118,     0,     0,    49,    48,    50,     0,     0,     0,
       0,     0,     0,    88,    81,    58,    64,    62,    63,    69,
      70,   113,    73,     0,     0,     0,     0,     0,    53,     0,
      85,     0,     0,   134,    88,    82,   123,     0,     0,     0,
       0,     0,     0,     0,    85,     0,     0,   134,     8,    89,
     124,   125,     0,     0,    55,    54,     0,     0,    84,     0,
       0,     0,   135,     0,     0,    56,     0,    83,     0,     0,
     119,     0,    44,     0,     0,     0,     0,     0,    90,     0,
     120,     0,    59,   108,     0,   107,     0,   109,   133,     0,
     121,     0,     0,   122,     0,     0,     0,   103
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    47,    55,    67,    82,   134,     5,     8,
      40,    41,    77,    78,    89,    90,   200,   162,   163,   180,
     181,   146,   147,   148,   115,   116,   117,   203,   204,    58,
      59,   223,   224,    99,   100,    61,    62,    92,    93,   120,
     103,   274,   275,    86,   173,   170,   155,   192,   261,   271,
     281,   284,   227,   242,    49,    44,    51,    52,    11,   237,
     238,    71,    72
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -215
static const yytype_int16 yypact[] =
{
    -215,    10,     0,  -215,     6,    17,  -215,    47,    57,    22,
      80,    58,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,    22,  -215,    83,  -215,  -215,    11,    41,    11,  -215,
      74,  -215,    41,  -215,    75,    65,  -215,    77,    86,    75,
      78,  -215,    65,  -215,  -215,  -215,    79,    45,  -215,    93,
      81,    45,    71,    84,    98,  -215,    88,  -215,    71,    89,
      90,   102,    66,  -215,    82,    94,   104,    96,    99,    85,
      66,   101,  -215,    82,    90,  -215,   108,   107,     2,   -24,
      85,  -215,  -215,   105,  -215,  -215,   106,   109,   114,   110,
     113,   112,   115,    13,   -18,  -215,   -24,   116,  -215,  -215,
     117,   118,   120,  -215,   119,   121,   123,   124,  -215,  -215,
    -215,  -215,  -215,  -215,   -29,  -215,    12,   122,   125,  -215,
     126,   128,   127,   129,  -215,  -215,   111,   -29,   130,   131,
     -11,   136,   133,   134,  -215,   138,   141,  -215,  -215,   142,
    -215,   137,    69,   111,  -215,    -1,   139,  -215,  -215,  -215,
     -11,  -215,   140,   150,   143,   144,   146,  -215,    -4,   148,
     132,    69,  -215,   152,   153,   154,   160,   161,   133,  -215,
     163,  -215,   162,   155,  -215,  -215,  -215,   156,   159,   158,
     165,   135,    33,    87,   132,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,   164,   166,    28,    28,   167,  -215,   169,
      75,   101,   168,   147,    87,  -215,  -215,    73,   145,   171,
     173,    28,   151,   175,    75,   172,   174,   147,  -215,  -215,
    -215,  -215,   176,    90,  -215,  -215,   181,   177,  -215,   184,
     188,   182,  -215,   -11,   191,  -215,   101,  -215,   183,   185,
    -215,   157,  -215,    28,   193,   195,   -11,   196,  -215,   190,
    -215,   194,  -215,   190,   198,  -215,   199,  -215,  -215,   -11,
    -215,   200,   -11,  -215,   197,   201,    90,  -215
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
     170,  -215,   149,  -215,   178,  -215,  -212,    46,  -215,    29,
    -215,    67,  -215,  -215,    97,  -215,  -215,     8,  -215,   -58,
    -215,    -9,  -215,   179,  -215,   180,  -215,   187,  -215,  -215,
    -214,  -215,   -56,   -94,    30,  -168,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,   186,  -215,   189,  -215,  -215,  -215,
     -17,  -215,   192
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     105,    65,   187,   229,   230,   167,   168,   234,   113,   144,
       3,   194,   195,   196,   183,   184,   185,   108,     4,   246,
     197,     6,   198,   199,   145,    48,   109,   114,   110,   111,
     112,   149,   150,   151,   152,   153,   132,   128,   133,   129,
     130,   131,   263,   194,   195,   196,     7,   220,   169,   221,
       9,   267,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
     240,   241,    10,    42,    43,   260,    46,    50,    54,    60,
      64,    57,    63,    69,    66,    70,    73,    74,   270,    76,
      79,    80,    81,    84,    85,    87,    88,    94,    95,    91,
     107,   280,    96,    97,   283,   102,    98,   106,   123,   119,
     137,   179,   121,   138,   139,   122,   124,   125,   126,   127,
     157,   136,   158,   160,   140,   222,   141,   142,   154,   143,
     171,   156,   159,   175,   161,   165,   177,   166,   172,   254,
     174,   176,   178,   188,   189,   186,   206,   207,   208,   190,
     191,   193,   233,   201,   209,   210,   202,   212,   213,   218,
     266,   214,   215,   216,   217,   244,   249,   245,   247,   248,
     226,   231,   228,   232,   235,   255,   250,   253,   257,   219,
     251,   258,   287,   256,   236,   262,   259,   268,   269,   264,
     272,   265,   278,   243,   273,   282,   276,   285,   279,   182,
     205,    45,   225,   135,   164,   239,   286,   277,   211,     0,
     252,     0,     0,     0,     0,     0,     0,    83,     0,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,    56,    68,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    75,     0,     0,     0,     0,   101,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   118,
     104
};

static const yytype_int16 yycheck[] =
{
      94,    59,   170,   215,   216,    16,    17,   221,    32,    38,
       0,    15,    16,    17,    15,    16,    17,    15,    18,   231,
      24,    15,    26,    27,    53,    14,    24,    51,    26,    27,
      28,    19,    20,    21,    22,    23,    54,    24,    56,    26,
      27,    28,   256,    15,    16,    17,    29,    14,    59,    16,
       3,   263,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
       7,     8,    25,     3,    26,   253,     3,    46,    14,    24,
       4,    16,    15,    14,    16,    50,     3,    16,   266,    28,
      16,     3,    14,    14,    14,     3,    40,    13,     4,    27,
       3,   279,    16,    14,   282,    14,    31,     9,     4,    14,
       3,    52,    16,     5,     4,    16,    16,    14,    16,    14,
       4,    15,     4,     4,    15,    48,    15,    14,    16,    15,
       4,    16,    15,     5,    33,    15,     4,    16,    15,   243,
      16,    10,    15,    13,     4,    16,     4,     4,     4,    16,
      16,    15,   220,    15,     4,     4,    34,     4,     6,     4,
      13,    16,    16,    14,    16,     4,   234,     4,    27,     4,
      16,    14,    16,    14,    16,     4,    14,    11,     4,    54,
      16,     3,   286,    16,    47,     4,    14,     4,     3,    16,
       4,    16,     4,    58,    14,     5,    12,    10,     9,   163,
     181,    41,   204,   116,   147,   224,    15,   273,   188,    -1,
     237,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,    -1,    -1,    -1,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,
      93
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    61,    62,     0,    18,    68,    15,    29,    69,     3,
      25,   118,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      70,    71,     3,    26,   115,    70,     3,    63,    14,   114,
      46,   116,   117,   114,    14,    64,   116,    16,    89,    90,
      24,    95,    96,    15,     4,    89,    16,    65,    95,    14,
      50,   121,   122,     3,    16,   122,    28,    72,    73,    16,
       3,    14,    66,    72,    14,    14,   103,     3,    40,    74,
      75,    27,    97,    98,    13,     4,    16,    14,    31,    93,
      94,    74,    14,   100,    97,   103,     9,     3,    15,    24,
      26,    27,    28,    32,    51,    84,    85,    86,    93,    14,
      99,    16,    16,     4,    16,    14,    16,    14,    24,    26,
      27,    28,    54,    56,    67,    84,    15,     3,     5,     4,
      15,    15,    14,    15,    38,    53,    81,    82,    83,    19,
      20,    21,    22,    23,    16,   106,    16,     4,     4,    15,
       4,    33,    77,    78,    81,    15,    16,    16,    17,    59,
     105,     4,    15,   104,    16,     5,    10,     4,    15,    52,
      79,    80,    77,    15,    16,    17,    16,   105,    13,     4,
      16,    16,   107,    15,    15,    16,    17,    24,    26,    27,
      76,    15,    34,    87,    88,    79,     4,     4,     4,     4,
       4,   104,     4,     6,    16,    16,    14,    16,     4,    54,
      14,    16,    48,    91,    92,    87,    16,   112,    16,    76,
      76,    14,    14,    89,   100,    16,    47,   119,   120,    91,
       7,     8,   113,    58,     4,     4,    76,    27,     4,    89,
      14,    16,   120,    11,   103,     4,    16,     4,     3,    14,
     105,   108,     4,   100,    16,    16,    13,    76,     4,     3,
     105,   109,     4,    14,   101,   102,    12,   102,     4,     9,
     105,   110,     5,   105,   111,    10,    15,   103
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1464 of yacc.c  */
#line 344 "parser.y"
    {
        CREATE(network_t, network);
        current_dbc = (dbc_t *)dbcptr;
        current_dbc->network = network;
        current_dbc->network->comment = NULL;
        current_dbc->network->attribute_list = NULL;
      }
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 355 "parser.y"
    { current_dbc->node_list = (yyvsp[(5) - (5)].node_list); }
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 357 "parser.y"
    { current_dbc->valtable_list = (yyvsp[(7) - (7)].valtable_list); }
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 359 "parser.y"
    { current_dbc->message_list = (yyvsp[(9) - (9)].message_list); }
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 362 "parser.y"
    { current_dbc->envvar_list  = (yyvsp[(12) - (12)].envvar_list); }
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 366 "parser.y"
    { current_dbc->attribute_definition_list = (yyvsp[(16) - (16)].attribute_definition_list); }
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 373 "parser.y"
    {
        current_dbc->version            = (yyvsp[(2) - (23)].string);
        current_dbc->signal_group_list  = (yyvsp[(23) - (23)].signal_group_list);
	current_dbc->attribute_rel_list = (yyvsp[(20) - (23)].attribute_rel_list);
      }
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 380 "parser.y"
    { (yyval.string) = (yyvsp[(2) - (2)].string); }
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 424 "parser.y"
    {
      (yyval.envvar_list) = NULL;
    }
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 428 "parser.y"
    {
      CREATE(envvar_list_t,list);
      list->envvar = (yyvsp[(1) - (2)].envvar);
      list->next   = (yyvsp[(2) - (2)].envvar_list);
      (yyval.envvar_list) = list;
    }
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 452 "parser.y"
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

  case 47:

/* Line 1464 of yacc.c  */
#line 479 "parser.y"
    {
        free((yyvsp[(2) - (5)].string));
      }
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 490 "parser.y"
    {
      CREATE(attribute_value_t, av);
      av->value_type    = vt_integer; /* preliminary value type */
      av->value.int_val = (yyvsp[(1) - (1)].number);
      (yyval.attribute_value) = av;
    }
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 497 "parser.y"
    {
      CREATE(attribute_value_t, av);
      av->value_type = vt_string;
      av->value.string_val = (yyvsp[(1) - (1)].string);
      (yyval.attribute_value) = av;
    }
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 504 "parser.y"
    {
      CREATE(attribute_value_t, av);
      av->value_type = vt_float;
      av->value.double_val = (yyvsp[(1) - (1)].double_val);
      (yyval.attribute_value) = av;
    }
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 519 "parser.y"
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

  case 54:

/* Line 1464 of yacc.c  */
#line 529 "parser.y"
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

  case 55:

/* Line 1464 of yacc.c  */
#line 540 "parser.y"
    {
      message_t *const message = message_find((yyvsp[(4) - (6)].number));
      if(message != NULL) {
        attribute_append(&message->attribute_list,(yyvsp[(2) - (6)].string),(yyvsp[(5) - (6)].attribute_value));
      } else {
        fprintf(stderr,"error: message %d not found\n", (int)(yyvsp[(4) - (6)].number));
        attribute_value_free((yyvsp[(5) - (6)].attribute_value));
        free((yyvsp[(2) - (6)].string));
      }
    }
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 557 "parser.y"
    {
      signal_t *const signal = signal_find((yyvsp[(4) - (7)].number),(yyvsp[(5) - (7)].string));

      if(signal != NULL) {
        attribute_append(&signal->attribute_list,(yyvsp[(2) - (7)].string),(yyvsp[(6) - (7)].attribute_value));
      } else {
        fprintf(stderr,"error: signal %d (%s) not found\n", (int)(yyvsp[(4) - (7)].number), (yyvsp[(5) - (7)].string));
        attribute_value_free((yyvsp[(6) - (7)].attribute_value));
        free((yyvsp[(2) - (7)].string));
      }
      free((yyvsp[(5) - (7)].string));
    }
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 573 "parser.y"
    {
      (yyval.attribute_rel_list) = NULL;
    }
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 577 "parser.y"
    {
      CREATE(attribute_rel_list_t,list);
      list->attribute_rel = (yyvsp[(1) - (2)].attribute_rel);
      list->next          = (yyvsp[(2) - (2)].attribute_rel_list);
      (yyval.attribute_rel_list) = list;
    }
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 596 "parser.y"
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

  case 62:

/* Line 1464 of yacc.c  */
#line 629 "parser.y"
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

  case 63:

/* Line 1464 of yacc.c  */
#line 644 "parser.y"
    {
      attribute_definition_t *const ad = attribute_definition_find((yyvsp[(2) - (4)].string), (yyvsp[(1) - (4)].attribute_object_class));
      free((yyvsp[(2) - (4)].string));
      if(ad != NULL && ad->value_type == vt_float) {
        ad->default_value.double_val = (yyvsp[(3) - (4)].double_val);
      }
    }
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 653 "parser.y"
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

  case 65:

/* Line 1464 of yacc.c  */
#line 675 "parser.y"
    { (yyval.attribute_object_class) = aoc_object; }
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 676 "parser.y"
    { (yyval.attribute_object_class) = aoc_relation; }
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 681 "parser.y"
    {
      (yyval.attribute_definition_list) = NULL;
    }
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 685 "parser.y"
    {
      CREATE(attribute_definition_list_t,list);
      list->attribute_definition = (yyvsp[(1) - (2)].attribute_definition);
      list->next                 = (yyvsp[(2) - (2)].attribute_definition_list);
      (yyval.attribute_definition_list) = list;
    }
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 696 "parser.y"
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

  case 70:

/* Line 1464 of yacc.c  */
#line 708 "parser.y"
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

  case 71:

/* Line 1464 of yacc.c  */
#line 719 "parser.y"
    {
      CREATE(attribute_definition_t,ad);
      ad->object_type              = (yyvsp[(1) - (4)].object_type);
      ad->name                     = (yyvsp[(2) - (4)].string);
      ad->value_type               = vt_string;
      ad->default_value.string_val = NULL;
      (yyval.attribute_definition) = ad;
    }
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 728 "parser.y"
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

  case 73:

/* Line 1464 of yacc.c  */
#line 738 "parser.y"
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

  case 74:

/* Line 1464 of yacc.c  */
#line 751 "parser.y"
    { (yyval.object_type) = ot_network; }
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 752 "parser.y"
    { (yyval.object_type) = ot_node; }
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 753 "parser.y"
    { (yyval.object_type) = ot_message; }
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 754 "parser.y"
    { (yyval.object_type) = ot_signal; }
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 755 "parser.y"
    { (yyval.object_type) = ot_envvar; }
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 757 "parser.y"
    { (yyval.object_type) = ot_node_signal; }
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 759 "parser.y"
    { (yyval.object_type) = ot_node_message; }
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 772 "parser.y"
    {
      signal_t *const signal = signal_find((yyvsp[(2) - (5)].number),(yyvsp[(3) - (5)].signal_name));

      if(signal != NULL) {
        if(signal->val_map == NULL) {
          signal->val_map = (yyvsp[(4) - (5)].val_map);
        } else {
          fprintf(stderr,
                  "error: duplicate val_map for signal %d (%s)\n", (int)(yyvsp[(2) - (5)].number), (yyvsp[(3) - (5)].signal_name));
          val_map_free((yyvsp[(4) - (5)].val_map));
        }
      } else {
        fprintf(stderr,"error: signal %d (%s) not found\n", (int)(yyvsp[(2) - (5)].number), (yyvsp[(3) - (5)].signal_name));
        val_map_free((yyvsp[(4) - (5)].val_map));
      }
      free((yyvsp[(3) - (5)].signal_name));
    }
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 791 "parser.y"
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

  case 85:

/* Line 1464 of yacc.c  */
#line 812 "parser.y"
    {
      (yyval.val_map) = NULL;
    }
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 816 "parser.y"
    {
      CREATE(val_map_t, val_map);
      val_map->val_map_entry = (yyvsp[(1) - (2)].val_map_entry);
      val_map->next          = (yyvsp[(2) - (2)].val_map);
      (yyval.val_map) = val_map;
    }
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 826 "parser.y"
    {
      CREATE(val_map_entry_t, val_map_entry);
      val_map_entry->index = (yyvsp[(1) - (2)].number);
      val_map_entry->value = (yyvsp[(2) - (2)].string);
      (yyval.val_map_entry) = val_map_entry;
    }
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 851 "parser.y"
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

  case 93:

/* Line 1464 of yacc.c  */
#line 873 "parser.y"
    {
      if(current_dbc->network != NULL) {
	current_dbc->network->comment =
	  string_merge(current_dbc->network->comment, (yyvsp[(2) - (3)].string));
      } else {
	string_free((yyvsp[(2) - (3)].string));
      }
    }
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 882 "parser.y"
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

  case 95:

/* Line 1464 of yacc.c  */
#line 893 "parser.y"
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

  case 96:

/* Line 1464 of yacc.c  */
#line 904 "parser.y"
    {
      message_t *const message = message_find((yyvsp[(3) - (5)].number));
      if(message != NULL) {
	message->comment = string_merge(message->comment, (yyvsp[(4) - (5)].string));
      } else {
        fprintf(stderr,"error: message %s not found\n", (yyvsp[(4) - (5)].string));
        string_free((yyvsp[(4) - (5)].string));
      }
    }
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 914 "parser.y"
    {
      signal_t *const signal = signal_find((yyvsp[(3) - (6)].number), (yyvsp[(4) - (6)].string));
      if(signal != NULL) {
	signal->comment = string_merge(signal->comment, (yyvsp[(5) - (6)].string));
      } else {
        fprintf(stderr,"error: signal %d (%s) not found\n", (int)(yyvsp[(3) - (6)].number), (yyvsp[(4) - (6)].string));
        string_free((yyvsp[(5) - (6)].string));
      }
      string_free((yyvsp[(4) - (6)].string));
    }
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 930 "parser.y"
    {
      (yyval.message_list) = NULL;
    }
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 934 "parser.y"
    {
      CREATE(message_list_t,list);
      list->message = (yyvsp[(1) - (2)].message);
      list->next    = (yyvsp[(2) - (2)].message_list);
      (yyval.message_list) = list;
    }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 944 "parser.y"
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

  case 101:

/* Line 1464 of yacc.c  */
#line 962 "parser.y"
    {
      (yyval.signal_list) = NULL;
    }
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 966 "parser.y"
    {
      CREATE(signal_list_t,list);
      list->signal = (yyvsp[(1) - (2)].signal);
      list->next   = (yyvsp[(2) - (2)].signal_list);
      (yyval.signal_list) = list;
    }
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 980 "parser.y"
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

  case 104:

/* Line 1464 of yacc.c  */
#line 1007 "parser.y"
    {
      (yyval.mux_info).mux_type = m_signal;
      (yyval.mux_info).mux_value = 0;
    }
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 1012 "parser.y"
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

  case 106:

/* Line 1464 of yacc.c  */
#line 1030 "parser.y"
    { (yyval.signal_name) = (string_t)(yyvsp[(1) - (1)].string); }
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 1031 "parser.y"
    { (yyval.signal_name_list) = (string_list_t *)(yyvsp[(1) - (1)].string_list); }
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 1035 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (1)].string);
      list->next   = NULL;
      (yyval.string_list) = list;
    }
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 1042 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (2)].string);
      list->next   = (yyvsp[(2) - (2)].string_list);
      (yyval.string_list) = list;
    }
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 1052 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (1)].string);
      list->next   = NULL;
      (yyval.string_list) = list;
    }
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 1059 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (3)].string);
      list->next   = (yyvsp[(3) - (3)].string_list);
      (yyval.string_list) = list;
    }
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 1069 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (1)].string);
      list->next   = NULL;
      (yyval.string_list) = list;
    }
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 1076 "parser.y"
    {
      CREATE(string_list_t,list);
      list->string = (yyvsp[(1) - (3)].string);
      list->next   = (yyvsp[(3) - (3)].string_list);
      (yyval.string_list) = list;
    }
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 1086 "parser.y"
    { (yyval.double_val) = (yyvsp[(1) - (1)].double_val); }
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 1087 "parser.y"
    { (yyval.double_val) = NAN; }
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 1088 "parser.y"
    { (yyval.double_val) = (double)(yyvsp[(1) - (1)].number); }
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 1091 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (1)].number); }
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 1092 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (1)].number); }
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 1094 "parser.y"
    { (yyval.double_val) = (yyvsp[(1) - (1)].double_val); }
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 1095 "parser.y"
    { (yyval.double_val) = (yyvsp[(1) - (1)].double_val); }
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 1096 "parser.y"
    { (yyval.double_val) = (yyvsp[(1) - (1)].double_val); }
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 1097 "parser.y"
    { (yyval.double_val) = (yyvsp[(1) - (1)].double_val); }
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 1099 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (1)].number); }
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 1102 "parser.y"
    { (yyval.number) = 0; }
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 1103 "parser.y"
    { (yyval.number) = 1; }
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 1110 "parser.y"
    {
      (yyval.node_list) = NULL;
    }
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 1114 "parser.y"
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

  case 128:

/* Line 1464 of yacc.c  */
#line 1127 "parser.y"
    {
      (yyval.node_list) = (yyvsp[(3) - (3)].node_list);
    }
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 1134 "parser.y"
    {
      (yyval.valtable_list) = NULL;
    }
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 1138 "parser.y"
    {
      CREATE(valtable_list_t, valtable_list);
      valtable_list->next     = (yyvsp[(2) - (2)].valtable_list);
      valtable_list->valtable = (yyvsp[(1) - (2)].valtable);
      (yyval.valtable_list) = valtable_list;
    }
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 1148 "parser.y"
    {
      CREATE(valtable_t, valtable);
      valtable->name    = (yyvsp[(2) - (4)].string);
      valtable->comment = NULL;
      valtable->val_map = (yyvsp[(3) - (4)].val_map);
      (yyval.valtable) = valtable;
    }
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 1165 "parser.y"
    {
      CREATE(signal_group_t,sg);
      sg->id   = (yyvsp[(2) - (7)].number);
      sg->name = (yyvsp[(3) - (7)].string);
      /* TODO: meaning of $4? */
      sg->signal_name_list = (yyvsp[(6) - (7)].signal_name_list);
      (yyval.signal_group) = sg;
    }
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 1178 "parser.y"
    {
      (yyval.signal_group_list) = NULL;
    }
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 1182 "parser.y"
    {
      CREATE(signal_group_list_t,list);
      list->signal_group = (yyvsp[(1) - (2)].signal_group);
      list->next         = (yyvsp[(2) - (2)].signal_group_list);
      (yyval.signal_group_list) = list;
    }
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 1193 "parser.y"
    {
      message_t *const message = message_find((yyvsp[(2) - (5)].number));
      if(message != NULL) {
	/* duplicate list: new one replaces old one */
	string_list_free(message->transmitter_list);
	message->transmitter_list = (yyvsp[(4) - (5)].string_list);
      } else {
        fprintf(stderr,"error: message %d not found\n", (int)(yyvsp[(2) - (5)].number));
	string_list_free((yyvsp[(4) - (5)].string_list));
      }
    }
    break;



/* Line 1464 of yacc.c  */
#line 3011 "src/libcandbc/parser.c"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



