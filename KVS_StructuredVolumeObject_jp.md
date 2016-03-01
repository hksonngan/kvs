# 3.4 構造格子型ボリュームオブジェクト #
構造格子型ボリュームオブジェクトは、各辺が座標軸に平行な直方体またはそれを歪ませた形状として表現されます。また、隣接する格子間において、境界面を除く内部の節点を共有する格子の数は8であり、格子の稜線（エッジ）を共有する格子の数は4となります。

## 3.4.1 データ構造 ##
KVSでは、構造格子型ボリュームオブジェクトは以下のような情報から構成されています。

**格子タイプ**
> 格子の種類を表します。均一格子、直交格子または湾曲格子を指定することができます。

  * **均一格子（uniform grid）**　格子点が直交等間隔に並ぶ形状
  * **直交格子（rectilinear grid）**　各軸は直交であるが隣接する格子間隔が異なる形状
  * **湾曲格子（curvilinear grid）**　直交格子と同じ接続関係を保ちそれを歪ませた形状

**解像度**
> 各軸方向の分割数を表します。

**ベクトル長**
> 数値データのベクトル長を表します。スカラ値の場合、１となります。

**座標**
> 節点の位置を表します。3次元の場合、x,y,zの値を持ちます。x, y, z座標の順でそれぞれ昇順となるように並べられその順に通し番号（節点番号）が自動的に割り振られます。均一格子の節点座標は、各座標軸上での分割数（解像度）が分かれば計算することができるため、明示的に指定する必要はありません。直交格子は、各座標軸上での分割点座標を単純に組み合わせることで得られます。湾曲格子については、直交格子を歪ませた形状であるため、全節点座標を明示的に指定する必要があります。

**数値データ**
> 節点上に定義される物理量を表します。節点番号順に並べられ、（節点数）×（ベクトル長）の１次元配列として定義します。

## 3.4.2 kvs::StructuredVolumeObjectクラス ##
KVSでは、構造格子型ボリュームオブジェクトはkvs::StructuredVolumeObjectクラスとして実装されています。以下では、kvs::StructuredVolumeObjectクラスの主なメソッドについて説明します。

```
const kvs::ValueArray<kvs::Real32>& coords() const
```
**機能**<br>
点の座標値の配列を返す。ただし、均一格子の場合は空である。<br>
<br>
<b>戻り値</b><br>
32ビット実数型（kvs::Real32型）の座標値の配列クラス<br>
<br><br>

<pre><code>const kvs::AnyValueArray&amp; values() const<br>
</code></pre>
<b>機能</b><br>
数値データの配列を返す。<br>
<br>
<b>戻り値</b><br>
動的型（kvs::AnyValue型）の数値データの配列クラス<br>
<br><br>

<pre><code>size_t veclen() const<br>
</code></pre>
<b>機能</b><br>
数値データのベクトル長を返す。<br>
<br>
<b>戻り値</b><br>
数値データのベクトル長。スカラ値の場合、１を返す。<br>
<br><br>

<pre><code>const kvs::Vector3ui&amp; resolution() const<br>
</code></pre>
<b>機能</b><br>
各軸方向の解像度を返す。<br>
<br>
<b>戻り値</b><br>
各軸方向の解像度を表す３次元ベクトルクラス<br>
<br><br>

<pre><code>size_t numberOfNodes() const<br>
</code></pre>
<b>機能</b><br>
節点数を返す。<br>
<br>
<b>戻り値</b><br>
節点数<br>
<br><br>

<pre><code>GridType gridType() const<br>
</code></pre>
<b>機能</b><br>
格子の種類を返す。<br>
<br>
<b>戻り値</b><br>
以下のいずれかの値を返す。<br>
<ul><li>kvs::StructuredVolumeObject::Uniform ... 均一格子<br>
</li><li>kvs::StructuredVolumeObject::Rectilinear ... 直交格子<br>
</li><li>kvs::StructuredVolumeObject::Curvilinear ... 湾曲格子<br>
</li><li>kvs::StructuredVolumeObject::UnknownGridType ... その他<br>
<br></li></ul>

