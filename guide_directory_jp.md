# kvs::Directoryクラス #

|ヘッダファイル|`#include <kvs/Directory>`|
|:------|:-------------------------|
|クラス名   |`kvs::Directory`          |

## 機能 ##
このクラスは、ディレクトリ名を解析するためのクラスです。文字列として指定されるディレクトリ名に対して、絶対パスの取得や指定ディレクトリ内に存在するファイル名の一覧取得、また、ディレクトリが存在するかどうかの判定などを簡単に行うことができます。

## 主なメソッド ##
このクラスの主なメソッドを説明します。

```
explicit Directory( const std::string& directory_path )
```

```
std::string directoryPath( bool absolute = false ) const
```

```
std::string directoryName() const
```

```
kvs::FileList& fileList()
```

```
const kvs::FileList& fileList() const
```

```
bool isDirectory() const
```

```
bool exists() const
```

```
bool parse( const std::string& direcotry_path )
```

```
kvs::FileList::iterator find( const kvs::File& file )
```

```
kvs::FileList::const_iterator find( const kvs::File& file ) const
```

## サンプルプログラム ##
次のような仕様のプログラムを作成します。

ディレクトリ名を入力とする。
  * 指定されたディレクトリが存在するかどうかチェックする。
  * 指定されたディレクトリ名のパス名、パス名を削除したディレクトリ名を表示する。
  * 指定されたディレクトリ内にあるファイル名とサイズを表示する。
  * 指定されたディレクトリ内に「test.cpp」という名前のファイルが存在するかどうかチェックする。

以下にプログラムを示します。
```
#include <iostream>
#include <kvs/Directory>

int main( int argc, char** argv )
{
    // ディレクトリ名が指定されなかった場合、使用方法を表示して終了する。
    if ( argc == 1 )
    {
        std::cerr << "Usage: " << argv[0] << " <directory name>" << std::endl;
        return 1;
    }

    // ディレクトリ名を設定する。
    const char* directory_name = argv[1];
    kvs::Directory directory( directory_name );

    // 指定されたディレクトリが存在するかどうかを確認する。
    if ( !directory.exists() )
    {
        std::cerr << "Error: " << directory_name << " is not existed." << std::endl;
        return 1;
    }

    // Check whether the given directory is a directory.
    if ( !directory.isDirectory() )
    {
        std::cerr << "Error: " << directory_name << " is not directory." << std::endl;
        return 1;
    }

    // ディレクトリ名情報を表示する。
    std::cout << "Directory path: " << directory.directoryPath() << std::endl;
    std::cout << "Directory path (absolute): " << directory.directoryPath(true) << std::endl;
    std::cout << "Directory name: " << directory.directoryName() << std::endl;

    // ディレクトリ内にあるファイルの数を出力する。
    std::cout << "Number of files in the directory: " << directory.fileList().size() << std::endl;

    // ディレクトリ内にあるファイルの名前とサイズを出力する。
    kvs::FileList::iterator file = directory.fileList().begin();
    kvs::FileList::iterator end = directory.fileList().end();
    while ( file != end )
    {
        std::cout << "\t" << file->fileName() << " [" << file->byteSize() << " bytes]" << std::endl;
        ++file;
    }

    // 「test.cpp」という名前のファイルが存在するかどうかチェックする。
    kvs::File f( "test.cpp" );
    file = directory.find( f );
    if ( file != end )
    {
        std::cout << f.filePath() << " is found in ";
        std::cout << directory.directoryPath(true) << std::endl;
    }
    else
    {
        std::cout << f.filePath() << " is not found in ";
        std::cout << directory.directoryPath(true) << std::endl;
    }

    return 0;
}
```