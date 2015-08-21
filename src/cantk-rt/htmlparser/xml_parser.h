#ifndef XML_PARSER_H
#define XML_PARSER_H

#include "xml_builder.h"

BEGIN_DECLS

#define MAX_ATTR_NR 48

struct _XmlParser;
typedef struct _XmlParser XmlParser;

XmlParser* xml_parser_create(void);
void       xml_parser_set_builder(XmlParser* thiz, XmlBuilder* builder);
void       xml_parser_parse(XmlParser* thiz, const char* xml, int length);
void       xml_parser_destroy(XmlParser* thiz);

END_DECLS

#endif/*XML_PARSER_H*/

