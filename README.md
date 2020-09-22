# Terminal effect
An easy software to emulate that stupid hacking console effect in films.

## How to run
This software can be used both on Windows and Linux.

### Windows
On Windows you don't have to do nothing because the program is already compiled.

### Linux
You need to download SDL2 and SDL2_mixer from your package manager like apt.
You can also delete dll files from directory because on Linux are useless.

## How to compile
If you want to compile the source file you have to use GCC.

### Windows
Go in the directory of the project and open CMD inside it.
```
gcc -O3 -Wall -Wextra main.c -o terminal_effect.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
```

## Linux
Go in the directory of the project and open your terminal inside it.
```
gcc -O3 -Wall -Wextra main.c -o terminal_effect -lSDL2 -lSDL2_mixer
```
## How to use
On Windows you can also just open the executable file and it will open the code.exe inside the directory.
If you dont want to read that code you can makes the software read from another .txt file.
To do it you need to give the rerlative or absolute path as first argument.

```
terminal_effect.exe "another/path/to/the/file.txt"
```
For standard utilization:
```
terminal_effect.exe
```
