compile-run: LeituraArquivo.c Hash/Hash.c Hash/ListaIngredientes.c Hash/IDHash.c Pat/Patricia.c Pat/IDPat.c 

	gcc -o run LeituraArquivo.c Hash/Hash.c Hash/ListaIngredientes.c Hash/IDHash.c Pat/Patricia.c Pat/IDPat.c && ./run