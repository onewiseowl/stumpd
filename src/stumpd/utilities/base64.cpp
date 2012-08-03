
#include <stumpd/utilities/base64.hpp>
#include <iostream>

void
stumpd::utilities::base64::encodeblock( unsigned char in[3], unsigned char out[4], int len )
{
    out[0] = stumpd::utilities::base64::cb64[ in[0] >> 2 ];
    out[1] = stumpd::utilities::base64::cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? stumpd::utilities::base64::cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? stumpd::utilities::base64::cb64[ in[2] & 0x3f ] : '=');
}

void
stumpd::utilities::base64::encode( char *in_data, char *out_data, int in_len )
{

    char* in_data_orig;
    char* out_data_orig;

    in_data_orig = in_data;
    out_data_orig = out_data;

    unsigned char in[3], out[4];
    int i, len, count;

    for(count=0;count<in_len;)
    {
        len = 0;
        for( i = 0; i < 3; i++ ) {
            //in[i] = (unsigned char) getc( infile );
            in[i] = (unsigned char)*in_data++;
            if( count < in_len) {
                len++;
            }
            else {
                in[i] = 0;
            }
        }
        if( len ) {
            stumpd::utilities::base64::encodeblock( in, out, len );
            for( i = 0; i < 4; i++ ) {
                //putc( out[i], outfile );
                *out_data = out[i];
                out_data++;
            }
            count += len;
        }
    }
  in_data = in_data_orig;
  out_data = out_data_orig;
}

void
stumpd::utilities::base64::decodeblock( unsigned char in[4], unsigned char out[3] )
{   
    out[ 0 ] = (unsigned char ) (in[0] << 2 | in[1] >> 4);
    out[ 1 ] = (unsigned char ) (in[1] << 4 | in[2] >> 2);
    out[ 2 ] = (unsigned char ) (((in[2] << 6) & 0xc0) | in[3]);
}

void 
stumpd::utilities::base64::decode( char *in_data, char *out_data, int in_len )
{
    unsigned char in[4], out[3], v;
    int i, len, count;
    char *out_data_orig, *in_data_new;
    //in_data_orig = in_data;
    in_data_new = in_data;
    out_data_orig = out_data;


    for (count=0;count<in_len;) {
        for( len = 0, i = 0; i < 4; i++ ) {
            v = 0;
            while( count<in_len-1 && v == 0 ) {
                v = (unsigned char) *in_data_new++;
                v = (unsigned char) ((v < 43 || v > 122) ? 0 : stumpd::utilities::base64::cd64[ v - 43 ]);
                if( v ) {
                    v = (unsigned char) ((v == '$') ? 0 : v - 61);
                }
            }
            if( count<in_len ) {
                len++;
                if( v ) {
                    in[ i ] = (unsigned char) (v - 1);
                }
            }
            else {
                in[i] = 0;
            }
        }
        if( len ) {
            stumpd::utilities::base64::decodeblock( in, out );
            for( i = 0; i < len - 1; i++ ) {
                *out_data++ = out[i];
            }
            count += len;
        }
      }
    //in_data = in_data_orig;
    fprintf(stdout, "last char: %c and %d\n", out_data[0], out_data[0]);
    out_data = out_data_orig;
}


std::string
stumpd::utilities::base64::decode(std::string input)
{

  if(input.length() != 0)
  {

    char *output;
    output = (char*)malloc(sizeof(char)*input.length()+20);
    memset(output, '\0', input.length()+20);

    if(output != NULL)
    {

      //memset(output, '\0', input.length()+2);
      stumpd::utilities::base64::decode((char *)input.c_str(), output, input.length());
      std::string output_str(output);  
  
      free(output);
      return output_str.substr(0, output_str.length());
    } else {
      return std::string(NULL);
    }
  } else {
    return std::string(NULL);
  }

}
