# 3. オブジェクト #
KVSにおいて、描画の対象となるデータはオブジェクト（object）と呼ばれ、幾何オブジェクト（geometric object）と３次元空間中に分布する数値データを表すボリュームオブジェクト（volumetric object）に大別されます。

幾何オブジェクトは、点・線分・面（ポリゴン）からなるデータであり、OpenGLやDirect Xといった一般的なグラフィックスライブラリで、基本的な描画要素として標準的にサポートされています。KVSでは、点オブジェクト（point object）、線分オブジェクト（line object）、ポリゴンオブジェクト（polygon object）をつかってそれらのデータ構造を表現することが可能です。

ボリュームオブジェクトは、３次元空間中に離散的に分布する数値データとして表現されます。そして、３次元空間は、多くの場合、格子（要素）と呼ばれる小立体に分割され、数値データは格子の頂点（節点）で定義されています。KVSでは、表現することのできる３次元空間の複雑度に応じて、格子を構造格子と非構造格子に分類し、それぞれ構造格子型ボリュームオブジェクト（structured volume object）と非構造格子型ボリュームオブジェクト（unstructured volume object）として表現しています。

![https://lh3.googleusercontent.com/_X4cB5gzzR7o/TdKMhGy0fuI/AAAAAAAAAC0/wTL77ongyZI/s800/KVSObjects.png](https://lh3.googleusercontent.com/_X4cB5gzzR7o/TdKMhGy0fuI/AAAAAAAAAC0/wTL77ongyZI/s800/KVSObjects.png)

ここでは、KVSで実装されている各オブジェクトのデータ構造とその取り扱い方について説明します。

  * [3.1 点オブジェクト（Point Object）](KVS_PointObject_jp.md)
  * [3.2 線分オブジェクト（Line Object）](KVS_LineObject_jp.md)
  * [3.3 ポリゴンオブジェクト（Polygon Object）](KVS_PolygonObject_jp.md)
  * [3.4 構造格子型ボリュームオブジェクト（Structured Volume Object）](KVS_StructuredVolumeObject_jp.md)
  * [3.5 非構造格子型ボリュームオブジェクト（Unstructured Volume Object）](KVS_UnstructuredVolumeObject_jp.md)