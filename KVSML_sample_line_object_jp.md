# KVSMLサンプルデータ (line object) #

線データ（line object）のKVSMLデータ形式サンプルです。

```
<KVSML>
  <Object type="LineObject">
    <LineObject line_type="segment" color_type="vertex">
      <Vertex nvertices="4">
	<Coord>
	  <DataArray>
	    1.0 0.0 2.0
	    2.0 0.0 2.0
	    1.5 0.8 1.7
	    1.5 0.0 1.1
	  </DataArray>
	</Coord>
	<Color>
	  <DataArray>
	    255 0 0
	    0 255 0
	    0 0 255
	    255 255 0
	  </DataArray>
	</Color>
      </Vertex>
      <Line nlines="6">
	<Size>
	  <DataValue>10</DataValue>
	</Size>
	<Connection>
	  <DataArray>
	    0 1
	    1 2
	    2 0
	    3 0
	    3 1
	    3 2
	  </DataArray>
	</Connection>
      </Line>
    </LineObject>
  </Object>
</KVSML>
```

![http://lh4.ggpht.com/_X4cB5gzzR7o/TE-gYprOTcI/AAAAAAAAACA/klG1q_nVlhg/s512/KVSML_line.png](http://lh4.ggpht.com/_X4cB5gzzR7o/TE-gYprOTcI/AAAAAAAAACA/klG1q_nVlhg/s512/KVSML_line.png)