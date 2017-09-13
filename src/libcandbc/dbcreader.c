/*  dbcReader.c --  frontend for DBC parser
    Copyright (C) 2007-2017 Andreas Heitmann

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "cantools_config.h"

#include <stdio.h>
#include <string.h>

typedef struct yy_buffer_state *YY_BUFFER_STATE;

#include "dbcmodel.h"
#include "dbcreader.h"

dbc_t *dbc_read_file(char *filename)
{
  extern void yyrestart( FILE *input_file );
  extern YY_BUFFER_STATE yy_create_buffer( FILE *file, int size );
  extern void yy_switch_to_buffer ( YY_BUFFER_STATE new_buffer );
  extern char *current_yacc_file;
  extern FILE *yyin;
  extern int yyparse (void *YYPARSE_PARAM);
  extern void yy_delete_buffer ( YY_BUFFER_STATE b );
  int error;
  YY_BUFFER_STATE bufstate;

  CREATE(dbc_t, dbc);
  if(dbc != NULL) {
    dbc->filename = NULL;
    dbc->version = NULL;
    dbc->node_list = NULL;
    dbc->valtable_list = NULL;
    dbc->message_list = NULL;
    dbc->envvar_list = NULL;
    dbc->attribute_rel_list = NULL;
    dbc->attribute_definition_list = NULL;
    dbc->signal_group_list = NULL;
    dbc->network = NULL;

    current_yacc_file = filename;

    if(filename != NULL) {
      yyin = fopen (filename, "r");
      if (yyin == NULL) {
        fprintf(stderr,"error: can't open the dbc file '%s' for reading\n",
                filename);
        dbc_free(dbc);
        return NULL;
      }
    } else {
      yyin = stdin;
    }

    yyrestart(yyin);

    bufstate = (void *)yy_create_buffer (yyin, 65535);
    yy_switch_to_buffer (bufstate);
    error = yyparse ((void *)dbc);
    yy_delete_buffer (bufstate);
    fclose (yyin);

    /* set filename */
    if(error == 0) {
      if(filename != NULL) {
        dbc->filename = strdup(filename);
      } else {
        dbc->filename = strdup("<stdin>");
      }
    } else {
      dbc->filename = NULL;
    }
  }

  return dbc;
}
