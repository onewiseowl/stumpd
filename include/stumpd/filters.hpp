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

  static const char *base64js =   "var keyStr = 'ABCDEFGHIJKLMNOP' +\
               'QRSTUVWXYZabcdef' +\
               'ghijklmnopqrstuv' +\
               'wxyz0123456789+/' +\
               '=';\
\
  function encode64(input) {\
     input = input;\
     var output = '';\
     var chr1, chr2, chr3 = '';\
     var enc1, enc2, enc3, enc4 = '';\
     var i = 0;\
\
     do {\
        chr1 = input.charCodeAt(i++);\
        chr2 = input.charCodeAt(i++);\
        chr3 = input.charCodeAt(i++);\
\
        enc1 = chr1 >> 2;\
        enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);\
        enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);\
        enc4 = chr3 & 63;\
\
        if (isNaN(chr2)) {\
           enc3 = enc4 = 64;\
        } else if (isNaN(chr3)) {\
           enc4 = 64;\
        }\
\
        output = output +\
           keyStr.charAt(enc1) +\
           keyStr.charAt(enc2) +\
           keyStr.charAt(enc3) +\
           keyStr.charAt(enc4);\
        chr1 = chr2 = chr3 = '';\
        enc1 = enc2 = enc3 = enc4 = '';\
     } while (i < input.length);\
\
     return output;\
  }\
\
  function decode64(input) {\
     var output = '';\
     var chr1, chr2, chr3 = '';\
     var enc1, enc2, enc3, enc4 = '';\
     var i = 0;\
     var base64test = /[^A-Za-z0-9\+\/\=]/g;\
     if (base64test.exec(input)) {\
        'There were invalid base64 characters in the input text.'\
     }\
     input = input.replace(/[^A-Za-z0-9\+\/\=]/g, '');\
\
     do {\
        enc1 = keyStr.indexOf(input.charAt(i++));\
        enc2 = keyStr.indexOf(input.charAt(i++));\
        enc3 = keyStr.indexOf(input.charAt(i++));\
        enc4 = keyStr.indexOf(input.charAt(i++));\
\
        chr1 = (enc1 << 2) | (enc2 >> 4);\
        chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);\
        chr3 = ((enc3 & 3) << 6) | enc4;\
\
        output = output + String.fromCharCode(chr1);\
\
        if (enc3 != 64) {\
           output = output + String.fromCharCode(chr2);\
        }\
        if (enc4 != 64) {\
           output = output + String.fromCharCode(chr3);\
        }\
\
        chr1 = chr2 = chr3 = '';\
        enc1 = enc2 = enc3 = enc4 = '';\
\
     } while (i < input.length);\
\
     return output;\
  }";
// Load all Javascript libraries from the .js files in /opt/stump/usr/lib/js/"


  int
  load_filters();

  std::string
  execute_filters(const char *data);

}
#endif
