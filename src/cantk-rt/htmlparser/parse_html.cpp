#include "xml_parser.h"
#include "parse_html.h"

typedef struct _BuilderInfo
{
	int script;
	string* str;
}BuilderInfo;

static void xml_builder_script_on_start_element(XmlBuilder* thiz, const char* tag, const char** attrs)
{
	BuilderInfo* priv = (BuilderInfo*)thiz->priv;

	if(strcmp(tag, "script") == 0) {
		int i = 0;
		priv->script++;
		while(attrs[i] != NULL) {
			const char* name = attrs[i];
			if(strcmp(name, "src") == 0) {
				const char* value = attrs[i+1];
				if(strstr(value, "cordova.js") == NULL) {
					*priv->str += "require(\"" + string(value) + "\");\n";;
				}
			}
			i+=2;
		}
	}

	return;
}

static void xml_builder_script_on_end_element(XmlBuilder* thiz, const char* tag)
{
	BuilderInfo* priv = (BuilderInfo*)thiz->priv;
	
	if(strcmp(tag, "script") == 0) {
		priv->script--;	
	}

	return;
}

static void xml_builder_script_on_text(XmlBuilder* thiz, const char* text, size_t length)
{
	BuilderInfo* priv = (BuilderInfo*)thiz->priv;
	if(priv->script > 0) {
		*priv->str += string(text, length);
	}

	return;
}

static void xml_builder_script_on_comment(XmlBuilder* thiz, const char* text, size_t length)
{
	BuilderInfo* priv = (BuilderInfo*)thiz->priv;

	return;
}

static void xml_builder_script_on_pi_element(XmlBuilder* thiz, const char* tag, const char** attrs)
{
	BuilderInfo* priv = (BuilderInfo*)thiz->priv;

	return;
}

static void xml_builder_script_on_error(XmlBuilder* thiz, int line, int row, const char* message)
{
	fprintf(stderr, "(%d,%d) %s\n", line, row, message);

	return;
}

string xml_builder_script_get_result(XmlBuilder* thiz)
{
	BuilderInfo* priv = (BuilderInfo*)thiz->priv;

	return *priv->str;
}

static void xml_builder_script_destroy(XmlBuilder* thiz)
{
	if(thiz != NULL)
	{
		BuilderInfo* priv = (BuilderInfo*)thiz->priv;
		delete priv->str;

		free(thiz);
	}

	return;
}

XmlBuilder* xml_builder_script_create()
{
	XmlBuilder* thiz = (XmlBuilder*)calloc(1, sizeof(XmlBuilder) + sizeof(BuilderInfo));

	if(thiz != NULL)
	{
		BuilderInfo* priv = (BuilderInfo*)thiz->priv;

		thiz->on_start_element  = xml_builder_script_on_start_element;
		thiz->on_end_element    = xml_builder_script_on_end_element;
		thiz->on_text           = xml_builder_script_on_text;
		thiz->on_comment        = xml_builder_script_on_comment;
		thiz->on_pi_element     = xml_builder_script_on_pi_element;
		thiz->on_error          = xml_builder_script_on_error;
		thiz->destroy           = xml_builder_script_destroy;

		priv->script = 0;
		priv->str = new string("");
	}

	return thiz;
}

string extractScriptInHTML(const char* content)
{
	string str;
	XmlParser* parser = NULL;
	XmlBuilder* builder = NULL;

	if(content != NULL) {
		parser = xml_parser_create();
		builder = xml_builder_script_create();
		xml_parser_set_builder(parser, builder);
		
		xml_parser_parse(parser, content, strlen(content));

		str = xml_builder_script_get_result(builder);

		xml_builder_destroy(builder);
		xml_parser_destroy(parser);
	}

	return str;
}

#ifdef TEST_HTML 

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
			buffer = (char*)malloc(st.st_size + 1);
			fread_ret = fread(buffer, st.st_size, 1, fp);
			buffer[st.st_size] = '\0';
		}
	}

	return buffer;
}

int main(int argc, char* argv[]) {
	if(argc == 2) {
		char* buffer = read_file(argv[1]);
		string str = extractScriptInHTML(buffer);
		printf("%s\n", str.c_str());
		free(buffer);
	}

	return 0;
}

#endif//HTML_TEST
