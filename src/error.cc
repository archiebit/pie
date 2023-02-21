#include <pie\error.hh>

#include <windows.h>

namespace pie::error
{
    dual warning( const char16 * message ) noexcept
    {
        if( not message ) message = u"Без описания";
        
        return MessageBoxW( nullptr, LPCWSTR( message ), L"Внимание!", MB_ICONWARNING | MB_OKCANCEL | MB_SETFOREGROUND ) == IDOK;
    }

    none closing( const char16 * message ) noexcept
    {
        if( not message ) message = u"Критическая ошибка!";

        MessageBoxW( NULL, LPCWSTR( message ), L"Ошибка!", MB_ICONERROR | MB_SETFOREGROUND | MB_OK );
        ExitProcess( 1 );
    }
}