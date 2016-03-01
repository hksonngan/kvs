# 1.5 動作確認 #
正常にKVSがインストールされたかどうか確認します。ここでは、KVSのインストール後に利用可能になるコマンドを利用し、KVSが利用可能な状態であるか確認します。

## 1.5.1 バージョンの確認 ##
kvscheckコマンドを利用してインストールされたKVSのバージョンを確認します。ターミナル上で、以下のように入力し、表示されるバージョンを確認してください。

```
> kvscheck -version      ※ "kvscheck -version"と入力しエンターキーを押す。
KVS version: 1.0.0       ※ バージョン名が表示される。この例では、バージョン1.0.0である。
```

kvscheckのその他の用法については、[こちら](KVS_kvscheck_jp.md)のページを参考にしてください。

## 1.5.2 テストデータの表示 ##
kvsviewコマンドを利用してテストデータを表示します。テストデータは[ここ](http://kvs.googlecode.com/files/KVS-data-1.0.0.zip)からダウンロードしてください。たとえば、ターミナル上で、以下のように入力すると、ロブスターデータの等値面表示ができます。

```
> cd KVSData
> kvsview -Isosurface lobster.fld
```

kvsviewのその他の用法については、[こちら](KVS_kvsview_jp.md)のページを参考にしてください。

## 1.5.3 サンプルプログラムのコンパイル ##
kvsmakeコマンドを利用してサンプルプログラムをコンパイルし実行します。

**Windowsの場合
```
> cd Example\SupportGLUT\SimpleTriangle
> kvsmake -G
> kvsmake
> SimpleTriangle.exe
```**

