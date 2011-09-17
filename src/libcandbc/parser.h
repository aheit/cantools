/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
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



/* Line 1685 of yacc.c  */
#line 200 "src/libcandbc/parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


