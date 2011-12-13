set PATH=D:/Qt/4.7.4/bin;%PATH%
rm -rf vsbuild
mkdir vsbuild
cd vsbuild
cmake -G "Visual Studio 9 2008" ..
devenv /Build "Release|Win32" QFootballStat.sln
