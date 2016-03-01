# 3.3 ポリゴンオブジェクト #
ポリゴンオブジェクトは、複数の稜線（エッジ）からなる平面上の多角形（ポリゴン）を組み合わせて表現されます。通常、ポリゴンオブジェクトを構成する多角形には、三角形や四角形が用いられます。

## 3.3.1 データ構造 ##
KVSでは、ポリゴンオブジェクトは以下のような情報から構成されています。

**ポリゴンタイプ**
> ポリゴンの種類を表します。KVSでは、ポリゴンを三角形または四角形で表現することができます。

  * **三角形（triangle）**　3つの頂点番号を1セットとして、指定された順に頂点を接続して三角形を表現します。
  * **四角形（quadrangle）**　4つの頂点番号を1セットとして、指定された順に頂点を接続して四角形を表現します。

**座標**
> ポリゴンを構成する点の座標を表します。点データと同様に、x, y, z値を並べて定義します。このとき、並べられた順に通し番号（頂点番号）が付けられます。

**色（カラー）**
> ポリゴンまたは点の色を表します。ポリゴンを構成する点に対して色を指定した場合、その指定された色から線形補間された色がポリゴンの色となります。

**法線ベクトル**
> ポリゴンまたは点の法線ベクトルを表します。ポリゴンまたは点に対して、ベクトルのx, y, z成分を並べて指定します。指定しない場合、シェーディング処理が無効となります。点を共有するポリゴンの法線ベクトルを平均することによって、点に対して法線ベクトルを定義することができ、ポリゴンの境界での不連続性が目立たず滑らかなポリゴンを描画することができます。

**接続情報**
> ポリゴンを構成する頂点番号を表します。線分オブジェクトと同様、座標値を設定する際に付与される通し番号を指定しなくてはいけません。

## 3.3.2 kvs::PolygonObjectクラス ##
KVSでは、ポリゴンオブジェクトはkvs::PolygonObjectクラスとして実装されています。以下では、kvs::PolygonObjectクラスの主なメソッドについて説明します。

```
const kvs::ValueArray<kvs::Real32>& coords()
```
**機能**<br>
点の座標値の配列を返す。<br>
<br>
<b>戻り値</b><br>
32ビット実数型の座標値の配列クラス<br>
<br><br>

<pre><code>const kvs::ValueArray&lt;kvs::UInt8&gt;&amp; colors()<br>
</code></pre>
<b>機能</b><br>
点またはポリゴンのカラー値の配列を返す。<br>
<br>
<b>戻り値</b><br>
8ビット符号なし整数型のカラー値の配列クラス<br>
<br><br>

<pre><code>const kvs::ValueArray&lt;kvs::Real32&gt;&amp; normals()<br>
</code></pre>
<b>機能</b><br>
点またはポリゴンの法線ベクトルの配列を返す。<br>
<br>
<b>戻り値</b><br>
32ビット実数型の法線ベクトルの配列クラス<br>
<br><br>

<pre><code>const kvs::ValueArray&lt;kvs::UInt32&gt;&amp; connections()<br>
</code></pre>
<b>機能</b><br>
接続情報の配列（頂点番号の配列）を返す。<br>
<br>
<b>戻り値</b><br>
32ビット符号なし整数型の接続情報の配列クラス<br>
<br><br>

<pre><code>size_t numberOfVertices()<br>
</code></pre>
<b>機能</b><br>
点の数を返す。<br>
<br>
<b>戻り値</b><br>
点の数<br>
<br><br>

<pre><code>size_t numberOfColors()<br>
</code></pre>
<b>機能</b><br>
カラー値の数を返す。<br>
<br>
<b>戻り値</b><br>
点またはポリゴンのカラー値の数。１の場合、すべてのポリゴンが同一色であることを示す。<br>
<br><br>

<pre><code>size_t numberOfNormals()<br>
</code></pre>
<b>機能</b><br>
法線ベクトルの数を返す。<br>
<br>
<b>戻り値</b><br>
点またはポリゴンの法線ベクトルの数<br>
<br><br>

<pre><code>size_t numberOfConnections()<br>
</code></pre>
<b>機能</b><br>
接続情報（頂点番号）の数を返す。<br>
<br>
<b>戻り値</b><br>
接続情報の数<br>
<br><br>

<pre><code>PolygonType polygonType() const<br>
</code></pre>
<b>機能</b><br>
ポリゴンの種類を返す。<br>
<br>
<b>戻り値</b><br>
以下のいずれかの値を返す。<br>
<ul><li>kvs::PolygonObject::Triangle ... 三角形<br>
</li><li>kvs::PolygonObject::Quadrangle ... 四角形<br>
</li><li>kvs::PolygonObject::Tri	 ... Triangleと同じ<br>
</li><li>kvs::PolygonObject::Quad ... Quadrangleと同じ<br>
</li><li>kvs::PolygonObject::UnknownPolygonType ... その他<br>
<br></li></ul>

