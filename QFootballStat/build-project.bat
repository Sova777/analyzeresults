set PATH=D:/Qt/4.8.0-vs2008/bin;%PATH%
rm -rf vsbuild
mkdir vsbuild
cd vsbuild
qmake CONFIG+="release" ..
nmake
