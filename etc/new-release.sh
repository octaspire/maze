#!/usr/bin/env sh

PROJECT_PATH=$1

echo "$PROJECT_PATH"

MAJOR=`grep "set(OCTASPIRE_MAZE_CONFIG_VERSION_MAJOR" "$PROJECT_PATH/CMakeLists.txt" | awk '{ print $2 }' | sed s/\)//`
MINOR=`grep "set(OCTASPIRE_MAZE_CONFIG_VERSION_MINOR" "$PROJECT_PATH/CMakeLists.txt" | awk '{ print $2 }' | sed s/\)//`
PATCH=`grep "set(OCTASPIRE_MAZE_CONFIG_VERSION_PATCH" "$PROJECT_PATH/CMakeLists.txt" | awk '{ print $2 }' | sed s/\)//`

echo    ""
echo    "-------------- New release for Octaspire Maze --------------"
echo    ""
echo    "Current version is $MAJOR.$MINOR.$PATCH"
echo -n "Is this release major, minor or patch? [major/minor/patch]: "

create_new_version() {
    MAJOR=$1
    MINOR=$2
    PATCH=$3
    NEW_MAJOR=$4
    NEW_MINOR=$5
    NEW_PATCH=$6

    echo "New version is $NEW_MAJOR.$NEW_MINOR.$NEW_PATCH\n"

    echo "\nUpdating CMakeLists.txt...\n--------------------------\n"
    sed -i "s/set(OCTASPIRE_MAZE_CONFIG_VERSION_MAJOR $MAJOR)/set(OCTASPIRE_MAZE_CONFIG_VERSION_MAJOR $NEW_MAJOR)/" "$PROJECT_PATH/CMakeLists.txt"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi
    sed -i "s/set(OCTASPIRE_MAZE_CONFIG_VERSION_MINOR $MINOR)/set(OCTASPIRE_MAZE_CONFIG_VERSION_MINOR $NEW_MINOR)/" "$PROJECT_PATH/CMakeLists.txt"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi
    sed -i "s/set(OCTASPIRE_MAZE_CONFIG_VERSION_PATCH $PATCH)/set(OCTASPIRE_MAZE_CONFIG_VERSION_PATCH $NEW_PATCH)/" "$PROJECT_PATH/CMakeLists.txt"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nRunning make...\n--------------------------\n"
    make
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nTesting...\n--------------------------\n"
    make test
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nGenerating amalgamation...\n--------------------------\n"
    "$PROJECT_PATH/etc/amalgamate.sh" "$PROJECT_PATH/etc"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nCompiling amalgamation...\n--------------------------\n"
    gcc -O3 -std=c99 "$PROJECT_PATH/etc/octaspire_maze_amalgamated.c" `pkg-config --cflags --libs sdl2` -lm -o "$PROJECT_PATH/build/octaspire_maze_amalgamated"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nTesting amalgamation...\n--------------------------\n"
    "$PROJECT_PATH/build/octaspire_maze_amalgamated" -h
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nRelease $NEW_MAJOR.$NEW_MINOR.$NEW_PATCH created."
}

read RELTYPE

if [ $RELTYPE = major ]; then
    echo "\nMAJOR RELEASE\n-------------"
    NEW_MAJOR=$((MAJOR + 1))
    NEW_MINOR=0
    NEW_PATCH=0

    create_new_version $MAJOR $MINOR $PATCH $NEW_MAJOR $NEW_MINOR $NEW_PATCH

elif [ $RELTYPE = minor ]; then
    echo "\nMINOR RELEASE\n-----------"
    NEW_MAJOR=$MAJOR
    NEW_MINOR=$((MINOR + 1))
    NEW_PATCH=0

    create_new_version $MAJOR $MINOR $PATCH $NEW_MAJOR $NEW_MINOR $NEW_PATCH

elif [ $RELTYPE = patch ]; then
    echo "\nPATCH RELEASE"
    NEW_MAJOR=$MAJOR
    NEW_MINOR=$MINOR
    NEW_PATCH=$((PATCH + 1))

    create_new_version $MAJOR $MINOR $PATCH $NEW_MAJOR $NEW_MINOR $NEW_PATCH

else
    echo "========================================================="
    echo "= major, minor or patch was expected. Going to quit now ="
    echo "========================================================="
    exit 1
fi
