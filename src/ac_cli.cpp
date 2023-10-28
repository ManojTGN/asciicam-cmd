#include "ac_cli.h"

#include "ac_json.h"

bool ac_cli_isGlobalConfigExist(){
    
    if (FILE *file = fopen("asciicam.global.config.json", "r")) {
        fclose(file);
        return true;
    }

    return false;

}

ac_cli_CONFIG ac_cli_createGlobalConfig(bool force){
    
    ac_cli_CONFIG config;
    // cout<<typeid(ac_cli_CONFIG_TYPE["fillModes"]).name()<<" "<<ac_cli_CONFIG_TYPE["fps"]<<endl;
    
    if(force || !ac_cli_isGlobalConfigExist()){

        string configString = ac_json_parseStruct(config);
        FILE *configFile = fopen("asciicam.global.config.json","w");
        
        fprintf(configFile, configString.c_str());
        fclose(configFile);

    }

    free(config.extends);
    return config;

}

bool ac_cli_setParameters(char **argv, int argc, ac_cli_CONFIG *config){
    
    for(int i = 1; i < argc; i+=2){

        if( strcmp(argv[i],"camera") == 0 ){
            config->camera = stoi(argv[i+1]);
        }else if(strcmp(argv[i],"cameradelay") == 0){
            config->cameraDelay = stoi(argv[i+1]);
        }else if(strcmp(argv[i],"fps") == 0){
            config->fps = stoi(argv[i+1]);
        }else if(strcmp(argv[i],"fpsdisplay") == 0){
            if(strcmp(argv[i+1],"1") == 0 || strcmp(argv[i+1],"true") == 0) config->fpsDisplay = true;
            else if(strcmp(argv[i+1],"0") == 0 || strcmp(argv[i+1],"false") == 0) config->fpsDisplay = false;
            else return false;
        }else if(strcmp(argv[i],"font") == 0){
            config->font = new wchar_t[  strlen(argv[i+1])+1 ];
            //@todo: try catch for mbstowcs() `size_t result ` 
            mbstowcs(config->font , argv[i+1], strlen(argv[i+1])+1);
        }else if(strcmp(argv[i],"fontsize") == 0){
            config->fontSize = stoi(argv[i+1]);
        }else if(strcmp(argv[i],"keyexit") == 0){
            //@todo: accept int input and convert to char
            //now it only accepts char type
            config->keyExit = argv[i+1][0];
        }else if(strcmp(argv[i],"keypause") == 0){
            //@todo: accept int input and convert to char
            //now it only accepts char type
            config->keyPause = argv[i+1][0];
        }else if(strcmp(argv[i],"keyscreenshot") == 0){
            //@todo: accept int input and convert to char
            //now it only accepts char type
            config->keyScreenshot = argv[i+1][0];
        }else if(strcmp(argv[i],"fillmode") == 0){
            config->fillMode = stoi(argv[i+1]);
        }
    }

    return true;

}
