
# Instrucciones de compilación
## Requisitos del sistema
### Linux Ubuntu
| Herramienta | Versión mínima | Comando
|---|---|---|
| CMake | 3.28 | `sudo snap install cmake` |
| Clion IDE | - | `sudo apt install clion --classic` |
| g++-14 | 14.2.0 | `sudo apt install g++-14` |
| build-essential | - | `sudo apt install build-essential` |
| graphviz | 2.43.0 | `sudo apt install graphviz libgraphviz-dev` |
| pkg-config | 1.8.1 | `sudo apt install pkg-config` |
| feh | 3.10.1 | `sudo apt install feh`


---
## Instalación y Compilacion
### Clonar source
```bash
git clone https://github.com/Caballa001/Proyecto1EDD.git
cd Proyecto1EDD
```
### Compilar y correr el proyecto
desde el directorio raiz
```bash
cat build.sh 				#Opcional, para ver lo que hace
chmod +x build.sh		
./build.sh
```

El ejecutable corre automáticamente desde ``/bin/Arboles``

---

## Path de archivo de carga
relativo a la raíz :
`entrada/items.csv`


---

## Path de archivos de salida
Relativo a la raíz :
`salidas/`
 



> Written with [StackEdit](https://stackedit.io/).
