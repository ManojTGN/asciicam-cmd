#ifndef CMD_H
#define CMD_H

#include "ac_cli.h"

#define NOMINMAX 1
#define byte win_byte_override
#include <windows.h>
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#else
#error max macro is already defined
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#else
#error min macro is already defined
#endif
#include <opencv2/opencv.hpp>
#undef min
#undef max
#undef byte

#include <cstring>
#include <thread>
#include <chrono>

using namespace std;

typedef struct ScreenBuffer{

    int width;
    int height;

    COORD writeAt;
    SMALL_RECT writeArea;

    char* screen;
    HANDLE hConsole;
    DWORD dwBytesWritten;

} ScreenBuffer;

int ac_cmd_rangeMap(int value, int leftMin, int leftMax, int rightMin, int  rightMax);

ScreenBuffer ac_cmd_createScreenBuffer(int width, int height, int writeAt_X, int writeAt_Y, ac_cli_CONFIG globalConfig);
bool ac_cmd_writeScreen(ScreenBuffer sb);
void ac_cmd_setScreenActive(ScreenBuffer sb);

void ac_cmd_getCamFrame(cv::Mat *frame,cv::VideoCapture vCapture);
void ac_cmd_renderLoop(ac_cli_CONFIG globalConfig);


#endif /* CMD_H */