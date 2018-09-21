// External/Project libraries
#include <ExternalSharedLibrary.hpp>
#include <ExternalStaticLibrary.hpp>
#include <NativeSharedLibrary.hpp>
#include <NativeStaticLibrary.hpp>
// System headers
#include <jni.h>
// C++ Standard Library headers
#include <sstream>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_roccoormm_nativelibrariesdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    ExternalSharedLibrary externalSharedLibrary;
    std::string hello_ExternalSharedLibrary = "Hello from " + externalSharedLibrary.Name();
    ExternalStaticLibrary externalStaticLibrary;
    std::string hello_ExternalStaticLibrary = "Hello from " + externalStaticLibrary.Name();
    NativeSharedLibrary nativeSharedLibrary;
    std::string hello_NativeSharedLibrary = "Hello from " + nativeSharedLibrary.Name();
    NativeStaticLibrary nativeStaticLibrary;
    std::string hello_NativeStaticLibrary = "Hello from " + nativeStaticLibrary.Name();

    std::stringstream ss;
    ss << hello << "\n";
    ss << hello_ExternalSharedLibrary << "\n";
    ss << hello_ExternalStaticLibrary << "\n";
    ss << hello_NativeSharedLibrary << "\n";
    ss << hello_NativeStaticLibrary << "\n";

    return env->NewStringUTF(ss.str().c_str());
}
