# 8.1 kvsmake #

## 8.1.1 機能 ##
KVSを利用するために必要な設定（インクルードパスおよびライブラリパスの設定やライブラリファイルのリンクなど）を組み込んだメイクファイルを自動生成し、実行ファイルまたはライブラリを作成（コンパイル）する。

## 8.1.2 使用方法 ##

```
Usage: kvsmake [options] <project_name/make_options>

Options:
-h      : ヘルプメッセージを表示する。
-g      : プロジェクト名を指定しメイクファイルを生成する。
-G      : カレントディレクトリ名をプロジェクト名としてメイクファイルを生成する。
-v      : VC向けのプロジェクトファイルを生成する。
-vc     : -vと同じ。
-vcproj : -vと同じ。
-q      : Qt向けのプロジェクトファイルを生成する。
-qt     : -qと同じ。
-qtproj : -qと同じ。
```

**kvsmake.conf**

KVS以外のライブラリをリンクして利用したい場合、カレントディレクトリに「kvsmake.conf」という名前の設定ファイルを準備する。設定ファイルの記述方法は以下の通りである。

kvsmake.confの記述
  * ファイル名は「kvsmake.conf」とする。
  * kvsmakeを実行するディレクトリに置いておく。
  * ファイル内に以下の変数を必要に応じて設定する。
    * INCLUDE\_PATH	インクルードパス
    * LIBRARY\_PATH	ライブラリパス
    * LINK\_LIBRARY	リンクするライブラリ名
    * INSTALL\_DIR	インストールディレクトリ名

  * 例）kvsmake.confにパスとライブラリを追加設定する。
```
% less kvsmake.conf
INCLUDE_PATH := -I/home/usrname/local/include
LIBRARY_PATH := -L/home/usrname/local/lib
LINK_LIBRARY := -lusrlib
INSTALL_DIR := /home/usrname/local/bin
```

  * 例）Windows環境下でMSVCを利用している場合は、パスの指定方法などが異なる。そのため、「kvsmake.vc.conf」という名前のファイルを用意し、以下のようにMSVC向けの設定を行うことができる。
```
% less kvsmake.conf
INCLUDE_PATH := /Ic:\home\usrname\local\include
LIBRARY_PATH := /LIBPATH:c:\home\usrname\local\lib
LINK_LIBRARY := usrlib.lib
INSTALL_DIR := c:\home\usrname\local\bin
```

## 8.1.3 使用例 ##

  1. プロジェクト名をカレントディレクトリ名としてコンパイルする。
```
% kvsmake -G
% kvsmake
※例えば、カレントディレクトリが「Test」の場合、「Test」という名前（Windows環境では拡張子「exe」が付く）の実行ファイルが生成される。
```
  1. プロジェクト名を指定し、コンパイルする。
```
% kvsmake -g <プロジェクト名>
% kvsmake
※例えば、プロジェクト名を「Test」と指定すると、「Test」という名前の実行ファイル（Windows環境では拡張子「exe」が付く）が生成される。
```
  1. ライブラリファイルを生成する。
```
% kvsmake -G　　または　　kvsmake -g <実行ファイル名>
% kvsmake lib
※例えば、プロジェクト名が「Test」の場合、「libTest.a」という名前のライブラリファイル（Windows環境では拡張子は「lib」となる）が生成される。
```
  1. Microsoft Visual C/C++向けのプロジェクトファイルを生成する。
```
% kvsmake -vcproj <プロジェクト名>
※生成される「<プロジェクト名>.xxx」をダブルクリックしIDEを起動する。
```
  1. Nokia社 Qt向けプロジェクトファイルを生成する。
```
% kvsmake -qtproj <プロジェクト名>
% qmake
※「<プロジェクト名>.pro」が生成されるので、qmakeコマンドを利用してコンパイルする。
```