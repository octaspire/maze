Game written in programming languages Dern and standard C99

To build on Raspberry Pi:

```shell
sudo apt-get install cmake git libsdl2-dev libsdl2-image-dev
git clone https://gitlab.com/octaspire/maze.git
cd maze
mkdir build
cd build
cmake ..
make
```

To run the unit tests:

```shell
test/octaspire-maze-test-runner
```

To start the game:

```shell
./octaspire-maze
```
