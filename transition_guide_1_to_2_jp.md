# KVS 1.x から 2.x への移行ガイド #

KVS 1.x から2.0へのバージョンアップに伴い、いくつかの仕様の変更とAPIの変更があります。ここでは、移行の際のガイドラインとして、変更があった仕様およびクラスについて、その修正方法とともにまとめています。




---


## バージョンの確認 ##
現在、利用しているKVSのバージョンを確認する方法について説明します。

### kvscheckコマンドを利用した確認方法 ###
kvscheckコマンドを利用して、現在インストールされているKVSのバージョンを確認することができます。コマンドターミナルを開けて、以下のようにコマンドを実行してください。kvscheckコマンドの利用法については[こちら](KVS_kvscheck_jp.md)を参考にしてください。

```
> kvscheck -version
KVS version: 2.0.0
```

### ソースコード内での確認方法 ###
kvs::Versionクラスを利用して、ソースコード内でKVSのバージョンを確認することができます。ヘッダファイル「`<kvs/Version>`」をインクルードし、以下のようにしてバージョン情報を取得することができます。[こちら](KVS_programming_build_jp.md)にも説明がありますので、参考にしてください。

```
#include <kvs/Version>
```
```
size_t major = kvs::Version::MajorVersion(); // メジャーバージョン番号の取得
size_t minor = kvs::Version::MinorVersion(); // マイナーバージョン番号の取得
size_t patch = kvs::Version::PatchVersion(); // パッチバージョン番号の取得
```

### プリプロセッサ命令を利用した確認方法 ###
プリプロセッサ命令（#if）を利用して、コンパイル時にバージョンを確認することができます。ヘッダファイル「`<kvs/Version>`」をインクルードし、以下のようにしてバージョンの違いによりソースコードの記述を切り分けることができます。

```
#include <kvs/Version>
```
```
#if ( KVS_VERSION_MAJOR == 1 )
    // KVSのバージョンが1.x.xのときの処理
#elif ( KVS_VERSION_MAJOR == 2 )
    // KVSのバージョンが2.x.xのときの処理
#endif
```

## 削除されたクラス ##

### kvs::glut::GlobalBase, kvs::glut::ScreenBaseなど ###
KVS1.0をリリースする以前のバージョンでは、たとえば、GLUTを使ってビューワアプリケーションを作成する場合は、ユーザが`kvs::glut::GlobalBase`および`kvs::glut::ScreenBase`を継承して独自のグローバルクラスおよびスクリーンクラスを定義する必要がありました。KVS1.0では、`kvs::glut::Application`および`kvs::glut::Screen`を利用して、継承することなく、ビューワアプリケーションの開発が可能となりましたが、下位バージョンとの互換性のために、それらに関連するクラスを残していました。KVS2.0へのバージョンアップを機に、下位互換性のために残していた以下のクラスを削除しました。

```
// 削除されたクラス
kvs::GlobalCore
kvs::ScreenCore
kvs::WindowBase
kvs::glut::GlobalBase
kvs::glut::ScreenBase
kvs::glut::Window
kvs::qt::GlobalBase
kvs::qt::ScreenBase
kvs::qt::Window
kvs::sage::GlobalBase
kvs::sage::ScreenBase
```

KVS2.0以降のバージョンでは、以下のクラスを利用してください。ビューワアプリケーションの開発は、[こちら](KVS_programming_draw_jp.md)を参考にしてください。

```
kvs::glut::Application
kvs::glut::Screen
kvs::qt::Application
kvs::qt::Screen
```

### kvs::glut::AxisObject, kvs::glut::AxisRenderer ###
座標軸を表示するために必要なクラスであったkvs::AxisObjectクラスとkvs::AxisRendererクラスを廃止し、代わりに、kvs::glut::!Axis3Dクラスを追加しました。KVS1.Xでは、ObjectをいったんAxisObjectに変換した後に、AxisRendererを使って座標軸を描画していましたが、もう少し簡単に描画するために、すべてのObjectに対応したRendererとして座標軸描画クラスを実装しました。

#### 修正点1 ####
以下のように修正してください。
```
// 修正前
kvs::PolygonObject* object = new kvs::PolygonImporter( filename );
kvs::glut::AxisObject* axis = new kvs::glut::AxisObject( object );
kvs::glut::AxisRenderer* axis_renderer = new kvs::glut::AxisRenderer();
screen.registerObject( axis, axis_renderer );
```
```
// 修正後
kvs::PolygonObject* object = new kvs::PolygonImporter( filename );
kvs::glut::Axis3D* axis = new kvs::glut::Axis3D();
screen.registerObject( object, axis );
```

### SupportGLEW ###
KVS2.0ではGLEWを必須ライブラリとしたために、SupportGLEWを廃止し、そこに含まれていたクラスをKVS本体に組み込みました。

