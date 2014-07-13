rm -rf android-build
mkdir android-build
cd android-build
qmake CONFIG+="release" ..
mingw32-make
mingw32-make INSTALL_ROOT=build install
androiddeployqt.exe --input android-libqfootballstat.so-deployment-settings.json --output build --ant D:/eclipse/plugins/org.apache.ant_1.8.4.v201303080030/bin/ant.bat --jdk "C:/Program Files/Java/jdk1.7.0_51"
cd ..
