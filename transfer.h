#ifndef CCG_MODUL_H
#define CCG_MODUL_H
#if     defined(_MSC_VER) ||    \
        defined(__WIN32) ||     \
        defined(__WIN32__) ||   \
        defined(_WIN32) ||      \
        defined(WIN32) ||       \
        defined(__WINNT) ||     \
        defined(__WINNT__) ||   \
        defined(__WINNT) ||		\
		defined(__WIN64) ||     \
        defined(__WIN64__) ||   \
        defined(_WIN64) ||      \
        defined(WIN64)

#   define WINDOWS

#include<iostream>
#include<windows.h>
#include<conio.h>
#include<tchar.h>

namespace ccg{
	BOOL SetCurrentPos(SHORT, SHORT);
}

#elif   defined(__linux) || defined(__linux__)

#   define LINUX


#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

namespace ccg{
	void SetCurrentPos(int, int);
}

#else

#   error Cannot determine OS type

#endif
namespace ccg{
	enum comand {BACKSPACE, ENTER, TAB, SPACE};
	enum arrow {UP, LEFT, RIGHT, DOWN, ELSE};
    enum symbol {DOUBLE_HORIZONTAL, TOP_LEFT_CORNER, TOP_RIGHT_CORNER, DOWN_RIGHT_CORNER, DOWN_LEFT_CORNER,
	VERTICAL, HORIZONTAL, VERTICAL_AND_HORIZONTAL, DOWN_AND_HORIZONTAL, LEFT_AND_VERTICAL,
	UP_AND_HORIZONTAL, RIGHT_AND_VERTICAL, LIGHT_SHADE, MEDIUM_SHADE, DARK_SHADE, RIGHT_POINTER,
	SMILING_FACE, CURRENCY_SIGN, ASTERISK, HEART, UP_POINTER, FULL_BLOCK, UP_DOWN_ARROW};
	void Pause();
	void ConsoleTitle();
	void CleanConsol();
	void sleep(int);
	int GetKey();
	int kbhit();
	int Arrows();
	void OutS(symbol);
	char GetC(comand);
}
#endif
