# Tarea Extraclase I: Arreglos Paginados

## Descripción

Esta tarea consiste en desarrollar dos programas en C++ para manejar archivos binarios grandes utilizando la paginación en memoria. Los programas son `generator` y `sorter`.

## Instrucciones

### Compilación

Para compilar ambos programas, utiliza los siguientes comandos:

g++ -o generator generator.cpp
g++ -o sorter sorter.cpp PagedArray.cpp

### Ejecucion

Generator: .\generator --size "<SIZE>" --output "<OUTPUT FILE PATH>"
Donde <SIZE> puede ser SMALL, MEDIUM o LARGE.
Y <OUTPUT FILE PATH> es la direccion donde se va a guardar


Sorter: .\sorter --input <INPUT FILE PATH> --output <OUTPUT FILE PATH> --alg <ALGORITHM>
Donde <ALGORITHM> puede ser QS (Quick Sort), IS (Insertion Sort) o BS (Bubble Sort),
<INPUT FILE PATH> la direccion donde van a estar los archivos
Y <OUTPUT FILE PATH> es la direccion donde se va a guardar
