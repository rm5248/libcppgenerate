#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#else
#include <unistd.h>
#include <string.h>
#endif

#if defined(_WIN32)
struct WinError{
    DWORD last_error;

    WinError( DWORD error ) : last_error( error ) {}

    friend std::wostream& operator<<( std::wostream& os, const WinError& what ){
        LPWSTR error_msg = nullptr;

        size_t size = FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, what.last_error, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
            (LPWSTR)&error_msg, 0, nullptr);

        if ( size == 0 )
            os << L"error code " << what.last_error;
        else{
            os << error_msg;
            LocalFree( error_msg );
        }

        return os;
    }
};
#endif

/* chdir into the path specified in the first argument if there is any specified. */
inline void optional_chdir( int argc, char** argv ){
#if defined(_WIN32)
    _setmode(_fileno(stderr), _O_U16TEXT);

    int win_argc;
    LPWSTR* win_argv = CommandLineToArgvW( GetCommandLineW(), &win_argc );

    if ( win_argv == nullptr ){
        std::wcerr << L"Couldn't retrieve commandline arguments: "
            << WinError( GetLastError() ) << L'\n';
        std::exit( 1 );
    }

    if ( win_argc > 2 ){
        std::wcerr << L"Superfluous command-line arguments specified!\n";
        std::exit( 1 );
    }

    if ( win_argc == 2 ){
        if (!SetCurrentDirectoryW(win_argv[1])){
            std::wcerr << L"Couldn't chdir into '" << win_argv[1]
                << L"': " << WinError( GetLastError() ) << L'\n';
            std::exit( 1 );
        }
    }

    if ( LocalFree(win_argv) != nullptr ){
        std::wcerr << L"Couldn't free argument list: "
            << WinError( GetLastError() ) << L'\n';
        std::exit( 1 );
    }
#else
    if ( argc > 2 ){
        std::cerr << "Superfluous command-line arguments specified!\n";
        std::exit( 1 );
    }

    if ( argc == 2 ){
        if ( chdir( argv[1] ) < 0 ){
            std::cerr << "Couldn't chdir into '" << argv[1] << "': "
                << strerror( errno ) << '\n';
            std::exit( 1 );
        }
    }
#endif
}
