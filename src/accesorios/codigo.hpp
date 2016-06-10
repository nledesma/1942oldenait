#ifndef INC_1942OLDENAIT_CODIGO_HPP
#define INC_1942OLDENAIT_CODIGO_HPP

// Para envio de mensajes
#define MENSAJEOK 1
#define CLIENTE_DESCONECTADO -2

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

#define ALTO_ENEMIGO_PEQUENIO 70
#define ANCHO_ENEMIGO_PEQUENIO 70

#define ALTO_ENEMIGO_ESCUADRON 70
#define ANCHO_ENEMIGO_ESCUADRON 70

#define ALTO_ENEMIGO_MEDIANO 90
#define ANCHO_ENEMIGO_MEDIANO 90

#define ALTO_ENEMIGO_GRANDE 150
#define ANCHO_ENEMIGO_GRANDE 100

#define ANCHO_DISPARO_ENEMIGO 10
#define ALTO_DISPARO_ENEMIGO 10

#define ANCHO_POWERUP 48
#define ALTO_POWERUP 48

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
#define LOOP_ETAPA_9 11
#define LOOP_ETAPA_10 12
#define LOOP_ETAPA_11 13
#define LOOP_ETAPA_12 14
#define LOOP_ETAPA_13 15
#define LOOP_ETAPA_14 16
#define LOOP_ETAPA_15 17
#define LOOP_ETAPA_16 18
#define LOOP_ETAPA_17 19
#define DESCONECTADO 20
#define EXPLOSION_ETAPA_1 21
#define EXPLOSION_ETAPA_2 22
#define EXPLOSION_ETAPA_3 23
#define EXPLOSION_ETAPA_4 24
#define EXPLOSION_ETAPA_5 25
#define EXPLOSION_ETAPA_6 26
#define EXPLOSION_ETAPA_7 27
#define EXPLOSION_ETAPA_8 28
#define EXPLOSION_ETAPA_9 29
#define EXPLOSION_ETAPA_10 30
#define OFFSET_ESTADO_DISPARO 50
#define OFFSET_ESTADO_LOOP 100
#define OFFSET_ESTADO_EXPLOSION 150
#define CODIGO_SIN_SONIDO 0
#define CODIGO_SONIDO_DISPARO 1
#define CODIGO_SONIDO_LOOP 2
#define CODIGO_SONIDO_EXPLOSION 3

/* Tipos de avion */

#define TIPO_AVION_PEQUENIO 1
#define TIPO_AVION_ESCUADRON 2
#define TIPO_AVION_MEDIANO 3
#define TIPO_AVION_GRANDE 4
#define TIPO_AVION 5

/* Tipos de disparos */

#define TIPO_DISPARO_AVION 6
#define TIPO_DISPARO_ENEMIGO 7

/* Tipos de PowerUps */
#define TIPO_POWERUP_BONIFICACION 1
#define TIPO_POWERUP_DOS_AMETRALLADORAS 2
#define TIPO_POWERUP_DESTRUIR_ENEMIGOS 3
#define TIPO_POWERUP_AVIONES_SECUNDARIOS 4
#define TIPO_POWERUP_BONIFICACION_1500 5

/* Estados avion enemigo */

#define AVION_ENEMIGO_0G 4
#define AVION_ENEMIGO_22G 3
#define AVION_ENEMIGO_45G 2
#define AVION_ENEMIGO_67G 1
#define AVION_ENEMIGO_90G 0
#define AVION_ENEMIGO_112G 15
#define AVION_ENEMIGO_135G 14
#define AVION_ENEMIGO_157G 13
#define AVION_ENEMIGO_180G 12
#define AVION_ENEMIGO_202G 11
#define AVION_ENEMIGO_225G 10
#define AVION_ENEMIGO_247G 9
#define AVION_ENEMIGO_270G 8
#define AVION_ENEMIGO_292G 7
#define AVION_ENEMIGO_315G 6
#define AVION_ENEMIGO_337G 5

#define AVION_ENEMIGO_FLIP_ETAPA_1 16
#define AVION_ENEMIGO_FLIP_ETAPA_2 17
#define AVION_ENEMIGO_FLIP_ETAPA_3 18
#define AVION_ENEMIGO_FLIP_ETAPA_4 19
#define AVION_ENEMIGO_FLIP_ETAPA_5 20
#define AVION_ENEMIGO_FLIP_ETAPA_6 21
#define AVION_ENEMIGO_FLIP_ETAPA_7 22

#define AVION_ENEMIGO_EXPLOSION_ETAPA_1 23
#define AVION_ENEMIGO_EXPLOSION_ETAPA_2 24
#define AVION_ENEMIGO_EXPLOSION_ETAPA_3 25
#define AVION_ENEMIGO_EXPLOSION_ETAPA_4 26
#define AVION_ENEMIGO_EXPLOSION_ETAPA_5 27

/* Estados avión enemigo grande */

#define AVION_ENEMIGO_GRANDE_NORMAL 0
#define AVION_ENEMIGO_GRANDE_DANIADO_1 1
#define AVION_ENEMIGO_GRANDE_DANIADO_2 2
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_1 3
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_2 4
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_3 5
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_4 6
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_5 7
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_6 8
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_7 9
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_8 10
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_9 11
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_10 12
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_11 13
#define AVION_ENEMIGO_GRANDE_EXPLOSION_ETAPA_12 14

/*Estados power ups */

#define POWER_UP_NORMAL 0
#define POWER_UP_ROTACION_1 1
#define POWER_UP_ROTACION_2 2
#define POWER_UP_ROTACION_3 3
#define POWER_UP_ROTACION_4 4
#define POWER_UP_ROTACION_5 5
#define POWER_UP_ROTACION_6 6
#define POWER_UP_COLISIONADO 7
/*#define POWER_UP_COLISIONADO_DESTRUIR_ENEMIGOS 8
#define POWER_UP_COLISIONADO_DOS_AMETRALLADORAS 9
#define POWER_UP_COLISIONADO_AVIONES_SECUNDARIOS 10
#define POWER_UP_COLISIONADO_BONIFICACION_1500 11*/
#define AVION_CON_POWERUP 12

/* Contador Loop avion */
#define CONTADOR_INICIAL 20

/* Códigos de eventos al cliente */
#define AVANZAR_ETAPA 0
#define FINALIZAR_JUEGO 1

/* Contador Sonido disparo */
#define CONTADOR_SONIDO_DISPARO_INICIAL 10

/* Respuestas de mainLoop */
#define CONTINUAR 1
#define CERRAR 2

/* Modos de juego */

#define COLABORATIVO 1
#define EQUIPOS 2

#endif //INC_1942OLDENAIT_CODIGO_HPP
