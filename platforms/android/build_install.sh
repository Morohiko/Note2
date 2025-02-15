#!/bin/bash
# build_and_install.sh
#
# This script builds the debug APK using Gradle and installs it on a connected Android device.
# Make sure you have JAVA_HOME set to Java 17 and adb in your PATH.
#
# Usage: ./build_and_install.sh

# Exit if any command fails
set -e

# Check if JAVA_HOME is set
if [ -z "$JAVA_HOME" ]; then
  echo "JAVA_HOME is not set. Please set JAVA_HOME to your Java 17 installation."
  exit 1
fi

# Build the debug APK
echo "Building the debug APK..."
./gradlew app:assembleDebug

# Locate the generated APK file
APK_PATH=$(find app/build/outputs/apk/debug -name "*-debug.apk" | head -n 1)

if [ -z "$APK_PATH" ]; then
  echo "APK not found in app/build/outputs/apk/debug. Exiting."
  exit 1
fi

echo "APK built at: $APK_PATH"

# Check if a device is connected
DEVICE_COUNT=$(adb devices | sed -n '2,$p' | grep -c "device")
if [ "$DEVICE_COUNT" -eq "0" ]; then
  echo "No connected Android device found. Please connect a device with USB debugging enabled."
  exit 1
fi

# Install the APK on the connected device
echo "Installing APK on the connected device..."
adb install -r "$APK_PATH"

if [ $? -eq 0 ]; then
  echo "APK installed successfully!"
else
  echo "APK installation failed."
  exit 1
fi

# Optional: Launch the app on the device
# Replace 'com.example.myapp' with your application's package name.
# echo "Launching the app..."
# adb shell monkey -p com.example.myapp -c android.intent.category.LAUNCHER 1

echo "Done."

