#include <stdio.h>
#include <ctype.h>
#include "xml_parser.h"

struct _XmlParser
{
	const char* read_ptr;

	int   attrs_nr;
	char* attrs[2*MAX_ATTR_NR+1];

	char* buffer;
	int buffer_used;
	int buffer_total;

	XmlBuilder* builder;
};

static const char* strtrim(char* str);
static void xml_parser_parse_entity(XmlParser* thiz);
static void xml_parser_parse_start_tag(XmlParser* thiz);
static void xml_parser_parse_end_tag(XmlParser* thiz);
static void xml_parser_parse_comment(XmlParser* thiz);
static void xml_parser_parse_pi(XmlParser* thiz);
static void xml_parser_parse_text(XmlParser* thiz);
static void xml_parser_reset_buffer(XmlParser* thiz);

char *my_strncpy(char *dest, const char *src, size_t n){
	strncpy(dest, src, n);
	dest[n] = '\0';

	return dest;
}

XmlParser* xml_parser_create(void)
{
	return (XmlParser*)ZALLOC(sizeof(XmlParser));
}

void xml_parser_set_builder(XmlParser* thiz, XmlBuilder* builder)
{
	thiz->builder = builder;

	return;
}

void xml_parser_parse(XmlParser* thiz, const char* xml, int length)
{
	int i = 0;
	enum _State
	{
		STAT_NONE,
		STAT_AFTER_LT,
		STAT_START_TAG,
		STAT_END_TAG,
		STAT_TEXT,
		STAT_PRE_COMMENT1,
		STAT_PRE_COMMENT2,
		STAT_COMMENT,
		STAT_DOCTYPE,
		STAT_PROCESS_INSTRUCTION,
	}state = STAT_NONE;

	thiz->read_ptr = xml;

	for(; *thiz->read_ptr != '\0' && (thiz->read_ptr - xml) < length; thiz->read_ptr++, i++)
	{
		char c = thiz->read_ptr[0];

		switch(state)
		{
			case STAT_NONE:
			{

				if(c == '<')
				{
					xml_parser_reset_buffer(thiz);
					state = STAT_AFTER_LT;
				}
				else if(!isspace(c))
				{
					state = STAT_TEXT;
				}
				break;
			}
			case STAT_AFTER_LT:
			{
				if(c == '?')
				{
					state = STAT_PROCESS_INSTRUCTION;
				}
				else if(c == '/')
				{
					state = STAT_END_TAG;
				}
				else if(c == '!')
				{
					state = STAT_PRE_COMMENT1;
				}
				else if(isalpha(c) || c == '_')
				{
					state = STAT_START_TAG;
				}
				else
				{
					xml_builder_on_error(thiz->builder, 0, 0, "unexpected char");
				}
				break;
			}
			case STAT_START_TAG:
			{
				xml_parser_parse_start_tag(thiz);
				state = STAT_NONE;
				break;
			}
			case STAT_END_TAG:
			{
				xml_parser_parse_end_tag(thiz);
				state = STAT_NONE;
				break;
			}
			case STAT_PROCESS_INSTRUCTION:
			{
				xml_parser_parse_pi(thiz);
				state = STAT_NONE;
				break;
			}
			case STAT_TEXT:
			{
				xml_parser_parse_text(thiz);
				state = STAT_NONE;
				break;
			}
			case STAT_PRE_COMMENT1:
			{
				if(c == '-')
				{
					state = STAT_PRE_COMMENT2;
				}
				else if(c == 'D') 
				{
					state = STAT_DOCTYPE;
				}
				else
				{
					xml_builder_on_error(thiz->builder, 0, 0, "expected \'-\'");
				}
				break;
			}
			case STAT_PRE_COMMENT2:
			{
				if(c == '-')
				{
					state = STAT_COMMENT;
				}
				else
				{
					xml_builder_on_error(thiz->builder, 0, 0, "expected \'-\'");
				}
			}
			case STAT_DOCTYPE: 
			{
				if(c == '>') 
				{
					//skip doctype
					state = STAT_NONE;
				}
				
				break;
			}
			case STAT_COMMENT:
			{
				xml_parser_parse_comment(thiz);	
				state = STAT_NONE;
				break;
			}
			default:break;
		}

		if(*thiz->read_ptr == '\0')
		{
			break;
		}
	}

	return;
}

