#ifndef PIE_LIMIT_HH
#define PIE_LIMIT_HH

namespace pie
{
    template <typename type>
    class limit;

    template <>
    class limit<unsigned char>
    {
    public:
        constexpr static unsigned char hex = 2;
        constexpr static unsigned char dec = 3;
        constexpr static unsigned char bin = 8;

        constexpr static unsigned char min = 0x00;
        constexpr static unsigned char max = 0xFF;
    };

    template <>
    class limit<unsigned short int>
    {
    public:
        constexpr static unsigned char hex = 4;
        constexpr static unsigned char dec = 5;
        constexpr static unsigned char bin = 16;

        constexpr static unsigned short int min = 0x0000;
        constexpr static unsigned short int max = 0xFFFF;
    };

    template <>
    class limit<unsigned int>
    {
    public:
        constexpr static unsigned char hex = 8;
        constexpr static unsigned char dec = 10;
        constexpr static unsigned char bin = 32;

        constexpr static unsigned int min = 0x0000'0000;
        constexpr static unsigned int max = 0xFFFF'FFFF;
    };

    template <>
    class limit<unsigned long int>
    {
    public:
        constexpr static unsigned char hex = 8;
        constexpr static unsigned char dec = 10;
        constexpr static unsigned char bin = 32;

        constexpr static unsigned long int min = 0x0000'0000;
        constexpr static unsigned long int max = 0xFFFF'FFFF;
    };

    template <>
    class limit<unsigned long long int>
    {
    public:
        constexpr static unsigned char hex = 16;
        constexpr static unsigned char dec = 20;
        constexpr static unsigned char bin = 64;

        constexpr static unsigned long long int min = 0x0000'0000'0000'0000;
        constexpr static unsigned long long int max = 0xFFFF'FFFF'FFFF'FFFF;
    };


    template <>
    class limit<signed char>
    {
    public:
        constexpr static unsigned char hex = 2;
        constexpr static unsigned char dec = 4;
        constexpr static unsigned char bin = 8;

        constexpr static signed char min = 0x80;
        constexpr static signed char max = 0x7F;
    };

    template <>
    class limit<signed short int>
    {
    public:
        constexpr static unsigned char hex = 4;
        constexpr static unsigned char dec = 6;
        constexpr static unsigned char bin = 16;

        constexpr static signed short int min = 0x8000;
        constexpr static signed short int max = 0x7FFF;
    };

    template <>
    class limit<signed int>
    {
    public:
        constexpr static unsigned char hex = 8;
        constexpr static unsigned char dec = 11;
        constexpr static unsigned char bin = 32;

        constexpr static signed int min = 0x8000'0000;
        constexpr static signed int max = 0x7FFF'FFFF;
    };

    template <>
    class limit<signed long int>
    {
    public:
        constexpr static unsigned char hex = 8;
        constexpr static unsigned char dec = 11;
        constexpr static unsigned char bin = 32;

        constexpr static signed long int min = 0x8000'0000;
        constexpr static signed long int max = 0x7FFF'FFFF;
    };

    template <>
    class limit<signed long long int>
    {
    public:
        constexpr static unsigned char hex = 16;
        constexpr static unsigned char dec = 20;
        constexpr static unsigned char bin = 64;

        constexpr static signed long long int min = 0x8000'0000'0000'0000;
        constexpr static signed long long int max = 0x7FFF'FFFF'FFFF'FFFF;
    };


    template <>
    class limit<float>
    {
    public:
        constexpr static unsigned char hex = 8;
        constexpr static unsigned char dec = 6;
        constexpr static unsigned char bin = 32;

        constexpr static float min = __builtin_bit_cast( float, 0xFF7F'0000 );
        constexpr static float max = __builtin_bit_cast( float, 0x7F7F'0000 );

        constexpr static float eps = __builtin_bit_cast( float, 0x3F80'0001 ) - __builtin_bit_cast( float, 0x3F80'0000 );
        constexpr static float inf = __builtin_bit_cast( float, 0x7F80'0000 );
        constexpr static float nan = __builtin_bit_cast( float, 0xFFC0'0001 );
    };

    template <>
    class limit<double>
    {
    public:
        constexpr static unsigned char hex = 16;
        constexpr static unsigned char dec = 15;
        constexpr static unsigned char bin = 64;

        constexpr static double min = __builtin_bit_cast( double, 0xFFEF'FFFF'FFFF'FFFF );
        constexpr static double max = __builtin_bit_cast( double, 0x7FEF'FFFF'FFFF'FFFF );

        constexpr static double eps = __builtin_bit_cast( double, 0x3FF0'0000'0000'0001 ) - __builtin_bit_cast( double, 0x3FF0'0000'0000'0000 );
        constexpr static double inf = __builtin_bit_cast( double, 0x7FF0'0000'0000'0000 );
        constexpr static double nan = __builtin_bit_cast( double, 0x7FF8'0000'0000'0001 );
    };


    template <>
    class limit<bool>
    {
    public:
        constexpr static unsigned char hex = 1;
        constexpr static unsigned char dec = 1;
        constexpr static unsigned char bin = 1;

        constexpr static bool min = false;
        constexpr static bool max = true;
    };


    template <>
    class limit<char>
    {
    public:
        constexpr static unsigned char hex = 2;
        constexpr static unsigned char dec = 4;
        constexpr static unsigned char bin = 8;

        constexpr static char min = 0x80;
        constexpr static char max = 0x7F;
    };

    template <>
    class limit<wchar_t>
    {
    public:
        constexpr static unsigned char hex = 4;
        constexpr static unsigned char dec = 5;
        constexpr static unsigned char bin = 16;

        constexpr static wchar_t min = 0x0000;
        constexpr static wchar_t max = 0xFFFF;
    };

    template <>
    class limit<char8_t>
    {
    public:
        constexpr static unsigned char hex = 2;
        constexpr static unsigned char dec = 3;
        constexpr static unsigned char bin = 8;

        constexpr static char8_t min = 0x00;
        constexpr static char8_t max = 0xFF;
    };

    template <>
    class limit<char16_t>
    {
    public:
        constexpr static unsigned char hex = 4;
        constexpr static unsigned char dec = 5;
        constexpr static unsigned char bin = 16;

        constexpr static char16_t min = 0x0000;
        constexpr static char16_t max = 0xFFFF;
    };

    template <>
    class limit<char32_t>
    {
    public:
        constexpr static unsigned char hex = 8;
        constexpr static unsigned char dec = 7;
        constexpr static unsigned char bin = 32;

        constexpr static char32_t min = 0x0000'0000;
        constexpr static char32_t max = 0x0010'FFFF;
    };
}

#endif