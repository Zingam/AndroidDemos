#ifndef NATIVELIBRARIES_NATIVESHAREDLIBRARY_H
#define NATIVELIBRARIES_NATIVESHAREDLIBRARY_H

#include <string>

class NativeSharedLibrary {
public:
    auto Name() const -> std::string;
};

#endif //NATIVELIBRARIES_NATIVESHAREDLIBRARY_H
