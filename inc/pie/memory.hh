#ifndef PIE_MEMORY_HH
#define PIE_MEMORY_HH

#include <pie\error.hh>

namespace pie::memory
{
    constexpr inline none copy( nadd target, cadd source, usize size ) noexcept
    {
        const dual first = source and target and size != 0;
        const dual other = source != target;

        if( first and other ) __builtin_memcpy( target, source, size );
    }
    constexpr inline none move( nadd target, cadd source, usize size ) noexcept
    {
        const dual first = source and target and size != 0;
        const dual other = source != target;

        if( first and other ) __builtin_memmove( target, source, size );
    }
    constexpr inline none move( nadd target, uint08 byte, usize size ) noexcept
    {
        if( target and size != 0 ) __builtin_memset( target, byte, size );
    }

    nadd give( usize size ) noexcept;
    none free( nadd place ) noexcept;

    usize client_usage( ) noexcept;
    usize system_usage( ) noexcept;
}

pie::nadd operator new( pie::usize size );
pie::nadd operator new( pie::usize size, pie::error::danger flag ) noexcept;
pie::nadd operator new( pie::usize size, pie::nadd place ) noexcept;

pie::nadd operator new[]( pie::usize size );
pie::nadd operator new[]( pie::usize size, pie::error::danger flag ) noexcept;
pie::nadd operator new[]( pie::usize size, pie::nadd place ) noexcept;

pie::none operator delete( pie::nadd place ) noexcept;
pie::none operator delete( pie::nadd place, pie::usize size ) noexcept;
pie::none operator delete( pie::nadd place, pie::nadd other ) noexcept;

pie::none operator delete[]( pie::nadd place ) noexcept;
pie::none operator delete[]( pie::nadd place, pie::usize size ) noexcept;
pie::none operator delete[]( pie::nadd place, pie::nadd other ) noexcept;

#endif