# Navod ke kompilaci
- Ke kompilaci je pozadovano Visual Studio 2019 nebo GCC 7.0.0+ a CMake 3.12.0+

## Linux
- mkdir build
- cd build/
- cmake ..
- make -j 4

## Windows
- Spuste CMake GUI
- Stistknete Browse Source a vyberte slozku s rozbalenym cvicenim
- Stistknete Browse Build a vyberte stejnou adresu s priponou build/, tzn. napr. cestaKeSlozce/izg_lab_01/build/
- Kliknete na Configure
- Nasledne kliknete na Generate
- Ve slozce build/ nyni bude soubor izg_lab_01.sln, pres ten spustte Visual Studio
- Nasledne lze jiz primo sestavit aplikaci a spustit
