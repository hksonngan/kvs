

# KVS XML data format #

KVSが標準的に扱うオブジェクトデータ形式（XML形式）について説明する。KVSで扱うオブジェクトデータは、幾何形状データ（Geometry object data）とボリューム形状データ（Volume object data）に分類され、以下の５種類のデータを処理の対象としている。

  * 幾何形状データ
    * 点データ（Point object）
    * 線データ（Line object）
    * 面データ（Polygon object）

  * ボリューム形状データ
    * 構造格子データ（Structured volume object）
    * 非構造格子データ（Unstructured volume object）

それぞれのデータ形式について説明する。

## 点データ（point object） ##
点群を表す幾何データであり、頂点の座標値（coordinate）、色（color）、法線（normal）、点の大きさ（size）に関する情報を持つ。

[サンプル](KVSML_sample_point_object_jp.md)
```
<KVSML>
  <Object type="PointObject">
    <PointObject>
      <Vertex nvertices="xxx">
      <!-- nvertices: 頂点数 -->
        <Coord>
          <DataArray> xxx </DataArray>
          <!-- 頂点の座標値を指定する。                           -->
          <!-- 例）                                               -->
          <!--     <DataArray> x0 y0 z0 x1 y1 z1 ... </DataArray> -->
        </Coord>
        <Color>
          <DataArray> xxx </DataArray> または <DataValue> xxx </DataValue>
          <!-- 頂点の色（0〜255の整数値）を指定する。             -->
          <!-- 指定しない場合は黒（0 0 0）となる。                -->
          <!-- 例）                                               -->
          <!-- * 頂点ごとに色を指定する場合                       -->
          <!--     <DataArray> r0 g0 b0 r1 g1 b1 ... </DataArray> -->
          <!-- * すべての頂点に同じ色を指定する場合               -->
          <!--     <DataValue> r g b </DataValue>                 -->
        </Color>
        <Normal>
          <DataArray> xxx </DataArray>
          <!-- 法線ベクトルを指定する。                                -->
          <!-- 指定しない場合はシェーディングが無効となる。            -->
          <!-- 例）                                                    -->
          <!--    <DataArray> nx0 ny0 nz0 nx1 ny1 nz1 ... </DataArray> -->
        </Normal>
        <Size>
          <DataArray> xxx </DataArray> または <DataValue> xxx </DataValue>
          <!-- 頂点の大きさを指定する。                 -->
          <!-- 指定しない場合は1となる。                -->
          <!-- 例）                                     -->
          <!-- * 頂点ごとに大きさを指定する場合         -->
          <!--     <DataArray> s0 s1 ... </DataArray>   -->
          <!-- * すべての頂点に同じ大きさを指定する場合 -->
          <!--     <DataValue> s </DataValue>           -->
        </Size>
      </Vertex>
    </PointObject>
  </Object>
</KVSML>
```

## 線データ（line Object） ##
線群を表す幾何データであり、頂点の座標値（coordinate）、線分または頂点の色（color）、線の太さ（size）、頂点の接続（connection）に関する情報を持つ。線の種類として、「線分（strip）」、「一本線（uniline）」、「複数線（polyline）」、「分割線（segment）」を表現できる。

[サンプル](KVSML_sample_line_object_jp.md)
```
<KVSML>
  <Object type="LineObject">
    <LineObject line_type="xxx" color_type="xxx">
    <!-- line_type:  線の種類 (strip, uniline, polyline, segment) -->
    <!-- color_type: 色付けの種類 (line, vertex)                  -->
      <Vertex nvertices="xxx">
      <!-- nvertices: 頂点数 -->
        <Coord>
          <DataArray> xxx </DataArray>
          <!-- 頂点の座標値を指定する。                           -->
          <!-- 例）                                               -->
          <!--     <DataArray> x0 y0 z0 x1 y1 z1 ... </DataArray> -->
        </Coord>
        <Color>
          <DataArray> xxx </DataArray> または <DataValue> xxx </DataValue>
          <!-- 線分または頂点の色（0〜255の整数値）を指定する。   -->
          <!-- 指定しない場合は黒（0 0 0）となる。                -->
          <!-- 例）                                               -->
          <!-- * 線分または頂点ごとに色を指定する場合             -->
          <!--     <DataArray> r0 g0 b0 r1 g1 b1 ... </DataArray> -->
          <!-- * すべての線分に同じ色を指定する場合               -->
          <!--     <DataValue> r g b </DataValue>                 -->
        </Color>
        <Size>
          <DataArray> xxx </DataArray> または <DataValue> xxx </DataValue>
          <!-- 線分の太さを指定する。                  -->
          <!-- 指定しない場合は1となる。               -->
          <!-- 例）                                    -->
          <!-- * 線分ごとに太さを指定する場合          -->
          <!--     <DataArray> s0 s1 ... </DataArray>  -->
          <!-- * すべての線分に同じ太さを指定する場合  -->
          <!--     <DataValue> s </DataValue>          -->
        </Size>
      </Vertex>
      <Line nlines="xxx">
      <!-- nlines: 線分数 -->
        <Connection>
          <DataArray> xxx </DataArray>
          <!-- 線分の接続情報（接続する頂点の番号）を指定する。-->
          <!-- 例）                                            -->
          <!--     <DataArray> id0 id1 id2 ... </DataArray>    -->
        </Connection>
      </Line>
    </LineObject>
  </Object>
</KVSML>
```

