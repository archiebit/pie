#include <pie\utils.hh>

namespace pie
{
    uint08 swap( uint08 x ) noexcept
    {
        static uint08 nibble[ ]
        {
            0, 8, 4, 12, 2, 10, 6, 14,
            1, 9, 5, 13, 3, 11, 7, 15
        };

        uint08 y = 0;
        uint08 c = 2;

        while( c-- )
        {
            y = ( y << 4 ) + nibble[ x bitand 15 ];
            x = ( x >> 4 );
        }
        
        return y;
    }
    uint16 swap( uint16 x, swaps option ) noexcept
    {
        uint16 y = 0;
        uint08 c = 2;

        if( option == bits ) while( c-- )
        {
            y = ( y << 8 ) + swap( uint08( x ) );
            x = ( x >> 8 );
        }

        if( option == byte ) asm
        (
            "ror cx, 8  \n"
            "mov %0, cx \n" : "=r"( y )
        );
        
        return y;
    }
    uint32 swap( uint32 x, swaps option ) noexcept
    {
        uint32 y = 0;
        uint08 c = 4;

        if( option == bits ) while( c-- )
        {
            y = ( y << 8 ) + swap( uint08( x ) );
            x = ( x >> 8 );
        }

        if( option == byte ) asm
        (
            "bswap ecx   \n"
            "mov %0, ecx \n" : "=r"( y )
        );
        
        return y;
    }
    uint64 swap( uint64 x, swaps option ) noexcept
    {
        uint64 y = 0;
        uint08 c = 8;

        if( option == bits ) while( c-- )
        {
            y = ( y << 8 ) + swap( uint08( x ) );
            x = ( x >> 8 );
        }

        if( option == byte ) asm
        (
            "bswap rcx   \n"
            "mov %0, rcx \n" : "=r"( y )
        );
        
        return y;
    }

    [[gnu::naked]] uint08 scan( uint08 x, dual reverse ) noexcept
    {
        asm
        (
            "mov eax, 255   \n"
            "mov r8d, 255   \n"
            "and ecx, 255   \n"
            "bsr r8d, ecx   \n"
            "bsf eax, ecx   \n"
            "cmp edx, 1     \n"
            "cmove eax, r8d \n"
            "ret            \n"
        );
    }
    [[gnu::naked]] uint08 scan( uint16 x, dual reverse ) noexcept
    {
        asm
        (
            "mov eax, 255   \n"
            "mov r8d, 255   \n"
            "and ecx, 65535 \n"
            "bsr r8d, ecx   \n"
            "bsf eax, ecx   \n"
            "cmp edx, 1     \n"
            "cmove eax, r8d \n"
            "ret            \n"
        );
    }
    [[gnu::naked]] uint08 scan( uint32 x, dual reverse ) noexcept
    {
        asm
        (
            "mov eax, 255   \n"
            "mov r8d, 255   \n"
            "bsr r8d, ecx   \n"
            "bsf eax, ecx   \n"
            "cmp edx, 1     \n"
            "cmove eax, r8d \n"
            "ret            \n"
        );
    }
    [[gnu::naked]] uint08 scan( uint64 x, dual reverse ) noexcept
    {
        asm
        (
            "mov eax, 255   \n"
            "mov r8d, 255   \n"
            "bsr r8,  rcx   \n"
            "bsf rax, rcx   \n"
            "cmp edx, 1     \n"
            "cmove rax, r8  \n"
            "ret            \n"
        );
    }

    dual peek( uint08 x, uint08 index ) noexcept
    {
        constexpr uint08 last = 7;

        return x bitand ( 1 << min( index, last ) ); 
    }
    dual peek( uint16 x, uint08 index ) noexcept
    {
        constexpr uint08 last = 15;

        return x bitand ( 1 << min( index, last ) ); 
    }
    dual peek( uint32 x, uint08 index ) noexcept
    {
        constexpr uint08 last = 31;

        return x bitand ( 1 << min( index, last ) ); 
    }
    dual peek( uint64 x, uint08 index ) noexcept
    {
        constexpr uint08 last = 63;

        return x bitand ( 1 << min( index, last ) ); 
    }

    dual poke( uint08 x, uint08 index, dual value ) noexcept
    {
        constexpr uint08 last = 7;

        if( value ) return x bitor        ( 1 << min( index, last ) );
        else        return x bitand compl ( 1 << min( index, last ) );
    }
    dual poke( uint16 x, uint08 index, dual value ) noexcept
    {
        constexpr uint08 last = 15;

        if( value ) return x bitor        ( 1 << min( index, last ) );
        else        return x bitand compl ( 1 << min( index, last ) );
    }
    dual poke( uint32 x, uint08 index, dual value ) noexcept
    {
        constexpr uint08 last = 31;

        if( value ) return x bitor        ( 1 << min( index, last ) );
        else        return x bitand compl ( 1 << min( index, last ) );
    }
    dual poke( uint64 x, uint08 index, dual value ) noexcept
    {
        constexpr uint08 last = 63;

        if( value ) return x bitor        ( 1 << min( index, last ) );
        else        return x bitand compl ( 1 << min( index, last ) );
    }

    [[gnu::naked]] uint32 extract( uint32 x, uint32 mask ) noexcept
    {
        asm
        (
            "pext eax, ecx, edx \n"
            "ret                \n"
        );
    }
    [[gnu::naked]] uint32 deposit( uint32 x, uint32 mask ) noexcept
    {
        asm
        (
            "pdep eax, ecx, edx \n"
            "ret                \n"
        );
    }
}