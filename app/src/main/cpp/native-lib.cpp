#include <jni.h>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <android/log.h>

extern "C" JNIEXPORT jstring

#define LOG_TAG "NDK_ROOT_CHECK"
#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

JNICALL
Java_com_example_ndkdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


bool fileExistsAndExecutable(const char* path) {
    struct stat fileStat;
    if (stat(path, &fileStat) == 0) {
        if (fileStat.st_mode & S_IXUSR) { // Check if the file is executable
            LOG_INFO("File found and executable: %s", path);
            return true;
        } else {
            LOG_INFO("File found but not executable: %s", path);
        }
    } else {
        LOG_INFO("File not found: %s", path);
    }
    return false;
}

// Check for known root paths
bool checkForRootPaths() {
    const char* paths[] = {
            "/system/app/Superuser.apk",
            "/system/xbin/",
            "sbin/",
            "system/xbin/",
            "data/local/xbin/",
            "system/sd/xbin/",
            "su/bin/",
            "xbin/"
    };

    LOG_INFO("Checking for known root paths...");
    for (const char* path : paths) {
        if (fileExistsAndExecutable(path)) {
            return true; // Root path detected
        }
    }
    LOG_INFO("No root paths detected.");
    return false;
}

// Function to check if the `su` command can run
bool checkForSuCommand() {
    LOG_INFO("Checking `su` command...");
    int exitCode = std::system("su -c 'id' > /data/local/tmp/su_test_log 2>&1");

    // Log the output of the command
    std::ifstream logFile("/data/local/tmp/su_test_log");
    if (logFile.is_open()) {
        std::string line;
        while (std::getline(logFile, line)) {
            LOG_INFO("`su` command output: %s", line.c_str());
        }
        logFile.close();
    } else {
        LOG_INFO("Failed to read `su` test log.");
    }

    return (exitCode == 0); // Root access if exit code is 0
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_ndkdemo_MainActivity_isDeviceRooted(JNIEnv *env, jobject /* this */) {
    LOG_INFO("Starting root detection...");

    // Root detection checks
    bool hasRootPaths = checkForRootPaths();
    bool hasSuCommand = checkForSuCommand();

    // Final result
    bool isRooted = hasRootPaths || hasSuCommand;

    LOG_INFO("Device rooted: %s", isRooted ? "true" : "false");
    return isRooted ? JNI_TRUE : JNI_FALSE;
}
