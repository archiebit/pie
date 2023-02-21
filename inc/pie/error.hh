#ifndef PIE_ERROR_HH
#define PIE_ERROR_HH

#include <pie\type.hh>

namespace pie::error
{
    enum argument  : uint08 { };
    enum operation : uint08 { };
    enum bounds    : uint08 { };
    enum null      : uint08 { };
    enum danger    : uint08 { nothrow };

    dual warning( const char16 * message ) noexcept;
    none closing( const char16 * message ) noexcept;
}

namespace pie
{
    using error::nothrow;
}

#endif