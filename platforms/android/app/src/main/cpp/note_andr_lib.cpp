#include <jni.h>
#include <string>

// Implementation of the native method called from Java.
extern "C" {
/*
 * Class:     com_example_note2_MainActivity
 * Method:    _setFilename
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL
Java_com_example_note2_MainActivity__1setFilename(JNIEnv* env, jobject, jstring filename) {
    return 0;
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

} // extern "C"