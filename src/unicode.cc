#include <pie\unicode.hh>
#include <pie\utils.hh>

namespace pie::unicode
{
    usize size( char32 point, encoding type ) noexcept
    {
        if( type == UTF08 )
        {
            if( point <= 0x0000'007F ) return 1;
            if( point <= 0x0000'07FF ) return 2;
            if( point <= 0x0000'FFFF ) return 3;
            if( point <= 0x0010'FFFF ) return 4;
            else                      return 0;
        }

        if( type == UTF16 )
        {
            if( point <= 0x0000'D7FF ) return 1;
            if( point <= 0x0000'DFFF ) return 0;
            if( point <= 0x0000'FFFF ) return 1;
            if( point <= 0x0010'FFFF ) return 2;
            else                      return 0;
        }

        return 0;
    }

    usize size( const char08 * symbol, encoding type ) noexcept
    {
        if( not symbol ) return 0;

        uint08 bit = scan( uint08( compl symbol[ 0 ] ), true );
        uint08 len = bit == 7 ? 1 : 7 - bit;

        if( bit == 255 or bit == 6 or bit < 3 )
        {
            return 0;
        }
        else for( uint08 i = 1; i < len; ++i )
        {
            if( ( symbol[ i ] bitand 0xC0 ) != 0x80 )
            return 0;
        }

        if( type == UTF08 ) return len;
        if( type == UTF16 ) return len == 4 ? 2 : 1;

        return 0;
    }
    usize size( const char16 * symbol, encoding type ) noexcept
    {
        if( not symbol ) return 0;

        dual x = false;
        dual y = false;

        ( x = ( symbol[ 0 ] bitand 0xFC00 ) == 0xD800 )
        and
        ( y = ( symbol[ 1 ] bitand 0xFC00 ) == 0xDC00 );

        if( x and y ) switch( type )
        {
            case UTF08: return 4;
            case UTF16: return 2;
        }

        if( not x and not y ) switch( type )
        {
            case UTF16: return 1;
            case UTF08:
                if( symbol[ 0 ] <= 0x007F ) return 1;
                if( symbol[ 0 ] <= 0x07FF ) return 2;
                if( symbol[ 0 ] <= 0xFFFF ) return 3;
        }

        return 0;
    }
    usize size( const char08 * string, encoding type, usize length ) noexcept
    {
        usize fine;
        usize step = 0, size = 0;

        const dual ranged = string and length != trail;
        const dual trails = string and length == trail;

        if( ranged ) while( length-- )
        {
            fine = unicode::size( string + step, UTF08 );

            if( not fine ) break;

            size += unicode::size( string + step, type );
            step += fine;
        }
        if( trails ) while( string[ step ] )
        {
            fine = unicode::size( string + step, UTF08 );

            if( not fine ) break;

            size += unicode::size( string + step, type );
            step += fine;
        }

        return size;
    }
    usize size( const char16 * string, encoding type, usize length ) noexcept
    {
        usize fine;
        usize step = 0, size = 0;

        const dual ranged = string and length != trail;
        const dual trails = string and length == trail;

        if( ranged ) while( length-- )
        {
            fine = unicode::size( string + step, UTF16 );

            if( not fine ) break;

            size += unicode::size( string + step, type );
            step += fine;
        }
        if( trails ) while( string[ step ] )
        {
            fine = unicode::size( string + step, UTF16 );

            if( not fine ) break;

            size += unicode::size( string + step, type );
            step += fine;
        }

        return size;
    }

    usize length( const char08 * string, usize size ) noexcept
    {
        usize fine;
        usize step = 0, count = 0;

        const dual ranged = string and size != trail;
        const dual trails = string and size == trail;

        if( ranged ) while( size != 0 )
        {
            fine = unicode::size( string + step, UTF08 );

            if( not fine ) break;

            step  += fine;
            size  -= fine;
            count += 1;
        }
        if( trails ) while( string[ step ] )
        {
            fine = unicode::size( string + step, UTF08 );

            if( not fine ) break;

            step  += fine;
            count += 1;
        }

        return count;
    }
    usize length( const char16 * string, usize size ) noexcept
    {
        usize fine;
        usize step = 0, count = 0;

        const dual ranged = string and size != trail;
        const dual trails = string and size == trail;

        if( ranged ) while( size != 0 )
        {
            fine = unicode::size( string + step, UTF08 );

            if( not fine ) break;

            step  += fine;
            size  -= fine;
            count += 1;
        }
        if( trails ) while( string[ step ] )
        {
            fine = unicode::size( string + step, UTF08 );

            if( not fine ) break;

            step  += fine;
            count += 1;
        }

        return count;
    }

    usize encode( char32 point, char08 * symbol ) noexcept
    {
        if( not symbol ) return 0;

        uint08 size = unicode::size( point, UTF08 );
        uint32 pack = point;

        switch( size )
        {
            case 2: pack = deposit( point, 0x0000'1F3F ); break;
            case 3: pack = deposit( point, 0x000F'3F3F ); break;
            case 4: pack = deposit( point, 0x073F'3F3F ); break;
        }

        switch( size )
        {
            case 2: pack += 0x0000'C080; break;
            case 3: pack += 0x00E0'8080; break;
            case 4: pack += 0xF080'8080; break;
        }

        for( uint08 i = size - 1; i < size; --i )
        {
            symbol[ i ] = pack; pack >>= 8;
        }

        return size;
    }
    usize encode( char32 point, char16 * symbol ) noexcept
    {
        if( not symbol ) return 0;

        uint08 size = unicode::size( point, UTF16 );
        uint32 pack = point;

        if( size == 2 )
        {
            pack -= 0x0001'0000;
            pack  = deposit( pack, 0x03FF'03FF );
            pack += 0xD800'DC00;
        }

        for( uint08 i = size - 1; i < size; --i )
        {
            symbol[ i ] = pack; pack >>= 16;
        }

        return size;
    }
    usize decode( char32 & point, const char08 * symbol ) noexcept
    {
        if( not symbol ) return 0;

        uint08 size = unicode::size( symbol, UTF08 );
        uint32 pack = 0;

        for( uint08 i = 0; i < size; ++i )
        {
            pack <<= 8;
            pack  += symbol[ i ];
        }

        switch( size )
        {
            case 1: point = extract( pack, 0x0000'007F ); break;
            case 2: point = extract( pack, 0x0000'1F3F ); break;
            case 3: point = extract( pack, 0x000F'3F3F ); break;
            case 4: point = extract( pack, 0x073F'3F3F ); break;
        }

        return size;
    }
    usize decode( char32 & point, const char16 * symbol ) noexcept
    {
        if( not symbol ) return 0;

        uint08 size = unicode::size( symbol, UTF16 );
        uint32 pack = 0;

        for( uint08 i = 0; i < size; ++i )
        {
            pack <<= 16;
            pack  += symbol[ i ];
        }

        if( size == 1 ) point = pack;

        if( size == 2 )
        {
            point  = extract( pack, 0x03FF'03FF );
            point += 0x0001'0000;
        }

        return size;
    }

    usize convert( char08 * target, const char16 * source ) noexcept
    {
        char32 point = limit<uint32>::max;

        return decode( point, source ), encode( point, target );
    }
    usize convert( char16 * target, const char08 * source ) noexcept
    {
        char32 point = limit<uint32>::max;

        return decode( point, source ), encode( point, target );
    }
    usize convert( char08 * target, const char16 * source, usize length ) noexcept
    {
        usize fine;
        usize step = 0, size = 0;

        char32 point;

        const dual ranged = source and target and length != trail;
        const dual trails = source and target and length == trail;
    
        if( ranged ) while( length-- )
        {
            fine  = decode( point, source + step );

            if( not fine ) break;

            size += encode( point, target + size );
            step += fine;
        }
        if( trails ) while( source[ step ] )
        {
            fine  = decode( point, source + step );

            if( not fine ) break;

            size += encode( point, target + size );
            step += fine;
        }

        return size;
    }
    usize convert( char16 * target, const char08 * source, usize length ) noexcept
    {
        usize fine;
        usize step = 0, size = 0;

        char32 point;

        const dual ranged = source and target and length != trail;
        const dual trails = source and target and length == trail;
    
        if( ranged ) while( length-- )
        {
            fine  = decode( point, source + step );

            if( not fine ) break;

            size += encode( point, target + size );
            step += fine;
        }
        if( trails ) while( source[ step ] )
        {
            fine  = decode( point, source + step );

            if( not fine ) break;

            size += encode( point, target + size );
            step += fine;
        }

        return size;
    }
}