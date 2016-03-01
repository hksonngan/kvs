# KVS Programming Guide #

  * 幾何データの可視化
  * スカラデータの可視化
    * 等値面抽出（kvs::Isosurface）
    * レイキャスティングレンダリング（kvs::RayCastingRenderer）
    * 伝達関数（kvs::TransferFunction）
  * ベクトルデータの可視化
    * 流線抽出（kvs::Streamline）
    * グリフ表示（kvs::ArrowGlyph, kvs::SphareGlyph）
  * 画像処理
    * カラー画像（kvs::ColorImage）
    * グレースケール画像（kvs::GrayImage）
    * ビット画像（kvs::BitImage）
  * [行列演算](guide_matrix_classes_jp.md)
    * [2,3,4次元ベクトル（kvs::Vector2, kvs::Vector3, kvs::Vector4）](guide_vector234_jp.md)
    * [N次元ベクトル（kvs::Vector）](guide_vectorn_jp.md)
    * [2,3,4次正方行列（kvs::Matrix22, kvs::Matrix33, kvs::Matrix44）](guide_matrix234_jp.md)
    * [MxN行列（kvs::Matrix）](guide_matrixmn_jp.md)
  * 数値計算
    * 乱数の生成（kvs::BoxMuller, kvs::MersenneTwister, kvs::Xorshift128）
    * 固有値分解（kvs::EigenDecomposer）
  * マルチスレッド
    * スレッド（kvs::Thread）
  * ネットワーク
    * TCPソケット（kvs::TCPSocket）
  * [ユーティリティクラス](guide_utility_classes_jp.md)
    * [コマンドライン（kvs::CommandLine）](guide_commandline_jp.md)
    * [ファイル（kvs::File）](guide_file_jp.md)
    * [ディレクトリ（kvs::Directory）](guide_directory_jp.md)
    * [基本型（kvs::Int8, kvs::UInt8, ...）](guide_type_jp.md)
    * [エンディアン（kvs::Endian）](guide_endian_jp.md)
    * [数値型配列（kvs::ValueArray）](guide_valuearray_jp.md)
    * [任意数値型配列（kvs::AnyValueArray）](guide_anyvaluearray_jp.md)