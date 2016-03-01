# 8.3 kvscheck #

## 8.3.1 機能 ##
KVSのバージョンや利用しているコンパイラの情報などを標準出力に表示する。また、KVSがサポートしている他のライブラリ（GLUT, Qt, SAGEなど）のバージョン情報や、KVSで読み込み可能なデータファイルのチェックも行うことができる。

## 8.3.2 使用方法 ##
```
Usage: kvscheck [options] <input value>

Options:
-h         : ヘルプメッセージを表示する。
-version   : KVSのバージョンを表示する 。(optional)
-platform  : プラットフォーム情報を表示する。 (optional)
-compiler  : コンパイラ情報を表示する。(optional)
-sizeof    : 数値型のサイズ（バイト数）を表示する。 (optional)
-support   : サポートしている他ライブラリの情報を表示する。 (optional)
-minmax    : 数値の最小値および最大値を表示する。 (optional)
-opengl    : OpenGLに関する情報を表示する。 (optional)
-extension : サポートしているOpenGL拡張機能に関する情報を表示する。 (optional)
-file      : KVSで読み込み可能なファイルの情報を表示する (optional: <filename>)
```

## 8.3.3 使用例 ##

  1. 現在インストールされているKVSのバージョンをチェックする。
```
> kvscheck -version
KVS version: 1.0.0
```
  1. 現在作業しているプラットフォームの情報を表示する。
```
> kvscheck -platform
Platform:   Mac OS X
CPU:        Intel x86 (32 bits)
Cores:      2 core(s)
Byte-order: Little endian
```
  1. 利用するコンパイラに関する情報を表示する。
```
> kvscheck -compiler
Compiler: GNU C/C++ (4.0.1)
```
  1. サポートしている他ライブラリに関する情報を表示する。
```
> kvscheck -support
Supported libraries:
GLUT - The OpenGL Utility Toolkit (version: 5)
GLEW - The OpenGL Extension Wrangler Library (version: 1.4.0)
SAGE - Scalable Adaptive Graphics Environment (version: 2.0)
```
  1. OpenGLに関する情報を表示する。
```
> kvscheck -opengl
Vendor:      NVIDIA Corporation
Renderer:    NVIDIA GeForce 8600M GT OpenGL Engine
GL Version:  2.0 NVIDIA-1.5.36
GLU Version: 1.3 MacOSX
```
  1. OpenGL拡張機能に関する情報を表示する。
```
> kvscheck -extension
GL Extensions (112):
	GL_ARB_transpose_matrix
...
	GL_SGIS_texture_edge_clamp
	GL_SGIS_texture_lod
GLU Extensions (0):
```
  1. KVSで読み込むことができるデータ（以下ではAVS Field data）の情報を表示する。
```
> kvscheck -file lobster.fld
Reading time:      0.049526 [sec]
Information:
bits    : 8
signed  : unsigned
veclen  : 1
nspace  : 3
ndim    : 3
dim     : 120 120 34
min ext : 0 0 0
max ext : 1 1 1
data    : byte
field   : uniform
label   :
```