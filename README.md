# Beam-Pursuit
Placeholder repository for CENG415's project. </br>
https://github.com/He-Is-HaZaRdOuS/rt-cpp

# About
Ongoing naive implementation of Whitted Ray Tracing. </br>
Scenes are loaded from json files and rendered using a single method call. </br>
Everything's done on the CPU currently, plan to offload it onto the GPU later...

# Disclaimer!
CMake does not recognize non-english characters in the build path. </br>
If your computer's file structure contains any non-english characters then you won't be able to compile the program. </br>
Please place the project folder somewhere such that the absolute path to it won't contain any non-english characters. </br>

## Installing CMake (3.28.1)
### (Windows && MacOS) </br>
Download the respective binaries from the following link and install them. </br>
https://cmake.org/download/ </br>
</br>
### (Linux) </br>
Open a terminal window and execute the following commands line by line </br>

```bash
 version=3.28
 build=1
 limit=3.20
 result=$(echo "$version >= $limit" | bc -l)
 os=$([ "$result" == 1 ] && echo "linux" || echo "Linux")
 mkdir ~/temp
 cd ~/temp
 wget https://cmake.org/files/v$version/cmake-$version.$build-$os-x86_64.sh
 sudo mkdir /opt/cmake
 sudo sh cmake-$version.$build-$os-x86_64.sh --prefix=/opt/cmake #(Type "y" to accept the license agreement and type "n" to forego installing inside the subdirectory)
 cmake --version #(expected output is "cmake version 3.28.1") 
```
</br>

## Installing MinGW (gcc for Windows)
* Download and install the gcc compiler for Windows from the following link. </br>
* https://nuwen.net/files/mingw/mingw-18.0-without-git.exe </br>
* Extract to somewhere temporary and then move it inside the "C:\Program Files" directory. </br>
* Then update the System Environment Path Variables to point to the /bin directory of MinGW </br>
* to verify the compiler is detected, open a powershell window and type
```bash
gcc --version
```

## Compilation
### (Linux  && MacOS)
open a terminal window and cd into the project folder </br>

#### (Release)
```bash
 mkdir build-release
 cd build-release
 cmake -DCMAKE_BUILD_TYPE=Release ..
 cmake --build .
```

#### (Debug)
```bash
 mkdir build-debug
 cd build-debug
 cmake -DCMAKE_BUILD_TYPE=Debug ..
 cmake --build .
```

#### (Release With Debug Info)
```bash
 mkdir build-relwithdebinfo
 cd build-relwithdebinfo
 cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
 cmake --build .
```

#### (Release With Minimum Size)
```bash
 mkdir build-minsizerel
 cd build-minsizerel
 cmake -DCMAKE_BUILD_TYPE=MinSizeRel ..
 cmake --build .
```
</br>

the executable will be generated inside the respective build-X folder. </br>

### (Windows)
open a powershell window and cd into the project folder </br>
#### (Release)
```bash
 mkdir build-release
 cd build-release
 cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
 make
```

#### (Debug)
```bash
 mkdir build-debug
 cd build-debug
 cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
 make
```
#### (Release With Debug Info)
```bash
 mkdir build-relwithdebinfo
 cd build-relwithdebinfo
 cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
 make
```

#### (Release With Minimum Size)
```bash
 mkdir build-minsizerel
 cd build-minsizerel
 cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel ..
 make
```

the executable will be generated inside the respective build-X folder. </br>

## Running
```bash
./Beam-Pursuit
```

## IDE's
#### CLion (Stable/Nova)
Open the project folder in CLion and configure CMake presets. </br>
