/**
Armazena a estrutura de uma Line

@author Murilo Marques Marinho
@version 1.1
*/

#ifndef LINE_HEADER_GUARD
#define LINE_HEADER_GUARD

/**
Estrutura da uma Line

@see TokenTable
@see Token
*/
typedef struct Line{
	/**
	A primeira Token da Line
	*/
	struct Token *firstToken;
	/**
	Ponteiro para a proxima Line
	*/
	struct Line *nextLine;
} Line;

extern void newLine(struct Line **line);
extern void addTokenToLine(struct Line **line, struct Token **token);
extern void addNewTokenToLine(struct Line **line, char *tokenName);
extern void freeLine(struct Line** line);
#endif
