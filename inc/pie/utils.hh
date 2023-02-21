#ifndef PIE_UTILS_HH
#define PIE_UTILS_HH

#include <pie\trait.hh>
#include <pie\type.hh>

namespace std
{
    template <typename type>
    class initializer_list
    {
    public:
        constexpr ~initializer_list( ) noexcept = default;
        constexpr  initializer_list( ) noexcept = default;
    
        constexpr pie::usize size( ) const noexcept
        {
            return tail - head;
        }

        constexpr const type * begin( ) const noexcept
        {
            return head;
        }
        constexpr const type * end( ) const noexcept
        {
            return tail;
        }

    private:
        constexpr  initializer_list( const type * head, const type * tail ) noexcept
        :   head( head ),
            tail( tail )
        { }

        const type * head = nullptr;
        const type * tail = nullptr;
    };
}

#define provide( sample ) static_cast<pie::remref<decltype( sample )> &&>( sample )
#define forward( sample ) static_cast<decltype( sample ) &&>( sample )

namespace pie
{
    template <typename type>
    using initials = std::initializer_list<type>;

    constexpr inline const auto & min( const auto & first, const auto &... other ) noexcept
    {
        if constexpr( sizeof...( other ) != 0 )
        {
            auto & small = min( other... );

            if( first < small ) return first;
            else                return small;
        }
        else return first;
    }
    constexpr inline const auto & max( const auto & first, const auto &... other ) noexcept
    {
        if constexpr( sizeof...( other ) != 0 )
        {
            auto & large = max( other... );

            if( first > large ) return first;
            else                return large;
        }
        else return first;
    }

    constexpr inline none exchange( auto & first, auto & other ) noexcept
    {
        auto tempo = provide( first );

        first = provide( other );
        other = provide( tempo );
    }

    enum swaps : uint08
    {
        bits, byte
    };

    uint08 swap( uint08 x ) noexcept;
    uint16 swap( uint16 x, swaps option ) noexcept;
    uint32 swap( uint32 x, swaps option ) noexcept;
    uint64 swap( uint64 x, swaps option ) noexcept;

    uint08 scan( uint08 x, dual reverse ) noexcept;
    uint08 scan( uint16 x, dual reverse ) noexcept;
    uint08 scan( uint32 x, dual reverse ) noexcept;
    uint08 scan( uint64 x, dual reverse ) noexcept;

    dual peek( uint08 x, uint08 index ) noexcept;
    dual peek( uint16 x, uint08 index ) noexcept;
    dual peek( uint32 x, uint08 index ) noexcept;
    dual peek( uint64 x, uint08 index ) noexcept;

    dual poke( uint08 x, uint08 index, dual value ) noexcept;
    dual poke( uint16 x, uint08 index, dual value ) noexcept;
    dual poke( uint32 x, uint08 index, dual value ) noexcept;
    dual poke( uint64 x, uint08 index, dual value ) noexcept;

    uint32 extract( uint32 x, uint32 mask ) noexcept;
    uint32 deposit( uint32 x, uint32 mask ) noexcept;
}

#endif