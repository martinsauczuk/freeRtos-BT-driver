## Driver UART v2
Firmware v2 is a C language software development environment for embedded
systems. At the moment it focuses specifically on the programming of 
microcontrollers.



## Librerías utilizadas
- [sAPI](https://github.com/epernia/sapi) (only for EDU-CIAA-NXP board).
- [FreeRTOS](http://www.freertos.org/).

## Explicación breve

- Cola de Tx: El driver se encarga de enviar a la uart los datos que se encuentren en esta cola, funciona como si fuera una cola de impresión, donde la uart es la impresora que se encargará de imprimir todo lo que tenga en la cola de impresión, sin importar de quien sea. **En la cola de Tx escribe la aplicación y extrae los datos el driver**

- Cola de Rx. El driver se encarga de chequear si hay dato en la uart y colocarlo en la cola de recepción, como si fuera una bandeja de mail. La aplicación cuando desea puede consultar dicha cola (ver mail no leido). Automaticamente cuando consulta dichos datos la cola se borra. Los datos son *extraídos* de la cola. **En la cola de Rx el driver solamente escribe y en la aplicación extrae.**


## This environment is based on

- **Workspace** by Pablo Ridolfi: <https://github.com/pridolfi/workspace>
- **sAPI** by Eric pernia: <https://github.com/epernia/sapi>