#### 修正点1 ####
SupportGLEW/Viewer以下に含まれていたクラスを、新たに追加したCore/Visualization/OpenGLに移動しました。そのため、名前空間およびインクルードファイル名を修正（"glew"を削除）する必要があります。
```
// 修正前
#include <kvs/glew/BufferObject>
#include <kvs/glew/FragmentShader>
#include <kvs/glew/FrameBufferObject>
#include <kvs/glew/GeometryShader>
#include <kvs/glew/IndexBufferObject>
#include <kvs/glew/PixelBufferObject>
#include <kvs/glew/ProgramObject>
#include <kvs/glew/RenderBuffer>
#include <kvs/glew/ShaderObject>
#include <kvs/glew/ShaderSource>
#include <kvs/glew/Texture3D>
#include <kvs/glew/VertexBufferObject>

kvs::glew::BufferObject
kvs::glew::FragmentShader
kvs::glew::FrameBufferObject
kvs::glew::GeometryShader
kvs::glew::IndexBufferObject
kvs::glew::PixelBufferObject
kvs::glew::ProgramObject
kvs::glew::RenderBuffer
kvs::glew::ShaderObject
kvs::glew::ShaderSource
kvs::glew::Texture3D
kvs::glew::VertexBufferObject
```
```
// 修正後
#include <kvs/BufferObject>
#include <kvs/FragmentShader>
#include <kvs/FrameBufferObject>
#include <kvs/GeometryShader>
#include <kvs/IndexBufferObject>
#include <kvs/PixelPackBufferObject>
#include <kvs/PixelUnpackBufferObject>
#include <kvs/ProgramObject>
#include <kvs/RenderBuffer>
#include <kvs/ShaderObject>
#include <kvs/ShaderSource>
#include <kvs/Texture3D>
#include <kvs/VertexBufferObject>

kvs::BufferObject
kvs::FragmentShader
kvs::FrameBufferObject
kvs::GeometryShader
kvs::IndexBufferObject
kvs::PixelPackBufferObject      // KVS1.xではkvs::glew::PixelBufferObject( Pack )
kvs::PixelUnpackBufferObject    // KVS1.xではkvs::glew::PixelBufferObject( Unpack )
kvs::ProgramObject
kvs::RenderBuffer
kvs::ShaderObject
kvs::ShaderSource
kvs::Texture3D
kvs::VertexBufferObject
```

#### 修正点2 ####
SupportGLEW/Renderer以下に含まれていたクラスを、Core/Visualization/Rendererに移動しました。修正点1と同様にして名前空間を修正してください。ただし、同名のクラス名が存在する場合、GPU版レンダラーについては、なめ空間glslを利用して区別することとしました。また、`kvs::glew::ParticleVolumeRenderer`については、`kvs::glsl::ParticleBasedRenderer`というクラス名に変更しています。
```
// 修正前
#include <kvs/glew/EnsembleAverageBuffer>
#include <kvs/glew/PreIntegrationTable>
#include <kvs/glew/ProjectedTetrahedraTable>
#include <kvs/glew/PointRenderer>
#include <kvs/glew/PolygonRenderer>
#include <kvs/glew/HAVSVolumeRenderer>
#include <kvs/glew/ParticleBasedRenderer>
#include <kvs/glew/ParticleVolumeRenderer>
#include <kvs/glew/RayCastinRenderer>
#include <kvs/glew/StochasticRendererBase>
#include <kvs/glew/StochasticPointRenderer>
#include <kvs/glew/StochasticLineRenderer>
#include <kvs/glew/StochasticPolygonRenderer>
#include <kvs/glew/StochasticTetrahedraRenderer>
#include <kvs/glew/StochasticMultipleTetranedraRenderer>
#include <kvs/glew/StochasticMultivariateTetrahedraRenderer>
#include <kvs/glew/StochasticRenderingEngine>
#include <kvs/glew/StochasticPointEngine>
#include <kvs/glew/StochasticLineEngine>
#include <kvs/glew/StochasticPolygonEngine>
#include <kvs/glew/StochasticTetrahedraEngine>
#include <kvs/glew/StochasticMultipleTetranedraEngine>
#include <kvs/glew/StochasticMultivariateTetrahedraEngine>
#include <kvs/glew/StochasticRenderingCompositor>
#include <kvs/glew/StochasticMultipleTetrahedraCompositor>

kvs::glew::EnsembleAverageBuffer
kvs::glew::PreIntegrationTable
kvs::glew::ProjectedTetrahedraTable
kvs::glew::PointRenderer
kvs::glew::PolygonRenderer
kvs::glew::HAVSVolumeRenderer
kvs::glew::ParticleBasedRenderer
kvs::glew::ParticleVolumeRenderer
kvs::glew::RayCastinRenderer
kvs::glew::StochasticRendererBase
kvs::glew::StochasticPointRenderer
kvs::glew::StochasticLineRenderer
kvs::glew::StochasticPolygonRenderer
kvs::glew::StochasticTetrahedraRenderer
kvs::glew::StochasticMultipleTetranedraRenderer
kvs::glew::StochasticMultivariateTetrahedraRenderer
kvs::glew::StochasticRenderingEngine
kvs::glew::StochasticPointEngine
kvs::glew::StochasticLineEngine
kvs::glew::StochasticPolygonEngine
kvs::glew::StochasticTetrahedraEngine
kvs::glew::StochasticMultipleTetranedraEngine
kvs::glew::StochasticMultivariateTetrahedraEngine
kvs::glew::StochasticRenderingCompositor
kvs::glew::StochasticMultipleTetrahedraCompositor
```
```
// 修正後
#include <kvs/EnsembleAverageBuffer>
#include <kvs/PreIntegrationTable>
#include <kvs/ProjectedTetrahedraTable>
#include <kvs/PointRenderer>
#include <kvs/PolygonRenderer>
#include <kvs/HAVSVolumeRenderer>
#include <kvs/ParticleBasedRenderer>
//#include <kvs/glew/ParticleVolumeRenderer>  // 廃止（#include <kvs/ParticleBasedRenderer>を利用）
#include <kvs/RayCastinRenderer>
#include <kvs/StochasticRendererBase>
#include <kvs/StochasticPointRenderer>
#include <kvs/StochasticLineRenderer>
#include <kvs/StochasticPolygonRenderer>
#include <kvs/StochasticTetrahedraRenderer>
#include <kvs/StochasticMultipleTetranedraRenderer>
#include <kvs/StochasticMultivariateTetrahedraRenderer>
#include <kvs/StochasticRenderingEngine>
#include <kvs/StochasticPointEngine>
#include <kvs/StochasticLineEngine>
#include <kvs/StochasticPolygonEngine>
#include <kvs/StochasticTetrahedraEngine>
#include <kvs/StochasticMultipleTetranedraEngine>
#include <kvs/StochasticMultivariateTetrahedraEngine>
#include <kvs/StochasticRenderingCompositor>
#include <kvs/StochasticMultipleTetrahedraCompositor>

kvs::EnsembleAverageBuffer
kvs::PreIntegrationTable
kvs::ProjectedTetrahedraTable
kvs::glsl::PointRenderer
kvs::glsl::PolygonRenderer
kvs::HAVSVolumeRenderer
kvs::glsl::ParticleBasedRenderer
//kvs::glew::ParticleVolumeRenderer  // 廃止（kvs::glsl::ParticleBasedRendererを利用）
kvs::glsl::RayCastinRenderer
kvs::StochasticRendererBase
kvs::StochasticPointRenderer
kvs::StochasticLineRenderer
kvs::StochasticPolygonRenderer
kvs::StochasticTetrahedraRenderer
kvs::StochasticMultipleTetranedraRenderer
kvs::StochasticMultivariateTetrahedraRenderer
kvs::StochasticRenderingEngine
kvs::StochasticPointEngine
kvs::StochasticLineEngine
kvs::StochasticPolygonEngine
kvs::StochasticTetrahedraEngine
kvs::StochasticMultipleTetranedraEngine
kvs::StochasticMultivariateTetrahedraEngine
kvs::StochasticRenderingCompositor
kvs::StochasticMultipleTetrahedraCompositor
```

