# Pendientes
- Ver como el cliente cierra la conexión con el servidor.
- Desencolar mensajes y devolverlos al cliente (no se está haciendo llamada al cicloDesencolar).
- Validaciones.
    - Pruebas de conectividad: desconectar a un cliente de repente.
    - XML incompleto.
    - Si se supera la cantidad maxima de clientes, hay que destruir uno que ya está conectado e intentar conectar el nuevo que quiere entrar.
      - Alternativa: conectarlo, mandarle un mensaje de que no puede conectarse, desconectarlo.
- Ver el problema de desconectarse y conectarse. Actualmente no es problema si se cierra el servidor en el medio. Esto indicaría que al cerrarse el servidor se cierran bien las conexiones, pero no así al desconectarse un cliente.
- Pasar por línea de comandos el archivo xml.
