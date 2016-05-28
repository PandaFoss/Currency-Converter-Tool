#!/bin/bash

echo "Instalando CCT..."

if gcc main.c -o cct -lcurl
then
	gcc main.c -o cct -lcurl
else	
	echo "Error al compilar, saliendo..."
	exit 2
fi

if sudo cp cct /bin/
then
	sudo cp cct /bin/
else	
	echo "Error al instalar, saliendo..."
	exit 3
fi

echo "Instalacion exitosa, saliendo..."
exit 0
