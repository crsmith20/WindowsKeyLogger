## Usage Instructions

My program logger is a keylogger implemented in C++. This program only works for Windows machines since it is based on the windows library allowing to hook input from the machine. By hooking keys typed, writes to file after each keystroke. There is an occasional error where when reading keystrokes, it is read as two inputs, one for being pressed and one for being released. This has been more prominently seen when compiled through command prompt. Another issue that has been observed is that when trying to record an input that requires to hit shift before getting a the desired key(e.g. "[shift] 90" on the log would really be keys "()"). Another issue arises when caps lock is already on when the program starts and then the key is pressed. It then becomes the opposite of what it is meant to do for the program(example below).

```
/* caps lock is already on */
// actual input
TEST WORDS
// log entry
test words
```
```
/* caps lock is turned off */
// actual input
test words
// log entry
TEST WORDS
```

By compiling and running on terminal, it can be run even after the terminal is closed. This is due to it running the program in the background processes. If you check task manager then you can find the program running. It will continue to run until either terminated through task manager or by shutting off the computer. If compiled and run through command prompt, only works while command prompt is open or while the window stays open from the executable file. If checking the task manager while the program is still up, will display command prompt or executable in the apps section. Once closed it will be taken out of the task manager. This means that it cannot be run as a background process when compiled through command prompt. Please see below on how to compile and run on respective terminal/command prompt.

```
/* if compiled on terminal */
cd project-directory
g++ -g -Wall -o logger logger.cpp
./logger
/* can close terminal while running and keeps working */
```
```
/* if compiled on command prompt */
cd project-directory
g++ -Wall -o -static-libstdc++ logger.cpp
-static-libstdc++ on command prompt, otherwise run executable
/* will only run while window or command prompt stays open */
```
