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
   will fail. You might need also to install a C compiler. To install
   development version of library 'SDL2' and gcc 3:

       - OpenIndiana: sudo pkg install sdl2 developer/gcc-3
-------------------------------------------------------------------------------
EnDoFmEsSaGe
echoToDefs
read -r BUILDSTR <<'EOF'
/usr/gcc/3.4/bin/gcc -O2 -std=c99 -Wall -Wextra -DOCTASPIRE_MAZE_AMALGAMATED_IMPLEMENTATION octaspire-maze-amalgamated.c -o octaspire-maze `sdl2-config --cflags --libs` -lm
EOF
echo $BUILDSTR
eval $BUILDSTR



printf "\nDone.\n$GREEN"
echo   "=================================================================="
echo   "Run the game like this:"
echo   "=================================================================="
printf "%b1)%b ./octaspire-maze --disable-joystick\n" $YELLOW $GREEN
echo "=================================================================="
echoToDefs

