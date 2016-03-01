# 1.3 ライブラリサポート #
KVSではいくつかの外部ライブラリをサポートしています。設定ファイル（kvs.conf）の対応するフラグを有効化し（0を1にする）コンパイルすることで、プログラム開発においてその機能を利用することができます。

## 1.3.1 ライブラリ ##
現在、KVSがサポートする外部ライブラリは以下のとおりです。ただし、利用するライブラリはあらかじめインストールしておく必要があります。

| **ライブラリ名** | **フラグ名** | **説明** |
|:-----------|:---------|:-------|
| CUDA       | KVS\_SUPPORT\_CUDA | NVIDIA社が提供するGPU向け開発環境|
| GLEW       | KVS\_SUPPORT\_GLEW | OpenGLの拡張機能を容易に利用するためのライブラリ※KVS2.0から必須となりました |
| GLUT       | KVS\_SUPPORT\_GLUT | ウィンドウの制御などをOSに依存せず行うためのOpenGL準拠のライブラリ |
| OpenCV     | KVS\_SUPPORT\_OPENCV | インテル社が開発したコンピュータビジョン向けライブラリ※KVS2.0から非対応となりました |
| Qt         | KVS\_SUPPORT\_QT | ノキア社が開発するOSに依存しないUI開発ライブラリ |
| SAGE       | KVS\_SUPPORT\_SAGE | イリノイ大学（EVL）が開発するタイルドディスプレイ向けライブラリ※KVS2.0から非対応となりました |
| OpenCABIN  | KVS\_SUPPORT\_OPENCABIN | 東京大学が開発した没入型表示装置およびタイルドディスプレイ向けライブラリ※KVS2.0から非対応となりました |

## 1.3.2 設定例 ##
GLUTおよびGLEWを事前にインストールしている場合のkvs.confの設定例を以下に示します。KVS\_SUPPORT\_GLUTは初期状態で1となっていますので、KVS\_SUPPORT\_GLEWを1にしてください。GPUが搭載されていない環境やOpenGL拡張機能を利用しない場合などはKVS\_SUPPORT\_GLEWは0にしてください。

```
KVS_SUPPORT_CAVE      = 0    ※廃止
KVS_SUPPORT_CUDA      = 0
KVS_SUPPORT_GLEW      = 1    ※KVS2.0から必須となったため廃止
KVS_SUPPORT_GLUT      = 1
KVS_SUPPORT_OPENCV    = 0
KVS_SUPPORT_QT        = 0
KVS_SUPPORT_SAGE      = 0    ※KVS2.0から非対応となったため廃止
KVS_SUPPORT_OPENCABIN = 0    ※KVS2.0から非対応となったため廃止
```