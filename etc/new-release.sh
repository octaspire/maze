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
    sed -i "s/Documentation for Octaspire Maze puzzle game version $MAJOR.$MINOR.$PATCH/Documentation for Octaspire Maze puzzle game version $NEW_MAJOR.$NEW_MINOR.$NEW_PATCH/" "$PROJECT_PATH/doc/book/Octaspire_Maze_Manual.adoc"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nRunning make...\n--------------------------\n"
    make
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nTesting...\n--------------------------\n"
    make test
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nBuilding book...\n--------------------------\n"
    make book-maze
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











    echo "\nRemoving old release directory, archive and signature...\n--------------------------\n"
    rm -rf "$PROJECT_PATH/etc/release.tar.bz2"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi
    rm -rf "$PROJECT_PATH/etc/release.tar.bz2.sig"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi
    rm -rf "$PROJECT_PATH/etc/release"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nCreating a directories for the source release...\n--------------------------\n"
    mkdir -p "$PROJECT_PATH/etc/release/version-$NEW_MAJOR.$NEW_MINOR.$NEW_PATCH"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi
    mkdir -p "$PROJECT_PATH/etc/release/version-$NEW_MAJOR.$NEW_MINOR.$NEW_PATCH/documentation"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nCreate a README file...\n--------------------------\n"
    echo \
"This is amalgamated single file source release for Octaspire Maze puzzle game\n\
version $NEW_MAJOR.$NEW_MINOR.$NEW_PATCH. File 'octaspire-maze-amalgamated.c'\n\
is all that is needed; it has no other dependencies than a C compiler and\n\
standard library supporting C99 and SDL2 library.\n\
\n\
SHA-512 checksums for this and older releases can be found from:\n\
https://octaspire.github.io/maze/\n\
If you want to check this release, download checksums for version $NEW_MAJOR.$NEW_MINOR.$NEW_PATCH from:\n\
https://octaspire.github.io/maze/checksums-$NEW_MAJOR.$NEW_MINOR.$NEW_PATCH\n\
\n\
Building instructions for all supported platforms (and scripts for building\n\
automatically) can be found in directory 'how-to-build'. Look for a file that\n\
has your platform's name in the file's name. If instructions for your\n\
platform are not yet added, looking instructions for a similar system will\n\
probably help. The amalgamation contains only one source file and should be\n\
straightforward to use. By using few compiler defines, the single file can\n\
be used for different purposes:\n\
\n\
\t(1) to build stand-alone unit test runner for the file.\n\
\t(2) to build the game.\n\
\n\
Octaspire Maze is work in progress. The most recent version\n\
of this amalgamated source release can be downloaded from:\n\
\n\
\t* https://octaspire.io/maze/release.tar.bz2\n\
\t* octaspire.com/maze/release.tar.bz2\n\
\t* https://octaspire.github.io/maze/release.tar.bz2\n\
\n\
Directory 'documentation' contains the manual 'Octaspire Maze Manual'.\n\
\n\
More information about Maze can be found from the homepage:\n\
octaspire.com/maze and https://octaspire.io/maze\n" > "$PROJECT_PATH/etc/release/version-$NEW_MAJOR.$NEW_MINOR.$NEW_PATCH/README"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nCopying amalgamation...\n--------------------------\n"
    cp "$PROJECT_PATH/etc/octaspire_maze_amalgamated.c" "$PROJECT_PATH/etc/release/version-$NEW_MAJOR.$NEW_MINOR.$NEW_PATCH/octaspire-maze-amalgamated.c"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nCopying LICENSE file...\n--------------------------\n"
    cp "$PROJECT_PATH/LICENSE" "$PROJECT_PATH/etc/release/version-$NEW_MAJOR.$NEW_MINOR.$NEW_PATCH/LICENSE"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nCopying book to the release directory...\n--------------------------\n"
    cp "$PROJECT_PATH/doc/book/Octaspire_Maze_Manual.html" "$PROJECT_PATH/etc/release/version-$NEW_MAJOR.$NEW_MINOR.$NEW_PATCH/documentation/"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi
    cp "$PROJECT_PATH/doc/book/Octaspire_Maze_Manual.pdf" "$PROJECT_PATH/etc/release/version-$NEW_MAJOR.$NEW_MINOR.$NEW_PATCH/documentation/"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nCopying build scripts to the release directory...\n--------------------------\n"
    cp -r "$PROJECT_PATH/etc/how-to-build/" "$PROJECT_PATH/etc/release/version-$NEW_MAJOR.$NEW_MINOR.$NEW_PATCH/"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nCompressing release directory into tar.bz2...\n--------------------------\n"
    cd "$PROJECT_PATH/etc/"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi
    tar --bzip2 -cf "release.tar.bz2" release
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nSigning release.tar.bz2...\n--------------------------\n"
    gpg -u 9bd2ccd560e9e29c --output "release.tar.bz2.sig" --detach-sig release.tar.bz2
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi

    echo "\nRemoving $PROJECT_PATH/release/ and creating it again with updates\n--------------------------\n"
    rm -rf "$PROJECT_PATH/release"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi
    cp -r "$PROJECT_PATH/etc/release/version-$NEW_MAJOR.$NEW_MINOR.$NEW_PATCH" "$PROJECT_PATH"
    RETVAL=$?; if [ $RETVAL != 0 ]; then exit $RETVAL; fi
    mv "$PROJECT_PATH/version-$NEW_MAJOR.$NEW_MINOR.$NEW_PATCH" "$PROJECT_PATH/release"
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
