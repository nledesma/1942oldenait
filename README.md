# 1942oldenait
_OL-DE-NAIT_

## Pendientes

- Arreglar que se está cerrando el servidor cuando se cierra el cliente "violentamente".
- Validaciones.
  - Pruebas de conectividad: desconectar a un cliente de repente.
  - Memoria.
  - XML:
    - Incompleto.
    - Tags duplicados (ej, dos ids para un mensaje).
    - No haya tags incorrectos ni valores imposibles (ej, boolean, complex, tu vieja).
  - Cliente: Unicidad de los ids de los mensajes para un cliente.
  - Niveles de log. Warning?
  - Si se supera la cantidad máxima de clientes, entonces que el servidor lo acepte, le mande un mensaje LLENO y lo tira. Si hay lugar, le manda un mensaje OK. Esto hace que sea necesario que el cliente espere un mensaje al conectarse.
- Ver el problema de desconectarse y conectarse. Actualmente no es problema si se cierra el servidor en el medio. Esto indicaría que al cerrarse el servidor se cierran bien las conexiones, pero no así al desconectarse un cliente. Dicen las malas lenguas que hay que hacer set_socket_opts o algo así.
- Pasar por línea de comandos el archivo xml. Por ahí podemos pasar opciones de log por acá.
- Los ids ahora son alfanuméricos.
- Cuando un cliente intenta mandar un mensaje sin haberse conectado a un servidor, rompe.
- La codificación ahora es una garcha. Ahora hay que mandar los caracteres sin procesar.
  - Tipo: int. Fijo.
  - Longitud del id. int.
  - Id.
  - Longitud del mensaje. int.
  - Mensaje. Esto son los dígitos que figuran en el XML.
