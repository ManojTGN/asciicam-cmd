
#ifndef JSON_H
#define JSON_H

#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdbool.h>

#include "ac_cli.h"

using namespace std;

bool ac_json_isEscapeChar(char c);
void ac_json_setValue(string attribute, string value, ac_cli_CONFIG* globalConfig);
ac_cli_CONFIG ac_json_parseFile(string fileDir);
string ac_json_parseStruct(ac_cli_CONFIG _struct, bool _isExtends = false);

#endif /* JSON_H */