def dp():
    with open( 'all_5_order_by_num.csv', 'r' ) as fr:
        lines = fr.readlines()
        with open( 'hex_5_num.csv', 'w' ) as fw:
            for line in lines:
                info = line.strip().split( ',' )
                fw.write( str( hex( int( info[ 0 ] ) ) ) + ',' + info[ 1 ] + '\n' )

def debug():
    with open( 'all_7.csv', 'r' ) as fr:
        lines = fr.readlines()
        cnt = 0
        for line in lines:
            info = line.strip().split( ',' )
            key = info[ 0 ]
            val = info[ 1 ]
            if int( key ) > ( 0x80_0000 ):
                cnt += 1
        print( cnt )



if __name__ == "__main__":
    debug()
    dp()
