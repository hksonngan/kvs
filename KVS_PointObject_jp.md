# 3.1 点オブジェクト #
点オブジェクトは、幾何形状を構成する最も基本的な描画要素です。数学的には、点は大きさ・面積・長さを持たない無限に小さい要素として定義されていますが、コンピュータグラフィックスにおいては、通常、ディスプレイで表示可能な最小単位（ピクセル）が有限であるため、点は有限の大きさを持ちます。

## 3.1.1 データ構造 ##
KVSでは、点オブジェクトは以下のような情報から構成されています。

**座標**
> 点の位置を表します。3 次元の場合、x,y,zの値を持つ。複数の点を表す場合は、x,y,z値を点の数だけ並べて１次元配列として定義します。

**色（カラー）**
> 点の色を表します。一般的には、赤,緑,青の値（RGB値）を持ちます。それぞれの値は、256 階調の整数値で表現されることが多く、プログラム上ではunsigned char 型として定義されます。複数の点に対して個別に色を設定する場合、座標データと同様に、点の数だけRGB値を並べて１次元配列として定義します。

**法線ベクトル**
> 点の法線を表します。３次元の場合、x,y,zの各成分の値を持ちます。座標データと同様に、複数の点に対してベクトルのx,y,z成分を並べて指定します。法線ベクトルを指定しない場合、描画の際にシェーディング処理が無効となります。

**大きさ（サイズ）**
> 点の大きさを表します。大きさを指定しない場合は1となります。単位はピクセル（画素）です。

## 3.1.2 kvs::PointObjectクラス ##
KVSでは、点オブジェクトはkvs::PointObjectクラスとして実装されています。以下では、kvs::PointObjectクラスの主なメソッドについて説明します。

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
点のカラー値の配列を返す。<br>
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
点の大きさの配列を返す。<br>
<br>
<b>戻り値</b><br>
32ビット実数型の点の大きさの配列クラス<br>
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
カラー値の数。１の場合、すべての点が同一色であることを示す。<br>
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
サイズ値の数を返す。<br>
<br>
<b>戻り値</b><br>
サイズ値の数。１の場合、すべての点が同一サイズであることを示す。<br>
<br><br>

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
指定されたインデックス番号の点のカラー値を返す。<br>
<br>
<b>引数</b><br>
index　点のインデックス番号。<br>
<br>
<b>戻り値</b><br>
指定されたインデックス番号の点のカラー値（RGBカラークラス）<br>
<br><br>

<pre><code>const kvs::Vector3f normal( const size_t index ) const<br>
</code></pre>
<b>機能</b><br>
指定されたインデックス番号の点の法線ベクトルを返す。<br>
<br>
<b>引数</b><br>
index　点のインデックス番号。<br>
<br>
<b>戻り値</b><br>
指定されたインデックス番号の点の法線ベクトル（3次元ベクトルクラス）<br>
<br><br>

<pre><code>kvs::Real32 size( const size_t index ) const<br>
</code></pre>
<b>機能</b><br>
指定されたインデックス番号の点のサイズを返す。<br>
<br>
<b>引数</b><br>
index　点のインデックス番号。<br>
<br>
<b>戻り値</b><br>
指定されたインデックス番号の点のサイズ<br>
<br><br>

<pre><code>void setCoords( const kvs::ValueArray&lt;kvs::Real32&gt;&amp; coords )<br>
</code></pre>
<b>機能</b><br>
点の座標値を設定する。設定する座標値を、x, y, zを点数分並べた配列として指定する。<br>
<br>
<b>引数</b><br>
coords　座標値の配列。指定する配列の型は32ビット実数型である。<br>
<br><br>

<pre><code>void setColors( const kvs::ValueArray&lt;kvs::UInt8&gt;&amp; colors )<br>
</code></pre>
<b>機能</b><br>
点のカラー値を設定する。設定するカラー値を、R, G, Bを点数分並べた配列として指定する。<br>
<br>
<b>引数</b><br>
colors　カラー値の配列。指定する配列の型は8ビット符号なし整数型である。<br>
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
点のサイズを設定する。設定する点のサイズを、それを点数分並べた配列として指定する。<br>
<br>
<b>引数</b><br>
sizes　サイズ値の配列。指定する配列の型は32ビット実数型である。<br>
<br><br>

<h2>3.1.3 作成例</h2>
点オブジェクトを作成し、それを描画するサンプルコードを以下に示します。例では、CreatePointObject関数で点オブジェクトを生成しています。<br>
<br>
<pre><code>#include &lt;kvs/glut/Application&gt;<br>
#include &lt;kvs/glut/Screen&gt;<br>
#include &lt;kvs/PointObject&gt;<br>
<br>
// 点の数<br>
const size_t N = 4;<br>
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
// 点オブジェクトを生成する関数<br>
kvs::PointObject* CreatePointObject()<br>
{<br>
    // KVSの配列クラス（kvs::ValueArray）にセットする。<br>
    kvs::ValueArray&lt;kvs::Real32&gt; coords( CoordArray, N * 3 );<br>
    kvs::ValueArray&lt;kvs::UInt8&gt; colors( ColorArray, N * 3 );<br>
<br>
    // 点オブジェクトを生成する。<br>
    kvs::PointObject* object = new kvs::PointObject();<br>
    object-&gt;setCoords( coords );<br>
    object-&gt;setColors( colors );<br>
    object-&gt;setSize( 10 );<br>
<br>
    // 生成した点オブジェクトのポインタを返す。<br>
    return object;<br>
}<br>
<br>
// メイン関数<br>
int main( int argc, char** argv )<br>
{<br>
    kvs::glut::Application app( argc, argv );<br>
<br>
    // 点オブジェクトの生成<br>
    kvs::PointObject* object = CreatePointObject();<br>
<br>
    kvs::glut::Screen screen( &amp;app );<br>
    screen.setTitle( "Point Object" );<br>
    screen.registerObject( object );<br>
    screen.show();<br>
<br>
    return app.run();<br>
}<br>
</code></pre>