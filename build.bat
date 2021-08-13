echo off

cd %~dp0\src
echo compiling HttpServer lib
echo.
qmake
mingw32-make release
cd ..
echo.
echo.

cd test
echo compiling test app
echo.
qmake
mingw32-make release
cd release
windeployqt httpServerTest.exe
copy /Y ..\..\src\release\httpServer.dll .
cd ../..
echo.
echo.

cd mytest
echo compiling mytest app
echo.
qmake
mingw32-make release
cd release
windeployqt MyTest.exe
copy /Y ..\..\src\release\httpServer.dll .
cd ../..
echo.
echo.

echo compilation done
pause
