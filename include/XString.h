#ifndef __XSTRING_H__
#define __XSTRING_H__

#include <iostream>

class XString {
public:
    std::vector< std::string > readlines( const std::string& filepath ) {
        std::vector< std::string > res;
        std::ifstream in;
        in.open( filepath.c_str() );
        if ( !in ) {
            std::cerr << "Unable to open file.";
            exit(1);   
        }
        std::string tmp;
        while ( in >> tmp ) {
            res.push_back( tmp );
        }
        in.close();
        return res;
    }

    std::vector< std::string > split( std::string str, std::string delim ) {
        std::vector< std::string > res;
        if ( str.size() == 0 ) return res;
        //先将要切割的字符串从string类型转换为char*类型
        char *strs = new char[ str.size() + 1 ]; //不要忘了
        for ( int i = 0; i < str.size(); ++ i ) {
            strs[ i ] = str[ i ];
        }
        strs[ str.size() ] = '\0';
        // strcpy( strs, str.c_str() );

        char *d = new char[ delim.size() + 1 ];
        for ( int i = 0; i < delim.size(); ++ i ) {
            d[ i ] = delim[ i ];
        }
        d[ delim.size() ] = '\0';
        // strcpy( d, delim.c_str() );

        char *p = strtok( strs, d );
        while ( p ) {
            std::string s = p; //分割得到的字符串转换为string类型
            res.push_back( s ); //存入结果数组
            p = strtok( NULL, d );
        }
        return res;
    }

    std::string strip( std::string s ) {
        int n = s.size();
        if ( s[ n - 1 ] == '\n' )
            return s.substr( 0, n - 1 );
        return s;
    }

};

#endif