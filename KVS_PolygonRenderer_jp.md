# 4.3 ポリゴンレンダラー #
ポリゴンレンダラーは、ポリゴンオブジェクトを描画するためのレンダラーです。ポリゴンオブジェクトに格納されている座標データや色データなどの情報をもとにして、OpenGLのGL\_TRIANGLESまたはGL\_QUADSを使ってポリゴンを描画します。

## 4.3.1 レンダリング機能 ##
KVSでは、ポリゴンレンダラーは以下のようのような機能を持っています。

**シェーディング**
> ポリゴンを構成する各面または各頂点に設定される法線ベクトルをもとに、光源位置を考慮して陰影処理（シェーディング処理）を行うことが可能です。点レンダラーと同様、立体感のある高品位な描画が可能です。

**アンチエイリアシング**
> 描画されるポリゴンの輪郭を滑らかに描画することで、高品位な描画を行うことが可能です。

**両面ライティング**
> 照明効果を有効にしている際、ポリゴンの裏面に対してもシェーディング処理が実行されます。

## 4.3.2 kvs::PolygonRendererクラス ##
KVSでは、ポリゴンレンダラーはkvs::PolygonRendererクラスとして実装されています。以下では、kvs::PolygonRendererクラスの主なメソッドについて説明します。

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

<pre><code>void enableAntiAliasing( const bool multisample )<br>
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

<h2>4.3.3 サンプルプログラム</h2>

ポリゴンオブジェクトのサンプルプログラムで示したCreatePolygonObject関数を利用してオブジェクトを作成し、それを描画するサンプルコードを以下に示します。<br>
<br>
<pre><code>#include &lt;kvs/glut/Application&gt;<br>
#include &lt;kvs/glut/Screen&gt;<br>
#include &lt;kvs/PolygonObject&gt;<br>
#include &lt;kvs/PolygonRenderer&gt;<br>
<br>
// メイン関数<br>
int main( int argc, char** argv )<br>
{<br>
    kvs::glut:::Application app( argc, argv );<br>
<br>
    // ポリゴンオブジェクトの生成<br>
    kvs::PolygonObject* object = CreatePolygonObject();<br>
<br>
    // ポリゴンレンダラーの生成<br>
    kvs::PolygonRenderer* renderer = new kvs::PolygonRenderer();<br>
    renderer-&gt;disableShading();<br>
    renderer-&gt;enableAntiAliasing();<br>
    renderer-&gt;enableTwoSideLighting();<br>
<br>
    kvs::glut::Screen screen( &amp;app );<br>
    screen.setTitle( “Create Polygon Renderer” );<br>
    screen.registerObject( object, renderer );<br>
    screen.show();<br>
<br>
    return app.run();<br>
}<br>
</code></pre>