# kvs::Fileクラス #

|ヘッダファイル|`#include <kvs/File>`|
|:------|:--------------------|
|クラス名   |`kvs::File`          |

## 機能 ##
このクラスは、ファイル名を解析するためのクラスです。文字列として指定されるファイル名に対して、パスの取得や拡張子の取得、また、ファイルが存在するかどうかの判定などを簡単に行うことができます。

## 主なメソッド ##
このクラスの主なメソッドを説明します。

```
File( const std::string& file_path )
```

```
std::string filePath( bool absolute = false ) const
```

```
std::string pathName( bool absolute = false ) const
```

```
std::string fileName() const
```

```
std::string baseName() const
```

```
std::string extension( bool complete = false ) const
```

```
size_t byteSize() const
```

```
bool isFile() const
```

```
bool exists() const
```

```
bool parse( const std::string& file_path )
```

```
static std::string Separator()
```

## サンプルプログラム ##
次のような仕様のプログラムを作成します。
  * ファイル名を入力とする。
  * 指定されたファイルが存在するかどうかチェックする。
  * 指定されたファイル名のパス名、ベース名、拡張子を表示する。
  * 指定されたファイルのサイズを表示する。

以下にプログラムを示します。

```
#include <iostream>
#include <kvs/File>

int main( int argc, char** argv )
{
    // ファイル名が指定されなかった場合、使用方法を表示して終了する。
    if ( argc == 1 )
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // ファイル名を設定する。
    const char* filename = argv[1];
    kvs::File file( filename );

    // 指定されたファイルが存在するかどうかを確認する。
    if ( !file.exists() )
    {
        std::cerr << "Error: " << filename << " is not existed." << std::endl;
        return 1;
    }

    // ファイル名情報を表示する。
    std::cout << "file path: " << file.filePath() << std::endl;
    std::cout << "path name: " << file.pathName() << std::endl;
    std::cout << "path name (absolute): " << file.pathName(true) << std::endl;
    std::cout << "file name: " << file.fileName() << std::endl;
    std::cout << "base name: " << file.baseName() << std::endl;
    std::cout << "extension: " << file.extension() << std::endl;
    std::cout << "extension (complete): " << file.extension(true) << std::endl;

    // ファイルサイズを表示する。
    std::cout << "file size: " << file.byteSize() << " [bytes]" << std::endl;

    return 0;
}
```