<pre><code>ColorType colorType() const<br>
</code></pre>
<b>機能</b><br>
ポリゴンの色づけの種類を返す。<br>
<br>
<b>戻り値</b><br>
以下のいずれかの値を返す。<br>
<ul><li>kvs::PolygonObject::VertexColor ... 点ごとに色付け<br>
</li><li>kvs::PolygonObject::PolygonColor ... ポリゴンごとに色付け<br>
</li><li>kvs::PolygonObject::UnknownColorType ... その他<br>
<br></li></ul>

<pre><code>NormalType normalType() const<br>
</code></pre>
<b>機能</b><br>
法線ベクトルの種類を返す。<br>
<br>
<b>戻り値</b><br>
以下のいずれかの値を返す。<br>
<ul><li>kvs::PolygonObject::VertexNormal ... 点ごとに定義<br>
</li><li>kvs::PolygonObject::PolygonNormal ... ポリゴンごとに定義<br>
</li><li>kvs::PolygonObject::UnknownNormalType ... その他<br>
<br></li></ul>

<pre><code>const kvs::Vector3f coord( const size_t index ) const<br>
</code></pre>
<b>機能</b><br>
指定されたインデックス番号の点の座標値を返す。<br>
<br>
<b>引数</b><br>
index　点のインデックス番号。<br>
<br>
<b>戻り値</b><br>
指定されたインデックス番号の点の座標値（3次元ベクトルクラス）<br>
<br><br>

<pre><code>const kvs::RGBColor color( const size_t index ) cosnt<br>
</code></pre>
<b>機能</b><br>
指定されたインデックス番号の点またはポリゴンのカラー値を返す。<br>
<br>
<b>引数</b><br>
index　点またはポリゴンのインデックス番号。<br>
<br>
<b>戻り値</b><br>
ポリゴンオブジェクトの色付けの種類がPolygonColorの場合、指定されるインデックス番号のポリゴンのカラー値（RGBカラークラス）。VertexColorの場合、指定されるインデックス番号の点のカラー値。<br>
<br><br>

<pre><code>const kvs::Vector3f normal( const size_t index ) const<br>
</code></pre>
<b>機能</b><br>
指定されたインデックス番号の点またはポリゴンの法線ベクトルを返す。<br>
<br>
<b>引数</b><br>
index　点またはポリゴンのインデックス番号。<br>
<br>
<b>戻り値</b><br>
ポリゴンオブジェクトの法線ベクトルの種類がPolygonNormalの場合、指定されるインデックス番号のポリゴンの法線ベクトル（3次元ベクトルクラス）。VertexNormalの場合、指定されるインデックス番号の点の法線ベクトル。<br>
<br><br>

<pre><code>void setCoords( const kvs::ValueArray&lt;kvs::Real32&gt;&amp; coords )<br>
</code></pre>
<b>機能</b><br>
点の座標値を設定する。設定する座標値を、x, y, zを点数分並べた配列として指定する。<br>
<br>
<b>引数</b><br>
coords　点の座標値の配列。指定する配列の型は32ビット実数型である。<br>
<br><br>

<pre><code>void setColors( const kvs::ValueArray&lt;kvs::UInt8&gt;&amp; colors )<br>
</code></pre>
<b>機能</b><br>
点またはポリゴンのカラー値を設定する。設定するカラー値を、R, G, Bを点数分並べた配列として指定する。<br>
<br>
<b>引数</b><br>
colors　点またはポリゴンのカラー値の配列。指定する配列の型は8ビット符号なし整数型である。<br>
<br><br>

<pre><code>void setNormals( const kvs::ValueArray&lt;kvs::Real32&gt;&amp; normals )<br>
</code></pre>
<b>機能</b><br>
点またはポリゴンの法線ベクトルを設定する。設定する法線ベクトルを、x, y, zを点数分並べた配列として指定する。<br>
<br>
<b>引数</b><br>
normals　点またはポリゴンの法線ベクトルの配列。指定する配列の型は32ビット実数型である。<br>
<br><br>

<pre><code>void setConnections( const kvs::ValueArray&lt;kvs::UInt32&gt;&amp; connections )<br>
</code></pre>
<b>機能</b><br>
点の接続情報を設定する。<br>
<br>
<b>引数</b><br>
normals　接続情報の配列。指定する配列の型は32ビット符号なし整数型である。<br>
<br><br>

<pre><code>void setPolygonType( const PolygonType polygon_type )<br>
</code></pre>
<b>機能</b><br>
ポリゴンの種類を設定する。<br>
<br>
<b>引数</b><br>
polygon_type　ポリゴンの種類。以下のいずれかの値を指定する。<br>
<ul><li>kvs::PolygonObject::Triangle ... 三角形<br>
</li><li>kvs::PolygonObject::Quadrangle ... 四角形<br>
</li><li>kvs::PolygonObject::Tri ... Triangleと同じ<br>
</li><li>kvs::PolygonObject::Quad ... Quadrangleと同じ<br>
<br></li></ul>

<pre><code>void setColorType( const ColorType color_type )<br>
</code></pre>
<b>機能</b><br>
ポリゴンの色づけの種類を設定する。<br>
<br>
<b>引数</b><br>
color_type　ポリゴンの色づけの種類。以下のいずれかの値を指定する。<br>
<ul><li>kvs::PolygonObject::VertexColor ... 点ごとに色付け<br>
</li><li>kvs::PolygonObject::PolygonColor ... ポリゴンごとに色付け<br>
<br></li></ul>