## 面データ（polygon Object） ##
面（ポリゴン）を表す幾何データであり、頂点の座標値（coordinate）、ポリゴンまたは頂点の色（color）、ポリゴンの不透明度（opacity）、接続（connection）に関する情報を持つ。面の種類として三角形（triangle）または四角形（quadrangle）を表現できる。

[サンプル](KVSML_sample_polygon_object_jp.md)
```
<KVSML>
  <Object type="PolygonObject">
    <PolygonObject polygon_type="xxx" color_type="xxx" normal_type="xxx">
    <!-- polygon_type: 面の種類 (triangle, quadrangle)      -->
    <!-- color_type:   色付けの種類 (polygon, vertex)       -->
    <!-- normal_type:  法線ベクトルの種類 (polygon, vertex) -->
      <Vertex nvertices="xxx">
      <!-- nvertices: 頂点数 -->
        <Coord>
          <DataArray> xxx </DataArray>
          <!-- 頂点の座標値を指定する。                           -->
          <!-- 例）                                               -->
          <!--     <DataArray> x0 y0 z0 x1 y1 z1 ... </DataArray> -->
        </Coord>
        <Color>
          <DataArray> xxx </DataArray> または <DataValue> xxx </DataValue>
          <!-- 面または頂点の色（0〜255の整数値）を指定する。     -->
          <!-- 指定しない場合は黒（0 0 0）となる。                -->
          <!-- 例）                                               -->
          <!-- * 面または頂点ごとに色を指定する場合               -->
          <!--     <DataArray> r0 g0 b0 r1 g1 b1 ... </DataArray> -->
          <!-- * すべての面に同じ色を指定する場合                 -->
          <!--     <DataValue> r g b </DataValue>                 -->
        </Color>
        <Normal>
          <DataArray> xxx </DataArray>
          <!-- 法線ベクトルを指定する。                                -->
          <!-- 指定しない場合はシェーディングが無効となる。            -->
          <!-- 例）                                                    -->
          <!--    <DataArray> nx0 ny0 nz0 nx1 ny1 nz1 ... </DataArray> -->
        </Normal>
      </Vertex>
      <Polygon npolygons="xxx">
      <!-- npolygons: 面数 -->
        <Connection>
          <DataArray> xxx </DataArray>
          <!-- 面の接続情報（接続する頂点の番号）を指定する。-->
          <!-- 例）                                          -->
          <!--     <DataArray> id0 id1 id2 ... </DataArray>  -->
        </Connection>
      </Polygon>
    </PolygonObject>
  </Object>
</KVSML>
```

## 構造型ボリュームデータ（structured volume object） ##

規則格子を表すボリュームデータであり、格子点（節点）に対するフィールド値（value）および座標値（coord）に関する情報を持つ。格子の種類として、直交等間隔格子（uniform）、直交不等間隔格子（rectilinear）、湾曲格子（curvilinear）を表現できる。

```
<KVSML>
  <Object type="StructuredVolumeObject">
    <StructuredVolumeObject resolution="xxx xxx xxx" grid_type="xxx">
    <!-- resolution: 格子サイズ（解像度） -->
    <!-- grid_type: 格子の種類（uniform, rectilinear, curvilinear） -->
      <Node>
        <Value veclen="xxx">
        <!-- veclen: フィールド値のベクトル長 -->
          <DataArray> xxx </DataArray>
          <!-- フィールド値を指定する。 -->
          <!-- 例１） 8ビット整数型（uchar）、ベクトル長１の場合 -->
          <!--     <DataArray type="uchar"> v0 v1 v2 ... </DataArray>  -->
          <!-- 例２） 単精度浮動小数型（float）、ベクトル長３の場合 -->
          <!--     <DataArray type="uchar"> v0x v0y v0z v1x v1y v1z  ... </DataArray>  -->
          <!-- 例３） 単精度浮動小数型（float）、外部アスキーファイル指定の場合 -->
          <!--     <DataArray type="float" file="node.dat" format="ascii"/>  -->
          <!-- 例４） 単精度浮動小数型（float）、外部バイナリファイル指定の場合 -->
          <!--     <DataArray type="float" file="node.dat" format="binary"/>  -->
        </Value>
      </Node>
    </StructuredVolumeObject>
  </Object>
</KVSML>
```

## 非構造型ボリュームデータ（unstructured volume object） ##

不規則格子を表すボリュームデータであり、格子点（節点）に対するフィールド値（value）および座標値（coord）、格子（要素）に対する接続情報（connection）に関する情報を持つ。格子の種類として、四面体一次要素（tetrahedra）、四面体二次要素（quadratic tetrahedra）、六面体一次要素（hexahedra）、六面体二次要素（quadratic hexahedra）を表現できる。

```
<KVSML>
  <Object type="UnstructuredVolumeObject">
    <!-- aaa: tetrahedra, quadratic tetrahedra, hexahedra, quadratic hexahedra -->
    <UnstructuredVolumeObject cell_type="aaa">
      <Node nnodes="xxx">
        <Value veclen="xxx">
          <DataArray>
        </Value>
        <Coord>
          <DataArray>
        </Coord>
      </Node>
      <Cell ncells="xxx">
        <Connection>
          <DataArray>
        </Connection>
      </Cell>
    </UnstructuredVolumeObject>
  </Object>
</KVSML>
```