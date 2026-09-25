# Dara v1.0

Dara es un lenguaje de programación sencillo creado como proyecto del curso de Compiladores.

El nombre Dara surge de la combinación de **Da**, de David, y **Ra**, de Araceli.

## Extensión

Los programas escritos en Dara utilizan la extensión `.da`.

## Estructura del proyecto

```text
Dara/
├── dara.l
├── dara.y
├── ast.h
├── ast.c
├── symbol_table.h
├── symbol_table.c
├── prueba_valida.da
├── prueba_invalida.da
└── README.md
```

## Tecnologías utilizadas

* Flex: análisis léxico.
* Bison: análisis sintáctico.
* C: implementación del compilador.
* AST: representación inicial del programa.
* Tabla de símbolos: almacenamiento de variables declaradas.

## ¿Cómo funciona?

El proceso del front-end de Dara es:

```text
Archivo .da
    ↓
Flex
    ↓
Tokens
    ↓
Bison
    ↓
Análisis sintáctico
    ↓
AST inicial
    ↓
Tabla de símbolos
```

### 1. Flex

Flex lee el archivo `.da` y reconoce los diferentes elementos del lenguaje, como:

* Palabras reservadas.
* Identificadores.
* Números enteros.
* Números reales.
* Operadores.
* Delimitadores.

### 2. Bison

Bison recibe los tokens generados por Flex y verifica que estén organizados de acuerdo con la gramática de Dara.

También permite construir el AST y realizar algunas validaciones básicas de variables.

### 3. AST

El AST representa la estructura del programa mediante nodos.

Se contemplan construcciones como:

* Declaraciones.
* Asignaciones.
* Entrada.
* Salida.
* Condicionales.
* Ciclos.
* Comparaciones.
* Operaciones aritméticas.
* Identificadores.
* Números.

### 4. Tabla de símbolos

La tabla de símbolos almacena información básica de las variables declaradas.

Para cada variable se guarda:

* Nombre.
* Tipo.

También se verifica que una variable haya sido declarada antes de utilizarla.

## Compilación con MSYS2 UCRT64

Para compilar Dara se utilizará **MSYS2 UCRT64**, junto con Flex, Bison y GCC.

Primero se debe abrir la terminal **MSYS2 UCRT64** y ubicarse en la carpeta donde se encuentra el proyecto.

Se verifica que las herramientas estén disponibles con:

```bash
flex --version
bison --version
gcc --version
```

Después, desde la carpeta `Dara`, se ejecutan los siguientes comandos:

```bash
bison -d dara.y
flex dara.l
gcc -o dara dara.tab.c lex.yy.c ast.c symbol_table.c
```

Si la compilación se realiza correctamente, se generará el ejecutable:

```text
dara.exe
```

## Ejecución

Para ejecutar un programa válido de Dara se utiliza:

```bash
./dara.exe prueba_valida.da
```

Para ejecutar el programa inválido:

```bash
./dara.exe prueba_invalida.da
```

## Flujo de ejecución

```text
prueba_valida.da
       ↓
     Flex
       ↓
    Tokens
       ↓
     Bison
       ↓
 Análisis sintáctico
       ↓
    AST inicial
       ↓
Tabla de símbolos
       ↓
    Resultado
```

## Pruebas

### Programa válido

Para probar el programa válido:

```bash
./dara.exe prueba_valida.da
```

El programa debe ser aceptado y mostrar:

* El AST.
* La tabla de símbolos.
* El mensaje de programa válido.

### Programa inválido

Para probar el programa inválido:

```bash
./dara.exe prueba_invalida.da
```

El programa debe detectar el error de sintaxis y mostrar el mensaje correspondiente de programa inválido.

## Estado actual

En esta entrega parcial se cuenta con un front-end funcional que integra:

* Análisis léxico con Flex.
* Análisis sintáctico con Bison.
* Integración Flex + Bison.
* AST inicial.
* Tabla de símbolos básica.
* Validación de variables declaradas.
* Prueba de programa válido.
* Prueba de programa inválido.

Las siguientes etapas del proyecto pueden ampliar la validación semántica, la representación del AST y las fases posteriores del compilador.
