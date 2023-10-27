#include "ac_cmd.h"

int ac_cmd_rangeMap(int value, int leftMin, int leftMax, int rightMin, int rightMax) {
    if (value < leftMin) value = leftMin;
    if (value > leftMax) value = leftMax;

    int result = rightMin + (value - leftMin) * (rightMax - rightMin) / (leftMax - leftMin);

    return result;
}

ScreenBuffer ac_cmd_createScreenBuffer(int width, int height, int writeAt_X, int writeAt_Y, ac_cli_CONFIG globalConfig) {

    ScreenBuffer sb;

    sb.width = width;
    sb.height = height;
    sb.writeAt.X = writeAt_X;
    sb.writeAt.Y = writeAt_Y;
    sb.dwBytesWritten = 0;

    sb.screen = new char[width*height];
    for(int h = 0; h < height; h++)
    for(int w = 0; w < width; w++)
    sb.screen[h*width + w] = ' ';

    sb.screen[height*width - 1] = '\0';
    sb.hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    GetCurrentConsoleFontEx(sb.hConsole, FALSE, &fontInfo);
    wcscpy(fontInfo.FaceName, globalConfig.font);
    
    fontInfo.dwFontSize.X = fontInfo.dwFontSize.Y = 8;
    SetCurrentConsoleFontEx(sb.hConsole, FALSE, &fontInfo); 

    // SMALL_RECT const minimal_window = { 0, 0, 1, 1 };
    // SetConsoleWindowInfo(sb.hConsole, TRUE, &minimal_window);

    sb.writeArea.Top = sb.writeArea.Left = 0;
    sb.writeArea.Bottom = height-1;
    sb.writeArea.Right = width-1;
    SetConsoleWindowInfo(sb.hConsole, TRUE, &sb.writeArea);

    COORD bufferSize = { (SHORT)width, (SHORT)height };
    SetConsoleScreenBufferSize(sb.hConsole, bufferSize);

    return sb;

}


bool ac_cmd_writeScreen( ScreenBuffer sb ){

    BOOL fSuccess = WriteConsoleOutputCharacter(sb.hConsole, sb.screen, sb.width * sb.height, sb.writeAt, &sb.dwBytesWritten);
    return fSuccess;

}

void ac_cmd_setScreenActive(ScreenBuffer sb){

    SetConsoleActiveScreenBuffer(sb.hConsole);

}

void ac_cmd_getCamFrame(cv::Mat *frame, cv::VideoCapture vCapture){
    
    if (!vCapture.isOpened()) {
        std::cerr << "ERR: Could not open camera" << std::endl;
        return;
    }

    cv::Mat currFrame;
    vCapture >> currFrame;

    if (currFrame.empty()) {
        std::cerr << "ERR: End of video stream." << std::endl;
        return;
    }
    
    *frame = currFrame;

}


void ac_cmd_renderLoop(ac_cli_CONFIG globalConfig){
    
    //for developement will be removed on release
    globalConfig.camera = 1;
    globalConfig.fillMode = 3;


    cv::VideoCapture vCapture(globalConfig.camera);
    //@todo: add resize to config to have customized resize value
    vCapture.set(cv::CAP_PROP_FRAME_WIDTH, 40/*vCapture.get(cv::CAP_PROP_FRAME_WIDTH)*.05*/);
    vCapture.set(cv::CAP_PROP_FRAME_HEIGHT, 40/*vCapture.get(cv::CAP_PROP_FRAME_HEIGHT)*.05*/);

    ScreenBuffer sb = ac_cmd_createScreenBuffer( vCapture.get(cv::CAP_PROP_FRAME_WIDTH),vCapture.get(cv::CAP_PROP_FRAME_HEIGHT), 0, 0, globalConfig);
    ac_cmd_setScreenActive(sb);
    
    while(true){
        cv::Mat frame;
        ac_cmd_getCamFrame(&frame,vCapture);
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        
        //@todo: add debug mode in config to enable this videocapture view
        // cv::imshow("__sxtv_resized_.07gs_ videoCapture", frame);

        for (int row = 0; row < frame.rows; row++) 
        for (int col = 0; col < frame.cols; col++) {
            int pixelValue = static_cast<int>(frame.at<uchar>(row, col));
            int ind = ac_cmd_rangeMap(pixelValue/*pixelValue ( blue + green + red ) / 3*/, 0, 255, 0, strlen(globalConfig.fillModes[globalConfig.fillMode].c_str()));

            sb.screen[row*frame.cols + col] = globalConfig.fillModes[globalConfig.fillMode][ind];
        }

        ac_cmd_writeScreen(sb);
        cv::waitKey(1);
    }

    vCapture.release();

}