### SupportSAGE, SupportOpenCABIN ###
利用頻度が低く、KVS2.0への対応に時間を要するため、SupportSAGEおよびSupportOpenCABINを非対応としました。タイルドディスプレイへの表示基盤については、KVS本体に独自基盤を組み込む予定です。

## スクリーンクラス ##

### kvs::glut::Screen, kvs::qt::Screen ###
Screenクラスの名称は変更していませんが、内部の継承関係を変更しました。これまで、Screenクラスは、`kvs::ScreenBase`クラスを継承して、kvs::glut::Screenクラスおよびkvs::qt::Screenクラスを実装していましたが、`kvs::ScreenBase`クラスが肥大化し、機能拡張等が困難となっていたため、いくつかの改善を行いました。

#### 修正点1 ####
`kvs::ScreenBase`クラスを共通イベント操作を行うためのベースクラスとし、GLUTおよびQtの各種コールバック関数（メソッド）をラップすることでAPIを共通化した`kvs::glut::ScreenBase`クラスおよび`kvs::qt::ScreenBase`クラスを追加しました。これらのクラスを継承することでGLUTとQtのAPIの違いを気にすることなく、ユーザ独自のスクリーンクラスを作成することができます。KVS2.0では、これらのクラスを継承したkvs::glut::Screenおよびkvs::qt::Screenクラスを標準スクリーンクラス（スクリーンの標準実装）として提供します。
```
// 修正前
// kvs::ScreenBase <-- kvs::glut::Screen
// kvs::ScreenBase <-- kvs::qt::Screen
namespace kvs { namespace glut { class Screen : public kvs::ScreenBase { ... }; } }
namespace kvs { namespace qt { class Screen : public kvs::ScreenBase { ... }; } }
```
```
// 修正後
// kvs::ScreenBase <-- kvs::glut::ScreenBase <-- kvs::glut::Screen
// kvs::ScreenBase <-- kvs::qt::ScreenBase <-- kvs::qt::Screen
namespace kvs { namespace glut { class ScreenBase : public kvs::ScreenBase { ... }; } }
namespace kvs { namespace qt { class ScreenBase : public kvs::ScreenBase { ... }; } }
namespace kvs { namespace glut { class Screen : public kvs::glut::ScreenBase { ... }; } }
namespace kvs { namespace qt { class Screen : public kvs::qt::ScreenBase { ... }; } }
```

