#!/usr/bin/env sh

YELLOW="$(tput setaf 3 ; tput bold)"
GREEN="$(tput setaf 2 ; tput bold)"
NOCOLOR="$(tput setaf 9 ; tput sgr0)"

CC=clang
COVERAGE=""

echoToDefs() { printf "$NOCOLOR\n" ; }

if [ "$#" -ge "1" ]; then CC=$1; fi
if [ "$2" = "--coverage" ]; then COVERAGE=$2; fi

printf "$YELLOW\n"
cat << EnDoFmEsSaGe
1. Building the game
   PLEASE NOTE: This game requires development version of 'SDL2' library
   (i.e. headers) to be installed on the system; otherwise compilation
   will fail. To install development version of library 'SDL2':

       - MINIX 3 (by building it manually from source):

         curl -O http://www.libsdl.org/release/SDL2-2.0.5.tar.gz
         tar zxf SDL2-2.0.5.tar.gz
         cd SDL2-2.0.5
         ./configure --disable-audio --disable-joystick --disable-cpuinfo
         gmake
         gmake install
-------------------------------------------------------------------------------
EnDoFmEsSaGe
echoToDefs
read -r BUILDSTR <<EOF
$CC -O2 -std=c99 -Wall -Wextra -DOCTASPIRE_MAZE_AMALGAMATED_IMPLEMENTATION \
    $COVERAGE                                                              \
    octaspire-maze-amalgamated.c -o octaspire-maze                         \
    \`sdl2-config --cflags --libs\` -lm
EOF
echo $BUILDSTR
eval $BUILDSTR



printf "\nDone.\n$GREEN"
echo   "=================================================================="
echo   "Run the game like this:"
echo   "=================================================================="
printf "%b1)%b ./octaspire-maze --disable-joystick --software-renderer\n" $YELLOW $GREEN
echo   "=================================================================="
echoToDefs

