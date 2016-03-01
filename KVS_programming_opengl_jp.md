# 2.3 OpenGLの利用 #
KVSでは、データを描画するためにOpenGLを利用しています。前節で説明したポリゴンデータを描画するkvs::PolygonRendererも内部でOpenGL関数を利用して実装しています。ここでは、利用者が独自にOpenGL関数を利用して三角形を描画する方法について説明します。

## 2.3.1 スクリーンの作成 ##
最初に、作業用フォルダを作成します。「lesson3」という名前のフォルダを作成し、そのフォルダ内に「main.cpp」という名前のファイルを作成してください。そして、前節と同じように、main.cppに以下のように可視化プログラムの骨格を記述してください。

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

## 2.3.2 描画イベントの作成 ##
三角形を描画するために、描画イベントを作成します。まず、OpenGL関数を利用するために必要なヘッダファイルをインクルードします。KVSでは、利用しているOSへの依存をなくすため、以下のようにしてヘッダファイルをインクルードします。

```
#include <kvs/OpenGL>
```


次に、描画イベントを作成します。KVSでは、描画イベントを作成するために、kvs::PaintEventListenerクラスを利用します。以下のようにヘッダファールをインクルードしてください。

```
#include <kvs/PaintEventListener>
```

描画イベントを定義するためには、kvs::PaintEventListenerクラスを継承した独自クラスを作成します。そして、そのクラス内部で、updateメソッドを実装します。このメソッドは、kvs::PaintEventListenerクラス内で仮想関数として定義されています。ここでは、以下のように、三角形を描画するための独自クラスPaintEventを定義します。

```
class PaintEvent : public kvs::PaintEventListener
{
public:

    void update();
};
```

描画する三角形を定義します。KVSの初期設定では、カメラ（視点）は基準空間座標系（世界座標系）上の(0,0,12)に設定されており、その座標系の原点を見ています。可視化プログラム起動時には、ウィンドウのサイズは512x512と設定されており、その中央が世界座標系原点と一致します。そして、カメラの画角の初期値は、45度に設定されているため、ウィンドウ内に描画される空間の領域は、世界座標系のX軸方向に-5〜5、Y軸方向に-5〜5となります。

上記のように設定される空間に対して、ウィンドウの中央に三角形を描画するために、以下のように、頂点座標値v0,v1,v2とそれに対応する色c0,c1,c2を設定します。

  * 座標値：v0 = (0, 3, 0), v1 = (3, -3, 0), v2 = (-3, -3, 0)
  * 色： c0 = (255, 0, 0), c1 = (0, 255, 0), c2 = (0, 0, 255)

このように定義される三角形を、OpenGL関数を使ってupdateメソッド内に記述します。

```
void PaintEvent::update()
{
    glBegin( GL_TRIANGLES );
    glColor3ub( 255,   0,   0 ); glVertex3d(  0.0,  3.0, 0.0 ); // c0, v0
    glColor3ub(   0, 255,   0 ); glVertex3d(  3.0, -3.0, 0.0 ); // c1, v1
    glColor3ub(   0,   0, 255 ); glVertex3d( -3.0, -3.0, 0.0 ); // c2, v2
    glEnd();
}
```

## 2.3.3 スクリーンへの登録 ##

## 2.3.4 コンパイルと実行 ##
完成したプログラムは以下のようになります。

```
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/OpenGL>
#include <kvs/PaintEventListener>

class PaintEvent : public kvs::PaintEventListener
{
public:

    void update();
};

void PaintEvent::update()
{
    glBegin( GL_TRIANGLES );
    glColor3ub( 255,   0,   0 ); glVertex3d(  0.0,  3.0, 0.0 ); // c0, v0
    glColor3ub(   0, 255,   0 ); glVertex3d(  3.0, -3.0, 0.0 ); // c1, v1
    glColor3ub(   0,   0, 255 ); glVertex3d( -3.0, -3.0, 0.0 ); // c2, v2
    glEnd();
}

int main( int argc, char** argv )
{
    kvs::glut::Application app( argc, argv );

    PaintEvent paint_event;

    kvs::glut::Screen screen( &app );
    screen.addPaintEvent( &paint_event );
    screen.show();

    return app.run();
}
```

前節と同様に、ターミナルを開き、プログラムをコンパイルします。「lesson3」フォルダに移動し、以下のようにしてコンパイルしてください。

```
> cd lesson3
> kvsmake -G
> kvsmake
```

コンパイルが終了したら、プログラムを実行します。

Windows環境では、以下のように実行します。

```
> lesson3.exe
```

Linux/Mac環境では、以下のように実行します。

```
> ./lesson3
```