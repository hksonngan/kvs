# 3.5 非構造格子型ボリュームオブジェクト #
非構造格子型ボリュームオブジェクトは、隣接する格子間の関係が規則的でなく、明示的な節点番号リストおよび節点の座標データの両方を持つ必要があります。多くの場合、節点番号のリストを使って格子を表現します。3次元空間を構成する格子の形状は任意であるため、対象となる3次元空間を格子分割する上での自由度が高い点が長所です。その代わり、格子形状の種類が多いという点で、構造格子型ボリュームオブジェクトよりも、格子内部の任意点における数値データ値の補間計算に時間がかかるという点が短所となります。

## 3.5.1 データ構造 ##
KVSでは、非構造格子型ボリュームオブジェクトは以下のような情報から構成されています。

**要素タイプ**
> 要素の種類を表します。KVSでは、四面体1次要素、四面体2次要素、六面体1次要素、六面体2次要素、ピラミッド要素を指定することができます。

  * **四面体1次要素（tetrahedra）**　四面体の頂点に数値データが定義されています。
  * **四面体2次要素（quadratic tetrahedra）**　四面体の頂点および稜線上に数値データが定義されています。
  * **六面体１次要素（hexahedra）**　六面体の頂点に数値データが定義されています。
  * **六面体2次要素（quadratic hexahedra）**　六面体の頂点および稜線上に数値データが定義されています。
  * **ピラミッド要素（pyramid）**　ピラミッド形状の頂点に数値データが定義されています。

**要素数**
> 要素の個数を表します。

**節点数**
> 節点の個数を表します。

**ベクトル長**
> 数値データのベクトル長を表します。スカラ値の場合、１となります。

**座標**
> 節点の位置を表します。3次元の場合、x,y,zの値を持ちます。このとき、並べられた順に通し番号（節点番号）が付けられます。

**数値データ**
> 節点上に定義される物理量を表します。節点番号順に並べられ、（節点数）×（ベクトル長）の１次元配列として定義します。

**接続情報**
> 要素を構成する節点番号を表します。要素タイプに応じて、節点番号を順に指定しなくてはいけません。

## 3.5.2 kvs::UnstructuredVolumeObjectクラス ##
KVSでは、非構造格子型ボリュームオブジェクトはkvs::UnstructuredVolumeObjectクラスとして実装されています。以下では、kvs::UnstructuredVolumeObjectクラスの主なメソッドについて説明します。

```
const kvs::ValueArray<kvs::Real32>& coords() const
```
**機能**<br>
節点の座標値の配列を返す。<br>
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

<pre><code>const kvs::ValueArray&lt;kvs::UInt32&gt;&amp; connections() const<br>
</code></pre>
<b>機能</b><br>
接続情報の配列（節点番号の配列）を返す。<br>
<br>
<b>戻り値</b><br>
32ビット符号なし整数型（kvs::UInt32型）の接続情報の配列クラス<br>
<br><br>

<pre><code>size_t veclen() const<br>
</code></pre>
<b>機能</b><br>
数値データのベクトル長を返す。<br>
<br>
<b>戻り値</b><br>
数値データのベクトル長。スカラ値の場合、１を返す。<br>
<br><br>

<pre><code>size_t numberOfNodes() const<br>
</code></pre>
<b>機能</b><br>
節点数を返す。<br>
<br>
<b>戻り値</b><br>
節点数<br>
<br>
<pre><code>size_t numberOfCells() const<br>
</code></pre>
<b>機能</b><br>
要素数を返す。<br>
<br>
<b>戻り値</b><br>
要素数<br>
<br><br>

<pre><code>CellType cellType() const<br>
</code></pre>
<b>機能</b><br>
要素の種類を返す。<br>
<br>
<b>戻り値</b><br>
以下のいずれかの値を返す。<br>
<ul><li>kvs::UnstructuredVolumeObject::Tetrahedra ... 四面体１次要素<br>
</li><li>kvs::UnstructuredVolumeObject::Hexahedra	 ... 六面体１次要素<br>
</li><li>kvs::UnstructuredVolumeObject::QuadraticTetrahedra ... 四面体２次要素<br>
</li><li>kvs::UnstructuredVolumeObject::QuadraticHexahedra ... 六面体２次要素<br>
</li><li>kvs::UnstructuredVolumeObject::Pyramid ... ピラミッド要素<br>
</li><li>kvs::UnstructuredVolumeObject::Point ... 点要素<br>
</li><li>kvs::UnstructuredVolumeObject::UnknownCellType ... その他<br>
<br></li></ul>

<pre><code>void setCoords( const kvs::ValueArray&lt;kvs::Real32&gt;&amp; coords )<br>
</code></pre>
<b>機能</b><br>
節点の座標値を設定する。設定する座標値を、x, y, zを点数分並べた配列（x0, y0, z0, x1, y1, z1, …, xi, yi, zi）として指定する。<br>
<br>
<b>引数</b><br>
coords　節点の座標値の配列。指定する配列の型は32ビット実数型（kvs::Real32型）である。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br>
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

<pre><code>void setConnections( const kvs::ValueArray&lt;kvs::UInt32&gt;&amp; connections )<br>
</code></pre>
<b>機能</b><br>
節点の接続情報を設定する。<br>
<br>
<b>引数</b><br>
normals　接続情報の配列。指定する配列の型は32ビット符号なし整数型（kvs::UInt32型）である。<br>
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

