# 8.2 kvsview #

## 8.2.1 機能 ##
KVSで読み込み可能なデータに対して、指定する手法で可視化した結果を表示する。手法を指定しない場合、ファイル形式に応じて、可視化パイプラインを構築し表示を行う。

## 8.2.2 使用方法 ##
```
Usage: kvsview [options] <input data file>

Options:
-h			: ヘルプメッセージを表示する。
-help			: 可視化コマンドごとのヘルプメッセージを表示する。 (ex. -help Isosurface)
-PointRenderer		: ポイントデータに対してPointRendererを利用して表示する。
-LineRenderer		: ラインデータに対してLineRendererを利用して表示する。
-PolygonRenderer	: ポリゴンデータに対してPolygonRendererを利用して表示する。
-Isosurface		: ボリュームデータに対して等値面抽出結果を表示する。
-SlicePlane		: ボリュームデータに対して任意断面を表示する。
-OrthoSlice		: ボリュームデータに対して直交断面を表示する。
-TransferFunction	: 伝達関数（カラーマップ）を表示する。
-ExtractEdges		: ボリュームデータに対して格子エッジを表示する。
-ExtractVertices 	: ボリュームデータに対して格子点を表示する。
-ExternalFaces		: ボリュームデータに対してデータ境界面（最外表面）を表示する。
-ParticleVolumeRenderer	: ボリュームデータに対してPBVRでの可視化結果を表示する。KVS2.0からは"ParticleBasedRenderer"。
-RayCastingRenderer	: ボリュームデータに対してレイキャスティングでの可視化結果を表示する。
-Histogram              : ボリュームデータに対してヒストグラムを表示する。
```

  1. PointRendererを利用した表示
```
Usage: kvsview -PointRenderer [options] <input data file>

Options:
-background_color	: 背景色を指定する。 (default: 212 221 229)
-background_color2	: 背景色（上部と下部）を指定する。 (optional: <top: r g b> <bottom: r g b>)
-bounds			: 境界ボックス（バウンディングボックス）を表示する。 (optional)
-bounds_color		: 境界ボックスの色を指定する。 (default: 0 0 0)
-screen_position	: スクリーンの表示位置を指定する。 (default: 0 0)
-screen_size		: スクリーンの大きさを指定する。 (default: 512 512)
-output			: 出力ファイル名を指定する。 (optional: <filename>)
-verbose		: 詳細情報を出力する。 (optional)
```
  1. 等値面抽出結果の表示
```
Usage: kvsview -Isosurface [options] <input data file>

Options:
-background_color	: 背景色を指定する。 (default: 212 221 229)
-background_color2	: 背景色（上部と下部）を指定する。 (optional: <top: r g b> <bottom: r g b>)
-bounds			: 境界ボックス（バウンディングボックス）を表示する。 (optional)
-bounds_color		: 境界ボックスの色を指定する。 (default: 0 0 0)
-screen_position	: スクリーンの表示位置を指定する。 (default: 0 0)
-screen_size		: スクリーンの大きさを指定する。 (default: 512 512)
-output			: 出力ファイル名を指定する。 (optional: <filename>)　※未実装
-verbose		: 詳細情報を出力する。 (optional)
-l			: 等値面レベルを指定する。 (default: 0)
-n			: 法線ベクトルの設定位置（poly[gon], vert[ex]）を指定する。 (default: poly)
-t			: 伝達関数ファイルを指定する。 (optional: <filename>)
```

## 8.2.3 使用例 ##

  1. ポイントデータを表示する。背景色を黒（0 0 0）、スクリーンサイズを800x600にする。
```
% kvsview -PointRenderer point_object.kvsml -background_color 0 0 0 -screen_size 800 600
```
  1. 等値面抽出結果（等値面レベル：100、頂点に法線ベクトル）を表示する。境界ボックスも表示する。
```
% kvsview -Isosurface lobster.fld -bounds -l 100 -n vert
```
  1. 画像を表示する。
```
% kvsview lenna.bmp
※画像の場合は、可視化手法を指定する必要はなく表示可能である。
```
  1. ポリゴンデータを表示する。可視化手法を指定しない場合は、自動的にPolygonRendererを利用して可視化する。
```
% kvsview polygon_object.kvsml
```
  1. ボリュームデータを表示する。可視化手法を指定しない場合は、レイキャスティングでの可視化結果を表示する。
```
% kvsview lobster.kvsml
```