#ifndef FILTERS_HEADER
#define FILTERS_HEADER

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <stumpd/database/mysql.hpp>
#include <stumpd/v8/v8.hpp>
#include <stumpd/utilities/base64.hpp>

namespace stumpd {
  static std::vector< std::vector <std::string> > filters;


  static const char *sleepjs = "function sleep(millis)\n{\n  var date = new Date();\n  var curDate = null;\n  do { curDate = new Date(); }\n  while(curDate-date < millis);\n}\n";

  static const char *base64js =   "var keyStr = 'ABCDEFGHIJKLMNOP' +\n               'QRSTUVWXYZabcdef' +\n               'ghijklmnopqrstuv' +\n               'wxyz0123456789+/' +\n               '=';\n\n  function encode64(input) {\n     input = input;\n     var output = '';\n     var chr1, chr2, chr3 = '';\n     var enc1, enc2, enc3, enc4 = '';\n     var i = 0;\n\n     do {\n        chr1 = input.charCodeAt(i++);\n        chr2 = input.charCodeAt(i++);\n        chr3 = input.charCodeAt(i++);\n\n        enc1 = chr1 >> 2;\n        enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);\n        enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);\n        enc4 = chr3 & 63;\n\n        if (isNaN(chr2)) {\n           enc3 = enc4 = 64;\n        } else if (isNaN(chr3)) {\n           enc4 = 64;\n        }\n\n        output = output +\n           keyStr.charAt(enc1) +\n           keyStr.charAt(enc2) +\n           keyStr.charAt(enc3) +\n           keyStr.charAt(enc4);\n        chr1 = chr2 = chr3 = '';\n        enc1 = enc2 = enc3 = enc4 = '';\n     } while (i < input.length);\n\n     return output;\n  }\n\n  function decode64(input) {\n     var output = '';\n     var chr1, chr2, chr3 = '';\n     var enc1, enc2, enc3, enc4 = '';\n     var i = 0;\n     var base64test = /[^A-Za-z0-9\+\/\=]/g;\n     if (base64test.exec(input)) {\n        'There were invalid base64 characters in the input text.'\n     }\n     input = input.replace(/[^A-Za-z0-9\+\/\=]/g, '');\n\n     do {\n        enc1 = keyStr.indexOf(input.charAt(i++));\n        enc2 = keyStr.indexOf(input.charAt(i++));\n        enc3 = keyStr.indexOf(input.charAt(i++));\n        enc4 = keyStr.indexOf(input.charAt(i++));\n\n        chr1 = (enc1 << 2) | (enc2 >> 4);\n        chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);\n        chr3 = ((enc3 & 3) << 6) | enc4;\n\n        output = output + String.fromCharCode(chr1);\n\n        if (enc3 != 64) {\n           output = output + String.fromCharCode(chr2);\n        }\n        if (enc4 != 64) {\n           output = output + String.fromCharCode(chr3);\n        }\n\n        chr1 = chr2 = chr3 = '';\n        enc1 = enc2 = enc3 = enc4 = '';\n\n     } while (i < input.length);\n\n     return output;\n  }\n";
// Load all Javascript libraries from the .js files in /opt/stump/usr/lib/js/"


  int
  load_filters();

  std::string
  execute_filters(const char *data);

}
#endif
