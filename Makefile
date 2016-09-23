CC=gcc 
OBJS= analisador_lexico.o analisador_sintatico.o analisador_escopo.o analisador_semantico.o alerta_erro.o pilha.o

.c.o:
	$(CC) -c $<

compilador: $(OBJS)
	$(CC) -o $@ $@.c  $(OBJS)	

clean:
	-rm *.o compilador 
