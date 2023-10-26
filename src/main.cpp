#include <opencv2/opencv.hpp>

#include "ac_cli.h"
#include "ac_json.h"
#include "ac_cmd.h"

using namespace std;

int main(int argc, char** argv) {

    if( !ac_cli_isGlobalConfigExist() )
        ac_cli_createGlobalConfig();

    ac_cli_CONFIG globalConfig = ac_json_parseFile("./asciicam.global.config.json");

    if(!globalConfig.status){
        cerr<<"ERR: Unable To Parse The Global Config `JSON` file"<<
        endl<<"ERR: ./asciicam.global.config.json"<<endl;
        return 1;
    }

    if(argc > 1 && !ac_cli_setParameters(argv, &globalConfig)){
        cout<<"WAR: Unable To Parse Some Parameters"<<endl;
    }

    ac_cmd_renderLoop(globalConfig);

    getchar();
    return 0;

}
