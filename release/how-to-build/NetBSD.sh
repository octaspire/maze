#!/usr/bin/env sh

YELLOW="$(tput setaf 3 ; tput bold)"
GREEN="$(tput setaf 2 ; tput bold)"
NOCOLOR="$(tput setaf 9 ; tput sgr0)"

echoToDefs() { printf "$NOCOLOR\n" ; }

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
-------------------------------------------------------------------------------
EnDoFmEsSaGe
echoToDefs
read -r BUILDSTR <<'EOF'
gcc -O2 -std=c99 -Wall -Wextra -DOCTASPIRE_MAZE_AMALGAMATED_IMPLEMENTATION octaspire-maze-amalgamated.c -o octaspire-maze `sdl2-config --cflags --libs` -lm
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

