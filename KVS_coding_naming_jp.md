# 9.2 命名規約 #
クラスや変数などの名前の付け方に関する規約をまとめます。

## 9.2.1 クラス名 ##
クラス名は、名前を構成する各単語は大文字で開始すること（upper camel case）とします。

```
ClassName
```

また、クラス名は、原則、名詞で表現し、省略形を避け意味や役割が簡単にわかる名前とします。

```
// Good
VolumeRenderer

// Bad
volumeRenderer
volume_renderer
RenderVolume
VolRen
```

## 9.2.2 メンバ変数名 ##
クラスを構成するメンバ変数の名前は、先頭にm\_を付け、単語間に下線を付けることとします。

```
m_member_variable
```

メンバ変数も、クラス名と同様に、省略形を避け意味が簡単にわかる名前とします。

```
// Good
m_sampling_step

// Bad
m_samplingstep
m_SamplingStep
m_sstep
sampling_step_
_sampling_step
```

## 9.2.3 メソッド名（publicおよびprotected属性) ##
public属性およびprotected属性を持つメソッドの名前は、先頭は小文字としてそれ以降の単語は大文字で開始すること（lower camel case）とします。

```
methodName
```

## 9.2.4 メソッド名（private属性) ##
private属性を持つメソッドの名前は、原則、各単語を小文字で開始し、かつ、単語間に下線を付けることとします。

```
method_name
```

## 9.2.5 関数名および静的メソッド名 ##
関数名は、名前を構成する各単語は大文字で開始すること（upper camel case）とします。また、静的メソッドについても、クラスのインスタンスを作成することなく通常の関数と同じような役割を果たすため、関数名と同様の命名規約を適用します。

```
FunctionName
StaticMethodName
```

## 9.2.6 マクロ名 ##
マクロ名は、全て大文字とし、先頭にKVSを付け、単語間には下線を付けることとします。

```
KVS_MACRO_NAME
```