#### 修正点2 ####
描画シーンを構成する要素であるCamera, Light, `ObjectManager`, `RendererManager`などは、KVS1.xでは、`kvs::ScreenBase`クラス内に直接定義されていたために、それを継承したスクリーンでは、シーンの操作およびその管理方法の変更ができませんでした。KVS2.0では、GLUT・Qt間でAPI非依存の統一的なコールバック処理を提供するベースクラスとして、シーンの構成要素をkvs::Sceneクラスとして切り出して、標準実装であるkvs::glut::Screenおよびkvs::qt::Screenクラス内に定義しました。その影響により、各描画要素へのアクセス方法について以下のような修正が必要となります。
```
// 修正前
screen.camera();
screen.light();
screen.mouse();
screen.background();
screen.objectManager();
screen.rendererManager();
screen.IDManager();
screen.controlTarget();
```
```
// 修正後
screen.scene()->camera();
screen.scene()->light();
screen.scene()->mouse();
screen.scene()->background();
screen.scene()->objectManager();
screen.scene()->rendererManager();
screen.scene()->IDManager();
screen.scene()->controlTarget();
```

#### 修正点3 ####
シーンの構成要素をkvs::Sceneクラスとして切り出した影響によって、独自イベントの実装の一部を修正する必要があります。KVS1.xでは、イベントを追加するために、各`EventListener`クラスを継承してユーザ独自のイベントを実装していました。その際に、`kvs::ScreenBase`クラスのポイントを返す「screen()」メソッドを利用してスクリーン（シーン）の構成要素にアクセスしていましたが、それらの定義場所が、`kvs::ScreenBase`クラスからkvs::Sceneクラスに変更となり、さらにkvs::Sceneが、kvs::glut::Screenおよびkvs::qt::Screenクラスで実体化されているために、以下のような修正が必要となります。
```
// 修正前（例）
class PaintEvent : public kvs::PaintEventListener
{
    ...
    void update()
    {
        ...
        screen()->camera();
        screen()->objectManager();
        ...
    }
};
```
```
// 修正後（例）
class PaintEvent : public kvs::PaintEventListener
{
    ...
    void update()
    {
        ...
        kvs::glut::Screen* glut_screen = static_cast<kvs::glut::Screen*>( screen() );
        glut_screen->scene()->camera();
        glut_screen->scene()->objectManager();
        ...
    }
};
```

#### 修正点4 ####
KVS1.xでは、イベントをスクリーンに追加または設定（書き換え）する際に、`addPaintEvent`, `addMousePressEvent`, `setPaintEvent`, `setMousePressEvent`などのメソッドを利用して、イベントの種類ごとに用意されたメソッドを呼び出す必要があった。KVS2.0では、イベントの種類に関わらず、追加する場合は`addEvent`、設定する場合は`setEvetn`というメソッドを利用することが可能です。これに伴い、以下のように修正してください。
```
// 修正前
addPaintEvent( paint_event );
addResizeEvent( resize_event );
addMousePressEvent( mouse_press_event );
addMouseMoveEvent( mouse_move_event )
addMouseReleaseEvent( mouse_release_event );
addMouseDoubleClickEvent( mouse_double_event );
addWheelEvent( wheel_event );
addKeyPressEvent( key_press_event );

setPaintEvent( paint_event );
setResizeEvent( resize_event );
setMousePressEvent( mouse_press_event );
setMouseMoveEvent( mouse_move_event )
setMouseReleaseEvent( mouse_release_event );
setMouseDoubleClickEvent( mouse_double_event );
setWheelEvent( wheel_event );
setKeyPressEvent( key_press_event );
```
```
// 修正後
addEvent( paint_event );
addEvent( resize_event );
addEvent( mouse_press_event );
addEvent( mouse_move_event )
addEvent( mouse_release_event );
addEvent( mouse_double_event );
addEvent( wheel_event );
addEvent( key_press_event );

setEvent( paint_event );
setEvent( resize_event );
setEvent( mouse_press_event );
setEvent( mouse_move_event )
setEvent( mouse_release_event );
setEvent( mouse_double_event );
setEvent( wheel_event );
setEvent( key_press_event );
```

## ファイルフォーマットクラス ##

### kvs::AVSFieldなど ###
kvs::AVSFieldクラスなどFileFormatに所属するクラスは、読み込んだデータの情報を標準出力するために<<オペレータを定義していましたが、それを廃止しインデント付き出力にも対応するためにprintメソッドを追加しました。その他、staticメソッド名の変更および一部廃止しました。

#### 修正点1 ####
<<オペレータの代わりにprintメソッドを利用してください。
```
// 修正前
kvs::AVSField field("lobster.fld");
std::cout << field << std::endl;
```
```
// 修正後
kvs::AVSField field("lobster.fld");
field.print( std::cout ); // インデントなし
field.print( std::cout, kvs::Indent(2) ); // インデント２を指定
```

