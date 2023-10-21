#include <opencv2/opencv.hpp>

#include "ac_cli.h"
#include "ac_json.h"

using namespace std;

int main(int argc, char** argv) {

    if( !ac_cli_isGlobalConfigExist() )
        ac_cli_createGlobalConfig();

    ac_cli_CONFIG globalConfig = ac_json_parseFile("./asciicam.global.config.json");

    

    if(!globalConfig.status){
        cout<<"ERR: Unable To Parse The Global Config `JSON` file"<<endl
            <<"ERR: ./asciicam.global.config.json"<<endl;
        return 1;
    }

    if(argc > 1){
        cout<<argv<<endl;    
    }

    getchar();
    return 0;

}
