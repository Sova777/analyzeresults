rem set PATH=D:/Qt/Qt5.0.0-vs2010/5.0.0/msvc2010/bin;%PATH%
set PATH=D:/Qt/4.8.0-vs2008/bin;%PATH%
rm -rf vsbuild
mkdir vsbuild
cd vsbuild
qmake CONFIG+="release" ..
nmake
