# kvs::Endianクラス #

|ヘッダファイル|`#include <kvs/Endian>`|
|:------|:----------------------|
|クラス名   |`kvs::Endian`          |

## 機能 ##
このクラスは、エンディアンの判別およびバイトスワップを行うクラスです。2バイト以上のデータをメモリ上に配置する際に、CPUによってその順序がことなるために、適切にその順序を修正する必要があります。主に、サンマイクロシステムズのSPARCなどでは「ビッグエンディアン」となり、IntelのX86系などでは「リトルエンディアン」となります。つまり、たとえば、SPARC CPU上で生成さらたバイナリデータを、Intel CPU上で読み込む場合には、順序の修正（バイトスワップ）を行う必要があります。kvs::Endianを使って、その修正を簡単に行うことができます。

## 主なメソッド ##
このクラスの主なメソッドを説明します。

```
static bool IsBig();
```

```
static bool IsLittle();
```

```
static void Swap( ValueType* value );
```

```
static void Swap( ValueType* value, size_t n );
```



## サンプルプログラム ##