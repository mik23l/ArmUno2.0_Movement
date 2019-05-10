/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    jsmn.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _JSMN_H    /* Guard against multiple inclusion */
#define _JSMN_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "variable_define.h"
#include "debug.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

#define JSMN_STRICT


    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

    /**
    * JSON type identifier. Basic types are:
    * 	o Object
    * 	o Array
    * 	o String
    * 	o Other primitive: number, boolean (true/false) or null
    */
    typedef enum {
        JSMN_UNDEFINED = 0,
        JSMN_OBJECT = 1,
        JSMN_ARRAY = 2,
        JSMN_STRING = 3,
        JSMN_PRIMITIVE = 4
    } jsmntype_t;
   
    enum jsmnerr {
        /* Not enough tokens were provided */
        JSMN_ERROR_NOMEM = -1,
        /* Invalid character inside JSON string */
        JSMN_ERROR_INVAL = -2,
        /* The string is not a full JSON packet, more bytes expected */
        JSMN_ERROR_PART = -3
    };
    
    /**
    * JSON token description.
    * type		type (object, array, string etc.)
    * start	start position in JSON data string
    * end		end position in JSON data string
    */
    typedef struct {
        jsmntype_t type;
        int start;
        int end;
        int size;
    #ifdef JSMN_PARENT_LINKS
        int parent;
    #endif
    } jsmntok_t;
    
    /**
    * JSON parser. Contains an array of token blocks available. Also stores
    * the string being parsed now and current position in that string
    */
    typedef struct {
        unsigned int pos; /* offset in the JSON string */
        unsigned int toknext; /* next token to allocate */
        int toksuper; /* superior token node, e.g parent object or array */
    } jsmn_parser;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************


    // *****************************************************************************
    /**
      @Function
        void jsmn_init(jsmn_parser *parser);

      @Summary
        Brief one-line description of the function.

      @Description
        Full description, explaining the purpose and usage of the function.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
     */
    void jsmn_init(jsmn_parser *parser);
    
    // *****************************************************************************
    /**
      @Function
        int jsmn_parse(jsmn_parser *parser, ReceiverLog *log, jsmntok_t *tokens, unsigned int num_tokens);

      @Summary
        Brief one-line description of the function.

      @Description
        Full description, explaining the purpose and usage of the function.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
     */
    int jsmn_parse(jsmn_parser *parser, ReceiverLog *log, jsmntok_t *tokens, unsigned int num_tokens);
    
    // *****************************************************************************
    /**
      @Function
        bool jsoneq(const char *json, jsmntok_t *tok, const char *s);

      @Summary
        Brief one-line description of the function.

      @Description
        Full description, explaining the purpose and usage of the function.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
     */
    bool jsoneq(const char *json, jsmntok_t *tok, const char *s);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _JSMN_H */

/* *****************************************************************************
 End of File
 */
