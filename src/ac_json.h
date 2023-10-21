
#ifndef JSON_H
#define JSON_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdbool.h>

#include "ac_cli.h"

using namespace std;

ac_cli_CONFIG ac_json_parseFile(string fileDir);
string ac_json_parseStruct(ac_cli_CONFIG _struct, bool _isExtends = false);

#endif /* JSON_H */