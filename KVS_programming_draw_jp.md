# 2.2 データの描画 #
KVSを使ってポリゴンデータを表示するプログラムを作成し、可視化プログラムの基本構造を説明します。

## 2.2.1 スクリーンの作成 ##
前説と同様に、作業フォルダを作成します。「lesson2」という名前のフォルダを作成し、そのフォルダ内に「main.cpp」という名前のファイルを作成してください。

KVSを使った可視化プログラムでは、データを表示するために、以下の2つのクラスを利用します。この2つのクラスは、SupportGLUTに含まれるクラスです。KVSでは、デスクトップ上にウィンドウを表示したり、マウスやキーボードを利用して操作するためにGLUTライブラリを利用しています。

```
kvs::glut::Application
kvs::glut::Screen
```

  * kvs::glut::Applicationクラスは、GLUTを使ったアプリケーションを統括するクラスです。１つのアプリーションに１つだけ定義します。
  * kvs::glut::Screenクラスは、表示されるウィンドウ上に実際にデータを描画するための基盤となるクラスです。複数定義した場合、複数のウィンドウが表示されます。

これらのクラスを利用するために、以下のようにヘッダファイルをインクルードします。

```
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
```

エディタで「main.cpp」を開き、以下のように、可視化プログラムの骨格を記述します。

```
#include <kvs/glut/Application>
#include <kvs/glut/Screen>

int main( int argc, char** argv )
{
    kvs::glut::Application app( argc, argv );

    kvs::glut::Screen screen( &app );
    screen.show();

    return app.run();
}
```

  * 6行目：アプリケーション変数（app）を定義します。引数に、コマンドライン引数の数（argc）と値（argv）を指定します。
  * 8行目：スクリーン変数（screen）を定義します。引数に、アプリケーション変数へのポインタを指定します。
  * 9行目：スクリーン変数のshowメソッドをコールしてスクリーンを表示します。
  * 11行目：アプリケーション変数のrunメソッドをコールしてプログラムを実行します。

## 2.2.2 ポリゴンデータの読み込み ##

次に、ポリゴンデータを読み込む処理を記述します。ポリゴンデータを読み込むために、以下の2つのクラスを利用します。

```
kvs::PolygonObject
kvs::PolygonImporter
```

  * kvs::PolygonObjectクラスは、ポリゴンデータを構成するデータを格納しておくためのクラスです。
  * kvs::PolygonImporterクラスは、ポリゴンデータファイルを読み込み、kvs::PolygonObjectクラスへデータを格納するためのクラスです。

必要なヘッダファイルは、以下のようにしてインクルードすることができます。

```
#include <kvs/PolygonObject>
#include <kvs/PolygonImporter>
```

これらのクラスを使って、以下にようにしてポリゴンデータを読み込み、kvs::PolygonObjectクラスとして定義されるオブジェクト変数（object）に格納することができます。データは、コマンドラインの第一引数でそのファイル名が指定されるとします。

```
kvs::PolygonObject* object = new kvs::PolygonImporter( argv[1] );
```

## 2.2.3 スクリーンへの登録 ##
KVSでは、読み込んだポリゴンデータをスクリーンに登録することによって、ウィンドウ内に表示します。具体的には、以下のようにスクリーン変数（screen）のregisterObjectメソッドを利用して登録することができます。

```
screen.registerObject( object );
```

スクリーンに登録されたデータは、KVS内部でメモリ管理されるため、データ読み込み時に確保したメモリを明示的に解放する必要はありません。つまり、メモリ確保されたobjectをdeleteする必要はありません。

## 2.2.4 コンパイルと実行 ##
完成したプログラムは、以下のようになります。

```
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/PolygonObject>
#include <kvs/PolygonImporter>

int main( int argc, char** argv )
{
    kvs::glut::Application app( argc, argv );

    kvs::PolygonObject* object = new kvs::PolygonImporter( argv[1] );

    kvs::glut::Screen screen( &app );
    screen.registerObject( object );
    screen.show();

    return app.run();
}
```

ターミナルを開き、プログラムをコンパイルします。「lesson2」フォルダに移動し、以下のようにしてコンパイルしてください。

```
> cd lesson2
> kvsmake -G
> kvsmake
```

正常にコンパイルができたら、プログラムを実行します。表示するポリゴンデータは、KVSのテストデータを利用します。[ここ](http://code.google.com/p/kvs/downloads/detail?name=KVS-data-1.0.0.zip&can=2&q=#makechanges)から、テストデータをダウンロードしてください。展開したフォルダ内にあるポリゴンデータpolygon.kvsmlをlesson2フォルダにコピーしてください。

Windows環境の場合は、以下のように実行します。

```
> lesson2.exe polygon.kvsml
```

Linux/Mac環境の場合は、以下のように実行します。

```
> ./lesson2 polygon.kvsml
```