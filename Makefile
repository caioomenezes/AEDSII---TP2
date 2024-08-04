# Define a regra padrão
all: compile-run

compile-run: LeituraArquivo.c Hash/Hash.c Hash/ListaIngredientes.c Hash/IDHash.c Pat/Patricia.c Pat/IDPat.c Hash/PesquisaHash.c Pat/PesquisaPat.c
	gcc -o run LeituraArquivo.c Hash/Hash.c Hash/ListaIngredientes.c Hash/IDHash.c Pat/Patricia.c Pat/IDPat.c Hash/PesquisaHash.c  Pat/PesquisaPat.c -lm && ./run

# Limpar arquivos compilados
clean:
	rm -f run *.o
