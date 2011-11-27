set PATH=D:/Qt/4.6.0/bin;%PATH%
cd build
cmake -G "Visual Studio 9 2008" ..
devenv /Build "Release|Win32" QFootballStat.sln
