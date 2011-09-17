/*  dbcWriter.c --  function for serializing the DBC model to a file
    Copyright (C) 2007-2009 Andreas Heitmann

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
#include <string.h>

typedef struct yy_buffer_state *YY_BUFFER_STATE;

#include <dbcModel.h>
#include <dbcWriter.h>

#define PLIST_ITER(iter) \
  for(;iter != NULL; iter = iter->next)

#define NEWLINE "\r\n"

#define newline(out) fputs(NEWLINE, out);

static void string_write(FILE *out, string_t string)
{
  if(string != NULL) {
    fprintf(out,"\"%s\"",string);
  } else {
    fputs("\"\"", out);
  }
}

static void identifier_write(FILE *out, string_t string)
{
  if(string != NULL) {
    fputs(string, out);
  }
}

static void comma_identifier_list_write(FILE *out, string_list_t *string_list)
{
  PLIST_ITER(string_list) {
    identifier_write(out, string_list->string);
    if(string_list->next) fputc(',', out);
  }
}

static void comma_string_list_write(FILE *out, string_list_t *string_list)
{
  PLIST_ITER(string_list) {
    string_write(out, string_list->string);
    if(string_list->next) fputc(',', out);
  }
}

static void space_identifier_list_write(FILE *out, string_list_t *string_list)
{
  PLIST_ITER(string_list) {
    identifier_write(out, string_list->string);
    if(string_list->next) fputc(' ', out);
  }
}

static void version_write(FILE *out, string_t version)
{
  fputs("VERSION ", out);
  string_write(out, version);
  newline(out);
}

static void symbol_write(FILE *out)
{
  newline(out);
  fprintf(out,
	  "NS_ : " NEWLINE
	  "	NS_DESC_" NEWLINE
	  "	CM_" NEWLINE
	  "	BA_DEF_" NEWLINE
	  "	BA_" NEWLINE
	  "	VAL_" NEWLINE
	  "	CAT_DEF_" NEWLINE
	  "	CAT_" NEWLINE
	  "	FILTER" NEWLINE
	  "	BA_DEF_DEF_" NEWLINE
	  "	EV_DATA_" NEWLINE
	  "	ENVVAR_DATA_" NEWLINE
	  "	SGTYPE_" NEWLINE
	  "	SGTYPE_VAL_" NEWLINE
	  "	BA_DEF_SGTYPE_" NEWLINE
	  "	BA_SGTYPE_" NEWLINE
	  "	SIG_TYPE_REF_" NEWLINE
	  "	VAL_TABLE_" NEWLINE
	  "	SIG_GROUP_" NEWLINE
	  "	SIG_VALTYPE_" NEWLINE
	  "	SIGTYPE_VALTYPE_" NEWLINE
	  "	BO_TX_BU_" NEWLINE
	  "	BA_DEF_REL_" NEWLINE
	  "	BA_REL_" NEWLINE
	  "	BA_DEF_DEF_REL_" NEWLINE
	  "	BU_SG_REL_" NEWLINE
	  "	BU_EV_REL_" NEWLINE
	  "	BU_BO_REL_" NEWLINE
	  "	SG_MUL_VAL_" NEWLINE);
}

static void message_section_write(FILE *out)
{
  fprintf(out, "BS_:" NEWLINE);
}

static void node_list_write(FILE *out, node_list_t *node_list)
{
  fprintf(out, "BU_: ");

  PLIST_ITER(node_list) {
    identifier_write(out, node_list->node->name);
    if(node_list->next) fputc(' ', out);
  }
  newline(out);
}

static void val_map_entry_write(FILE *out, val_map_entry_t *val_map_entry)
{
  fprintf(out, "%lu \"%s\" ",
	  val_map_entry->index,
	  val_map_entry->value);
}

static void val_map_write(FILE *out, val_map_t *val_map)
{
  PLIST_ITER(val_map) {
    val_map_entry_write(out, val_map->val_map_entry);
  }
}

static void valtable_write(FILE *out, valtable_t *valtable)
{
  fputs("VAL_TABLE_ ", out);
  identifier_write(out, valtable->name);
  fputc(' ', out);
  val_map_write(out, valtable->val_map);
  fputs(";" NEWLINE, out);
}

static void valtable_list_write(FILE *out, valtable_list_t *valtable_list)
{
  PLIST_ITER(valtable_list) {
    valtable_write(out, valtable_list->valtable);
  }
  newline(out);
}

static void mux_info_write(FILE *out, signal_t *signal)
{
  switch(signal->mux_type) {
  case m_multiplexor:
    fputc('M', out);
    break;
  case m_multiplexed:
    fputc('m', out);
    fprintf(out,"%lu",signal->mux_value);
    break;
  case m_signal:
  default:
    break;
  }
  fputc(' ', out);
}

static void signal_write(FILE *out, signal_t *signal)
{
  fprintf(out, " SG_ %s", signal->name);
  mux_info_write(out,signal);
  fprintf(out, ": %u|%u@%u%c (%.11G,%.11G) [%.11G|%.11G] ",
	  signal->bit_start,
	  signal->bit_len,
	  signal->endianess,
	  signal->signedness?'-':'+',
	  signal->scale,
	  signal->offset,
	  signal->min,
	  signal->max);
  string_write(out,signal->unit);
  fputs("  ", out);
  comma_identifier_list_write(out, signal->receiver_list);
  newline(out);
}

static void signal_list_write(FILE *out, signal_list_t *signal_list)
{
  PLIST_ITER(signal_list) {
    signal_write(out, signal_list->signal);
  }
  newline(out);
}

static void message_write(FILE *out, message_t *message)
{
  fprintf(out, "BO_ %lu %s: %u %s" NEWLINE,
	  message->id,
	  message->name,
	  message->len,
	  message->sender);
  signal_list_write(out, message->signal_list);
}

static void message_list_write(FILE *out, message_list_t *message_list)
{
  PLIST_ITER(message_list) {
    message_write(out, message_list->message);
  }
}

static void envvar_comment_write(FILE *out, envvar_t *envvar)
{
  if(envvar->comment != NULL) {
    fputs("CM_ EV_ ", out);
    identifier_write(out, envvar->name);
    fputc(' ', out);
    string_write(out, envvar->comment);
    fputs(";" NEWLINE, out);
  }
}

static void node_comment_write(FILE *out, node_t *node)
{
  if(node->comment != NULL) {
    fprintf(out, "CM_ BU_ %s \"%s\";" NEWLINE, node->name, node->comment);
  }
}

static void message_comment_write(FILE *out, message_t *message)
{
  if(message->comment != NULL) {
    fprintf(out, "CM_ BO_ %lu \"%s\";" NEWLINE, message->id, message->comment);
  }
}

static void signal_comment_write(FILE *out, uint32 id, signal_t *signal)
{
  if(signal->comment != NULL) {
    fprintf(out, "CM_ SG_ %lu ",id);
    identifier_write(out, signal->name);
    fputc(' ', out);
    string_write(out, signal->comment);
    fputs(";" NEWLINE, out);
  }
}

static void comment_list_write(FILE *out, dbc_t *dbc)
{
  if(dbc->network->comment != NULL) {
    fputs("CM_ ", out);
    string_write(out,dbc->network->comment);
    fputs(";" NEWLINE, out);
  }

  {
    envvar_list_t *envvar_list = dbc->envvar_list;
    PLIST_ITER(envvar_list) {
      envvar_comment_write(out, envvar_list->envvar); 
    }
  }
  {
    node_list_t *node_list = dbc->node_list;
    PLIST_ITER(node_list) {
      node_comment_write(out, node_list->node); 
    }
  }
  {
    message_list_t *message_list = dbc->message_list;
    PLIST_ITER(message_list) {
      message_comment_write(out, message_list->message); 
    }
  }
  {
    message_list_t *message_list = dbc->message_list;
    PLIST_ITER(message_list) {
      signal_list_t *signal_list = message_list->message->signal_list;
      PLIST_ITER(signal_list) {
	signal_comment_write(out,
			     message_list->message->id,
			     signal_list->signal); 
      }
    }
  }
}

static void attribute_definition_write(
  FILE *out, attribute_definition_t *attribute_definition)
{
  switch(attribute_definition->object_type) {
  case ot_network: fputs("BA_DEF_", out); break;
  case ot_node:    fputs("BA_DEF_ BU_", out); break;
  case ot_message: fputs("BA_DEF_ BO_", out); break;
  case ot_signal:  fputs("BA_DEF_ SG_", out); break;
  case ot_envvar:  fputs("BA_DEF_ EV_", out); break;
  case ot_node_signal:  fputs("BA_DEF_REL_ BU_SG_REL_", out); break;
  case ot_node_message: fputs("BA_DEF_REL_ BU_BO_REL_", out); break;
  default: break;
  }

  fputs("  ", out);

  string_write(out, attribute_definition->name);

  switch(attribute_definition->value_type) {
  case vt_integer:
    fprintf(out," INT %ld %ld", 
	    attribute_definition->range.int_range.min,
	    attribute_definition->range.int_range.max);
    break;
  case vt_float:
    fprintf(out," FLOAT %lg %lg", 
	    attribute_definition->range.double_range.min,
	    attribute_definition->range.double_range.max);
    break;
  case vt_string:
    fprintf(out," STRING ");
    break;
  case vt_enum:
    fprintf(out," ENUM  ");
    comma_string_list_write(out,attribute_definition->range.enum_list);
    break;
  case vt_hex:
    fprintf(out," HEX %ld %ld", 
	    attribute_definition->range.hex_range.min,
	    attribute_definition->range.hex_range.max);
    break;
  }
  fputs(";" NEWLINE, out);
}

static void attribute_definition_list_write(
  FILE *out, attribute_definition_list_t *attribute_definition_list)
{
  PLIST_ITER(attribute_definition_list) {
    attribute_definition_write(out,
      attribute_definition_list->attribute_definition);
  }
}
static void value_write(
  FILE *out,
  value_type_t value_type,
  value_union_t value)
{
  switch(value_type) {
  case vt_integer:
    fprintf(out,"%ld", value.int_val);
    break;
  case vt_float:
    fprintf(out,"%lg", value.double_val);
    break;
  case vt_string:
    string_write(out, value.string_val);
    break;
  case vt_enum:
    string_write(out, value.enum_val);
    break;
  case vt_hex:
    fprintf(out,"%lu", value.hex_val);
    break;
  }
}

static void attribute_definition_default_write(
  FILE *out,
  attribute_definition_t *attribute_definition,
  attribute_object_class_t aoc)
{
  switch(aoc) {
  case aoc_object:   fputs("BA_DEF_DEF_  ", out);    break;
  case aoc_relation: fputs("BA_DEF_DEF_REL_ ", out); break;
  default: break;
  }

  string_write(out, attribute_definition->name);

  fputc(' ', out);

  value_write(out,
	      attribute_definition->value_type,
	      attribute_definition->default_value);

  fputs(";" NEWLINE, out);
}

static attribute_object_class_t attribute_definition_getObjectClass(
  attribute_definition_t *ad)
{
  switch(ad->object_type) {
  case ot_network:
  case ot_node:
  case ot_message:
  case ot_signal:
    return aoc_object;
  case ot_node_signal:
  case ot_node_message:
    return aoc_relation;
  default:
    return aoc_undefined;
  }
}

static void attribute_definition_default_list_write(
  FILE *out,
  attribute_definition_list_t *attribute_definition_list,
  attribute_object_class_t aoc)
{
  PLIST_ITER(attribute_definition_list) {
    attribute_definition_t *ad =
      attribute_definition_list->attribute_definition;

    if(aoc == attribute_definition_getObjectClass(ad)) {
      attribute_definition_default_write(out,
	attribute_definition_list->attribute_definition,
	aoc);
    }
  }
}

static void attribute_value_write(FILE *out, attribute_value_t *attribute_value)
{
  value_write(out,
	      attribute_value->value_type,
	      attribute_value->value);
}

static void attribute_write(FILE *out, attribute_t *attribute, string_t target)
{
  fputs("BA_ ",out);
  string_write(out, attribute->name);
  fputc(' ', out);
  if(target != NULL) {
    fputs(target, out);
    fputc(' ', out);
  }
  attribute_value_write(out, attribute->value);
  fputs(";" NEWLINE, out);
}

static void attribute_list_write(
  FILE *out,
  attribute_list_t *attribute_list,
  string_t target)
{
  PLIST_ITER(attribute_list) {
    attribute_write(out, attribute_list->attribute, target);
  }
}

static void node_attribute_list_write(FILE *out, node_list_t *node_list)
{
  PLIST_ITER(node_list) {
    string_t target = (string_t)malloc(3+1+strlen(node_list->node->name)+1);

    sprintf(target, "BU_ %s", node_list->node->name);
    attribute_list_write(out, node_list->node->attribute_list, target);
    string_free(target);
  }
}

static void message_attribute_list_write(FILE *out, message_list_t *message_list)
{
  PLIST_ITER(message_list) {
    string_t target = (string_t)malloc(3+1+10+1);

    sprintf(target, "BO_ %lu", message_list->message->id);
    attribute_list_write(out, message_list->message->attribute_list, target);
    string_free(target);
  }
}

static void signal_attribute_list_write(FILE *out, message_list_t *message_list)
{
  PLIST_ITER(message_list) {
    const message_t *message = message_list->message;
    signal_list_t *signal_list = message->signal_list;
    PLIST_ITER(signal_list) {
      const signal_t *signal = signal_list->signal;
      if(signal->attribute_list != NULL) {
	string_t target = (string_t)malloc(3+1+10+1+strlen(signal->name)+1);
	sprintf(target, "SG_ %lu %s",
		message->id,
		signal->name);
	attribute_list_write(out, signal->attribute_list, target);
	string_free(target);
      }
    }
  }
}

static void attribute_rel_write(
  FILE *out,
  attribute_rel_t *attribute_rel)
{
  fputs("BA_REL_ ", out);
  string_write(out, attribute_rel->name);
  fputs(" BU_SG_REL_ ", out);
  identifier_write(out, attribute_rel->node->name);
  fprintf(out, " SG_ %lu ", attribute_rel->message->id);
  identifier_write(out, attribute_rel->signal->name);
  fputs(" " , out);
  attribute_value_write(out, attribute_rel->attribute_value);
  fputs(";" NEWLINE, out);
}

static void attribute_rel_list_write(
  FILE *out,
  attribute_rel_list_t *attribute_rel_list)
{
  PLIST_ITER(attribute_rel_list) {
    attribute_rel_write(out, attribute_rel_list->attribute_rel);
  }
}

static void signal_val_map_write(FILE *out, message_list_t *message_list)
{
  PLIST_ITER(message_list) {
    const message_t *message = message_list->message;
    signal_list_t *signal_list = message->signal_list;
    PLIST_ITER(signal_list) {
      const signal_t *signal = signal_list->signal;
      val_map_t *val_map = signal->val_map;
      if(val_map != NULL) {
	fprintf(out, "VAL_ %lu %s ", message->id, signal->name);
	val_map_write(out, val_map);
	fputs(";" NEWLINE, out);
      }
    }
  }
}

static void message_transmitter_list_write(
  FILE *out,
  message_list_t *message_list)
{
  PLIST_ITER(message_list) {
    const message_t *message = message_list->message;
    if(message->transmitter_list != NULL) {
      fprintf(out, "BO_TX_BU_ %lu : ", message->id);
      comma_identifier_list_write(out, message->transmitter_list);
      fputs(";" NEWLINE,out);
    }
  }
}

static void signal_group_write(FILE *out, signal_group_t *signal_group)
{
  fprintf(out, "SIG_GROUP_ %lu %s 1 : ",
	  signal_group->id,
	  signal_group->name);
  space_identifier_list_write(out, signal_group->signal_name_list);
  fputs(";" NEWLINE,out);
}

static void signal_group_list_write(
  FILE *out,
  signal_group_list_t *signal_group_list)
{
  PLIST_ITER(signal_group_list) {
    signal_group_write(out, signal_group_list->signal_group);
  }
}

void dbc_write(FILE *out, dbc_t *dbc)
{
  if(dbc != NULL && out != NULL) {
    version_write(out, dbc->version);
    newline(out);
    symbol_write(out);
    newline(out);
    message_section_write(out);
    newline(out);
    node_list_write(out, dbc->node_list);
    valtable_list_write(out, dbc->valtable_list);
    newline(out);
    message_list_write(out, dbc->message_list);
    message_transmitter_list_write(out, dbc->message_list);
    newline(out);
    newline(out);
    comment_list_write(out, dbc);
    attribute_definition_list_write(out, dbc->attribute_definition_list);
    attribute_definition_default_list_write(out,
      dbc->attribute_definition_list, aoc_object);
    attribute_definition_default_list_write(out,
      dbc->attribute_definition_list, aoc_relation);
    attribute_list_write(out, dbc->network->attribute_list, NULL);
    node_attribute_list_write(out, dbc->node_list);
    message_attribute_list_write(out, dbc->message_list);
    signal_attribute_list_write(out, dbc->message_list);
    attribute_rel_list_write(out, dbc->attribute_rel_list);
    signal_val_map_write(out, dbc->message_list);
    signal_group_list_write(out, dbc->signal_group_list);
  }
}
