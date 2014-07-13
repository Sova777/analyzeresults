rm -rf android-build
mkdir android-build
cd android-build
qmake CONFIG+="release" ANDROID_PACKAGE_SOURCE_DIR+="../android" ..
mingw32-make
mingw32-make INSTALL_ROOT=build install
androiddeployqt.exe --input android-libeuler.so-deployment-settings.json --output build --ant D:/eclipse/plugins/org.apache.ant_1.8.4.v201303080030/bin/ant.bat --jdk "C:/Program Files/Java/jdk1.7.0_45"
cd ..
