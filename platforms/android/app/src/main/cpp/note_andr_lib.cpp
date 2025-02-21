#include <jni.h>
#include <string>

// Example function from your "C++ library" (here simulated inline)
std::string getGreeting() {
    return "Hello from C++!";
}

// Implementation of the native method called from Java.
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_note2_MainActivity_stringFromJNI(JNIEnv* env, jobject /* this */) {
    // Call the example C++ function.
    std::string greeting = getGreeting();

    // Optionally add some additional text.
    std::string fullGreeting = "Native library says: " + greeting;

    // Return the result as a jstring.
    return env->NewStringUTF(fullGreeting.c_str());
}
