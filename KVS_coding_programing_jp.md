# 9.3 プログラミング規約 #
実装に関する規約をまとめます。

## 9.3.1 メンバ変数の定義 ##
クラスのメンバ変数は、原則、private属性を付けて定義することとします。

```
private:
    int m_x;
    int m_y;
```

## 9.3.2 基本型の引数 ##
intやfloatなどの基本型（プリミティブ型）の値を入力として渡す場合は、それが入力値でありかつ変更が許されない値であることを明示するために、const属性を付けて記述することとします。

```
void Func( const int x )
```

## 9.3.3 ポインタ渡しと参照渡し ##
比較的大きなクラスまたは構造体を関数（メソッド）の引数として渡す場合は、それが入力である場合はconst属性を付けて参照渡しとし、出力または入出力である場合はポインタ渡しとします。

```
void Func( const ClassA& input, ClassB* output1, ClassC* input_output )
```

## 9.3.4 インクルードガード ##
ヘッダファイルの多重インクルードを防ぐため、すべて大文字で"`KVS__<名前空間名>__<ファイル名>_H_INCLUDE`"という書式のシンボル名を持つインクルードガード（defineガード）をヘッダファイルに記述することとします。ただし、名前空間がない場合は<名前空間>は省略可能であり、<ファイル名>が複数の単語からなる場合は下線で区切り記述することとします。また、最近では、多くのコンパイラで"`#pragma once`"（pragmaガード）が利用可能になってきていることから、defineガードにかえてpragmaガードを試験的に導入していくことを検討しています。

```
#ifndef KVS__NAMESPACE__FILE_NAME_H_INCLUDE
#define KVS__NAMESPACE__FILE_NAME_H_INCLUDE
...
#endif

#ifndef KVS__FILE_NAME_H_INCLUDE
#define KVS__FILE_NAME_H_INCLUDE
...
#endif
```