#include "ac_json.h"


void ac_json_setValue(string attribute, string value, ac_cli_CONFIG* globalConfig){

}

bool ac_json_isEscapeChar(char c){return (/*c==' '||*/c=='\r'||c=='\t'||c=='\n'||c=='\0');}
ac_cli_CONFIG ac_json_parseFile(string fileDir){

    ac_cli_CONFIG configStruct;

    if(fileDir.find(".json") != fileDir.size() -5 )
        return configStruct;

    ifstream configFile(fileDir);
    if(!configFile)
        return configStruct;

    configStruct.status = true;
    return configStruct;

    int _ifFound;
    string line;string tLine = "";
    while (getline(configFile, line)) {
        line.erase(0,line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(remove_if(line.begin(), line.end(), ac_json_isEscapeChar),line.end());

        if((_ifFound = line.find("\"//\"")) != string::npos)
            line.replace(_ifFound, line.length() - _ifFound, " ");
        tLine += line;
    }
    
    cout<<tLine<<endl;

    configStruct.status = true;
    return configStruct;

}

string ac_json_parseStruct(ac_cli_CONFIG _struct, bool _isExtends){

    std::wstring wStr(1, *_struct.font);
    std::string fontName(wStr.begin(), wStr.end());

    string parsedString = 
        "{\n\t\"camera\":"+to_string(_struct.camera)+","+(!_isExtends?"       \"//\":\"Camera 0 (default cam) [0-n]\",":"")+"\n\t"+
        "\"cameraDelay\":"+to_string(_struct.cameraDelay)+","+(!_isExtends?"  \"//\":\"Camera Frames Delay (low end user)\",":"")+"\n\n\t"+
        "\"fps\":"+to_string(_struct.fps)+","+(!_isExtends?"         \"//\":\"Max Fps can be reached / maintained\",":"")+"\n\t"+
        "\"fpsDisplay\":"+(_struct.fpsDisplay?"true":"false")+","+(!_isExtends?"\"//\":\"Show Fps\",":"")+"\n\n\t"+
        "\"font\":\""+fontName+"\","+(!_isExtends?"        \"//\":\"Installed Font Name\",":"")+"\n\t"+
        "\"fontSize\":"+to_string(_struct.fontSize)+","+(!_isExtends?"    \"//\":\"Adjust according to your screen\",":"")+"\n\n\t"+
        "\"keyExit\":\""+(char) _struct.keyExit+"\","+(!_isExtends?"    \"//\":\"Exit Key       'q'\",":"")+"\n\t"+
        "\"keyPause\":\""+(char) _struct.keyPause+"\","+(!_isExtends?"    \"//\":\"Pause Key      'p'\",":"")+"\n\t"+
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