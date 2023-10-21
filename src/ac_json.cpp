#include "ac_json.h"

ac_cli_CONFIG ac_json_parseFile(string fileDir){

    ac_cli_CONFIG configStruct;

    if(fileDir.find(".json") != fileDir.size() -5 )
        return configStruct;

    FILE* configFile = fopen(fileDir.c_str(),"r");
    if(!configFile)
        return configStruct;

    //@todo:    parse the json data and return it as `ac_cli_CONFIG` struct
    //          for now it returns default config struct

    configStruct.status = true;
    return configStruct;

}

string ac_json_parseStruct(ac_cli_CONFIG _struct, bool _isExtends){

    string parsedString = 
        "{\n\t\"camera\":"+to_string(_struct.camera)+","+(!_isExtends?"       \"//\":\"Camera 0 (default cam) [0-n]\",":"")+"\n\t"+
        "\"cameraDelay\":"+to_string(_struct.cameraDelay)+","+(!_isExtends?"  \"//\":\"Camera Frames Delay (low end user)\",":"")+"\n\n\t"+
        "\"fps\":"+to_string(_struct.fps)+","+(!_isExtends?"         \"//\":\"Max Fps can be reached / maintained\",":"")+"\n\t"+
        "\"fpsDisplay\":"+(_struct.fpsDisplay?"true":"false")+","+(!_isExtends?"\"//\":\"Show Fps\",":"")+"\n\n\t"+
        "\"fontDir\":\""+_struct.fontDir+"\","+(!_isExtends?"     \"//\":\"TTF (or) OTF supported\",":"")+"\n\t"+
        "\"fontSize\":"+to_string(_struct.fontSize)+","+(!_isExtends?"    \"//\":\"Adjust according to your screen\",":"")+"\n\n\t"+
        "\"keyExit\":\""+(char) _struct.keyExit+"\","+(!_isExtends?"    \"//\":\"Exit Key       'q'\",":"")+"\n\t"+
        "\"keyPause\":\""+(char) _struct.keyPause+"\","+(!_isExtends?"    \"//\":\"Pause Key      'SPACE'\",":"")+"\n\t"+
        "\"keyScreenshot\":\""+(char) _struct.keyScreenshot+"\","+(!_isExtends?"\"//\":\"Screenshot Key 'a'\",":"")+"\n\n\t"+
        "\"fillModes\":[\n\t\t"
    ;

    for(int i = 0; i < _struct.fillModesSize; i++)
        parsedString+= "\""+_struct.fillModes[i]+"\""+(i==_struct.fillModesSize-1?"\n\t":",\n\t\t");
    parsedString += "],\n\t\"fillMode\":"+to_string(_struct.fillMode)+","+(!_isExtends?"    \"//\":\"Selected Fill Mode From The `fillModes` array [0-n]\",":"")+"\n\n";

    if(!_isExtends){
        parsedString += (_struct.isExtends?"\t\"extends\":":"\t\"extends\":{}\n}");
        if(_struct.isExtends && _struct.extends != NULL)
            parsedString += ac_json_parseStruct(*_struct.extends,true)+"\n}";
    }else parsedString += "\t}";
    
    return parsedString;

}