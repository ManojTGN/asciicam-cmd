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

    if(force || !ac_cli_isGlobalConfigExist()){

        string configString = ac_json_parseStruct(config);
        FILE *configFile = fopen("asciicam.global.config.json","w");
        
        fprintf(configFile, configString.c_str());
        fclose(configFile);

    }

    free(config.extends);
    return config;

}
