# kvs::CommandLineクラス #

|ヘッダファイル|`#include <kvs/CommandLine>`|
|:------|:---------------------------|
|クラス名   |`kvs::CommandLine`          |

## 機能 ##
このクラスは、コマンドライン引数を解析するためのクラスです。コマンドラインから起動するアプリケーション（CUIアプリケーション）を開発する際に、オプションの指定および取得、ヘルプの表示などを簡単に行うことができます。

## メソッド ##
このクラスの主なメソッドを説明します。

```
CommandLine( int argc, char** argv )
```

```
CommandLine( int argc, char** argv, const std::string& command_name )
```

```
void addHelpOption( const std::string& help_option = "h" )
```

```
void addOption(
    const std::string& name,
    const std::string& description,
    size_t nvalues = 0,
    bool is_required = false );
```

```
void addValue( const std::string& description, bool is_required = true )
```

```
template <class T>
T optionValue( const std::string& option_name, size_t index = 0 ) const
```

```
bool hasOption( const std::string& option_name ) const
```

```
bool hasOptionValue( const std::string& option_name ) const
```

```
size_t numberOfOptions() const
```

```
template <class T>
T value( size_t index = 0 ) const
```

```
bool hasValues() const
```

```
size_t numberOfValues() const
```

## サンプルプログラム ##
次のような仕様のプログラムを作成します。
  * ２つの数値を入力し、その四則演算結果を、指定されるファイルに書き出す。
  * ２つの数値は、オプション「x」および「y」で数値（float型）を指定する。
  * 実施する四則演算は、オプション「o」で文字（string型）で指定する。
  * オプション「o」で指定する文字は、「sum, sub, mul, div」のいずれかとする。
  * オプション「o」が指定されていない場合は、「sum」が指定されたとみなす（初期値）。
  * 入力値としてファイル名を指定する。
  * ファイル名が指定されていない場合は、標準出力に結果を表示する。

以下にプログラムを示します。

```
#include <iostream>
#include <fstream>
#include <string>
#include <kvs/CommandLine>


int main( int argc, char** argv )
{
    // 仕様に従いコマンドライン引数を設定する。
    kvs::CommandLine commandline( argc, argv );
    commandline.addHelpOption();
    commandline.addOption( "x","floating value 1 (required).", 1, true );
    commandline.addOption( "y","floating value 2 (required).", 1, true );
    commandline.addOption( "o","operator 'sum', 'sub', 'mul', 'div' (default: 'sum').", 1, false );
    commandline.addValue( "filename.", false );

    // コマンドライン引数を解析する。
    if ( !commandline.parse() ) return 1;

    // オプション「x」で指定される数値を取得する。
    float x = commandline.optionValue<float>("x");

    // オプション「y」で指定される数値を取得する。
    float y = commandline.optionValue<float>("y");

    // オプション「o」で文字列を取得する。
    std::string o = "sum"; // 初期値
    if ( commandline.hasOption("o") )
    {
        o = commandline.optionValue<std::string>("o");
    }

    // 指定された演算を実行する。
    float result = 0.0f;
    if ( o == "sum" )
    {
        o = "+";
        result = x + y;
    }
    else if ( o == "sub" )
    {
        o = "-";
        result = x - y;
    }
    else if ( o == "mul" )
    {
        o = "*";
        result = x * y;
    }
    else if ( o == "div" )
    {
        o = "/";
        result = x / y;
    }
    else
    {
        std::cerr << "Unknown operator '" << o << "'." << std::endl;
        return 1;
    }

    // 演算結果を出力する。
    if ( commandline.hasValues() )
    {
        // ファイル名が指定された場合、そのファイルに結果を出力する。
        std::string filename = commandline.value<std::string>();
        std::ofstream ofs( filename.c_str(), std::ios::out );
        ofs << x << " " << o << " " << y << " = " << result << std::endl;
        ofs.close();
    }
    else
    {
        // ファイル名が指定されない場合、標準出力に結果を表示する。
        std::cout << x << " " << o << " " << y << " = " << result << std::endl;
    }

    return 0;
}
```