#### 修正点2 ####
メソッド名を以下のように修正してください。ただし、KVSML関係クラス以外のクラスにおいては、CheckFileFormatメソッドを廃止しました。
```
// 修正前
CheckFileExtension
CheckFileFormat
```
```
// 修正後
CheckExtension
CheckFormat // KVSML関係クラスのみ
```

## 行列演算クラス ##

### kvs::Vector2, kvs::Vector3, kvs::Vector4, kvs::Vector ###
ベクトル系クラスでは、正規化されたベクトルを返すメソッドnormalizeが実装されていたが、自分自身が正規化される場合とされない場合の２つのメソッドが同じ名前で実装されていました。KVS2.0では、混乱を避けるために、自分自身を正規化するメソッド（正規化されたベクトルは返さない）と、正規化されたベクトルを返すメソッド（自分自身は正規化されない）を、それぞれ、normalizeとnormalizedとして処理を区別するようにしました。その他、いくつかの初期化メソッドを廃止しました。

#### 修正点1 ####
以下に修正例を示します。
```
// 修正前
kvs::Vector3f v1( 1, 2, 3 );
kvs::Vecto3f v2 = v1.normalize(); // v1の正規化ベクトルをv2にコピー（v1は正規化される？されない？）
v1.normalize(); // v1を正規化（v1は正規化される？されない？）
```
```
// 修正後
kvs::Vector3f v1( 1, 2, 3 );
kvs::Vecto3f v2 = v1.normalized(); // v1の正規化ベクトルをv2にコピー（v1は正規化されない）
v1.normalize(); // v1を正規化（v1は正規化される）
```

#### 修正点2 ####
全ての要素を指定した値で初期化するためのコンストラクタとsetメソッドを廃止しました。代わりにAllメソッドを使用してください。
```
// 修正前
kvs::Vector3f v( 2.0 ); // 全ての要素を2.0にする。
v.set( 3.0 ); // 全ての要素を3.0にする。
```
```
// 修正前
kvs::Vector3f v = kvs::Vector3f::All( 2.0 ); // 全ての要素を2.0にする。
v = kvs::Vector3f::All( 3.0 ); // 全ての要素を3.0にする。
```

### kvs::Matrix22, kvs::Matrix33, kvs::Matrix44, kvs::Matrix ###
マトリックス系クラスにおいても、ベクトル系クラスと同様に、逆行列を計算するメソッドinverseと転置行列を計算するメソッドtransposeが、それぞれ2つの同名メソッド（自分自身を書き換えるものと書き換えないもの）があるために混乱が生じていました。KVS2.0では、自分自身を書き換えるメソッドinverse, transposeと、自分自身を書き換えず処理された行列を返すメソッドinversed, transposedとして処理を区別するようにしました。その他、いくつかの初期化メソッドを廃止しました。

#### 修正点1 ####
以下に修正例を示します。
```
// 修正前
kvs::Matrix33f m1( 1, 2, 3, 4, 5, 6, 7, 8, 9 );
kvs::Matrix33f m2 = m1.inverse(); // m1の逆行列をm2にコピー（m1は逆行列になる？ならない？）
kvs::Matrix33f m3 = m2.transpose(); // m2の転置行列をm3にコピー（m2は転置行列になる？ならない？）
m1.inverse(); // m1の逆行列を計算（m1は逆行列になる？ならない？）
m2.transpose(); // m2の転置行列を計算（m2は転置行列になる？ならない？）
```
```
// 修正後
kvs::Matrix33f m1( 1, 2, 3, 4, 5, 6, 7, 8, 9 );
kvs::Matrix33f m2 = m1.inverted(); // m1の逆行列をm2にコピー（m1は逆行列ならない）
kvs::Matrix33f m3 = m2.transposed(); // m2の転置行列をm3にコピー（m2は転置行列ならない）
m1.invert(); // m1の逆行列を計算（m1は逆行列になる）
m2.transpose(); // m2の転置行列を計算（m2は転置行列になる）
```

#### 修正点2 ####
全ての要素を指定した値で初期化するためのコンストラクタとsetメソッドを廃止しました。代わりにAllメソッドを使用してください。
```
// 修正前
kvs::Matrix33f m( 2.0 ); // 全ての要素を2.0にする。
m.set( 3.0 ); // 全ての要素を3.0にする。
```
```
// 修正前
kvs::Matrix33f m = kvs::Matrix33f::All( 2.0 ); // 全ての要素を2.0にする。
m = kvs::Matrix33f::All( 3.0 ); // 全ての要素を3.0にする。
```

### kvs::Matrix ###
行列の行数と列数を取得するためのメソッドの名前を変更しました。

#### 修正点 ####
以下のように修正してください。
```
// 修正前
kvs::Matrix<float> m( 3, 4 );
size_t nrows = m.nrows(); // 行数を取得する。
size_t ncolumns = m.ncolumns(); // 列数を取得する。
```
```
// 修正後
kvs::Matrix<float> m( 3, 4 );
size_t nrows = m.rowSize(); // 行数を取得する。
size_t ncolumns = m.columnSize(); // 列数を取得する。
```