static void xml_parser_reset_buffer(XmlParser* thiz)
{
	thiz->buffer_used = 0;
	thiz->attrs_nr = 0;
	thiz->attrs[0] = NULL;

	return;
}

static int xml_parser_strdup(XmlParser* thiz, const char* start, int length)
{
	int offset = -1;

	if((thiz->buffer_used + length) >= thiz->buffer_total)
	{
		int length = thiz->buffer_total+(thiz->buffer_total>>1) + 128;
		char* buffer = (char*)REALLOC(thiz->buffer, length);
		if(buffer != NULL)
		{
			thiz->buffer = buffer;
			thiz->buffer_total = length;
		}
	}

	if((thiz->buffer_used + length) >= thiz->buffer_total)
	{
		return offset;
	}

	offset = thiz->buffer_used;
	my_strncpy(thiz->buffer + offset, start, length);
	thiz->buffer[offset + length] = '\0';
	strtrim(thiz->buffer+offset);
	thiz->buffer_used += length + 1;

	return offset;
}

static void xml_parser_parse_attrs(XmlParser* thiz, char end_char)
{
	int i = 0;
	enum _State
	{
		STAT_PRE_KEY,
		STAT_KEY,
		STAT_PRE_VALUE,
		STAT_VALUE,
		STAT_END,
	}state = STAT_PRE_KEY;

	char value_end = '\"';
	const char* start = thiz->read_ptr;

	int attrsOffset[MAX_ATTR_NR] = {0};

	thiz->attrs_nr = 0;
	for(; *thiz->read_ptr != '\0' && thiz->attrs_nr < MAX_ATTR_NR; thiz->read_ptr++)
	{
		char c = *thiz->read_ptr;
	
		switch(state)
		{
			case STAT_PRE_KEY:
			{
				if(c == end_char || c == '>')
				{
					state = STAT_END;
				}
				else if(!isspace(c))
				{
					state = STAT_KEY;
					start = thiz->read_ptr;
				}
			}
			case STAT_KEY:
			{
				if(c == '=')
				{
					attrsOffset[thiz->attrs_nr++] = xml_parser_strdup(thiz, start, thiz->read_ptr - start);
					state = STAT_PRE_VALUE;
				}

				break;
			}
			case STAT_PRE_VALUE:
			{
				if(c == '\"' || c == '\'')
				{
					state = STAT_VALUE;
					value_end = c;
					start = thiz->read_ptr + 1;
				}
				break;
			}
			case STAT_VALUE:
			{
				if(c == value_end)
				{
					attrsOffset[thiz->attrs_nr++] = xml_parser_strdup(thiz, start, thiz->read_ptr - start);
					state = STAT_PRE_KEY;
				}
			}
			default:break;
		}

		if(state == STAT_END)
		{
			break;
		}
	}
	
	for(i = 0; i < thiz->attrs_nr; i++)
	{
		thiz->attrs[i] = thiz->buffer + (attrsOffset[i]);
	}
	thiz->attrs[thiz->attrs_nr] = NULL;

	return;
}

static void xml_parser_parse_start_tag(XmlParser* thiz)
{
	enum _State
	{
		STAT_NAME,
		STAT_ATTR,
		STAT_END,
	}state = STAT_NAME;

	char* tag_name = NULL;
	int tag_name_offset = 0;
	const char* start = thiz->read_ptr - 1;

	for(; *thiz->read_ptr != '\0'; thiz->read_ptr++)
	{
		char c = *thiz->read_ptr;
	
		switch(state)
		{
			case STAT_NAME:
			{
				if(isspace(c) || c == '>' || c == '/')
				{
					tag_name_offset = xml_parser_strdup(thiz, start, thiz->read_ptr - start);
					state = (c != '>' && c != '/') ? STAT_ATTR : STAT_END;
				}
				break;
			}
			case STAT_ATTR:
			{
				xml_parser_parse_attrs(thiz, '/');
				state = STAT_END;

				break;
			}
			default:break;
		}

		if(state == STAT_END)
		{
			break;
		}
	}
	
	tag_name = thiz->buffer + tag_name_offset;
	xml_builder_on_start_element(thiz->builder, tag_name, (const char**)thiz->attrs);
	
	if(thiz->read_ptr[0] == '/')
	{
		xml_builder_on_end_element(thiz->builder, tag_name);
	}

	for(; *thiz->read_ptr != '>' && *thiz->read_ptr != '\0'; thiz->read_ptr++);

	return;
}

