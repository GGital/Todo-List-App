#pragma once
#ifndef UI_H
#define UI_H
// #define NOMINMAX
#include <iostream>
#include <string>
#include <cstdlib>
// #include <windows.h>

#define _XOPEN_SOURCE 700

// ANSI Escape Codes for Terminal Styling
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Text Formatting
#define ANSI_BOLD "\x1b[1m"
#define ANSI_UNDERLINE "\x1b[4m"
#define ANSI_BLINK "\x1b[5m"

// Background Colors
#define ANSI_BG_RED "\x1b[41m"
#define ANSI_BG_GREEN "\x1b[42m"
#define ANSI_BG_YELLOW "\x1b[43m"

/*
void enable_ansi_colors()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error: Unable to get console handle.\n";
        return;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        std::cerr << "Error: Unable to get console mode.\n";
        return;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        std::cerr << "Error: Unable to set console mode.\n";
    }
}
*/

class UI
{
public:
    void ClearScreen()
    {
        printf("\033[2J\033[H");
        fflush(stdout); // Ensure output is flushed immediately
    }
};
#endif // UI_H