## 数値計算クラス ##

### kvs::ResponseSurface ###
サンプル点の数および変数の数を取得するメソッド名を変更しました。

#### 修正点1 ####
メソッド名を以下のように修正しました。
```
// 修正前
kvs::ResponseSurface rs;
size_t npoints = rs.npoints(); // サンプル点の数の取得
size_t nvariables = rs.nvariables(); // 変数の数の取得
```
```
// 修正後
kvs::ResponseSurface rs;
size_t npoints = rs.numberOfPoints(); // サンプル点の数の取得
size_t nvariables = rs.numberOfVariables(); // 変数の数の取得
```

## スレッドクラス ##

### kvs::Thread ###
３つのスリープメソッドの名前を変更しました。

#### 修正点1 ####
メソッド名を以下のように修正してください。
```
// 修正前
kvs::Thread::sleep(1); // 1秒スリープ
kvs::Thread::msleep(1); // 1ミリ秒スリープ
kvs::Thread::usleep(1); // 1マイクロ秒スリープ
```
```
// 修正後
kvs::Thread::Sleep(1); // 1秒スリープ
kvs::Thread::MilliSleep(1); // 1ミリ秒スリープ
kvs::Thread::MicroSleep(1); // 1マイクロ秒スリープ
```

## 可視化クラス ##

### kvs::Tubeline ###
チューブの分割数を指定するメソッドの名前を修正しました。

#### 修正点1 ####
メソッド名を以下のように修正してください。
```
// 修正前
kvs::Tubeline* tubeline = new kvs::Tubeline();
tubeline->setNDivisions( 10 );
```
```
// 修正後
kvs::Tubeline* tubeline = new kvs::Tubeline();
tubeline->setNumberOfDivisions( 10 );
```

### kvs::ArrowGlyph, kvs::DiamondGlyph, kvs::SphereGlyph ###
グリフ系クラスをMapperからRendererに移動しました。その影響で利用方法が少し変更になりました。

