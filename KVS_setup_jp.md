# 1.1 準備 #
KVSのコンパイルには、C++コンパイラが必要です。Windowsの場合は、Microsoft Visual C++を利用します。また、Linux/Mac OS Xの場合は、gcc (g++) およびmakeを利用します。その他にも、C++コンパイラはいくつか存在しますが、ここでは上記の２つのコンパイラの利用を想定して説明します。また、KVSを利用して可視化アプリケーションを開発する場合、可視化結果をウィンドウに表示するためにGLUTが必要となります。また、KVSではGPUの高速化機能を利用するためにGLEWを利用しています。特に、制限などがない場合、この２つのライブラリを事前にインストールしておいてください。※KVS2.0からGLEWは必須となりました。

## 1.1.1 Windows ##
**コンパイラのインストール**

Windowsの場合は、Microsoft Visual C++を利用します。無料版のMicrosoft Visual C++ Expressを利用することが可能ですので、以下からインストーラをダウンロードし、指示に従いインストールしてください。

> [Microsoft Visual Studio](http://www.microsoft.com/japan/msdn/vstudio/express/)

**GLUTのインストール**

GLUTは以下のサイトからバイナリをダウンロードすることができます。

> [Nate Robins - OpenGL - GLUT for Win32](http://www.xmission.com/~nate/glut.html)

「glut-3.7.6-bin.zip (117 KB) 」をクリックし、ZIPファイルをダウンロードしてください。ファイル解凍後、そこに含まれる以下のファイルを指定するフォルダにコピーしてください。

| ファイル名 | コピー先 |
|:------|:-----|
| glut32.dll | C:\Windows\System32<br>C:\Windows\SysWOW64 (Windows 7/8/8.1 64bit版の場合) <br>
<tr><td> glut32.lib </td><td> C:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib </td></tr>
<tr><td> glut.h </td><td> C:\Program Files\Microsoft SDKs\Windows\v7.0A\Include\gl </td></tr></tbody></table>

※コピー先のパス内の「v7.0A」はインストールするコンパイラのバージョンによって数字が異なるかもしれません。上記は、Microsoft Visual C++ 2010 Expressをインストールした場合の例を示しています。<br>
<br>
<b>GLEWのインストール</b>

GLEWは以下のサイトからバイナリをダウンロードすることができます。KVS2.0からGLEWが必須となりましたので事前にインストールしておいてください。<br>
<br>
<blockquote>[GLEW: The OpenGL Extension Wrangler Library](http://glew.sourceforge.net/)

「Windows 32-bit」をクリックし、ZIPファイルをダウンロードしてください。Windows7を利用している場合でも、トラブルを避けるため、64bit版ではなく32bit版をインストールしてください。ファイル解凍後、GLUTと同様に、そこに含まれる以下のファイルを指定するフォルダにコピーしてください。

| ファイル名 | コピー先 |
|:------|:-----|
| glew32.dll | C:\Windows\System32<br>C:\Windows\SysWOW64 (Windows 7/8/8.1 64bit版の場合) <br>
<tr><td> glew32.lib, glew32s.lib </td><td> C:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib </td></tr>
<tr><td> glew.h, wglew.h </td><td> C:\Program Files\Microsoft SDKs\Windows\v7.0A\Include\gl </td></tr></tbody></table>

<h2>1.1.2 Linux ##
**コンパイラのインストール**

Linuxの場合は、各ディストリビューションに応じたパッケージ管理用GUIアプリケーション（たとえば、UbuntuではSynaptic）を利用してコンパイラ（g++とmake）をインストールすることができます。

ターミナルからインストールすることも可能です。Ubuntuでは、以下のようにして必要なパッケージ一式をインストールすることもできます。
```
> sudo apt-get install build-essential
```

**GLUTのインストール**

GLUTもコンパイラと同様にパッケージ管理用GUIアプリケーションから簡単にインストールできます。ただし、インストールの際は、devキーワードが付いた開発用パッケージをインストールしてください。また、GLUTはfreeglutという名前でパッケージ管理されていることが多いです。freeglutというパッケージがある場合はそちらをインストールしてください。

ターミナルからインストールする場合、たとえば、Ubuntuでは以下のようにしてインストールすることができます。以下では、バージョン3をインストールする例を示しています。

```
> sudo apt-get install freeglut3-dev libglut3-dev
```

**GLEWのインストール**

GLEWもGLUTと同様に開発用パッケージをインストールしてください。Ubuntuを利用している場合、ターミナルから以下のようにしてインストールすることができます。もちろん、Synapticなどを利用してインストールすることも可能です。以下では、バージョン1.5をインストールする例を示しています。

```
> sudo apt-get install libglew1.5-dev
```

## 1.1.3 Mac OS X ##
**コンパイラのインストール**

Mac OS Xの場合は、Xcodeをインストールするとgcc (g++) およびmakeコマンドがインストールされます。付属DVDもしくはMac Dev CenterからXcodeをダウンロードしインストールしてください。Mac OS X 10.7 Lion を利用している人は、App Storeからダウンロードおよびインストールができます。

> [Mac Dev Center](http://developer.apple.com/devcenter/mac/index.action)

> [App Store](http://click.linksynergy.com/fs-bin/click?id=i21s0ZPB3B8&subid=&offerid=94348.1&type=10&tmpid=3910&RD_PARM1=http%3A%2F%2Fitunes.apple.com%2Fjp%2Fapp%2Fxcode%2Fid448457090%3Fmt%3D12)

Xcode 5以降は、コマンドラインから以下を実行してコマンドラインツールをインストールする必要があります。

```
> xcode-select --install
```

**GLUTのインストール**

Mac OS Xでは、GLUTは既にインストールされていますので、あらためてインストールする必要はありません。

**GLEWのインストール**

GLEWは、MacPortsというパッケージ管理ソフトウェアを利用して、インストールすることができます。先に示したGLEWのサイトからソースコードをダウンロードしコンパイルすることも可能ですが、ここではMacPortsを利用したインストール方法について説明します。

まず、以下からOSのバージョンにあったMacPortsのパッケージ（pkgファイル）をダウンロードし、インストールしてください。

> [The MacPorts Project](http://www.macports.org/)

MacPortsをインストール後、ターミナル（「アプリケーション」→「ユーティリティ」→「ターミナル.app」）を開き、以下のようにしてGLEWをインストールすることができます。

```
> sudo port install glew
```