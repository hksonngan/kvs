# KVSMLサンプルデータ (polygon object) #

面データ（polygon object）のKVSMLデータ形式サンプルです。

```
<KVSML>
  <Object type="PolygonObject">
    <PolygonObject polygon_type="triangle" color_type="vertex" normal_type="vertex">
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
	<Normal>
	  <DataArray>
	    0.00  0.3  0.8
	    0.00 -0.9  0.0
	    0.72  0.3 -0.4
	    -0.72  0.3 -0.4
	  </DataArray>
	</Normal>
      </Vertex>
      <Polygon npolygons="4">
	<Connection>
	  <DataArray>
	    0 1 2
	    0 3 1
	    1 3 2
	    0 2 3
	  </DataArray>
	</Connection>
      </Polygon>
    </PolygonObject>
  </Object>
</KVSML>
```

![http://lh6.ggpht.com/_X4cB5gzzR7o/TE-gY-0X_iI/AAAAAAAAACE/ZAR3HUW06-Y/s512/KVSML_polygon.png](http://lh6.ggpht.com/_X4cB5gzzR7o/TE-gY-0X_iI/AAAAAAAAACE/ZAR3HUW06-Y/s512/KVSML_polygon.png)