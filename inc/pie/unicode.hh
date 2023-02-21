#ifndef PIE_UNICODE_HH
#define PIE_UNICODE_HH

#include <pie\limit.hh>
#include <pie\type.hh>

namespace pie::unicode
{
    enum encoding
    {
        UTF08, UTF16
    };

    constexpr usize trail = limit<usize>::max;

    usize size( char32 point, encoding type ) noexcept;

    usize size( const char08 * symbol, encoding type ) noexcept;
    usize size( const char16 * symbol, encoding type ) noexcept;
    usize size( const char08 * string, encoding type, usize length ) noexcept;
    usize size( const char16 * string, encoding type, usize length ) noexcept;

    usize length( const char08 * string, usize size ) noexcept;
    usize length( const char16 * string, usize size ) noexcept;

    usize encode( char32 point, char08 * symbol ) noexcept;
    usize encode( char32 point, char16 * symbol ) noexcept;
    usize decode( char32 & point, const char08 * symbol ) noexcept;
    usize decode( char32 & point, const char16 * symbol ) noexcept;

    usize convert( char08 * target, const char16 * source ) noexcept;
    usize convert( char16 * target, const char08 * source ) noexcept;
    usize convert( char08 * target, const char16 * source, usize length ) noexcept;
    usize convert( char16 * target, const char08 * source, usize length ) noexcept;
}

namespace pie
{
    using unicode::encoding;
    using unicode::trail;
}

#endif