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
#define ANSI_COLOR_PEACH "\x1b[38;5;223m"
#define ANSI_COLOR_LAVENDER "\x1b[38;5;183m"
#define ANSI_COLOR_BABY_BLUE "\x1b[38;5;153m"
#define ANSI_COLOR_BABY_BLUE2 "\x1b[38;5;117m"  // sky blue
#define ANSI_COLOR_BABY_BLUE3 "\x1b[38;5;111m"  // medium pastel blue
#define ANSI_COLOR_BABY_BLUE4 "\x1b[38;5;75m"   // sea
#define ANSI_COLOR_BABY_BLUE5 "\x1b[38;5;69m"   // deep sea
#define ANSI_COLOR_GRAY "\x1b[38;5;250m"
#define ANSI_COLOR_GREEN2 "\x1b[38;5;120m"
#define ANSI_COLOR_PASTEL_ORANGE "\x1b[38;5;223m"
#define ANSI_COLOR_ORANGE "\x1b[38;5;216m"
#define ANSI_COLOR_ORANGE2"\x1b[38;5;202m"

#define ANSI_COLOR_VIOLET "\x1b[95m"
//กรอบรุ้ง
#define ANSI_COLOR_RW1 "\x1b[38;5;225m"  // pastel pink
#define ANSI_COLOR_RW2 "\x1b[38;5;219m"  // fresh pink
#define ANSI_COLOR_RW3 "\x1b[38;5;213m"  // pinkpurple
#define ANSI_COLOR_RW4 "\x1b[38;5;207m"  // ม่วงพาสเทล
#define ANSI_COLOR_RW5 "\x1b[38;5;141m"  // ม่วงน้ำเงิน
#define ANSI_COLOR_RW6 "\x1b[38;5;111m"  // ฟ้าอ่อน
#define ANSI_COLOR_RW7 "\x1b[38;5;117m"  // ฟ้าน้ำทะเล
#define ANSI_COLOR_RW8 "\x1b[38;5;123m"  // เขียวอมฟ้า
#define ANSI_COLOR_RW9 "\x1b[38;5;120m"  // เขียวมินต์
#define ANSI_COLOR_RW10 "\x1b[38;5;157m"  // เขียวอ่อน
#define ANSI_COLOR_RW11 "\x1b[38;5;186m"  // เหลืองเขียว
#define ANSI_COLOR_RW12 "\x1b[38;5;229m"  // เหลืองนวล
#define ANSI_COLOR_RW13 "\x1b[38;5;223m"  // ส้มอ่อน
#define ANSI_COLOR_RW14 "\x1b[38;5;215m"  // ส้มกลาง
#define ANSI_COLOR_RW15 "\x1b[38;5;209m"  // แสด

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
#endif