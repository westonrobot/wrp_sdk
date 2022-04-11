## Build the sample code

### Install dependencies

```
$ sudo apt-get install -y software-properties-common
$ sudo add-apt-repository ppa:lely/ppa && sudo apt-get update
$ sudo apt-get install -y pkg-config liblely-coapp-dev liblely-co-tools
```

If you don't install the above dependencies (which are required by the peripheral drivers), only the robot base samples will be built.

### Build the sample code 

```
$ mkdir build && cd build
$ cmake ..
$ make -j8
```

You will get executable "sample_xxx" inside the build/bin folder.