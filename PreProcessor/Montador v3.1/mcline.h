/**
Armazena a estrutura de uma MCLine

@author Murilo Marques Marinho
@version 1.0
*/

#ifndef MACHINE_CODE_LINE
#define MACHINE_CODE_LINE
/**
Estrutura de uma Machine Code line.
Armazena os dados necessarios para uma linha de codigo de maquina.
*/
typedef struct MCLine{
	/**
	A proxima linha	(MCLine)
	*/
	struct MCLine* nextLine;
	/**
	A instrucao (Inst) que essa linha (MCLine) tera.	
	*/
	struct Inst* inst;
} MCLine;

void newMCLine(MCLine** mcLine);

#endif
