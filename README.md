# **NDK Demo - Device Root Checker**

This is a simple Android application developed using Kotlin and Jetpack Compose to check if the device is rooted or not. The app uses native C/C++ code via the Android NDK (Native Development Kit) to perform the root check.

## **Features**

**Root Check:** The app checks if the device is rooted using a native method from a C/C++ library.

## **Requirements**

**Android Studio (with the necessary SDKs)**
**Android NDK:** To use native methods in Kotlin.
**Kotlin:** The primary language for Android development.
**Jetpack Compose:** For building UI with Kotlin.

## **Setup**

Follow these steps to set up the project:

1. **Clone the repository:**
- git clone https://github.com/yourusername/ndkdemo.git

2. **Open the project in Android Studio:** 
- Open Android Studio and navigate to File -> Open and select the project folder.

3. **Configure the NDK:** 
- The project uses native code for root checking. Ensure the NDK is set up properly. You can configure it in Android Studio:
- Go to File -> Project Structure -> SDK Location.
- Make sure the "Android NDK location" is set to the correct path.

4. **Build the project:** 
- You can build the project using the "Build" option in Android Studio.

5. **Run the app:** 
- Select an emulator or connect a physical device and run the app.