<pre><code>void setNumberOfNodes( const size_t nnodes )<br>
</code></pre>
<b>機能</b><br>
節点数を設定する。<br>
<br>
<b>引数</b><br>
nnodes　節点数<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void setNumberOfCells( const size_t ncells )<br>
</code></pre>
<b>機能</b><br>
要素数を設定する。<br>
<br>
<b>引数</b><br>
ncells　要素数<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void setCellType( const CellType cell_type )<br>
</code></pre>
<b>機能</b><br>
要素の種類を設定する。<br>
<br>
<b>引数</b><br>
cell_type　要素の種類。以下のいずれかの値を指定する。<br>
<ul><li>kvs::UnstructuredVolumeObject::Tetrahedra ... 四面体１次要素<br>
</li><li>kvs::UnstructuredVolumeObject::Hexahedra ... 六面体１次要素<br>
</li><li>kvs::UnstructuredVolumeObject::QuadraticTetrahedra ... 四面体２次要素<br>
</li><li>kvs::UnstructuredVolumeObject::QuadraticHexahedra ... 六面体２次要素<br>
</li><li>kvs::UnstructuredVolumeObject::Pyramid ... ピラミッド要素<br>
</li><li>kvs::UnstructuredVolumeObject::Point ... 点要素<br>
</li><li>kvs::UnstructuredVolumeObject::UnknownCellType ... その他</li></ul>

<b>戻り値</b><br>
なし<br>
<br><br>

<h2>3.5.3 作成例</h2>
非構造格子型ボリュームオブジェクトを作成し、それをいったんポリゴンデータに変換し描画するサンプルコードを以下に示します。例では、CreateUnstructuredVolumeObject関数で非構造格子型ボリュームオブジェクトを生成しています。<br>
<br>
<pre><code>#include &lt;kvs/glut/Application&gt;<br>
#include &lt;kvs/glut/Screen&gt;<br>
#include &lt;kvs/UnstructuredVolumeObject&gt;<br>
#include &lt;kvs/ExternalFaces&gt;<br>
<br>
// 節点数と要素数<br>
const size_t nnodes = 7;<br>
const size_t ncells = 5;<br>
<br>
// 数値データのベクトル長<br>
const size_t veclen = 1;<br>
<br>
// 座標値配列の定義<br>
kvs::Real32 CoordArray[ nnodes * 3 ] = {<br>
    0.0,  7.0,  7.0,  // 点0の座標<br>
    5.0, 14.0,  7.0,  // 点1の座標<br>
    9.0,  7.0,  7.0,  // 点2の座標<br>
    4.0,  9.0, 14.0,  // 点3の座標<br>
    4.0,  9.0,  0.0,  // 点4の座標<br>
    5.0,  4.0,  4.0,  // 点5の座標<br>
    4.0,  0.0,  9.0   // 点6の座標<br>
};<br>
<br>
// 数値データ<br>
kvs::Real32 ValueArray[ nnodes * veclen ] = {<br>
    0.8, // 点0の数値データ<br>
    0.3, // 点1の数値データ<br>
    0.4, // 点2の数値データ<br>
    0.4, // 点3の数値データ<br>
    0.2, // 点4の数値データ<br>
    0.5, // 点5の数値データ<br>
    0.3  // 点6の数値データ<br>
};<br>
<br>
// 接続情報配列の定義<br>
kvs::UInt32 ConnectionArray[ ncells * 4 ] = {<br>
    0, 1, 2, 3, // 点0, 1, 2, 3を接続（四面体0）<br>
    0, 1, 2, 4, // 点0, 1, 2, 4を接続（四面体1）<br>
    0, 2, 4, 5, // 点0, 2, 4, 5を接続（四面体2）<br>
    0, 2, 5, 6, // 点0, 2, 5, 6を接続（四面体3）<br>
    0, 2, 3, 6  // 点0, 2, 3, 6を接続（四面体4）<br>
};<br>
<br>
// 非構造格子型ボリュームオブジェクト（四面体１次要素）を生成する関数<br>
kvs::UnstructuredVolumeObject* CreateUnstructuredVolumeObject()<br>
{<br>
    // KVSの配列クラス（kvs::ValueArray）および動的型配列クラス（kvs::AnyValueArray）にセットする。<br>
    kvs::ValueArray&lt;kvs::Real32&gt; coords( CoordArray, sizeof( CoordArray ) / sizeof( kvs::Real32)  );<br>
    kvs::ValueArray&lt;kvs::UInt32&gt; connections( ConnectionArray, sizeof( ConnectionArray ) / sizeof( kvs::UInt32) );<br>
    kvs::ValueArray&lt;kvs::Real32&gt; values( ValueArray, sizeof( ValueArray ) / sizeof( kvs::Real32) );<br>
<br>
    // 非構造格子型ボリュームオブジェクトを生成する。<br>
    kvs::UnstructuredVolumeObject* object = new kvs::UnstructuredVolumeObject();<br>
    object-&gt;setCellType( kvs::UnstructuredVolumeObject::Tetrahedra );<br>
    object-&gt;setVeclen( veclen );<br>
    object-&gt;setNumberOfNodes( nnodes );<br>
    object-&gt;setNumberOfCells( ncells );<br>
    object-&gt;setCoords( coords );<br>
    object-&gt;setConnections( connections );<br>
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
    // 非構造格子型ボリュームオブジェクト（四面体１次要素）の生成<br>
    kvs::UnstructuredVolumeObject* volume = CreateUnstructuredVolumeObject();<br>
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
    screen.setTitle( "Unstructured Volume Object" );<br>
    screen.registerObject( object );<br>
    screen.show();<br>
<br>
    return app.run();<br>
}<br>
</code></pre>