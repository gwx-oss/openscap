/**
 * @file oval_parser_impl.h
 * \brief Open Vulnerability and Assessment Language
 *
 * See more details at http://oval.mitre.org/
 */

/*
 * Copyright 2009-2010 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors:
 *      "David Niemoller" <David.Niemoller@g2-inc.com>
 */

#ifndef OVAL_PARSER_H_
#define OVAL_PARSER_H_

#include <libxml/xmlreader.h>
#include "public/oval_agent_api.h"
#include "../common/util.h"

OSCAP_HIDDEN_START;

struct oval_parser_context {
	struct oval_definition_model *definition_model;
	struct oval_syschar_model *syschar_model;
	struct oval_results_model *results_model;
	struct oval_variable_model *variable_model;
	//struct oval_sysinfo            *syschar_sysinfo;
	xmlTextReader *reader;
	void *user_data;
};

struct oval_definition_model *oval_parser_context_model(struct oval_parser_context *context);

int oval_definition_model_parse(xmlTextReaderPtr, struct oval_parser_context *);
int oval_syschar_model_parse(xmlTextReaderPtr, struct oval_parser_context *);
int oval_results_model_parse(xmlTextReaderPtr , struct oval_parser_context *, struct oval_result_directives **);

void libxml_error_handler(void *, const char *, xmlParserSeverities severity, xmlTextReaderLocatorPtr locator);

int oval_parser_boolean(const char *, int);
int oval_parser_boolean_attribute(xmlTextReaderPtr reader, char *attname, int defval);
int oval_parser_int_attribute(xmlTextReaderPtr reader, char *attname, int defval);

int oval_parser_skip_tag(xmlTextReaderPtr reader, struct oval_parser_context *context);

typedef void (*oval_xml_value_consumer) (char *, void *);
int oval_parser_text_value(xmlTextReaderPtr, struct oval_parser_context *, oval_xml_value_consumer, void *);

typedef int (*oval_xml_tag_parser) (xmlTextReaderPtr, struct oval_parser_context *, void *);
int oval_parser_parse_tag(xmlTextReaderPtr, struct oval_parser_context *, oval_xml_tag_parser, void *);

void oval_text_consumer(char *text, void *user);

OSCAP_HIDDEN_END;

#endif				/* OVAL_PARSER_H_ */
