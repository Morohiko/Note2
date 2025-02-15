# Note

## build for Linux
mkdir build
cd build
cmake ..
make

## build for andoird
sudo apt update
sudo apt install openjdk-17-jdk

mkdir build
cd build
cmake .. -DPLATFORM=android
ANDROID_HOME=/home/user/android/sdk JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64 make

## tests
ctest
