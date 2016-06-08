#OBJS specifies which files to compile as part of the project
OBJS = Boton/boton.cpp Boton/botonJugar.cpp Boton/botonSalir.cpp  Boton/botonEnColaboracion.cpp  Boton/botonPorEquipos.cpp  Boton/botonModoPractica.cpp  Boton/botonSiguiente.cpp Menu/menu.cpp Menu/menuPrincipal.cpp Menu/menuModosDeJuego.cpp Menu/menuDatosDeUsuario.cpp ventana.cpp figura.cpp menuBotones.cpp
#boton.cpp botonIniciarJuego.cpp botonOpciones.cpp botonSalir.cpp menu.cpp ventana.cpp textura.cpp botonesPrueba.cpp
#CC specifies which compiler we're using
CC = g++ #COMPILER_FLAGS specifies the additional compilation options we're using # -w suppresses all warnings
COMPILER_FLAGS = -w
#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = menuBotones
#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