#### 修正点1 ####
以下のように修正してください。kvs::DiamondGlyphクラスおよびkvs::SphereGlyphクラスについても同様に修正してください。その他詳細については、参考プログラム [ArrowGlyph](http://code.google.com/p/kvs/source/browse/trunk/Example/Visualization/ArrowGlyph/main.cpp)、[DiamondGlyph](http://code.google.com/p/kvs/source/browse/trunk/Example/Visualization/DiamondGlyph/main.cpp)、[SphereGlyph](http://code.google.com/p/kvs/source/browse/trunk/Example/Visualization/SphereGlyph/main.cpp)を参考にしてください。
```
// 修正前
kvs::StructuredVolumeObject* volume = new kvs::StructuredVolumeImporter( filename ); // ベクタデータの読み込み
kvs::GlyphObject* object = new kvs::ArrowGlyph( volume );
kvs::GlyphRenderer* renderer = new kvs::GlyphRenderer();
screen.registerObject( object, renderer );
```
```
// 修正後
kvs::StructuredVolumeObject* object = new kvs::StructuredVolumeImporter( filename ); // ベクタデータの読み込み
kvs::ArrowGlyph* renderer = new kvs::ArrowGlyph();
screen.registerObject( object, renderer );
```

### kvs::Bounds ###
kvs::BoundsをFilterからRendererに移動しました。その影響で利用方法が少し変更になりました。

#### 修正点1 ####
以下のように修正してください。
```
// 修正前
kvs::StructuredVolumeObject* volume = new kvs::StructuredVolumeImporter( filename ); // データの読み込み
kvs::LineObject* object = new kvs::Bounds( volume );
object->setColor( kvs::RGBColor( 255, 255, 255 ) );
object->setSize( 3.0 );
kvs::LineRenderer* renderer = new kvs::LineRenderer();
screen.registerObject( object, renderer );
```
```
// 修正後
kvs::StructuredVolumeObject* object = new kvs::StructuredVolumeImporter( filename ); // データの読み込み
kvs::Bounds* bounds = new kvs::Bounds();
bounds->setLineColor( kvs::RGBColor( 255, 255, 255 ) );
bounds->setLineWidth( 3.0 );
screen.registerObject( object, bounds );
```

#### 修正点2 ####
KVS1.Xのkvs::Boundsクラスはkvs::LineObjectを出力するFilerメソッドであったが、KVS2.0ではRendererメソッドとなったため、そのままではLineObjectとして扱うことができない。境界線ボックスをLineObjectとして扱いたい場合は、outputLineObjectメソッドを使ってLineObjectを生成することができる。
```
// 修正前
kvs::LineObject* object = new kvs::Bounds( volume );
```
```
// 修正後
kvs::Bounds* bounds = new kvs::Bounds();
kvs::LineObject* object = bounds->outputLineObject( volume );
```

### kvs::PointObjectなど ###
kvs::PointObjectクラスをはじめとするObject系クラスで、情報を標準出力する<<オペレータを廃止しました。代わりに、printメソッドを利用してください。その他、いくつかのクラスでメソッド名を変更しています。

#### 修正点1 ####
以下のように修正してください。
```
// 変更前
kvs::PointObject object;
std::cout << object << std::endl;
```
```
// 変更後
kvs::PointObject object;
object.print( std::cout ); // インデントなし
object.print( std::cout, kvs::Indent(2) ); // インデント2を指定
```

#### 修正点2 ####
「〇〇の数」を返すメソッドおよび設定するメソッドの名前を変更しました。以下のように修正してください。
```
// 修正前
nvertices // 頂点の数
ncolors // 色値の数
nnormals // 法線ベクトルの数
nconnections // 接続情報の数
nsizes // サイズ値の数
nopacities // 不透明値の数
nnodes // ノードの数
ncells // セルの数
nnodesPerLine // 1行あたりのノードの数（kvs::StructuredVolumeObject）
nnodesPerSlice // 1スライスあたりのノードの数（kvs::StructuredVolumeObject）
setNNodes // ノードの数を設定する（kvs::UnstructuredVolumeObject）
setNCells // セルの数を設定する（kvs::UnstructuredVolumeObject）
```
```
// 修正後
numberOfVertices // 頂点の数
numberOfColors // 色値の数
numberOfNormals // 法線ベクトルの数
numberOfConnections // 接続情報の数
numberOfSizes // サイズ値の数
numberOfOpacities // 不透明値の数
numberOfNodes // ノードの数
numberOfCells // セルの数
numberOfNodesPerLine // 1行あたりのノードの数（kvs::StructuredVolumeObject）
numberOfNodesPerSlice // 1スライスあたりのノードの数（kvs::StructuredVolumeObject）
setNumberOfNodes // ノードの数を設定する（kvs::UnstructuredVolumeObject）
setNumberOfCells // セルの数を設定する（kvs::UnstructuredVolumeObject）
```

## ユーティリティクラス ##

### kvs::CommandLine ###
KVS 1.xでは、add\_help\_option, add\_option, add\_valueメソッドがprotected属性であったために、ユーザプログラム内で、kvs::CommandLineクラスを継承し、独自のコマンド引数処理クラスを定義する必要がありました。KVS 2.0では、これらのメソッドをpublic属性として定義することで、継承することなくコマンドライン引数の処理を行うことが可能となります。その他、いくつかのメソッド名の変更があります。

#### 修正点 ####
メソッド名を以下のように修正してください。kvs::CommandLineクラスを継承せずに利用する方法については、[こちら](guide_commandline_jp.md)を参考にしてください。
```
// 修正前
add_help_option
add_option
add_value

noptions
nvalues
```
```
// 修正後
addHelpOption
addOption
addValue

numberOfOptions
numberOfValues
```

### kvs::Directory ###
「ディレクトリが存在するかどうか」を確認するためのメソッド名を変更しました。

#### 修正点 ####
メソッド名を以下のように修正してください。
```
// 修正前
isExisted
```
```
// 修正後
exists
```

### kvs::File ###
「ファイルが存在するかどうか」を確認するためのメソッド名を変更しました。

#### 修正点 ####
メソッド名を以下のように修正してください。
```
// 修正前
isExisted
```
```
// 修正後
exists
```

### kvs::Endian ###
いくつかのメソッド名および引数の仕様を変更しました。

#### 修正点1 ####
Checkが何を確認するのかが不明瞭であったため、Checkを廃止し、具体的にビッグエンディアンまたはリトルエンディアンかどうかを確認するためのメソッド（IsBig, IsLittle）を追加しましたので、以下のように修正してください。

```
// 修正前
if ( kvs::Endian::Check() == kvs::Endian::Big )
    // ビッグエンディアンであった場合の処理
if ( kvs::Endian::Check() == kvs::Endian::Little )
    // リトルエンディアンであった場合の処理
```

```
// 修正後
if ( kvs::Endian::IsBig() )
    // ビッグエンディアンであった場合の処理
if ( kvs::Endian::IsLittle() )
    // リトルエンディアンであった場合の処理
```

#### 修正点2 ####
プログラミング規約に従いバイトスワップ対象となる数値を参照渡しではなくポインタ渡しに変更しましたので、以下のように修正してください。

```
// 修正前
kvs::Real32 value = 123.4f;
kvs::Endian::Swap( value );
```

```
// 修正後
kvs::Real32 value = 123.4f;
kvs::Endian::Swap( &value );
```


### kvs::ValueArray ###

#### 修正点1 ####
`shallowCopy( const ValueArray& )`が廃止されました。代わりに代入演算子を使用してください。

```
// 修正前
a.shallowCopy( b );
```

```
// 修正後
a = b;
```

#### 修正点2 ####
`deepCopy( const ValueArray& )`が廃止されました。代わりに`clone()`を使用してください。

```
// 修正前
a.deepCopy( b );
```

```
// 修正後
a = b.clone();
```

#### 修正点3 ####
`deepCopy( const T*, size_t )`が廃止されました。代わりに`assign()`を使用してください。

```
// 修正前
a.deepCopy( b, n );
```

```
// 修正後
a.assign( b, n );
```

#### 修正点4 ####
`isEmpty()`の名称が`empty()`に変更されました。

```
// 修正前
a.isEmpty();
```

```
// 修正後
a.empty();
```

#### 修正点5 ####
`swapByte()`が廃止されました。代わりに`Endian::Swap()`を使用してください。ただし数値型に限ります。

```
// 修正前
a.swapByte();
```

```
// 修正後
kvs::Endian::Swap( a.data(), a.size() );
```

#### 修正点6 ####
`deallocate()`の名称が`release()`に変更されました。

```
// 修正前
a.deallocate();
```

```
// 修正後
a.release();
```

#### 修正点7 ####
`allocate( size_t )`の返り値が`void`に変更されました。従来の返り値を使用したい場合は、`data()`を使用してください。なお、従来はメモリ確保に失敗した場合、`NULL`を返す場合がありましたが、KVS2.0では、`std::bad_alloc`が投げられます。

```
// 修正前
T* p = a.allocate( n );
```

```
// 修正後
a.allocate( n );
T* p = a.data();
```

#### 修正点8 ####
`pointer()`の名称が`data()`に変更されました。

```
// 修正前
a.pointer();
```

```
// 修正後
a.data();
```

#### 修正点9 ####
`counter()`が廃止されました。完全な代替の関数はありませんが、`counter()->value()`と同等の値は`use_count()`で取得できます。また、手動で参照カウントを増加、減少させる`counter()->increment(`)及び`counter()->decrement()`は、`sharedPointer()`で共有ポインタを取得し、それを別の場所で保持することで代替可能です。マルチスレッド時に、`counter()->key()`によって実現していたMutexによる排他処理は、`KVS_ENABLE_THREAD_SAFE`をコンパイル時にセットすることで自動で行われるようになりました。

