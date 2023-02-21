#ifndef PIE_TYPE_HH
#define PIE_TYPE_HH

#ifndef __WIN64
#   error 'Windows x86-64' is target platform
#endif

namespace pie
{
    using uint08 = unsigned char;
    using uint16 = unsigned short int;
    using uint32 = unsigned int;
    using uint64 = unsigned long long int;

    using sint08 = signed char;
    using sint16 = signed short int;
    using sint32 = signed int;
    using sint64 = signed long long int;
    
    using real32 = float;
    using real64 = double;

    using none = void;
    using dual = bool;

    using usize = unsigned long long int;
    using uintp = unsigned long long int;

    using ssize = signed long long int;
    using sintp = signed long long int;

    using cadd = const void *;
    using nadd = void *;

    using char08 = char8_t;
    using char16 = char16_t;
    using char32 = char32_t;
}

#endif