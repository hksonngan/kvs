# 3.2 線分オブジェクト #
線分オブジェクトは、点を接続することによって表現することが可能なため、 先に説明した点オブジェクトの情報に加え、点の接続情報を持ちます。

## 3.2.1 データ構造 ##
KVSでは、線分オブジェクトは以下のような情報から構成されています。

**線分タイプ**
> 線分の種類を表します。KVSでは、線分データは、接続情報の指定方法により以下の4種類の線分を表現できます。

  * **線分（strip）**　頂点番号を指定しない場合、頂点を順番に接続して折れ線を表現します。

  * **一本線（uniline）**　通る頂点のみを指定し、指定された点を順に接続して折れ線を表現します。

  * **複数線（polyline）**　始点と終点を複数指定することで、複数の折れ線を表現します。始点と終点の間にある頂点を順に接続します。

  * **分割線（segment line）**　始点と終点を複数指定することで、複数の直線を表現します。始点と終点を直線的に接続します。

**座標**
> 線分を構成する点の座標を表します。点データと同様に、x, y, z値を並べて定義します。このとき、並べられた順に通し番号（頂点番号）が付けられます。

**色（カラー）**
> 線分または点の色を表します。線分を構成する点に対して色を指定した場合、その指定された色から線形補間された色が線分の色となります。

**法線ベクトル**
> 頂点の法線を表します。線分を構成する頂点に対して、ベクトルのx, y, z成分を並べて指定します。指定しない場合、シェーディング処理が無効となります。

**太さ（サイズ）**
> 線分の太さを表します。太さを指定しない場合は1となります。単位はピクセル（画素）です。

**接続情報**
> 線分を構成する頂点番号を表します。このとき、座標値を設定する際に付与される通し番号を適切に指定しなくてはいけません。

## 3.2.2 kvs::LineObjectクラス ##
KVSでは、線分オブジェクトはkvs::LineObjectクラスとして実装されています。以下では、kvs::LineObjectクラスの主なメソッドについて説明します。

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
点または線分のカラー値の配列を返す。<br>
<br>
<b>戻り値</b><br>
8ビット符号なし整数型のカラー値の配列クラス<br>
<br><br>

<pre><code>const kvs::ValueArray&lt;kvs::Real32&gt;&amp; normals()<br>
</code></pre>
<b>機能</b><br>
点の法線ベクトルの配列を返す。<br>
<br>
<b>戻り値</b><br>
32ビット実数型の法線ベクトルの配列クラス<br>
<br><br>

<pre><code>const kvs::ValueArray&lt;kvs::Real32&gt;&amp; sizes()<br>
</code></pre>
<b>機能</b><br>
線分の太さの配列を返す。<br>
<br>
<b>戻り値</b><br>
32ビット実数型の線の太さの配列クラス<br>
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
点または線分のカラー値の数。１の場合、すべての線分が同一色であることを示す。<br>
<br><br>

<pre><code>size_t numberOfNormals()<br>
</code></pre>
<b>機能</b><br>
法線ベクトルの数を返す。<br>
<br>
<b>戻り値</b><br>
法線ベクトルの数<br>
<br><br>

<pre><code>size_t numberOfSizes()<br>
</code></pre>
<b>機能</b><br>
線分のサイズ値の数を返す。<br>
<br>
<b>戻り値</b><br>
線分のサイズ値の数。１の場合、すべての線分が同一サイズであることを示す。<br>
<br><br>

<pre><code>size_t numberOfConnections()<br>
</code></pre>
<b>機能</b><br>
接続情報（頂点番号）の数を返す。<br>
<br>
<b>戻り値</b><br>
接続情報の数<br>
<br><br>

<pre><code>LineType lineType() const<br>
</code></pre>
<b>機能</b><br>
線分の種類を返す。<br>
<br>
<b>戻り値</b><br>
以下のいずれかの値を返す。<br>
<ul><li>kvs::LineObject::Strip ... 線分<br>
</li><li>kvs::LineObject::Uniline ... 一本線<br>
</li><li>kvs::LineObject::Polyline ... 複数線<br>
</li><li>kvs::LineObject::Segment ... 分割線<br>
</li><li>kvs::LineObject::UnknownLineType ... その他<br>
<br></li></ul>

<pre><code>ColorType colorType() const<br>
</code></pre>
<b>機能</b><br>
線分の色づけの種類を返す。<br>
<br>
<b>戻り値</b><br>
以下のいずれかの値を返す。<br>
<ul><li>kvs::LineObject::VertexColor ... 点ごとに色付け<br>
</li><li>kvs::LineObject::LineColor ... 線分ごとに色付け<br>
</li><li>kvs::LineObject::UnknownColorType ... その他<br>
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
指定されたインデックス番号の線分または点のカラー値を返す。<br>
<br>
<b>引数</b><br>
index　線分または点のインデックス番号。<br>
<br>
<b>戻り値</b><br>
格納されている線分オブジェクトの色付けの種類がLineColorの場合、指定されるインデックス番号の線分のカラー値（RGBカラークラス）。VertexColorの場合、指定されるインデックス番号の点のカラー値。<br>
<br><br>

<pre><code>const kvs::Vector3f normal( const size_t index ) const<br>
</code></pre>
<b>機能</b><br>
指定されたインデックス番号の点の法線ベクトルを返す。<br>
<br>
<b>引数</b><br>
index　点のインデックス番号。<br>
<br>
<b>戻り値</b>
指定されたインデックス番号の点の法線ベクトル（3次元ベクトルクラス）<br>
<br><br>