<pre><code>void setCoords( const kvs::ValueArray&lt;kvs::Real32&gt;&amp; coords )<br>
</code></pre>
<b>機能</b><br>
節点の座標値を設定する。均一格子の場合は、座標値を指定する必要はない。直交格子の場合は、各軸上での分割点の座標値を、x, y, zの順で並べた配列（x0, x1, …, xi, y0, y1, …. yj, z0, z1, …, zk）として指定する。湾曲格子の場合は、設定する座標値を、x, y, zを点数分並べた配列（x0, y0, z0, x1, y1, z1, …, xi, yi, zi）として指定する。<br>
<br>
<b>引数</b><br>
coords　節点の座標値の配列。指定する配列の型は32ビット実数型（kvs::Real32型）である。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void setValues( const kvs::AnyValueArray&amp; values )<br>
</code></pre>
<b>機能</b><br>
節点の数値データを設定する。節点番号順に、（節点数）×（ベクトル長）の長さの配列を指定する。<br>
<br>
<b>引数</b><br>
values　節点の数値データの配列。指定する配列の型は動的型（kvs::AnyValueArray型）である。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void setVeclen( const size_t veclen )<br>
</code></pre>
<b>機能</b><br>
数値データのベクトル長を設定する。<br>
<br>
<b>引数</b><br>
veclen　数値データのベクトル長<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void setResolution( const kvs::Vector3ui&amp; resolution )<br>
</code></pre>
<b>機能</b><br>
各軸方向の解像度を設定する。<br>
<br>
<b>引数</b><br>
resolution　各軸方向の解像度<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void setGridType( const GridType grid_type )<br>
</code></pre>
<b>機能</b><br>
格子の種類を設定する。<br>
<br>
<b>引数</b><br>
grid_type　格子の種類。以下のいずれかの値を指定する。<br>
<ul><li>kvs::StructuredVolumeObject::Uniform ... 均一格子<br>
</li><li>kvs::StructuredVolumeObject::Rectilinear ... 直交格子<br>
</li><li>kvs::StructuredVolumeObject::Curvilinear ... 湾曲格子<br>
</li><li>kvs::StructuredVolumeObject::UnknownGridType ... その他</li></ul>

<b>戻り値</b><br>
なし<br>
<br>

<h2>3.4.3 作成例</h2>
構造格子型ボリュームオブジェクトを作成し、それをいったんポリゴンデータに変換し描画するサンプルコードを以下に示します。例では、CreateStructuredVolumeObject関数で構造格子型ボリュームオブジェクトを生成しています。<br>
<br>
<pre><code>#include &lt;kvs/glut/Application&gt;<br>
#include &lt;kvs/glut/Screen&gt;<br>
#include &lt;kvs/StructuredVolumeObject&gt;<br>
#include &lt;kvs/ExternalFaces&gt;<br>
<br>
// 格子の解像度<br>
const size_t dimx = 3;<br>
const size_t dimy = 3;<br>
const size_t dimz = 3;<br>
<br>
// 数値データのベクトル長<br>
const size_t veclen = 1;<br>
<br>
// 数値データ<br>
kvs::UInt8 ValueArray[ dimx * dimy * dimz * veclen ] = {<br>
     0,  10,   0,<br>
    50, 255, 200,<br>
     0, 100,   0,<br>
<br>
    50,   0, 150,<br>
     0,   0,   0,<br>
   150,   0,  50,<br>
<br>
     0, 255, 0,<br>
    50,  10, 50,<br>
     0, 255, 0<br>
};<br>
<br>
// 構造格子型ボリュームオブジェクト（均一格子）を生成する関数<br>
kvs::StructuredVolumeObject* CreateStructuredVolumeObject()<br>
{<br>
    // KVSの動的型配列クラス（kvs::AnyValueArray）にセットする。<br>
    kvs::AnyValueArray values( ValueArray, sizeof( ValueArray ) );<br>
<br>
    // 構造格子型ボリュームオブジェクトを生成する。<br>
    kvs::StructuredVolumeObject* object = new kvs::StructuredVolumeObject();<br>
    object-&gt;setGridType( kvs::StructuredVolumeObject::Uniform );<br>
    object-&gt;setVeclen( veclen );<br>
    object-&gt;setResolution( kvs::Vector3ui( dimx, dimy, dimz ) );<br>
    object-&gt;setValues( values );<br>
<br>
    return object;<br>
}<br>
<br>
// メイン関数<br>
int main( int argc, char** argv )<br>
{<br>
    kvs::glut::Application app( argc, argv );<br>
<br>
    // 構造格子型ボリュームオブジェクト（均一格子）の生成<br>
    kvs::StructuredVolumeObject* volume = CreateStructuredVolumeObject();<br>
<br>
    // 境界面ポリゴンの抽出<br>
    // ※ボリュームデータをいったんポリゴンデータに変換する。<br>
    kvs::PolygonObject* object = new kvs::ExternalFaces( volume );<br>
<br>
    // ボリュームデータの削除<br>
    // ※ポリゴンデータに変換したため元データを削除する。<br>
    delete volume;<br>
<br>
    kvs::glut::Screen screen( &amp;app );<br>
    screen.setTitle( "Structured Volume Object" );<br>
    screen.registerObject( object );<br>
    screen.show();<br>
<br>
    return app.run();<br>
}<br>
</code></pre>