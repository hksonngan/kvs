# KVS XML data format #

This page describes about the object data formats (XML) which is supported in KVS.

  * Geometric object data
    * Point object
    * Line object
    * Polygon object

  * Volumetric object data
    * Structured volume object
    * Unstructured volume object

## Point object ##

```
<KVSML>
  <Object type="PointObject">
    <PointObject>
      <Vertex nvertices="xxx">
        <Coord>
          <DataArray>
        </Coord>
        <Color>
          <DataArray> or <DataValue>
        </Color>
        <Normal>
          <DataArray>
        </Normal>
        <Size>
          <DataArray> or <DataValue>
        </Size>
      </Vertex>
    </PointObject>
  </Object>
</KVSML>
```

## Line Object ##

```
<KVSML>
  <Object type="LineObject">
    <!-- aaa: strip, uniline, polyline, segment -->
    <!-- bbb: line, vertex -->
    <LineObject line_type="aaa" color_type="bbb">
      <Vertex nvertices="xxx">
        <Coord>
          <DataArray>
        </Coord>
        <Color>
          <DataArray> or <DataValue>
        </Color>
        <Size>
          <DataArray> or <DataValue>
        </Size>
      </Vertex>
      <Line nlines="xxx">
        <Connection>
          <DataArray>
        </Connection>
      </Line>
    </LineObject>
  </Object>
</KVSML>
```

## Polygon Object ##

```
<KVSML>
  <Object type="PolygonObject">
    <!-- aaa: triangle, quadrangle -->
    <!-- bbb: polygon, vertex -->
    <PolygonObject polygon_type="aaa" color_type="bbb">
      <Vertex nvertices="xxx">
        <Coord>
          <DataArray>
        </Coord>
        <Color>
          <DataArray> or <DataValue>
        </Color>
        <Normal>
          <DataArray>
        </Normal>
      </Vertex>
      <Polygon npolygons="xxx">
        <Connection>
          <DataArray>
        </Connection>
      </Polygon>
    </PolygonObject>
  </Object>
</KVSML>
```

## Structured volume object ##

```
<KVSML>
  <Object type="StructuredVolumeObject">
    <!-- aaa: uniform, rectilinear, curvilinear -->
    <StructuredVolumeObject resolution="xxx xxx xxx" grid_type="aaa">
      <Node>
        <Value veclen="xxx">
          <DataArray>
        </Value>
      </Node>
    </StructuredVolumeObject>
  </Object>
</KVSML>
```

## Unstructured volume object ##

```
<KVSML>
  <Object type="UnstructuredVolumeObject">
    <!-- aaa: tetrahedra, quadratic tetrahedra, hexahedra, quadratic hexahedra -->
    <UnstructuredVolumeObject cell_type="aaa">
      <Node nnodes="xxx">
        <Value veclen="xxx">
          <DataArray>
        </Value>
        <Coord>
          <DataArray>
        </Coord>
      </Node>
      <Cell ncells="xxx">
        <Connection>
          <DataArray>
        </Connection>
      </Cell>
    </UnstructuredVolumeObject>
  </Object>
</KVSML>
```