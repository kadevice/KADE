set working_dir=%CD%

cd %working_dir%\mamex4
make clean
make

cd %working_dir%\usbhidx2
make clean
make

cd %working_dir%\usbhidx4
make clean
make

cd %working_dir%