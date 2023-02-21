#ifndef PIE_TRAIT_HH
#define PIE_TRAIT_HH

namespace pie::inl
{
    template <unsigned long long int index, typename head, typename... tail>
    struct choose
    {
        using out = typename choose<index - 1, tail...>::out;
    };

    template <typename head, typename... tail>
    struct choose<0, head, tail...>
    {
        using out = head;
    };

    template <typename type> struct remref                      { using out = type; };
    template <typename type> struct remref<type &>              { using out = type; };
    template <typename type> struct remref<type &&>             { using out = type; };

    template <typename type> struct remptr                      { using out = type; };
    template <typename type> struct remptr<type *>              { using out = type; };

    template <typename type> struct remcon                      { using out = type; };
    template <typename type> struct remcon<const type>          { using out = type; };

    template <typename type> struct remvol                      { using out = type; };
    template <typename type> struct remvol<volatile type>       { using out = type; };

    template <typename type> struct remcov                      { using out = type; };
    template <typename type> struct remcov<const type>          { using out = type; };
    template <typename type> struct remcov<volatile type>       { using out = type; };
    template <typename type> struct remcov<const volatile type> { using out = type; };

    template <typename type> auto declval( int ) -> typename remref<type>::out &&;
    template <typename type> auto declval( ... ) -> type;
}


#define declare( type ) pie::inl::declval<type>( 0 )

namespace pie
{
    template <unsigned long long int...>
    struct indicies;

    template <unsigned long long int... tail, unsigned long long int head>
    struct indicies<head, tail...>
    {
        using out = typename indicies<head - 1, head - 1, tail...>::out;
    };

    template <unsigned long long int... tail>
    struct indicies<0, tail...>
    {
        using out = indicies<tail...>;
    };


    template <unsigned long long int bound>
    using sequence = typename indicies<bound>::out;

    template <unsigned long long int index, typename... list>
    using choose   = typename inl::choose<index, list...>::out;


    template <typename type>
    using remref = typename inl::remref<type>::out;

    template <typename type>
    using remptr = typename inl::remptr<type>::out;

    template <typename type>
    using remcon = typename inl::remcon<type>::out;

    template <typename type>
    using remvol = typename inl::remvol<type>::out;

    template <typename type>
    using remcov = typename inl::remcov<type>::out;
}

namespace pie::inl
{
    template <typename, typename>
    constexpr inline bool same = false;

    template <typename type>
    constexpr inline bool same<type, type> = true;


    template <typename>
    constexpr inline bool function = false;

    template <typename ret, typename... arg>
    constexpr inline bool function<ret( arg... )> = true;

    template <typename ret, typename... arg>
    constexpr inline bool function<ret( * )( arg... )> = true;

    template <typename ret, typename... arg>
    constexpr inline bool function<ret( & )( arg... )> = true;
}

namespace pie
{
    template <typename type, typename... list>
    concept same = ( inl::same<type, list> or ... );

    template <typename type>
    concept reference = same<type, remref<type> &, remref<type> &&>;

    template <typename type>
    concept pointer   = same<type, remptr<type> *>;

    template <typename type>
    concept constant  = same<type, const remcon<type>>;

    template <typename type>
    concept unstable  = same<type, volatile remvol<type>>;

    template <typename type>
    concept function  = inl::function<type>;


    template <typename type>
    concept boolean  = same<remcov<type>, bool>;

    template <typename type>
    concept nothing  = same<remcov<type>, void>;

    template <typename type>
    concept floating = same<remcov<type>, float, double>;

    template <typename type>
    concept uintable = same<remcov<type>, unsigned char, unsigned short int, unsigned int, unsigned long int, unsigned long long int, bool, wchar_t, char8_t, char16_t, char32_t>;

    template <typename type>
    concept sintable = same<remcov<type>, signed char, signed short int, signed int, signed long int, signed long long int, char>;

    template <typename type>
    concept integral = uintable<type> or sintable<type>;

    template <typename type>
    concept symbolic = same<remcov<type>, char, wchar_t, char8_t, char16_t, char32_t>;

    template <typename type>
    concept internal = floating<type> or integral<type> or nothing<type>;
}

#endif