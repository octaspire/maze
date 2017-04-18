[![Build Status](https://travis-ci.org/octaspire/maze.svg?branch=master)](https://travis-ci.org/octaspire/maze)

Game written in programming languages Dern and standard C99

To build on Raspberry Pi or Debian:

```shell
sudo apt-get install cmake git libsdl2-dev libsdl2-image-dev
git clone https://github.com/octaspire/maze.git
cd maze/build
cmake ..
make
```

To build on Ubuntu (16.04 LTS)

```shell
sudo add-apt-repository universe
sudo apt-get update
sudo apt-get install cmake git libsdl2-dev libsdl2-image-dev
git clone https://github.com/octaspire/maze.git
cd maze/build
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
If you want to know more about Octaspire Dern, the language manual can be found from here:
[http://www.octaspire.com/dern](http://www.octaspire.com/dern)

