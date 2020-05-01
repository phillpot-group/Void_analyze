// ideas for the platform stuff are taken from here: https://github.com/onqtam/COLOR/blob/master/COLOR/parts/COLOR_fwd.h
// not using __APPLE__ because... this is how Catch does it
#pragma once

#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
#define COLOR_PLATFORM_MAC
#elif defined(__IPHONE_OS_VERSION_MIN_REQUIRED)
#define COLOR_PLATFORM_IPHONE
#elif defined(_WIN32)
#define COLOR_PLATFORM_WINDOWS
#else // COLOR_PLATFORM
#define COLOR_PLATFORM_LINUX
#endif // COLOR_PLATFORM

#if !defined(COLOR_CONFIG_COLORS_NONE)
#if !defined(COLOR_CONFIG_COLORS_WINDOWS) && !defined(COLOR_CONFIG_COLORS_ANSI)
#ifdef COLOR_PLATFORM_WINDOWS
#define COLOR_CONFIG_COLORS_WINDOWS
#else // linux
#define COLOR_CONFIG_COLORS_ANSI
#endif // platform
#endif // COLOR_CONFIG_COLORS_WINDOWS && COLOR_CONFIG_COLORS_ANSI
#endif // COLOR_CONFIG_COLORS_NONE

#ifdef COLOR_PLATFORM_WINDOWS
#ifdef __AFXDLL
#include <AfxWin.h>
#else
#include <Windows.h>
#endif // __AFXDLL
#endif // COLOR_PLATFORM_WINDOWS

#include <iostream>

namespace Color
{
enum Enum
{
    None = 0,
    White,
    Red,
    Green,
    Blue,
    Cyan,
    Yellow,
    Grey,

    Bright = 0x10,

    BrightRed = Bright | Red,
    BrightGreen = Bright | Green,
    LightGrey = Bright | Grey,
    BrightWhite = Bright | White
};
} // namespace Color

namespace
{
#ifdef COLOR_CONFIG_COLORS_WINDOWS
HANDLE g_stdoutHandle;
WORD g_origFgAttrs;
WORD g_origBgAttrs;
bool g_attrsInitted = false;

int colors_init()
{
    if (!g_attrsInitted)
    {
        g_stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        g_attrsInitted = true;
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
        GetConsoleScreenBufferInfo(g_stdoutHandle, &csbiInfo);
        g_origFgAttrs = csbiInfo.wAttributes & ~(BACKGROUND_GREEN | BACKGROUND_RED |
                                                 BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        g_origBgAttrs = csbiInfo.wAttributes & ~(FOREGROUND_GREEN | FOREGROUND_RED |
                                                 FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    }
    return 0;
}

int dumy_init_console_colors = colors_init();
#endif // COLOR_CONFIG_COLORS_WINDOWS

void color_to_stream(std::ostream &s, Color::Enum code)
{
    //  ((void)s);    // for COLOR_CONFIG_COLORS_NONE or COLOR_CONFIG_COLORS_WINDOWS
    //  ((void)code); // for COLOR_CONFIG_COLORS_NONE
#ifdef COLOR_CONFIG_COLORS_ANSI
    auto col = "";
    // clang-format off
            switch(code) { //!OCLINT missing break in switch statement / unnecessary default statement in covered switch statement
                case Color::Red:         col = "[0;31m"; break;
                case Color::Green:       col = "[0;32m"; break;
                case Color::Blue:        col = "[0;34m"; break;
                case Color::Cyan:        col = "[0;36m"; break;
                case Color::Yellow:      col = "[0;33m"; break;
                case Color::Grey:        col = "[1;30m"; break;
                case Color::LightGrey:   col = "[0;37m"; break;
                case Color::BrightRed:   col = "[1;31m"; break;
                case Color::BrightGreen: col = "[1;32m"; break;
                case Color::BrightWhite: col = "[1;37m"; break;
                case Color::Bright: // invalid
                case Color::None:
                case Color::White:
                default:                 col = "[0m";
            }
    // clang-format on
    s << "\033" << col;
#endif // COLOR_CONFIG_COLORS_ANSI
#ifdef COLOR_CONFIG_COLORS_WINDOWS

#define COLOR_SET_ATTR(x) SetConsoleTextAttribute(g_stdoutHandle, x | g_origBgAttrs)

    // clang-format off
    switch (code) {
        case Color::White:       COLOR_SET_ATTR(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE); break;
        case Color::Red:         COLOR_SET_ATTR(FOREGROUND_RED);                                      break;
        case Color::Green:       COLOR_SET_ATTR(FOREGROUND_GREEN);                                    break;
        case Color::Blue:        COLOR_SET_ATTR(FOREGROUND_BLUE);                                     break;
        case Color::Cyan:        COLOR_SET_ATTR(FOREGROUND_BLUE | FOREGROUND_GREEN);                  break;
        case Color::Yellow:      COLOR_SET_ATTR(FOREGROUND_RED | FOREGROUND_GREEN);                   break;
        case Color::Grey:        COLOR_SET_ATTR(0);                                                   break;
        case Color::LightGrey:   COLOR_SET_ATTR(FOREGROUND_INTENSITY);                                break;
        case Color::BrightRed:   COLOR_SET_ATTR(FOREGROUND_INTENSITY | FOREGROUND_RED);               break;
        case Color::BrightGreen: COLOR_SET_ATTR(FOREGROUND_INTENSITY | FOREGROUND_GREEN);             break;
        case Color::BrightWhite: COLOR_SET_ATTR(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE); break;
        case Color::None:
        case Color::Bright: // invalid
        default:                 COLOR_SET_ATTR(g_origFgAttrs);
    }
// clang-format on
#endif // COLOR_CONFIG_COLORS_WINDOWS
}
} // namespace

namespace Color
{
inline std::ostream &operator<<(std::ostream &s, Color::Enum code)
{
    color_to_stream(s, code);
    return s;
}
} // namespace Color
