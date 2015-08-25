#ifndef XML_BUILDER_H
#define XML_BUILDER_H

#include "console.h"

#ifdef __cplusplus
#define BEGIN_DECLS extern "C" {
#define END_DECLS }
#else
#define BEGIN_DECLS
#define END_DECLS
#endif

#define ZERO_LEN_ARRAY     0
#define ALLOC(s)       malloc(s)
#define REALLOC(p, s)  realloc(p, s)
#define ZALLOC(s)      calloc(1, s)
#define FREE(p)        if(p) {free(p); p = NULL;}
#define ZFREE(p, size) if(p) {memset((p), 0x00, (size)); free(p); p = NULL;}

#define return_if_fail(p)          if(!(p)) { LOGI("%s:%d "#p" failed.\n", __func__, __LINE__); return;}
#define return_val_if_fail(p, val) if(!(p)) { LOGI("%s:%d "#p" failed.\n", __func__, __LINE__); return (val);}

BEGIN_DECLS

struct _XmlBuilder;
typedef struct _XmlBuilder XmlBuilder;

typedef void (*XmlBuilderOnStartElementFunc)(XmlBuilder* thiz, const char* tag, const char** attrs);
typedef void (*XmlBuilderOnEndElementFunc)(XmlBuilder* thiz, const char* tag);
typedef void (*XmlBuilderOnTextFunc)(XmlBuilder* thiz, const char* text, size_t length);
typedef void (*XmlBuilderOnCommentFunc)(XmlBuilder* thiz, const char* text, size_t length);
typedef void (*XmlBuilderOnPiElementFunc)(XmlBuilder* thiz, const char* tag, const char** attrs);
typedef void (*XmlBuilderOnErrorFunc)(XmlBuilder* thiz, int line, int row, const char* message);
typedef void (*XmlBuilderDestroyFunc)(XmlBuilder* thiz);

struct _XmlBuilder
{
	XmlBuilderOnStartElementFunc on_start_element;
	XmlBuilderOnEndElementFunc   on_end_element;
	XmlBuilderOnTextFunc         on_text;
	XmlBuilderOnCommentFunc      on_comment;
	XmlBuilderOnPiElementFunc    on_pi_element;
	XmlBuilderOnErrorFunc        on_error;
	XmlBuilderDestroyFunc        destroy;

	char priv[ZERO_LEN_ARRAY];
};

static inline void xml_builder_on_start_element(XmlBuilder* thiz, const char* tag, const char** attrs)
{
	return_if_fail(thiz != NULL && thiz->on_start_element != NULL);

	thiz->on_start_element(thiz, tag, attrs);

	return;
}

static inline void xml_builder_on_end_element(XmlBuilder* thiz, const char* tag)
{
	return_if_fail(thiz != NULL);
	if(thiz->on_end_element != NULL)
	{
		thiz->on_end_element(thiz, tag);
	}

	return;
}

static inline void xml_builder_on_text(XmlBuilder* thiz, const char* text, size_t length)
{
	return_if_fail(thiz != NULL);
	if(thiz->on_text != NULL)
	{
		thiz->on_text(thiz, text, length);
	}

	return;
}

static inline void xml_builder_on_comment(XmlBuilder* thiz, const char* text, size_t length)
{
	return_if_fail(thiz != NULL);
	if(thiz->on_comment != NULL)
	{
		thiz->on_comment(thiz, text, length);
	}

	return;
}

static inline void xml_builder_on_pi_element(XmlBuilder* thiz, const char* tag, const char** attrs)
{
	return_if_fail(thiz != NULL);
	if(thiz->on_pi_element != NULL)
	{
		thiz->on_pi_element(thiz, tag, attrs);
	}

	return;
}

static inline void xml_builder_on_error(XmlBuilder* thiz, int line, int row, const char* message)
{
	return_if_fail(thiz != NULL);
	if(thiz->on_error != NULL)
	{
		thiz->on_error(thiz, line, row, message);
	}

	return;
}

static inline void xml_builder_destroy(XmlBuilder* thiz)
{
	if(thiz != NULL && thiz->destroy != NULL)
	{
		thiz->destroy(thiz);
	}

	return;
}

END_DECLS

#endif/*XML_BUILDER_H*/

