# Makefile pour TP2
# à adapter au besoin

C11=--std=c++11
SRC_AVL= $(wildcard *_arbreAVL.cpp)
EXEC_AVL= $(SRC_AVL:.cpp=)
OPTIONS = -Wall

#Option -g pour avoir les infos de débogage
#OPTIONS = -g -O0 -Wall

#Option -O3 pour le code optimisé
#OPTIONS = -O3 -Wall

# Syntaxe : cible : dépendance1 dépendance2 ...
# Ensuite, la ou les ligne(s) débutant par une tabulation (\t) donne les commandes pour construire une cible

all : tp2 $(EXEC_AVL)

tp2: tp2.o historique.o
	g++ $(C11) $(OPTIONS) -o tp2 tp2.o historique.o

tp2.o: tp2.cpp
	g++ $(C11) $(OPTIONS) -c -o tp2.o tp2.cpp

historique.o: historique.h historique.cpp arbreavl.h 
	g++ $(C11) $(OPTIONS) -c -o historique.o historique.cpp

avl: $(EXEC_AVL)
	@for exec in $(EXEC_AVL); do \
		./$$exec; \
	done

memoire: $(EXEC_AVL)
	@./memoire.sh

public: tp2
	@./public.sh

clean :
	rm -f *.o
	rm -f tp2
	rm -f *~
	rm -f $(EXEC_AVL)

