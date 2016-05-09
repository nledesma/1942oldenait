#ifndef INC_1942OLDENAIT_CODIGO_HPP
#define INC_1942OLDENAIT_CODIGO_HPP

/* Colores */

#define BASE 1
#define AZUL 2
#define ROJO 3
#define VERDE 4

/* Colores */

#define JUGADOR_1 BASE
#define JUGADOR_2 AZUL
#define JUGADOR_3 ROJO
#define JUGADOR_4 VERDE

/* Eventos */

#define EVENTO_VACIO 0
#define ARRIBA_PRESIONA 1
#define ARRIBA_SUELTA 2
#define ABAJO_PRESIONA 3
#define ABAJO_SUELTA 4
#define IZQUIERDA_PRESIONA 5
#define IZQUIERDA_SUELTA 6
#define DERECHA_PRESIONA 7
#define DERECHA_SUELTA 8
#define PRESIONA_ESPACIO 9
#define PRESIONA_ENTER 10
#define PRESIONA_R 11
#define PRESIONA_X 12

/* Dimensiones */

#define ANCHO_ESCENARIO 800
#define ALTO_ESCENARIO 800
#define ANCHO_AVION_COMUN 80
#define ALTO_AVION_COMUN 80
#define ANCHO_DISPARO_COMUN 20
#define ALTO_DISPARO_COMUN 40

/* Estados avion */

#define ESTADO_NORMAL 0
#define GIRANDO_IZQUIERDA 1
#define GIRANDO_DERECHA 2
#define LOOP_ETAPA_1 3
#define LOOP_ETAPA_2 4
#define LOOP_ETAPA_3 5
#define LOOP_ETAPA_4 6
#define LOOP_ETAPA_5 7
#define LOOP_ETAPA_6 8
#define LOOP_ETAPA_7 9
#define LOOP_ETAPA_8 10

/* Contador Loop avion */
#define CONTADOR_INICIAL 150

#endif //INC_1942OLDENAIT_CODIGO_HPP