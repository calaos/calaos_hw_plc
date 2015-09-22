# Cross compiler

Install a cross compiler. Mine comes from https://launchpad.net/gcc-arm-embedded/+download

Add the toolchain to your PATH : 

```
export PATH=$PATH:/home/nico/toolchains/gcc-arm-none-eabi-4_9-2015q1/bin/
```

now arm-none-gnueabi-gcc/ls/as should be find.

# Autotools

Create configure script and makefiles :

```
./autogen.sh
./configure --with-board=stm32-olinuxino --host=arm-none-eabi
```

For now only stm32-olinuxino is supported.

# Build

```
make
```

Bu