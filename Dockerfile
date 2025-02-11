# Utiliza una imagen base de Ubuntu
FROM ubuntu:latest

# Información del mantenedor
LABEL maintainer="NopAngel <angelgabrielnieto@outlook.com>"

# Instala las dependencias necesarias
RUN apt-get update && \
    apt-get install -y gcc make python3

# Crea el directorio de la aplicación
WORKDIR /app

# Copia el código fuente al contenedor
COPY src/ src/
COPY include/ include/
COPY .DragonC .DragonC

# Compila el intérprete de Dragon
RUN gcc src/Dragon.c -o Dragon

# Define el comando predeterminado
CMD ["./Dragon", ".DragonC"]
