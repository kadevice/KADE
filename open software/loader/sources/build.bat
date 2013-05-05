echo *** Build script for KADE Loader 
echo ***
echo *** Define local paths to your Python and NSIS programs ***
set python_path="c:\python26\python"
set nsis_path="c:\program files\nsis\makensis"

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