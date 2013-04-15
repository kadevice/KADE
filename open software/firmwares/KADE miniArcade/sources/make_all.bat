set working_dir=%CD%

cd %working_dir%\kade-gen
make clean
make

cd %working_dir%\kade-key-custom
make clean
make

cd %working_dir%\kade-led-demo
make clean
make

cd %working_dir%\kade-mame
make clean
make

cd %working_dir%\kade-mame-custom
make clean
make

cd %working_dir%\kade-pin-custom
make clean
make

cd %working_dir%\kade-program
make clean
make

cd %working_dir%\kade-ps3-custom
make clean
make

cd %working_dir%\kade-psx-custom
make clean
make

cd %working_dir%\kade-psx-minimus
make clean
make

cd %working_dir%\kade-xbox-custom
make clean
make

cd %working_dir%\kade-rotary-custom
make clean
make

cd %working_dir%\kade-icade
make clean
make

cd %working_dir%\tests\minimus
make clean
make

cd %working_dir%