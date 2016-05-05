### Estructura del Juego

- **resources**
  - lib *(librerías)*
  - xml *(archivos de xml)*
  - **img** *(imágenes y sprites)*
- **src**
  - **accesorios**
    - colaConcurrente *(utilidad del servidor y el cliente)*
    - **codigo.hpp** *(contiene constantes utilizadas por el juego, tanto en la vista como en el modelo, e inclusive puede incluir los códigos de respuesta tipificados en el cliente y el servidor)*
  - **juego**
    - **Modelo** *(encargado del motor del juego, calcular movimientos y estados)*
      - **controlador.cpp** *(maneja los eventos que comunica el cliente y delega los comportamientos a quien corresponda)*
      - **juego.cpp** *(encargado de realizar el ciclo que maneja eventos y realiza todos los movimientos y actualizaciones de posición)*
      - **avion.cpp** *(logica de movimiento, estados, y creación de disparos)*
      - **disparo.cpp** *(logica de movimiento)*
      - **elemento.cpp** *(idem)*
      - **escenario.cpp** *(actualiza la posicion del nivel y el scroll del fondo)*
    - **Vista** *(encargado de renderizar los componentes dada su posición y estado)*
      - **avionVista.cpp** *(precargar texturas e imágenes y renderizar)*
      - **disparoVista.cpp** *(precargar texturas e imágenes y renderizar)*
      - **elementoVista.cpp** *(precargar texturas e imágenes y renderizar)*
      - **escenarioVista.cpp** *(precargar texturas e imágenes y renderizar)*
  - logger *(encargado de escribir logs de eventos en la ejecución)*
  - **net**
    - **cliente** *(encargado de cíclicamente llamar a la renderización de los componentes proveidos por el servidor y comunicar al servidor los eventos de teclado de cada jugador.)*
    - **mensaje** *(mensaje y protocolo de comunicación del juego)*
    - **servidor** *(encargado del motor del juego, y de interpretar las interacciones de teclado de los clientes jugadores)*

### Protocolo de los mensajes durante el juego

- #### Cliente a servidor

  - *(A definir, es simple porque sólo comunica eventos de teclado)*

- #### Servidor a cliente

  - ##### Etapa inicialización de escenario *(a definir)*
  - ##### Etapa de actualización de estados y posiciones

    - **Primera lectura:** longitud del mensaje [int]

    - **Segunda lectura:**
       - ** *Orden del mensaje:* **

        1. **[** escenario **]**

        2. **[** avion_1 **][** ... **][** avion_n **]**

        3. **[** elemento_1 **][** ... **][** elemento_n **]**

        4. **[** disparo_1 **][** ... **][** disparo_n **]**

  - **Estructura mensaje escenario:**

    **[** posición offset [float] **]**

  - **Estructura mensaje avión:**

      **[** nº de avión *(o jugador)* [byte] **][** pos_x [float] **][** pos_y [float] **][** estado_animación [byte] **]**

  - **Estructura mensaje elemento:**

      **[** id_elemento [byte] **][** pos_x [float] **][** pos_y [float] **]**

  - ** Estructura mensaje disparo:**

      **[** pos_x [float] **][** pos_y [float] **]**
