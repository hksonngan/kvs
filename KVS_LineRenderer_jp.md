# 4.2 線分レンダラー #
線分レンダラーは、線分オブジェクトを描画するためのレンダラーです。線分オブジェクトに格納されている座標データや色データなどの情報をもとにして、OpenGLのGL\_LINESまたはGL\_LINE\_STRIPを使って線分を描画します。

## 4.2.1 レンダリング機能 ##
KVSでは、線分レンダラーは以下のようのような機能を持っています。

**アンチエイリアシング**
> 点レンダラーと同様に、描画される線分の輪郭を滑らかに描画することで、ジャギーの発生を防ぐことができます。

## 4.2.2 kvs::LineRendererクラス ##
KVSでは、線分レンダラーはkvs::LineRendererクラスとして実装されています。以下では、kvs::LineRendererクラスの主なメソッドについて説明します。

```
void enableAntiAliasing( const bool multisample = false )
```
**機能**<br>
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

<h2>4.2.3 サンプルプログラム</h2>
線分オブジェクトのサンプルプログラムで示したCreateLineObject関数を利用してオブジェクトを作成し、それを描画するサンプルコードを以下に示します。<br>
<br>
<pre><code>#include &lt;kvs/glut/Application&gt;<br>
#include &lt;kvs/glut/Screen&gt;<br>
#include &lt;kvs/LineObject&gt;<br>
#include &lt;kvs/LineRenderer&gt;<br>
<br>
// メイン関数<br>
int main( int argc, char** argv )<br>
{<br>
    kvs::glut:::Application app( argc, argv );<br>
<br>
    // 点オブジェクトの生成<br>
    kvs::LineObject* object = CreateLineObject();<br>
<br>
    // 線分レンダラーの生成<br>
    kvs::LineRenderer* renderer = new kvs::LineRenderer();<br>
    renderer-&gt;enableAntiAliasing();<br>
<br>
    kvs::glut::Screen screen( &amp;app );<br>
    screen.setTitle( “Create Line Renderer” );<br>
    screen.registerObject( object, renderer );<br>
    screen.show();<br>
<br>
    return app.run();<br>
}<br>
</code></pre>