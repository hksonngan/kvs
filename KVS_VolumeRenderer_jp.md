# 4.4 ボリュームレンダラー #
ボリュームオブジェクトを描画する場合には、いったん幾何オブジェクトに変換してから描画する方法（間接法）と、直接画像データを生成する方法（直接法）があります。

間接法では、ボリュームオブジェクトの種類や目的に応じて幾何オブジェクトに変換します。たとえば、スカラ場のボリュームオブジェクトに対して等値面（ポリゴンオブジェクト）を抽出し描画する方法や、ベクトル場に対して流線（線分オブジェクト）を計算し描画する方法などがあります。

一方、直接法では、ボリュームオブジェクトから断片的な情報を抽出して描画する間接法とは異なり、ボリュームオブジェクトを半透明の雲のように表現することで内部構造を含めた全体的な特徴を表現することができます。一般に、ボリュームレンダリングという場合は、この直接法のことを指します。

ここでは、代表的なボリュームレンダリングの１つであるレイキャスティングレンダラーについて簡単に説明します。

## 4.4.1 レンダリング機能 ##
レイキャスティング法は、画素ごとに定義される視線に沿って輝度値方程式と呼ばれる積分方程式を解くことによって対応する輝度値（色）を計算し、画像データを生成する手法です。KVSでは、この手法をレイキャスティングレンダラーとして実装しており、以下のようのような機能を持っています。

**シェーディング**
> 視線上のサンプリング点上で計算されるスカラ勾配ベクトルをもとにしてシェーディング処理を行います。幾何オブジェクトと同様に、陰影を付けることでより立体感のある描画可能となります。また、ボリュームレンダラーでは、独自にシェーディング機能を実装しており、標準ではサポートされていないフォンシェーディングによる陰影処理が可能です。KVSでは、ランバートモデルによるシェーディングとフォンモデルによるシェーディングを選択することができます。

**伝達関数**
> ボリュームオブジェクトを描画するためには、格子上に定義される数値データを色データに変換する必要があります。このときに、利用されるものが伝達関数（transfer function）です。一般的に、伝達関数は、横軸に数値データ（スカラ値）をとり、縦軸に色および不透明度をとる関数として表現されます。この伝達関数を適切に設定することによって、特定領域の強調や分類といったことが可能となります。

**詳細度制御**
> ボリュームレンダリングでは、画素単位で輝度値方程式を計算する必要があり、計算コストの高い処理となるため、幾何オブジェクトの場合に比べ描画速度が低下し対話性が損なわれる可能性があります。それを防ぐために、詳細度（LOD,Level-Of-Detail）制御技術があります。たとえば、データを回転しているときには粗く描画することで対話性を高め、静止時には詳細に描画することで画質を高めて描画するような制御が行われます。

## 4.4.2 kvs::RayCastingRendererクラス ##
KVSでは、レイキャスティングレンダラーはkvs::RayCastingRendererクラスとして実装されています。ただし、現在は構造格子型ボリュームオブジェクト（均一格子）のみに対応しています。以下では、kvs::RayCastingRendererクラスの主なメソッドについて説明します。

```
void enableShading()
```
**機能**<br>
シェーディング処理を有効にする。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void disableShading()<br>
</code></pre>
<b>機能</b><br>
シェーディング処理を無効にする。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void enableLODControl( const size_t ray_width = 3 )<br>
</code></pre>
<b>機能</b><br>
詳細度制御を有効にする。<br>
<br>
<b>引数</b><br>
ray_width　視線の幅。初期値は３である。ray_width × ray_widthの領域を１単位（同一色）として描画する。この数値を大きくすることで回転時の描画速度は向上するが、画質が粗くなる。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void disableLODControl()<br>
</code></pre>
<b>機能</b><br>
詳細度制御を無効にする。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br>
<pre><code>template &lt;typename ShadingType&gt;<br>
void setShader( const ShadingType shader )<br>
</code></pre>
<b>機能</b><br>
シェーダーを設定する。<br>
<br>
<b>引数</b><br>
shader　シェーダー。ランバートシェーディング（<code>kvs::Shader::Lambert</code>）、フォンシェーディング（<code>kvs::Shader::Phong</code>）、ブリン・フォンシェーディング（<code>kvs::Shader::BlinnPhong</code>）を指定することができる。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void setTransferFunction( cont kvs::TransferFunction&amp; tfunc )<br>
</code></pre>
<b>機能</b><br>
伝達関数を設定する。<br>
<br>
<b>引数</b><br>
tfunc　伝達関数<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<h2>4.4.3 サンプルプログラム</h2>
kvs::HydrogenVolumeDataクラスを使って構造格子型ボリュームオブジェクト（均一格子）を作成し、それを描画するサンプルコードを以下に示します。<br>
<br>
<pre><code>#include &lt;kvs/glut/Application&gt;<br>
#include &lt;kvs/glut/Screen&gt;<br>
#include &lt;kvs/StructuredVolumeObject&gt;<br>
#include &lt;kvs/HydrogenVolumeData&gt;<br>
#include &lt;kvs/RayCastingRenderer&gt;<br>
#include &lt;kvs/TransferFunction&gt;<br>
<br>
<br>
// メイン関数<br>
int main( int argc, char** argv )<br>
{<br>
    kvs::glut::Application app( argc, argv );<br>
<br>
    // 構造格子型の水素分子データ（解像度: 32x32x32）の生成<br>
    kvs::Vector3ui resolution( 32, 32, 32 );<br>
    kvs::StructuredVolumeObject* object = new kvs::HydrogenVolumeData( resolution );<br>
<br>
    // レイキャスティングレンダラーの生成<br>
    kvs::RayCastingRenderer* renderer = new kvs::RayCastingRenderer();<br>
    renderer-&gt;enableShading();<br>
    renderer-&gt;enableLODControl( 5 );<br>
<br>
    // シェーダーの設定<br>
    // ＊ランバートシェーダーの場合      kvs::Shader::Lambert( ka, kd )<br>
    // ＊フォンシェーダーの場合          kvs::Shader::Phong( ka, kd, ks, n )<br>
    // ＊ブリン・フォンシェーダーの場合  kvs::Shader::BlinnPhong( ka, kd, ks, n )<br>
    float ka = 0.3;<br>
    float kd = 0.5;<br>
    float ks = 0.8;<br>
    float n  = 100;<br>
    renderer-&gt;setShader( kvs::Shader::Phong( ka, kd, ks, n ) );<br>
<br>
    // 伝達関数（256階調）の設定<br>
    kvs::TransferFunction tfunc( 256 );<br>
    renderer-&gt;setTransferFunction( tfunc );<br>
<br>
    kvs::glut::Screen screen( &amp;app );<br>
    screen.setTitle( "Create Ray-casting Renderer" );<br>
    screen.registerObject( object, renderer );<br>
    screen.show();<br>
<br>
    return app.run();<br>
}<br>
</code></pre>