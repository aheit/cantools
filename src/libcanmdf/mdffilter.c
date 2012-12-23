/*  mdffilter -- filter and transform signal names
    Copyright (C) 2012 Andreas Heitmann

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

#include <stdio.h>
#include <limits.h>
#include <fnmatch.h>
#include <stdlib.h>
#include <string.h>
#include "mdffilter.h"

extern char *strdup(const char *);
static int filter_test_channel(const mdf_t *const mdf,
			       const filter_t *const filter,
			       const cn_block_t *const cn_block);

static const filter_element_t *filter_match(const filter_element_t *const fe,
			       const uint32_t channel,
			       const char *message, const char *signal)
{
  if(fe != NULL) {
    if(fe->channel_wildcard || (fe->channel == channel))
      if(0 == fnmatch(fe->message, message,0))
	if(0 == fnmatch(fe->signal, signal,0))
	  return fe;
    return filter_match(fe->next, channel, message, signal);
  } else {
    return NULL;
  }
}

static char *
standard_name(const char *message, const char *signal)
{
  /* create matlab signal name */
  const char *src;
  char *dst;
  char *mat_name = malloc(strlen(message)+1+strlen(signal)+1);
  dst=mat_name;
	
  /* message name */
  for(src=message; *src; src++, dst++) {
    *dst=*src;
  }
  *dst++ ='_';
	
  /* signal long name */
  for(src=signal; *src; src++, dst++) {
    if(*src==':') *dst='_';
    else *dst=*src;
  }
  *dst='\0';
  return mat_name;
}

char *
filter_apply(const filter_t *filter, const uint32_t channel,
	     const char *message, const char *signal)
{
  char *mat_name = NULL;
  const filter_element_t *el;

  if(filter) {
    el = filter_match(filter->first, channel, message, signal);
    if(el != NULL) {             /* element found? */
      if(el->operation == '+') { /* accept? */
	if(el->newname) {        /* new name given? */
	  mat_name = strdup(el->newname);
	} else {                 /* no new name given */
	  mat_name = standard_name(message, signal);
	}
      }
    }
  } else {                       /* no filter */
    mat_name = standard_name(message, signal);
  }
  return mat_name;
}

int
filter_test_channel(const mdf_t *const mdf,
		    const filter_t *const filter,
		    const cn_block_t *const cn_block)
{
  uint32_t can_id, can_channel;
  ce_block_t *ce_block;
  char *message;
  const char *name;

    /* signal name */
  name = cn_get_long_name(mdf, cn_block);
  
  /* message info */
  ce_block = ce_block_get(mdf, cn_block->link_extensions);
  if(ce_block != NULL && ce_block->extension_type == 19) {
    message = ce_block->supplement.vector_can.message_name;
    can_id = ce_block->supplement.vector_can.can_id;
    can_channel = ce_block->supplement.vector_can.can_channel;
  } else {
    message = "none";
    can_id = 0;
    can_channel = 0;
  }
  
  return filter_apply(filter, can_channel, message, name) != NULL;
}

int
filter_test_channel_group(const mdf_t *const mdf,
		    const filter_t *const filter,
		    const cg_block_t *const cg_block)
{
  const cn_block_t *cn_block;

  for( cn_block = cn_block_get(mdf, cg_block->link_cn_block);
       cn_block;
       cn_block = cn_block_get(mdf, cn_block->link_next_cn_block)) {
    if(filter_test_channel(mdf, filter, cn_block)) {
      return 1;
    }
  }
  return 0;
}

filter_t *
mdf_filter_create(const char *filename)
{
  filter_t *filter = (filter_t *)malloc(sizeof(filter_t));
  filter_element_t **next_filter_element;
  FILE *fp;
  char line[LINE_MAX];
  char *token;
  char_t operation;
  uint32_t channel;
  uint8_t channel_wildcard;
  char *message;
  char *signal;
  char *newname;

  filter->first = NULL;
  next_filter_element = &(filter->first);
  fp = fopen(filename,"r");
  if(fp) {
    int linenr = 0;
    while(fgets(line, LINE_MAX, fp) != NULL) {
      linenr++;
      if((line[0] == '/') && (line[1] == '/')) continue;
      if(line[0] == '\n') continue;
      if(line[0] == '\r') continue;

      token = strtok(line, " \t\r\n");
      if(token == NULL) {
	fprintf(stderr, "error: can't parse filter operation, line %d\n",linenr);
	goto ERROR;
      }

      /* operation */
      if((token[0] == '+') || (token[0]=='-')) {
	operation = token[0];
      } else {
	fprintf(stderr, "error: unexpected filter operation '%c' (ascii %d). Please use + or - to allow or reject signals\n",
		token[0], token[0]);
	goto ERROR;
      }

      /* CAN channel */
      token = strtok(NULL, " \t\r\n");
      if(token == NULL) {
	fprintf(stderr, "error: can't parse channel number, line %d\n",linenr);
	goto ERROR;
      }
      channel_wildcard = (token[0] == '*');
      if(channel_wildcard) {
	channel = 0;
      } else {
	if(1 != sscanf(token,"%lu",(unsigned long *)&channel)) {
	  fprintf(stderr, "error: can't parse channel number %s\n",token);
	  goto ERROR;
	}
      }

      /* message name */
      token = strtok(NULL, " \t\r\n");
      if(token == NULL) {
	fprintf(stderr, "error: can't parse message name, line %d\n",linenr);
	goto ERROR;
      }
      message = token;

      /* signal name */
      token = strtok(NULL, " \t\r\n");
      if(token == NULL) {
	fprintf(stderr, "error: can't parse signal name, line %d\n",linenr);
	goto ERROR;
      }
      signal = token;

      /* new name */
      token = strtok(NULL, " \t\r\n");
      newname = token;

      /* create element */
      {
	filter_element_t *filter_element =
	  (filter_element_t *)malloc(sizeof(filter_element_t));
	filter_element->next = NULL;
	filter_element->operation = operation;
	filter_element->channel = channel;
	filter_element->channel_wildcard = channel_wildcard;
	filter_element->message = strdup(message);
	filter_element->signal  = strdup(signal);
	if(newname != NULL) {
	  filter_element->newname = strdup(newname);
	} else {
	  filter_element->newname = NULL;
	}
	*next_filter_element = filter_element;
	next_filter_element = &(filter_element->next);
      }

      
    }
    fclose(fp);
    goto OK;
  } else {
    fprintf(stderr, "error: can't read filter file %s\n",filename);
    goto ERROR;
  }
ERROR:
  free(filter);
  filter = NULL;
OK:
  return filter;
}

static void
filter_element_free(filter_element_t *filter_element)
{
  if(filter_element->next) filter_element_free(filter_element->next);
  if(filter_element->message) free(filter_element->message);
  if(filter_element->signal) free(filter_element->signal);
  if(filter_element->newname) free(filter_element->newname);
  free(filter_element);
}

void
filter_free(filter_t *filter)
{
  if(filter != NULL) {
    filter_element_free(filter->first);
    free(filter);
  }
}

