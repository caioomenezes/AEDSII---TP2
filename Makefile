#Pra rodar em linux 

#compile-run: exercicio1.c LeituraArquivo.c Hash.c ListaIngredientes.c IndiceInvertido.c (quebrar aqui) gcc -o run exercicio1.c LeituraArquivo.c Hash.c ListaIngredientes.c IndiceInvertido.c && ./run
compile-run: LeituraArquivo.c Hash.c ListaIngredientes.c IndiceInvertido.c
	gcc -o run LeituraArquivo.c Hash.c ListaIngredientes.c IndiceInvertido.c && ./run