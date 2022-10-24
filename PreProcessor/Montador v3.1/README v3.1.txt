*********************************************************************
*********************MONTARILO***************************************
*********************************************************************
By: Murilo Marques Marinho 
Version: 3.1

LEIA README v3.0.pdf (totalmente equivalente para a v3.1) para descrição das estruturas de dados e funcionamento do programa.

Como usar:
make <- compila o programa
make exemplos  <- monta todos os exemplos disponiveis, todos ficam na pasta exemplos_montados

Como limpar:
make clean <- limpa os .o
make exemplos_clean <- limpa os codigos exemplo montados

Como descrito em montador.c:
Uso: ./montador arquivodeentrada.txt arquivodesaida

Saida do arquivo conforme padroes ELF.
Adicao automatica de simbolos de DEBUG na sintaxe STABS

>>>>>> Observações: 

Escrita:   Não faz diferenciação entre maísculas e minúsculas: ADD_LOVE = add_love = Add_Love
	   O mesmo serve para instruções e diretivas.

Endereços: Em HEXADECIMAL devem iniciar com número E terminar com H. Não são aceitos número de endereços em outro formato (DECIMAL, BINARIO, OCTAL...)

Imediatos e diretivas: Numeros positivos. Ou Decimais ou Hexadecimais, sendo a diferenciação entre eles o H no final.
	   Exemplo: adi 16   => C6a 10a
		    adi 16H  => C6a 16a
		    adi 0AAH => C6a AAa
		    adi AAH  => Erro

Estrutura do código:

	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		   .begin <identificador>
		   	<Diretivas PUBLIC e EXTERN>
		   .text
			<.start <identificador>> <= facultativo.
			<INSTRUÇÕES>
		   .data
			<DIRETIVAS DS E DB>
		   .end

	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	.text e .data podem estar invertidos.
	Falhas em seguir essa sintaxe geram erros, e as mensagens nem sempre ajudam muito.
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Estrutura de instruções:
	<INSTRUCAO> <ESPAÇO> <ARGUMENTO> <VIRGULA> <ARGUMENTO> => Qualquer espaçamento entre as vírgulas e os argumentos dará, sem dúvidas, um ERRO FATAL.

Estrutura da diretiva DB também segue esse modelo:
	<DB> <ESPAÇO> <VALOR> <VIRGULA> <VALOR> <VIRGULA> <...>

Erros:
	A maioria dos erros é verificado e informado devidamente ao usuário. Alguns errors, contudo, passam e são visíveis apenas no código de saída.
	São uma minoria mas não custa avisar. Por mais que os codigos de erro tenham sido revisados nessa versao, algumas coisas fogem da logica.

