#!/usr/bin/env sh

YELLOW="$(tput setaf 3 ; tput bold)"
GREEN="$(tput setaf 2 ; tput bold)"
NOCOLOR="$(tput setaf 9 ; tput sgr0)"

CC=gcc
COVERAGE=""

echoToDefs() { printf "$NOCOLOR\n" ; }

if [ "$#" -ge "1" ]; then CC=$1; fi
if [ "$2" = "--coverage" ]; then COVERAGE=$2; fi

printf "$YELLOW\n"
cat << EnDoFmEsSaGe
1. Building the game
   PLEASE NOTE: This game requires development version of 'SDL2' library
   (i.e. headers) to be installed on the system; otherwise compilation
   will fail. To install development version of library 'SDL2' manually:

       - NetBSD: curl -O http://www.libsdl.org/release/SDL2-2.0.5.tar.gz
                 tar zxf SDL2-2.0.5.tar.gz
                 cd SDL2-2.0.5
                 ./configure --disable-joystick       \\
                             --disable-audio          \\
                             --disable-x11-shared     \\
                             --enable-directfb-shared
                 gmake
                 sudo gmake install

    (If you have installed SDL2 with 'sudo pkgin install SDL2' you might
    have to remove it first by running 'sudo pkgin remove SDL2' and then
    install SDL2 manually. This is the way I was able to get SDL2 to work
    in NetBSD at the moment.)
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
printf "%b1)%b ./octaspire-maze -s --disable-joystick\n" $YELLOW $GREEN
echo "=================================================================="
echoToDefs