<pre><code>kvs::Real32 size( const size_t index ) const<br>
</code></pre>
<b>機能</b><br>
指定されたインデックス番号の線分のサイズを返す。<br>
<br>
<b>引数</b><br>
index　線分のインデックス番号。<br>
<br>
<b>戻り値</b><br>
指定されたインデックス番号の線分のサイズ<br>
<br><br>

<pre><code>const kvs::Vector2ui connection( const size_t index ) const<br>
</code></pre>
<b>機能</b><br>
指定されたインデックス番号の線分を構成する頂点番号を返す。<br>
<br>
<b>引数</b><br>
index　線分のインデックス番号。<br>
<br>
<b>戻り値</b><br>
指定されたインデックス番号の線分を構成する頂点番号（2次元ベクトルクラス）<br>
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
線分または点のカラー値を設定する。設定するカラー値を、R, G, Bを点数分並べた配列として指定する。<br>
<br>
<b>引数</b><br>
colors　線分または点のカラー値の配列。指定する配列の型は8ビット符号なし整数型である。<br>
<br><br>

<pre><code>void setNormals( const kvs::ValueArray&lt;kvs::Real32&gt;&amp; normals )<br>
</code></pre>
<b>機能</b><br>
点の法線ベクトルを設定する。設定する法線ベクトルを、x, y, zを点数分並べた配列として指定する。<br>
<br>
<b>引数</b><br>
normals　法線ベクトルの配列。指定する配列の型は32ビット実数型である。<br>
<br><br>

<pre><code>void setSizes( const kvs::ValueArray&lt;kvs::Real32&gt;&amp; sizes )<br>
</code></pre>
<b>機能</b><br>
点のサイズを設定する。設定するサイズ値を、それを点数分並べた配列として指定する。<br>
<br>
<b>引数</b><br>
sizes　点のサイズ値の配列。指定する配列の型はfloat型である。<br>
<br><br>

<pre><code>void setConnections( const kvs::ValueArray&lt;kvs::UInt32&gt;&amp; connections )<br>
</code></pre>
<b>機能</b><br>
点の接続情報を設定する。<br>
<br>
<b>引数</b><br>
normals　接続情報の配列。指定する配列の型は32ビット符号なし整数型である。<br>
<br><br>

<pre><code>void setLineType( const LineType line_type )<br>
</code></pre>
<b>機能</b><br>
線分の種類を設定する。<br>
<br>
<b>引数</b><br>
line_type　線分の種類。以下のいずれかの値を指定する。<br>
<ul><li>kvs::LineObject::Strip ... 線分<br>
</li><li>kvs::LineObject::Uniline ... 一本線<br>
</li><li>kvs::LineObject::Polyline ... 複数線<br>
</li><li>kvs::LineObject::Segment ... 分割線<br>
<br></li></ul>

<pre><code>void setColorType( const ColorType color_type )<br>
</code></pre>
<b>機能</b><br>
線分の色づけの種類を設定する。<br>
<br>
<b>引数</b><br>
color_type　線分の色づけの種類。以下のいずれかの値を指定する。<br>
<ul><li>kvs::LineObject::VertexColor ... 点ごとに色付け<br>
</li><li>kvs::LineObject::LineColor ... 線分ごとに色付け<br>
<br></li></ul>

<h2>3.2.3 作成例</h2>
線分オブジェクトを作成し、それを描画するサンプルコードを以下に示します。例では、CreateLineObject関数で線分オブジェクトを生成しています。<br>
<br>
<pre><code>#include &lt;kvs/glut/Application&gt;<br>
#include &lt;kvs/glut/Screen&gt;<br>
#include &lt;kvs/LineObject&gt;<br>
<br>
// 点の数<br>
const size_t N = 4;<br>
<br>
// 線分の数<br>
const size_t L = 6;<br>
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
// 接続情報配列の定義<br>
kvs::UInt32 ConnectionArray[ L * 2 ] = {<br>
    0, 1,  // 点0と点1を接続<br>
    1, 2,  // 点1と点2を接続<br>
    2, 0,  // 点2と点0を接続<br>
    3, 0,  // 点3と点0を接続<br>
    3, 1,  // 点3と点1を接続<br>
    3, 2   // 点3と点2を接続<br>
};<br>
<br>
// 線分オブジェクトを生成する関数<br>
kvs::LineObject* CreateLineObject()<br>
{<br>
    // KVSの配列クラス（kvs::ValueArray）にセットする。<br>
    kvs::ValueArray&lt;kvs::Real32&gt; coords( CoordArray, N * 3 );<br>
    kvs::ValueArray&lt;kvs::UInt8&gt; colors( ColorArray, N * 3 );<br>
    kvs::ValueArray&lt;kvs::UInt32&gt; connections( ConnectionArray, L * 2 );<br>
<br>
    // 線分オブジェクトを生成する。<br>
    kvs::LineObject* object = new kvs::LineObject();<br>
    object-&gt;setCoords( coords );<br>
    object-&gt;setColors( colors );<br>
    object-&gt;setConnections( connections );<br>
    object-&gt;setSize( 10 );<br>
    object-&gt;setLineType( kvs::LineObject::Segment );<br>
    object-&gt;setColorType( kvs::LineObject::VertexColor );<br>
<br>
    // 生成した線分オブジェクトのポインタを返す。<br>
    return object;<br>
}<br>
<br>
// メイン関数<br>
int main( int argc, char** argv )<br>
{<br>
    kvs::glut::Application app( argc, argv );<br>
<br>
    // 線分オブジェクトの生成<br>
    kvs::LineObject* object = CreateLineObject();<br>
<br>
    kvs::glut::Screen screen( &amp;app );<br>
    screen.setTitle( "Line Object" );<br>
    screen.registerObject( object );<br>
    screen.show();<br>
<br>
    return app.run();<br>
}<br>
</code></pre>