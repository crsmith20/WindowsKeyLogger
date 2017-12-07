# Program 4

See instructions here: https://www.cs.usfca.edu/~mmalensek/courses/cs220/assignments/program-4.html

## Usage Instructions

My program logger, is a key logger implemented in C++. This program only works for Windows machines since it is based off the windows library allowing to hook input from the machine. By hooking keys typed, writes to file after each key stroke. There is an occasional error where when reading keystokes it is read as two inputs, one for being pressed and one for being released. This has been more prominantly seen when comiled through command prompt.

By compiling and running on terminal, it can be run even after the terminal is closed. This is due to it running the program in the background processes. If you check task manager then you can find the program running. It will continue to run until either terminated through task manager or by shutting off the computer. If compiled and run through command prompt, only works while command prompt is open or while the window stays open from the executable file. If checking the task manager while program is still up, will display command prompt or executable in apps section. Once closed it will be taken out of the task manager. This means that it cannot be run as a background prcess when compiled through command prompt. Please see below on how to compile and run on respective terminal/command prompt.


```
// if compiled on terminal
cd project-directory
g++ -g -Wall -o logger logger.cpp
./logger
// can close terminal while running and keeps working
```
```
// if compiled on command prompt
cd project-directory
g++ -Wall -o -static-libstdc++ logger.cpp
-static-libstdc++ on command prompt, otherwise run executable
// will only run while window or command prompt stays open
```

