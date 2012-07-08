#ifndef STUMPD_UTILITIES_BASE64_HEADER
#define STUMPD_UTILITIES_BASE64_HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

namespace stumpd {
  namespace utilities  {
    namespace base64    {

      /*
      ** Translation Table as described in RFC1113
      */
      static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

      /*
      ** Translation Table to decode (created by author)
      */
      static const char cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";


      void
      encodeblock( unsigned char in[3], unsigned char out[4], int len );

      void
      encode( char *in_data, char *out_data, int in_len );

      void
      decodeblock( unsigned char in[4], unsigned char out[3] );

      void 
      decode( char *in_data, char *out_data, int in_len );

      std::string
      decode(std::string input);

    }
  }
}

#endif
