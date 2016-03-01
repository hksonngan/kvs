# 4.1 点レンダラー #
点レンダラーは、点オブジェクトを描画するためのレンダラーです。点オブジェクトに格納されている座標データや色データなどの情報をもとにして、OpenGLのGL\_POINTSを使って点を描画します。点のサイズを指定した場合には、指定するサイズ（単位はピクセル）の点が正方形として描画されます。

## 4.1.1 レンダリング機能 ##
KVSでは、点レンダラーは以下のようのような機能を持っています。

**シェーディング**
> 点に設定される法線ベクトルをもとに、光源位置を考慮して陰影処理（シェーディング処理）を行うことで、明暗のコントラストが付き立体感の高い描画が可能です。

**アンチエイリアシング**
> 描画される点の輪郭を滑らかに描画することで、ジャギー（jaggy）の発生を軽減し高品位な描画を行うことが可能です。

**両面ライティング**
> 照明効果を有効にしている際、通常、点は法線ベクトルと正対する向き（表面）にシェーディング処理が行われますが、その反対側の面（裏面）には処理が行われません。両面ライティングを行うことで、裏面に対してもシェーディング処理が実行されます。

## 4.1.2 kvs::PointRendererクラス ##
KVSでは、点レンダラーはkvs::PointRendererクラスとして実装されています。以下では、kvs::PointRendererクラスの主なメソッドについて説明します。

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

<pre><code>void enableAntiAliasing( const bool multisample = false )<br>
</code></pre>
<b>機能</b><br>
アンチエイリアシング処理を有効にする。<br>
<br>
<b>引数</b><br>
multisample　マルチサンプリングのオン・オフ。指定しない場合オフ。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void disableAntiAliasing()<br>
</code></pre>
<b>機能</b><br>
アンチエイリアシング処理を無効にする。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void enableTwoSideLighting()<br>
</code></pre>
<b>機能</b><br>
両面ライティング処理を有効にする。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<pre><code>void disableTwoSideLighting()<br>
</code></pre>
<b>機能</b><br>
両面ライティング処理を無効にする。<br>
<br>
<b>戻り値</b><br>
なし<br>
<br><br>

<h2>4.1.3 サンプルプログラム</h2>

点オブジェクトのサンプルプログラムで示したCreatePointObject関数を利用してオブジェクトを作成し、それを描画するサンプルコードを以下に示します。<br>
<br>
<pre><code>#include &lt;kvs/glut/Application&gt;<br>
#include &lt;kvs/glut/Screen&gt;<br>
#include &lt;kvs/PointObject&gt;<br>
#include &lt;kvs/PointRenderer&gt;<br>
<br>
// メイン関数<br>
int main( int argc, char** argv )<br>
{<br>
    kvs::glut:::Application app( argc, argv );<br>
<br>
    // 点オブジェクトの生成<br>
    kvs::PointObject* object = CreatePointObject();<br>
<br>
    // 点レンダラーの生成<br>
    kvs::PointRenderer* renderer = new kvs::PointRenderer();<br>
    renderer-&gt;disableShading();<br>
    renderer-&gt;enableAntiAliasing();<br>
    renderer-&gt;enableTwoSideLighting();<br>
<br>
    kvs::glut::Screen screen( &amp;app );<br>
    screen.setTitle( “Create Point Renderer” );<br>
    screen.registerObject( object, renderer );<br>
    screen.show();<br>
<br>
    return app.run();<br>
}<br>
</code></pre>