### kvs::AnyValueArray ###
以前の`AnyValueArray`の使い方は危険なものが多かったので、直接配列の中身を操作するような関数を廃止し、`ValueArray`をラップすることに集中し、配列の操作は`ValueArray`に任せる形にしました。直接配列の中身を操作したい場合は、`asValueArray`で`ValueArray`型に変換してから使ってください。なお、`v = a.asValueArray<T>()`のようにして生成した`ValueArray v`は、`a`と配列を共有します。このため、`v`を書き換えると、`a`の内容も書き換わります。このことに注意して使ってください。

#### 修正点1 ####
コンストラクタ`AnyValueArray( const T*, size_t )`が廃止されました。以下のように修正してください。

```
// 修正前
AnyValueArray a( p, n );
```

```
// 修正後
AnyValueArray a( kvs::ValueArray( p, n ) );
```

#### 修正点2 ####
コンストラクタ`AnyValueArray( const std::vector<T>& )`が廃止されました。以下のように修正してください。

```
// 修正前
kvs::AnyValueArray a( v );
```

```
// 修正後
kvs::AnyValueArray a( kvs::ValueArray( v ) );
```

#### 修正点3 ####
`shallowCopy( const ValueArray<T>& )`が廃止されました。以下のように修正してください。

```
// 修正前
a.shallowCopy( b );
```

```
// 修正後
a = kvs::AnyValueArray( b );
```

#### 修正点4 ####
`shallowCopy( const AnyValueArray& )`が廃止されました。代わりに代入演算子を使用してください。

```
// 修正前
a.shallowCopy( b );
```

```
// 修正後
a = b;
```

#### 修正点5 ####
`deepCopy( const T*, size_t )`が廃止されました。以下のように修正してください。

```
// 修正前
a.deepCopy( p, n );
```

```
// 修正後
a = kvs::AnyValueArray( kvs::ValueArray( p, n ) );
```

#### 修正点6 ####
`isEmpty()`の名称が`empty()`に変更されました。

```
// 修正前
a.isEmpty();
```

```
// 修正後
a.empty();
```

#### 修正点7 ####
`swapByte()`が廃止されました。代わりに`Endian::Swap()`を使用してください。以下のように修正すれば、同等の機能が得られますが、基本的にエンディアン変換は`ValueArray`の段階で行なってください。

```
// 修正前
a.swapByte();
```

```
// 修正後

```

#### 修正点8 ####
`deallocate()`の名称が`release()`に変更されました。

```
// 修正前
a.deallocate();
```

```
// 修正後
a.release();
```

#### 修正点9 ####
`pointer()`の名称が`data()`に変更されました。

```
// 修正前
a.pointer();
```

```
// 修正後
a.data();
```

#### 修正点10 ####
`pointer<T>()`が廃止されました。以下のようにすれば、同等の機能が得られますが、基本的に`ValueArray`に変換してから`ValueArray.data()`を使うようにしてください。

```
// 修正前
a.pointer<T>();
```

```
// 修正後
static_cast<T*>( a.data() ); //非const版
static_cast<const T*>( a.data() ); //const版
```

#### 修正点11 ####
`counter()`が廃止されました。代替の関数はありませんが、`sharedPointer()`を使うことで、同等の機能を得ることができます。詳しくは`ValueArray.counter()`の修正を参照してください。