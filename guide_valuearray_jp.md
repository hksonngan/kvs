# kvs::ValueArrayクラス #

|ヘッダファイル|`#include <kvs/ValueArray>`|
|:------|:--------------------------|
|クラス名   |`kvs::ValueArray<T>`       |

## 機能 ##
このクラスは、数値型の配列を表すクラスです。通常の配列と同じ働きをしますが、配列のサイズ（要素数）の管理に加えて、データの共有を実現することができます。配列のコピーという操作には、見かけ上複数の配列が生成されますが、実際には同じデータであるので、メモリ上でそのデータを共有するコピー（shallow copy）と、実際にメモリ上で同じデータを複数配置するコピー（deep copy）が考えられます。kvs::ValueArrayクラスを利用して、このような操作を簡単に実現することができます。

## 主なメソッド ##
このクラスの主なメソッドを説明します。他のメソッドの機能はだいたいSTLコンテナと同じです。

```
ValueArray( const size_t size )
```
size個の要素を持つ配列を新たに確保します。

```
ValueArray( const T* values, const size_t size )
```
`size`個の要素を持つ配列を新たに確保し、`values`が指す要素を先頭として、`size`個の要素で配列を初期化します。

```
ValueArray( const std::vector<T>& values )
```

```
template <typename InIter>
ValueArray( InIter first, InIter last )
```

```
void assign( const value_type* values, const size_t size )
```
要素を代入します。<br>
<code>v.assign( values, size )</code>
は<br>
<code>v = ValueArray( values, size )</code>
と等価です。<br>
<br>
<pre><code>template &lt;typename InIter&gt;<br>
void assign( InIter first, InIter last )<br>
</code></pre>
要素を代入します。<br>
<code>v.assign( first, last )</code>
は<br>
<code>v = ValueArray( first, last )</code>
と等価です。<br>
<br>
<pre><code>T&amp; operator []( const size_t index )<br>
const T&amp; operator []( const size_t index ) const<br>
</code></pre>
<code>index</code>番目の要素にアクセスします。<br>
<br>
<pre><code>size_t size() const<br>
</code></pre>
配列の要素数を返します。<br>
<br>
<pre><code>size_t byteSize() const<br>
</code></pre>
配列のメモリ上での大きさをバイト単位で返します。<br>
<br>
<pre><code>void swap( ValueArray&amp; other )<br>
</code></pre>
<code>other</code>と配列を入れ替えます。<br>
<br>
<pre><code>ValueArray clone() const<br>
</code></pre>
配列のdeep copyを返します。<br>
<br>
<pre><code>T&amp; at( const size_t index )<br>
const T&amp; at( const size_t index ) const<br>
</code></pre>

<pre><code>void allocate( const size_t size )<br>
</code></pre>
<code>size</code>個の要素を新たに確保します。<br>
<br>
<pre><code>void release()<br>
</code></pre>
配列を解放します。<br>

<pre><code>void fill( const T&amp; value )<br>
</code></pre>
配列の要素を全て<code>value</code>で埋めます。<br>
<br>
<pre><code>bool unique() const<br>
</code></pre>
配列が共有されていなければ<code>true</code>を返します。<br>
ただし、<code>empty() == true</code>の場合の返り値は不定です。<br>
<br>
<pre><code>void isolate()<br>
</code></pre>
配列の共有を切断します。<br>
配列を共有している他の<code>ValueArray</code>に影響を与えずに配列の内容を書き換えたい場合に使用します。<br>
<br>
<h2>サンプルプログラム</h2>