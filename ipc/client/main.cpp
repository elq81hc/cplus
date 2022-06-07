#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#define BUFSIZE 512
 
int _tmain(int argc, TCHAR *argv[]) 
{
    HANDLE hPipe;
    DWORD dwWritten;


    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Pipe"), 
                       GENERIC_READ | GENERIC_WRITE, 
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);
    if (hPipe != INVALID_HANDLE_VALUE)
    {
        WriteFile(hPipe,
                  "Hello Pipe\n",
                  12,   // = length of string + terminating '\0' !!!
                  &dwWritten,
                  NULL);

        CloseHandle(hPipe);
    }

    return (0);
}