static void xml_parser_parse_end_tag(XmlParser* thiz)
{
	char* tag_name = NULL;
	const char* start = thiz->read_ptr;
	for(; *thiz->read_ptr != '\0'; thiz->read_ptr++)
	{
		if(*thiz->read_ptr == '>')
		{
			tag_name = thiz->buffer + xml_parser_strdup(thiz, start, thiz->read_ptr-start);
			xml_builder_on_end_element(thiz->builder, tag_name);

			break;
		}
	}
	
	return;
}

static void xml_parser_parse_comment(XmlParser* thiz)
{
	enum _State
	{
		STAT_COMMENT,
		STAT_MINUS1,
		STAT_MINUS2,
	}state = STAT_COMMENT;

	const char* start = ++thiz->read_ptr;
	for(; *thiz->read_ptr != '\0'; thiz->read_ptr++)
	{
		char c = *thiz->read_ptr;

		switch(state)
		{
			case STAT_COMMENT:
			{
				if(c == '-')
				{
					state = STAT_MINUS1;
				}
				break;
			}
			case STAT_MINUS1:
			{
				if(c == '-')
				{
					state = STAT_MINUS2;
				}
				else
				{
					state = STAT_COMMENT;
				}
				break;
			}
			case STAT_MINUS2:
			{
				if(c == '>')
				{
					xml_builder_on_comment(thiz->builder, start, thiz->read_ptr-start-2);
					return;
				}
			}
			default:break;
		}
	}

	return;
}

static void xml_parser_parse_pi(XmlParser* thiz)
{
	enum _State
	{
		STAT_NAME,
		STAT_ATTR,
		STAT_END
	}state = STAT_NAME;

	char* tag_name = NULL;
	int tag_name_offset = 0;
	const char* start = thiz->read_ptr;

	for(; *thiz->read_ptr != '\0'; thiz->read_ptr++)
	{
		char c = *thiz->read_ptr;
	
		switch(state)
		{
			case STAT_NAME:
			{
				if(isspace(c) || c == '>')
				{
					tag_name_offset = xml_parser_strdup(thiz, start, thiz->read_ptr - start);
					state = c != '>' ? STAT_ATTR : STAT_END;
				}

				break;
			}
			case STAT_ATTR:
			{
				xml_parser_parse_attrs(thiz, '?');
				state = STAT_END;
				break;
			}
			default:break;
		}

		if(state == STAT_END)
		{
			break;
		}
	}
	
	tag_name = thiz->buffer + (int)tag_name_offset;
	xml_builder_on_pi_element(thiz->builder, tag_name, (const char**)thiz->attrs);	

	for(; *thiz->read_ptr != '>' && *thiz->read_ptr != '\0'; thiz->read_ptr++);

	return;
}

static void xml_parser_parse_text(XmlParser* thiz)
{
	const char* start = thiz->read_ptr - 1;
	for(; *thiz->read_ptr != '\0'; thiz->read_ptr++)
	{
		char c = *thiz->read_ptr;

		if(c == '<')
		{
			if(thiz->read_ptr > start)
			{
				xml_builder_on_text(thiz->builder, start, thiz->read_ptr-start);
			}
			thiz->read_ptr--;
			return;
		}
		else if(c == '&')
		{
			xml_parser_parse_entity(thiz);
		}
	}

	return;
}

static void xml_parser_parse_entity(XmlParser* thiz)
{
	/*TODO*/

	return;
}

void xml_parser_destroy(XmlParser* thiz)
{
	if(thiz != NULL)
	{
		FREE(thiz->buffer);
		FREE(thiz);
	}

	return;
}

static const char* strtrim(char* str)
{
	char* p = NULL;

	p = str + strlen(str) - 1;

	while(p != str && isspace(*p)) 
	{
		*p = '\0';
		p--;
	}

	p = str;
	while(*p != '\0' && isspace(*p)) p++;

	if(p != str)
	{
		char* s = p;
		char* d = str;
		while(*s != '\0')
		{
			*d = *s;
			d++;
			s++;
		}
		*d = '\0';
	}

	return str;
}

#ifdef TEST

