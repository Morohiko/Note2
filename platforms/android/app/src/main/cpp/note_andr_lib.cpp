#include <jni.h>
#include <string>

#include "note.h"

Note note;

std::string jstringToStdString(JNIEnv* env, jstring jStr) {
    if (!jStr)
        return "";
    const char* chars = env->GetStringUTFChars(jStr, nullptr);
    std::string result(chars);
    env->ReleaseStringUTFChars(jStr, chars);
    return result;
}

std::wstring jstringToStdWString(JNIEnv* env, jstring jStr) {
    if (!jStr)
        return L"";

    // Get the length of the jstring.
    jsize length = env->GetStringLength(jStr);
    
    // Get the UTF-16 encoded characters (jchar is 16-bit).
    const jchar* rawChars = env->GetStringChars(jStr, nullptr);
    
    // Create a std::wstring from the jchar array.
    std::wstring result;
    result.resize(length);
    for (jsize i = 0; i < length; ++i) {
        result[i] = static_cast<wchar_t>(rawChars[i]);
    }
    
    // Release the raw characters.
    env->ReleaseStringChars(jStr, rawChars);
    
    return result;
}

bool jbooleanToBool(jboolean value) {
    return (value == JNI_TRUE);
}

/*
 * Class:     com_example_note2_MainActivity
 * Method:    _setFilename
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL
Java_com_example_note2_MainActivity__1setFilename(JNIEnv* env, jobject, jstring filename) {
    std::string name = jstringToStdString(env, filename);
    if (name.empty()) {
        return static_cast<jint>(-1);
    }
    return static_cast<jint>(note.setFilename(name));
}

/*
 * Class:     com_example_note2_MainActivity
 * Method:    _performReadAllDates
 * Signature: (Ljava/lang/String;Ljava/util/List;)I
 */
JNIEXPORT jint JNICALL
Java_com_example_note2_MainActivity__1performReadAllDates(JNIEnv* env, jobject, jstring key, jobject dateList) {
    return 0;
}

/*
 * Class:     com_example_note2_MainActivity
 * Method:    _performReadByDate
 * Signature: (Ljava/util/Date;Ljava/lang/String;Ljava/lang/StringBuilder;)I
 */
JNIEXPORT jint JNICALL
Java_com_example_note2_MainActivity__1performReadByDate(JNIEnv* env, jobject, jobject datetime, jstring key, jobject output) {
    return 0;
}

/*
 * Class:     com_example_note2_MainActivity
 * Method:    _performWriteToFile
 * Signature: (Ljava/lang/String;ZLjava/util/Date;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL
Java_com_example_note2_MainActivity__1performWriteToFile(JNIEnv* env, jobject, jstring text, jboolean isCustomTime, jobject datetime, jstring key) {
    return 0;
}
