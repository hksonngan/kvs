# 8.4 kvsconv #

## 8.4.1 機能 ##
KVSで読み込み可能なデータを対象としてデータ変換を行う。KVSフォーマットへはこのコマンドを利用して変換することができる。

## 8.4.2 使用方法 ##
```
Usage: kvsconv [options] <input value>

Options:
-h         : ヘルプメッセージを表示する。
-help      : 変換コマンドごとのヘルプメッセージを表示する。 (ex. -help fld2kvsml)
-fld2kvsml : AVS Field データからKVSML（Structured volume object）データへ変換する。
-ucd2kvsml : AVS UCD データからKVSML（Unstructured volume object）データへ変換する。
-img2img   : 画像データの変換を行う。
```

  1. AVS Field データからKVSML（Structured volume object）データへの変換
```
Usage: kvsconv -fld2kvsml [options] <input data file>

Options:
-output : 出力ファイル名を指定する。 (default: <input_basename>.<output_extension>)
-e      : データ部分を外部ファイルとして出力する。 (optional)
-b      : データ部分をバイナリ形式の外部ファイルとして出力する。 (optional)
```
  1. AVS UCD データからKVSML（Unstructured volume object）データへの変換
```
Usage: kvsconv -ucd2kvsml [options] <input data file>

Options:
-output : 出力ファイル名を指定する。 (default: <input_basename>.<output_extension>)
-e      : データ部分を外部ファイルとして出力する。 (optional)
-b      : データ部分をバイナリ形式の外部ファイルとして出力する。 (optional)
```
  1. 画像データの変換を行う。
```
Usage: kvsconv -img2img [options] <input data file>

Options:
-output	: 出力ファイル名を指定する。 (default: <input_basename>.<output_extension>)
-s		: 画像を拡大／縮小する。 (optional: <scale>)
-r		: 画像サイズを変更する。 (optional: <width> <height>)
-g		: 手法を指定してグレースケール画像に変換する。 (default: 0)
			0 = Mean value
			1 = Middle value
			2 = Median value
			3 = NTSC weighted mean value
			4 = HDTV weighted mean value
-b		: 手法を指定して二値画像に変換する。 (default: 0)
			0 = P-Tile
			1 = Distinction
			2 = Byer
			3 = Halftone
			4 = Emphasized halftone
			5 = Screw
			6 = Deformed screw
			7 = Dot concentrate
```

## 8.4.3 使用例 ##

  1. AVS Field データをKVSMLデータ（内部データタイプ）に変換する。
```
% kvsconv -fld2kvsml lobster.fld -output lobster.kvsml
% ls
lobster.fld    lobster.kvsml
```
  1. AVS Field データをKVSMLデータ（アスキー形式外部データタイプ）に変換する。
```
% kvsconv -fld2kvsml lobster.fld -e -output lobster.kvsml
% ls
lobster.fld    lobster.kvsml    lobster_value.dat
```
  1. AVS UCD データをKVSMLデータ（バイナリ形式外部データタイプ）に変換する。
```
% kvsconv -ucd2kvsml blunt.inp -e -b -output blunt.kvsml
% ls
blunt.inp    blunt.kvsml    blunt_connect.dat    blunt_coord.dat    blunt_value.dat
```
  1. 画像を拡大する。
```
% kvsconv -img2img lenna.bmp -s 2 -output lenna2.bmp
```
  1. 画像をグレースケール化（Mean value法）する。
```
% kvsconv -img2img lenna.bmp -g 0 -output lenna_gray.bmp
```
  1. 画像を二値化（P-Tile法）する。
```
% kvsconv -img2img lenna.bmp -b 0 -output lenna_bit.bmp
```