typedef struct _BuilderInfo
{
	FILE* fp;
}BuilderInfo;

static void xml_builder_dump_on_start_element(XmlBuilder* thiz, const char* tag, const char** attrs)
{
	int i = 0;
	BuilderInfo* priv = (BuilderInfo*)thiz->priv;
	fprintf(priv->fp, "<%s", tag);

	for(i = 0; attrs != NULL && attrs[i] != NULL && attrs[i + 1] != NULL; i += 2)
	{
		fprintf(priv->fp, " %s=\"%s\"", attrs[i], attrs[i + 1]);
	}
	fprintf(priv->fp, ">");

	return;
}

static void xml_builder_dump_on_end_element(XmlBuilder* thiz, const char* tag)
{
	BuilderInfo* priv = (BuilderInfo*)thiz->priv;
	fprintf(priv->fp, "</%s>\n", tag);

	return;
}

static void xml_builder_dump_on_text(XmlBuilder* thiz, const char* text, size_t length)
{
	BuilderInfo* priv = (BuilderInfo*)thiz->priv;
	fwrite(text, length, 1, priv->fp);

	return;
}

static void xml_builder_dump_on_comment(XmlBuilder* thiz, const char* text, size_t length)
{
	BuilderInfo* priv = (BuilderInfo*)thiz->priv;
	fprintf(priv->fp, "<!--");
	fwrite(text, length, 1, priv->fp);
	fprintf(priv->fp, "-->\n");

	return;
}

static void xml_builder_dump_on_pi_element(XmlBuilder* thiz, const char* tag, const char** attrs)
{
	int i = 0;
	BuilderInfo* priv = (BuilderInfo*)thiz->priv;
	fprintf(priv->fp, "<?%s", tag);

	for(i = 0; attrs != NULL && attrs[i] != NULL && attrs[i + 1] != NULL; i += 2)
	{
		fprintf(priv->fp, " %s=\"%s\"", attrs[i], attrs[i + 1]);
	}
	fprintf(priv->fp, "?>\n");

	return;
}

static void xml_builder_dump_on_error(XmlBuilder* thiz, int line, int row, const char* message)
{
	fprintf(stderr, "(%d,%d) %s\n", line, row, message);

	return;
}

static void xml_builder_dump_destroy(XmlBuilder* thiz)
{
	if(thiz != NULL)
	{
		free(thiz);
	}

	return;
}

XmlBuilder* xml_builder_dump_create(FILE* fp)
{
	XmlBuilder* thiz = (XmlBuilder*)calloc(1, sizeof(XmlBuilder) + sizeof(BuilderInfo));

	if(thiz != NULL)
	{
		BuilderInfo* priv = (BuilderInfo*)thiz->priv;

		thiz->on_start_element  = xml_builder_dump_on_start_element;
		thiz->on_end_element    = xml_builder_dump_on_end_element;
		thiz->on_text           = xml_builder_dump_on_text;
		thiz->on_comment        = xml_builder_dump_on_comment;
		thiz->on_pi_element     = xml_builder_dump_on_pi_element;
		thiz->on_error          = xml_builder_dump_on_error;
		thiz->destroy           = xml_builder_dump_destroy;

		priv->fp = fp != NULL ? fp : stdout;
	}

	return thiz;
}


XmlBuilder* xml_builder_dump_create(FILE* fp);

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char* read_file(const char* file_name)
{
	char* buffer = NULL;
	FILE* fp = fopen(file_name, "r");
	size_t fread_ret = 0;

	if(fp != NULL)
	{
		struct stat st = {0};
		if(stat(file_name, &st) == 0)
		{
			buffer = malloc(st.st_size + 1);
			fread_ret = fread(buffer, st.st_size, 1, fp);
			buffer[st.st_size] = '\0';
		}
	}

	return buffer;
}

int main(int argc, char* argv[])
{
	XmlParser* thiz = NULL;
	XmlBuilder* builder = NULL;

	thiz = xml_parser_create();
	builder = xml_builder_dump_create(NULL);
	xml_parser_set_builder(thiz, builder);
	
	if(argc > 1)
	{
		char* buffer = read_file(argv[1]);
		xml_parser_parse(thiz, buffer, strlen(buffer));
		free(buffer);
	}

	xml_builder_destroy(builder);
	xml_parser_destroy(thiz);

	return 0;
}

#endif

