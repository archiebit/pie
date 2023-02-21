#include <pie\memory.hh>
#include <pie\macro.hh>

#include <processthreadsapi.h>
#include <errhandlingapi.h>
#include <heapapi.h>
#include <psapi.h>

using namespace pie;

namespace pie::memory
{
    static usize usage = 0;
    static HANDLE heap = GetProcessHeap( );

    nadd give( usize size ) noexcept
    {
        nadd place = nullptr;

        if( size  ) place  = HeapAlloc( heap, 0, size );
        if( place ) usage += HeapSize( heap, 0, place );

        return place;
    }
    none free( nadd place ) noexcept
    {
        if( not place ) return;

        dual fine = HeapValidate( heap, 0, place );

        if( fine )
        {
            usage -= HeapSize( heap, 0, place );
            fine   = HeapFree( heap, 0, place );

            if( not fine ) GetLastError( );
        }
    }

    usize client_usage( ) noexcept
    {
        return usage;
    }
    usize system_usage( ) noexcept
    {
        using normal = PROCESS_MEMORY_COUNTERS;
        using extend = PROCESS_MEMORY_COUNTERS_EX;

        auto counts = extend( );
        auto handle = GetCurrentProcess( );
        auto points = reinterpret_cast<normal *>( & counts );
    
        K32GetProcessMemoryInfo( handle, points, sizeof( counts ) );

        return counts.PagefileUsage;
    }
}

nadd operator new( usize size )
{
    if( nadd place = memory::give( size ) )
    {
        return place;
    }
    else throw error::operation( );
}
nadd operator new( usize size, error::danger flag ) noexcept
{
    unuse flag;

    return memory::give( size );
}
nadd operator new( usize size, nadd place ) noexcept
{
    unuse size;

    return place;
}

nadd operator new[]( usize size )
{
    if( nadd place = memory::give( size ) )
    {
        return place;
    }
    else throw error::operation( );
}
nadd operator new[]( usize size, error::danger flag ) noexcept
{
    unuse flag;

    return memory::give( size );
}
nadd operator new[]( usize size, nadd place ) noexcept
{
    unuse size;

    return place;
}

none operator delete( nadd place ) noexcept
{
    memory::free( place );
}
none operator delete( nadd place, usize size ) noexcept
{
    unuse size;

    memory::free( place );
}
none operator delete( nadd place, nadd other ) noexcept
{
    unuse place;
    unuse other;
}

none operator delete[]( nadd place ) noexcept
{
    memory::free( place );
}
none operator delete[]( nadd place, usize size ) noexcept
{
    unuse size;

    memory::free( place );
}
none operator delete[]( nadd place, nadd other ) noexcept
{
    unuse place;
    unuse other;
}