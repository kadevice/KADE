echo *** Build script for KADE Loader 
echo ***

echo *** Define local paths to your Python, NSIS ***
set python_path="c:\python26\python"
set nsis_path="c:\program files\nsis\makensis"

echo *** OPTIONAL Code signing of executables - you will need to obtain your own code signing certificate ***
echo *** Password for certificate is held in sign_pass variable which is set in the unprovided password.cmd file ***
set sign_path="C:\Program Files\Microsoft SDKs\Windows\v7.0A\bin\signtool"
call password.cmd

echo *** Make version information available to install scripts ***
echo !define PRODUCTVERSION > nsis.tmp \
type version.txt >> nsis.tmp

echo *** Building executables - output to dist folder ***
%python_path% build.py py2exe

echo *** Include the keyboard testing utility (you can grab latest build from utilities folder) ***
copy keytest.exe dist
copy saystatic.exe dist

echo *** Packaging files into installers ***
%nsis_path% setup.nsi
%nsis_path% update.nsi

echo *** OPTIONAL: Code Signing Installer Executable
%sign_path% sign /f certs\certificate.pfx /p %sign_pass% /t http://timestamp.comodoca.com/authenticode setup.exe
%sign_path% sign /f certs\certificate.pfx /p %sign_pass% /t http://timestamp.comodoca.com/authenticode update.exe

echo *** OPTIONAL: Make ZIP files
set zip_path="C:\Program Files\7-Zip\7z"
%zip_path% a -tzip setup.zip setup.exe
%zip_path% a -tzip update.zip update.exe
