# daagudumoothalu

## English Version
<details>
<summary>Click to expand</summary>

## Hide-and-seek in the kingdom of Mahishmathi

</details>

## Telugu Version
<details>
<summary>హుదా కా కసం, హసం కా హుకుం, ఖోలో సేసే</summary>

## మాహిష్మతి సామ్రాజ్యంలో దాగుడుమూతలు

దాగుడుమూతలు ఒక ప్రాచీన ఆటలు. ఇది ప్రాచీన భారత దేశంలో ప్రచలితమైన ఆటలలో ఒకటి.

</details>

## OS

- [x] Ubuntu - 22.04
- [ ] MacOS -
- [ ] Windows -

## Setup

0. TODO

1. Create a workspace directory and change to it.
  
    ```bash
    mkdir -p ~/me_ws/

    cd ~/me_ws/
    ```

2. Clone the repository.
  
    ```bash
    git clone https://github.com/mahishmathi-empire/daagudumoothalu.git
    ```

3. Switch from main branch to setup.
  
    ```bash
    git checkout setup
    ```

4. Build the package.
  
    ```bash
    ./daagudumoothalu/build.sh -p daagudumoothalu -c -i -- -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=OFF
    ```

    - `-p` specifies the package name.
    - `-c` cleans the build directory.
    - `-i` installs the package.
    - `--` passes the arguments to `cmake`.
    -  `-DCMAKE_BUILD_TYPE=Debug` specifies the build type.
    -  `-DENABLE_TESTS=ON` enables the tests.

5. Build the tests.
  
    ```bash
    ./daagudumoothalu/build.sh -p daagudumoothalu -c -i -- -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=ON
    ```

## Test

1. Create install/bin/ directories and change to bin.
  
    ```bash
    mkdir -p ~/me_ws/install/bin/

    cd ~/me_ws/install/bin/
    ```

2. Run the executable.
  
    ```bash
    ./test
    ```

## TODO

- [ ] Create a struct to hold Vulkan objects.