<pre><code>void setNormalType( const NormalType normal_type )<br>
</code></pre>
<b>機能</b><br>
法線ベクトルの種類を設定する。<br>
<br>
<b>引数</b><br>
normal_type　法線ベクトルの種類。以下のいずれかの値を指定する。<br>
<ul><li>kvs::PolygonObject::VertexNormal ... 点ごとに定義<br>
</li><li>kvs::PolygonObject::PolygonNormal ... ポリゴンごとに定義<br>
<br></li></ul>

<h2>3.3.3 作成例</h2>
ポリゴンオブジェクトを作成し、それを描画するサンプルコードを以下に示します。例では、CreatePolygonObject関数でポリゴンオブジェクトを生成しています。<br>
<br>
<pre><code>#include &lt;kvs/glut/Application&gt;<br>
#include &lt;kvs/glut/Screen&gt;<br>
#include &lt;kvs/PolygonObject&gt;<br>
<br>
// 点の数<br>
const size_t N = 4;<br>
<br>
// ポリゴンの数<br>
const size_t P = 4;<br>
<br>
// 座標値配列の定義<br>
kvs::Real32 CoordArray[ N * 3 ] = {<br>
    1.0, 0.0, 2.0,  // 点0の座標 (1.0, 0.0, 2.0)<br>
    2.0, 0.0, 2.0,  // 点1の座標 (2.0, 0.0, 2.0)<br>
    1.5, 0.8, 1.7,  // 点2の座標 (1.5, 0.8, 1.7)<br>
    1.5, 0.0, 1.1   // 点3の座標 (1.5, 0.0, 1.1)<br>
};<br>
<br>
// カラー値配列の定義<br>
kvs::UInt8 ColorArray[ N * 3 ] = {<br>
    255,   0,   0,  // 点0の色 赤(255,   0,   0)<br>
      0, 255,   0,  // 点1の色 緑(  0, 255,   0)<br>
      0,   0, 255,  // 点2の色 青(  0,   0, 255)<br>
    255, 255,   0   // 点3の色 黄(255, 255,   0)<br>
};<br>
<br>
// 法線ベクトル配列の定義<br>
kvs::Real32 NormalArray[ N * 3 ] = {<br>
     0.00,  0.3,  0.8,  // 点0に対する法線ベクトル<br>
     0.00, -0.9,  0.0,  // 点1に対する法線ベクトル<br>
     0.72,  0.3, -0.4,  // 点2に対する法線ベクトル<br>
    -0.72,  0.3, -0.4   // 点3に対する法線ベクトル<br>
};<br>
<br>
// 接続情報配列の定義<br>
kvs::UInt32 ConnectionArray[ P * 3 ] = {<br>
    0, 1, 2,  // 点0, 1, 2を接続<br>
    0, 3, 1,  // 点0, 3, 1を接続<br>
    1, 3, 2,  // 点0, 3, 2を接続<br>
    0, 2, 3   // 点0, 2, 3を接続<br>
};<br>
<br>
// ポリゴンオブジェクトを生成する関数<br>
kvs::PolygonObject* CreatePolygonObject()<br>
{<br>
    // KVSの配列クラス（kvs::ValueArray）にセットする。<br>
    kvs::ValueArray&lt;kvs::Real32&gt; coords( CoordArray, N * 3 );<br>
    kvs::ValueArray&lt;kvs::UInt8&gt; colors( ColorArray, N * 3 );<br>
    kvs::ValueArray&lt;kvs::Real32&gt; normals( NormalArray, N * 3 );<br>
    kvs::ValueArray&lt;kvs::UInt32&gt; connections( ConnectionArray, P * 3 );<br>
<br>
    // ポリゴンオブジェクトを生成する。<br>
    kvs::PolygonObject* object = new kvs::PolygonObject();<br>
    object-&gt;setCoords( coords );<br>
    object-&gt;setColors( colors );<br>
    object-&gt;setNormals( normals );<br>
    object-&gt;setConnections( connections );<br>
    object-&gt;setPolygonType( kvs::PolygonObject::Triangle );<br>
    object-&gt;setColorType( kvs::PolygonObject::VertexColor );<br>
    object-&gt;setNormalType( kvs::PolygonObject::VertexNormal );<br>
<br>
    // 生成したポリゴンオブジェクトのポインタを返す。<br>
    return object;<br>
}<br>
<br>
// メイン関数<br>
int main( int argc, char** argv )<br>
{<br>
    kvs::glut::Application app( argc, argv );<br>
<br>
    // ポリゴンオブジェクトの生成<br>
    kvs::PolygonObject* object = CreatePolygonObject();<br>
<br>
    kvs::glut::Screen screen( &amp;app );<br>
    screen.setTitle( "Polygon Object" );<br>
    screen.registerObject( object );<br>
    screen.show();<br>
<br>
    return app.run();<br>
}<br>
</code></pre>