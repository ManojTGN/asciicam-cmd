#ifndef CLI_H
#define CLI_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdbool.h>

#define MAX_FILLMODES 10

using namespace std;

typedef struct config{

    bool status = false;

    int camera = 0;
    int cameraDelay = 0;

    int fps = 60;
    bool fpsDisplay = true;

    string fontDir = " ";
    int fontSize = 16;

    char keyExit = 133;
    char keyPause = 32;
    char keyScreenshot = 97;

    string fillModes[MAX_FILLMODES] = {"","","",""};
    int fillModesSize = 4;
    int fillMode = 0;

    bool isExtends = false;
    struct config *extends = NULL;

} ac_cli_CONFIG;

bool ac_cli_isGlobalConfigExist(); /* Returns TRUE if Global Config File Exists else FALSE */
ac_cli_CONFIG ac_cli_createGlobalConfig(bool force = true);  /* Create Global Config File and returns TRUE if created else FALSE */

#endif /* CLI_H */