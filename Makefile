# Este Makefile se provee como ejemplo para su modificacion. Puede utilizarlo
# en su proyecto de forma directa llenando los campos faltantes o puede
# extenderlo segun las necesidades de su solucion.
#
# GDSO 2-2014

# Coloque aqui el nombre del archivo ejecutable de su proyecto.
TARGET =monitorD
# Coloque aqui los nombres de todos los archivos compilados con extension .o
# necesarios para su proyecto.
OBJECTS = main.o demonio.o
CFLAGS = -O3 -Wall 
LDLIBS = -pthread

# Punto de entrada para make si se ejecuta sin parametros.
all: $(TARGET)

# Esta regla compila el proyecto completo una vez que todos los archivos objeto
# ya han sido compilados.
$(TARGET): $(OBJECTS)
	gcc -o $(TARGET) $(OBJECTS) $(CFLAGS) $(LDLIBS)

# Coloque aqui las lineas necesarias para compilar los archivos objeto que
# definio en $(OBJECTS)
# Ejemplo: Si definio arriba "OBJECTS = main.o" debe entonces agregar una linea
# como la siguiente:
# main.o: main.c

main.o: main.c demonio.h
demonio.o: demonio.c demonio.h

# Esta regla sustituye las banderas que se pasan al compilador por banderas
# utiles para depuracion.
debug: CFLAGS = -g -Wall -D_DEBUG
debug: all

# Esta regla permite instalar el proyecto como un servicio de sistema asumiendo
# que el archivo init.sh tenga el formato correcto. Debe ser ejecutada como
# usuario root.
install: $(TARGET)
	cp $(TARGET) /sbin/$(TARGET)
	cp init.sh /etc/init.d/$(TARGET)
	chmod 755 /etc/init.d/$(TARGET)
	update-rc.d $(TARGET) defaults

# Esta regla desinstala el proyecto. Debe ser ejecutada como usuario root
# despues de haber ejecutado la regla install.
uninstall:
	update-rc.d -f $(TARGET) remove
	$(RM) /sbin/$(TARGET) /etc/init.d/$(TARGET)

# Esta regla limpia los archivos creados por la compilacion.
clean:
	$(RM) $(TARGET) *.o
