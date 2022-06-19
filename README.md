## ELF Study

### 一、环境准备

* OS: ubuntu 20.04.4 LTS x86_64
* 安装以下软件包：

    ```shell
    $ sudo apt install -y cmake llvm-dev clang clang-tools clangd clang-format ninja-build libspdlog-dev
    ```
* 安装 `VScode` 插件，`clangd、CMake Tools、CMake`

### 二、编译

```shell
$ mkdir build
$ cd build
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
$ ninja
```

### 三、运行

```shell
$ cd build
$ ./ElfStudy
```

### 参考文档

1. [Building LLVM with CMake](https://llvm.org/docs/CMake.html)
2. [一个完整的cmake+clang+llvm编译链接hello-world过程](https://blog.csdn.net/tanmx219/article/details/86681167)