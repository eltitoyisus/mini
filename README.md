# minishell

## Visión General

Minishell es un proyecto fundamental de la escuela, diseñado para replicar la funcionalidad básica de un shell UNIX como Bash. Este proyecto busca profundizar la comprensión del manejo de procesos, la gestión de descriptores de archivos, las señales y el análisis sintáctico (parsing) de la línea de comandos.

## Prompt y Lectura de Entrada: 
Muestra un prompt interactivo y lee la línea de comandos.

## Parsing:

- Maneja la separación de comandos mediante el operador de tubería (|).
- Gestiona las redirecciones de entrada (<), salida (>), y el modo de adición (>>).
- Implementa la característica "here document" (<<).
- Gestiona complicaciones de bash como "without space" entre ALGUNOS operadores.
- Gestiona tema de comillas dobles y simples.

## Comandos Built-in: 

Implementación de comandos internos del shell:

    echo (con soporte para la opción -n)

    cd

    pwd

    export

    unset

    env

    exit

## SNAKE (GAME)
Sí introduces la palabra "Snake", se abrirá un proceso que es un mini juego hecho con ASCII. ;D
    
