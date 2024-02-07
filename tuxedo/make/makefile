PROC = $(ORACLE_HOME)/bin/proc
PROC_CFLAGS = code=ANSI_C
PROCINCLUDES = include=include include=/usr/include include=/usr/lib/gcc/x86_64-redhat-linux/4.8.2/include include=/usr/include/linux sys_include=/usr/include include=../inc
PROCFLAGS = $(PROC_CFLAGS) $(PROCINCLUDES)

# Directorios/Rutas 
BIN = ../bin
OBJ = ../obj
SRC = ../src
INC = ../inc
FML = ../fml
CC = gcc

# Generacion de Aplicacion
all: campos_fml precompila srvTuxedoBD cliTuxedoBD

# Compilacion de Campos FML
campos_fml: $(FML)/biblioBD.fml
		mkfldhdr32 $(FML)/biblioBD.fml
		mv biblioBD.fml.h $(INC)

#Precompila
precompila:
		@echo "Precompilando ..."
		$(PROC) $(PROCFLAGS) \
		include=/usr/include/c++/8/x86_64-redhat-linux \
		include=$(ORACLE_HOME)/precomp/public \
		include=$(ORACLE_HOME)/rdbms/public \
		include=../inc \
		include=$(TUXDIR)/include \
		$(SRC)/srvTuxedoBD.pc

# Generacion de Servidores
srvTuxedoBD: $(OBJ)/srvTuxedoBD.o
		@echo Compilando el servidor srvTuxedoBD
		buildserver -v -f $(OBJ)/srvTuxedoBD.o \
		-f "-I$(INC)" \
		-l "-L$(ORACLE_HOME)/lib" \
		-o "$(BIN)/srvTuxedoBD -lclntsh" \
		-s insert_Negocio_FML

# Generacion de Cliente
cliTuxedoBD: $(OBJ)/cliTuxedoBD.o
	@echo Compilando el cliente cliTuxedoBD
	buildclient -f $(OBJ)/cliTuxedoBD.o -o $(BIN)/cliTuxedoBD

# Generacion de Ficheros Objeto
$(OBJ)/srvTuxedoBD.o: $(SRC)/srvTuxedoBD.c
		@echo "Genera objetos ..."
		$(CC) -c -I/usr/include/c++/4.8.2/x86_64-redhat-linux \
				-I$(ORACLE_HOME)/precomp/public -I$(ORACLE_HOME)/rdbms/public -I../inc \
				-I$(TUXDIR)/include -L$(ORACLE_HOME)/lib -L$(TUXDIR)/lib $(SRC)/srvTuxedoBD.c -o \
				$(OBJ)/srvTuxedoBD.o -lclntsh -lfml32 -ltux
$(OBJ)/cliTuxedoBD.o: $(SRC)/cliTuxedoBD.c
		$(CC) -c -I../inc -I$(TUXDIR)/include $(SRC)/cliTuxedoBD.c -o \
			$(OBJ)/cliTuxedoBD.o

# Borrado
cleanALL:
		rm $(OBJ)/*.o

cleanElem:
	rm $(OBJ)/*.o $(BIN)/cliTuxedoBD $(BIN)/srvTuxedoBD
			rm ../logs/ULOG*