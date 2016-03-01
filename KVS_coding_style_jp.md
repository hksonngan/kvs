# 9.1 スタイル規約 #
字下げや括弧の位置などソースコードの見栄えに関する規約をまとめます。一部のプログラム言語を除き、スタイル自体はプログラムの処理に影響を与えるものではなく必須ではないですが、ソースコードに一貫性を持たせるためにいくつかの規約を決めています。

## 9.1.1 字下げ ##
字下げはプログラムの構造をわかりやすくするために重要であり、多くのエディタではタブキーを押下することによって字下げを行います。しかし、タブ文字の幅は設定により異なり、ソースコードを開く環境によってはスタイルを崩す原因となる可能性があります。そのため、KVSでは、字下げはタブ文字を利用せず、半角スペース４文字で表現することとします。ただし、switch文内のcaseやdefaultのラベル、およびクラスのメンバ変数やメソッドのアクセス属性を指定するprivate, protected, publicの修飾子については字下げを行わず記述することとします。

```
// Good
void Func()
{
    const int n = 10;
    for ( int i = 0; i < n; i++ )
    {
        DoSomething();
    }
}

switch( x )
{
case y:
    break;
default:
    break;
}

class ClassName
{
public:
    ClassName();
};
```
```
// Bad
void Func()
{
const int n = 10;
for ( int i = 0; i < n; i++ )
{
DoSomething();
}
}

switch( x )
{
    case y:
        break;
    default:
        break;
}

class ClassName
{
    public:
        ClassName();
};
```

## 9.1.2 中括弧の位置 ##
処理ブロックの範囲を表現する中括弧の位置については、様々なスタイルが存在しますが、KVSでは次のようにスタイルを統一します。中括弧の開始位置（開き中括弧（"{"）の位置）は、if文やfor文などの制御文の後ろではなく、その次の行に改行し、直前の行の先頭文字と同じに位置に置くこととします。また、閉じ中括弧（"}"）は、処理ブロックの最後から独立した位置に置くこととします。また、クラス定義および関数定義においても、制御文と同様に、中括弧は独立した行に置くこととする。
```
// Good
if ( x == y )
{
   DoSomething();
}

for ( int i = 0; i < n; i++ )
{
   DoSomething();
}

class ClassName
{
public:
    ClassName();
};

void FuncName()
{
    DoSomething();
}
```
```
// Bad
if ( x == y ) {
   DoSomething();
}

for ( int i = 0; i < n; i++ ) {
   DoSomething();
}

class ClassName {
public:
    ClassName();
};

void FuncName() {
    DoSomething();
}
```

## 9.1.3 制御文の括弧の位置 ##
制御文の条件などを記述するための括弧については、ifやforなどの命令の後ろにスペースを空け、空き括弧（"("）を置くこととし、その直後の条件式等は空き括弧の後ろにスペースを明けて記述することとします。また、閉じ括弧（")"）の直前にもスペースを空けることとします。

```
// Good
if ( x == y )
for ( int i = 0; i < n; i++ )
while ( x < y )
```
```
// Bad
if(x == y)
for(int i = 0; i < n; i++)
while(x < y)
```

## 9.1.4 return文の括弧 ##
プログラムにおいて、return文は関数の終了を表し、同時に呼び出しもとに値（戻り値）を返す役割を持ちます。一般的に、return文の戻り値は括弧を付けて記述される場合と付けずに記述される場合がありますが、KVSでは括弧を付けずに記述することとします。

```
// Good
return x;
```
```
// Bad
return( x );
```

## 9.1.5 引数なしの関数の定義 ##
引数を持たない関数を定義する場合、明示的にvoidと記述することがありますが、KVSではvoidを付けず括弧のみを記述することとします。

```
// Good
void Func()
{
    DoSomething();
}
```
```
// Bad
void Func( void )
{
    DoSomething();
}
```

## 9.1.6 初期化リスト ##
クラスの複数のメンバ変数に対してコンストラクタで初期化を行う場合、メンバ変数であることを目立たせるなどの目的で、初期化リストの行頭に区切り文字「,」を付けることがありますが、KVSでは「,」は行末に付けることとします。

```
// Good
ClassName::ClassName( int param1, int param2, int param3 ):
    m_param1( param1 ),
    m_param2( param2 ),
    m_param3( param3 )
{
    DoSomething();
}
```
```
// Bad
ClassName::ClassName( int param1, int param2, int param3 )
    : m_param1( param1 )
    , m_param2( param2 )
    , m_param3( param3 )
{
    DoSomething();
}
```