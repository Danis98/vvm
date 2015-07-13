#ifndef _TOKEN_TYPE_H
#define _TOKEN_TYPE_H

enum tok_type{
	TOK_PARAM,
	TOK_IDENTIFIER,
	TOK_INT,
	TOK_DOUBLE,
	TOK_BOOL,
	TOK_STRING
};

tok_type get_token_type(std::string tok);

#endif