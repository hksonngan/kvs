#  DON'T EDIT THIS FILE.
#  THIS IS GENERATED BY "Configuration/configure_BuildRule.py".


OBJECTS := \
$(OUTDIR)/./FileFormat/AVSField/AVSField.o \
$(OUTDIR)/./FileFormat/AVSUCD/AVSUcd.o \
$(OUTDIR)/./FileFormat/BMP/Bmp.o \
$(OUTDIR)/./FileFormat/BMP/FileHeader.o \
$(OUTDIR)/./FileFormat/BMP/InfoHeader.o \
$(OUTDIR)/./FileFormat/DICOM/Attribute.o \
$(OUTDIR)/./FileFormat/DICOM/Dicom.o \
$(OUTDIR)/./FileFormat/DICOM/DicomList.o \
$(OUTDIR)/./FileFormat/DICOM/Element.o \
$(OUTDIR)/./FileFormat/DICOM/Item.o \
$(OUTDIR)/./FileFormat/DICOM/Tag.o \
$(OUTDIR)/./FileFormat/DICOM/VR.o \
$(OUTDIR)/./FileFormat/DICOM/Value.o \
$(OUTDIR)/./FileFormat/DICOM/Window.o \
$(OUTDIR)/./FileFormat/FileFormatBase.o \
$(OUTDIR)/./FileFormat/KVSML/CellTag.o \
$(OUTDIR)/./FileFormat/KVSML/ColorTag.o \
$(OUTDIR)/./FileFormat/KVSML/ConnectionTag.o \
$(OUTDIR)/./FileFormat/KVSML/CoordTag.o \
$(OUTDIR)/./FileFormat/KVSML/DataArrayTag.o \
$(OUTDIR)/./FileFormat/KVSML/DataValueTag.o \
$(OUTDIR)/./FileFormat/KVSML/KVSMLObjectLine.o \
$(OUTDIR)/./FileFormat/KVSML/KVSMLObjectPoint.o \
$(OUTDIR)/./FileFormat/KVSML/KVSMLObjectPolygon.o \
$(OUTDIR)/./FileFormat/KVSML/KVSMLObjectStructuredVolume.o \
$(OUTDIR)/./FileFormat/KVSML/KVSMLObjectUnstructuredVolume.o \
$(OUTDIR)/./FileFormat/KVSML/KVSMLTag.o \
$(OUTDIR)/./FileFormat/KVSML/KVSMLTransferFunction.o \
$(OUTDIR)/./FileFormat/KVSML/LineObjectTag.o \
$(OUTDIR)/./FileFormat/KVSML/LineTag.o \
$(OUTDIR)/./FileFormat/KVSML/NodeTag.o \
$(OUTDIR)/./FileFormat/KVSML/NormalTag.o \
$(OUTDIR)/./FileFormat/KVSML/ObjectTag.o \
$(OUTDIR)/./FileFormat/KVSML/OpacityTag.o \
$(OUTDIR)/./FileFormat/KVSML/PointObjectTag.o \
$(OUTDIR)/./FileFormat/KVSML/PolygonObjectTag.o \
$(OUTDIR)/./FileFormat/KVSML/PolygonTag.o \
$(OUTDIR)/./FileFormat/KVSML/SizeTag.o \
$(OUTDIR)/./FileFormat/KVSML/StructuredVolumeObjectTag.o \
$(OUTDIR)/./FileFormat/KVSML/TagParser.o \
$(OUTDIR)/./FileFormat/KVSML/TransferFunctionParser.o \
$(OUTDIR)/./FileFormat/KVSML/UnstructuredVolumeObjectTag.o \
$(OUTDIR)/./FileFormat/KVSML/ValueTag.o \
$(OUTDIR)/./FileFormat/KVSML/VertexTag.o \
$(OUTDIR)/./FileFormat/PNM/Header.o \
$(OUTDIR)/./FileFormat/PNM/Pbm.o \
$(OUTDIR)/./FileFormat/PNM/Pgm.o \
$(OUTDIR)/./FileFormat/PNM/Ppm.o \
$(OUTDIR)/./FileFormat/STL/Stl.o \
$(OUTDIR)/./FileFormat/TIFF/Entry.o \
$(OUTDIR)/./FileFormat/TIFF/Header.o \
$(OUTDIR)/./FileFormat/TIFF/ImageFileDirectory.o \
$(OUTDIR)/./FileFormat/TIFF/Tag.o \
$(OUTDIR)/./FileFormat/TIFF/TagDictionary.o \
$(OUTDIR)/./FileFormat/TIFF/Tiff.o \
$(OUTDIR)/./FileFormat/XML/TinyXML.o \
$(OUTDIR)/./FileFormat/XML/XMLComment.o \
$(OUTDIR)/./FileFormat/XML/XMLDeclaration.o \
$(OUTDIR)/./FileFormat/XML/XMLDocument.o \
$(OUTDIR)/./FileFormat/XML/XMLElement.o \
$(OUTDIR)/./FileFormat/XML/XMLNode.o \
$(OUTDIR)/./Image/BitImage.o \
$(OUTDIR)/./Image/ColorImage.o \
$(OUTDIR)/./Image/GrayImage.o \
$(OUTDIR)/./Image/HSVColor.o \
$(OUTDIR)/./Image/ImageBase.o \
$(OUTDIR)/./Image/RGBAColor.o \
$(OUTDIR)/./Image/RGBColor.o \
$(OUTDIR)/./Matrix/Matrix.o \
$(OUTDIR)/./Matrix/Matrix33.o \
$(OUTDIR)/./Matrix/Matrix44.o \
$(OUTDIR)/./Matrix/Vector.o \
$(OUTDIR)/./Matrix/Vector2.o \
$(OUTDIR)/./Matrix/Vector3.o \
$(OUTDIR)/./Matrix/Vector4.o \
$(OUTDIR)/./Network/HttpConnector.o \
$(OUTDIR)/./Network/HttpRequestHeader.o \
$(OUTDIR)/./Network/IPAddress.o \
$(OUTDIR)/./Network/MessageBlock.o \
$(OUTDIR)/./Network/Socket.o \
$(OUTDIR)/./Network/SocketAddress.o \
$(OUTDIR)/./Network/SocketSelector.o \
$(OUTDIR)/./Network/SocketTimer.o \
$(OUTDIR)/./Network/TCPServer.o \
$(OUTDIR)/./Network/TCPSocket.o \
$(OUTDIR)/./Network/Url.o \
$(OUTDIR)/./Numeric/MersenneTwister.o \
$(OUTDIR)/./Numeric/Quaternion.o \
$(OUTDIR)/./Numeric/Xorshift128.o \
$(OUTDIR)/./Thread/Condition.o \
$(OUTDIR)/./Thread/Mutex.o \
$(OUTDIR)/./Thread/MutexLocker.o \
$(OUTDIR)/./Thread/ReadLocker.o \
$(OUTDIR)/./Thread/ReadWriteLock.o \
$(OUTDIR)/./Thread/Semaphore.o \
$(OUTDIR)/./Thread/Thread.o \
$(OUTDIR)/./Thread/WriteLocker.o \
$(OUTDIR)/./Utility/AnyValue.o \
$(OUTDIR)/./Utility/AnyValueArray.o \
$(OUTDIR)/./Utility/BitArray.o \
$(OUTDIR)/./Utility/CommandLine.o \
$(OUTDIR)/./Utility/Date.o \
$(OUTDIR)/./Utility/Directory.o \
$(OUTDIR)/./Utility/FastTokenizer.o \
$(OUTDIR)/./Utility/File.o \
$(OUTDIR)/./Utility/Message.o \
$(OUTDIR)/./Utility/ReferenceCounter.o \
$(OUTDIR)/./Utility/String.o \
$(OUTDIR)/./Utility/SystemInformation.o \
$(OUTDIR)/./Utility/Time.o \
$(OUTDIR)/./Utility/Tokenizer.o \
$(OUTDIR)/./Utility/Value.o \
$(OUTDIR)/./Utility/ValueArray.o \
$(OUTDIR)/./Visualization/Exporter/LineExporter.o \
$(OUTDIR)/./Visualization/Exporter/PointExporter.o \
$(OUTDIR)/./Visualization/Exporter/PolygonExporter.o \
$(OUTDIR)/./Visualization/Exporter/StructuredVolumeExporter.o \
$(OUTDIR)/./Visualization/Exporter/UnstructuredVolumeExporter.o \
$(OUTDIR)/./Visualization/Filter/Bounds.o \
$(OUTDIR)/./Visualization/Filter/FilterBase.o \
$(OUTDIR)/./Visualization/Filter/LineIntegralConvolution.o \
$(OUTDIR)/./Visualization/Filter/TrilinearInterpolator.o \
$(OUTDIR)/./Visualization/Filter/Tubeline.o \
$(OUTDIR)/./Visualization/Importer/ImageImporter.o \
$(OUTDIR)/./Visualization/Importer/ImporterBase.o \
$(OUTDIR)/./Visualization/Importer/LineImporter.o \
$(OUTDIR)/./Visualization/Importer/PointImporter.o \
$(OUTDIR)/./Visualization/Importer/PolygonImporter.o \
$(OUTDIR)/./Visualization/Importer/StructuredVolumeImporter.o \
$(OUTDIR)/./Visualization/Importer/UnstructuredVolumeImporter.o \
$(OUTDIR)/./Visualization/Mapper/CellByCellMetropolisSampling.o \
$(OUTDIR)/./Visualization/Mapper/CellByCellUniformSampling.o \
$(OUTDIR)/./Visualization/Mapper/ColorMap.o \
$(OUTDIR)/./Visualization/Mapper/ExtractVertices.o \
$(OUTDIR)/./Visualization/Mapper/FrequencyTable.o \
$(OUTDIR)/./Visualization/Mapper/HexahedralCell.o \
$(OUTDIR)/./Visualization/Mapper/HitAndMissSampling.o \
$(OUTDIR)/./Visualization/Mapper/Isosurface.o \
$(OUTDIR)/./Visualization/Mapper/MapperBase.o \
$(OUTDIR)/./Visualization/Mapper/MarchingCubes.o \
$(OUTDIR)/./Visualization/Mapper/MarchingCubesTable.o \
$(OUTDIR)/./Visualization/Mapper/MarchingTetrahedra.o \
$(OUTDIR)/./Visualization/Mapper/MarchingTetrahedraTable.o \
$(OUTDIR)/./Visualization/Mapper/MetropolisSampling.o \
$(OUTDIR)/./Visualization/Mapper/OpacityMap.o \
$(OUTDIR)/./Visualization/Mapper/OrthoSlice.o \
$(OUTDIR)/./Visualization/Mapper/QuadraticHexahedralCell.o \
$(OUTDIR)/./Visualization/Mapper/QuadraticTetrahedralCell.o \
$(OUTDIR)/./Visualization/Mapper/SlicePlane.o \
$(OUTDIR)/./Visualization/Mapper/Streamline.o \
$(OUTDIR)/./Visualization/Mapper/StreamlineBase.o \
$(OUTDIR)/./Visualization/Mapper/TetrahedralCell.o \
$(OUTDIR)/./Visualization/Mapper/TransferFunction.o \
$(OUTDIR)/./Visualization/Object/AxisObject.o \
$(OUTDIR)/./Visualization/Object/GeometryObjectBase.o \
$(OUTDIR)/./Visualization/Object/ImageObject.o \
$(OUTDIR)/./Visualization/Object/LineObject.o \
$(OUTDIR)/./Visualization/Object/ObjectBase.o \
$(OUTDIR)/./Visualization/Object/PointObject.o \
$(OUTDIR)/./Visualization/Object/PolygonObject.o \
$(OUTDIR)/./Visualization/Object/StructuredVolumeObject.o \
$(OUTDIR)/./Visualization/Object/UnstructuredVolumeObject.o \
$(OUTDIR)/./Visualization/Object/VolumeObjectBase.o \
$(OUTDIR)/./Visualization/Pipeline/ObjectImporter.o \
$(OUTDIR)/./Visualization/Pipeline/PipelineModule.o \
$(OUTDIR)/./Visualization/Pipeline/VisualizationPipeline.o \
$(OUTDIR)/./Visualization/Renderer/ImageRenderer.o \
$(OUTDIR)/./Visualization/Renderer/LineRenderer.o \
$(OUTDIR)/./Visualization/Renderer/ParticleBuffer.o \
$(OUTDIR)/./Visualization/Renderer/ParticleBufferAccumulator.o \
$(OUTDIR)/./Visualization/Renderer/ParticleBufferCompositor.o \
$(OUTDIR)/./Visualization/Renderer/ParticleVolumeRenderer.o \
$(OUTDIR)/./Visualization/Renderer/PointRenderer.o \
$(OUTDIR)/./Visualization/Renderer/PolygonRenderer.o \
$(OUTDIR)/./Visualization/Renderer/Ray.o \
$(OUTDIR)/./Visualization/Renderer/RayCastingRenderer.o \
$(OUTDIR)/./Visualization/Renderer/RendererBase.o \
$(OUTDIR)/./Visualization/Renderer/Shader.o \
$(OUTDIR)/./Visualization/Renderer/VolumeRayIntersector.o \
$(OUTDIR)/./Visualization/Renderer/VolumeRendererBase.o \
$(OUTDIR)/./Visualization/Viewer/Background.o \
$(OUTDIR)/./Visualization/Viewer/Camera.o \
$(OUTDIR)/./Visualization/Viewer/DisplayFormat.o \
$(OUTDIR)/./Visualization/Viewer/DisplayList.o \
$(OUTDIR)/./Visualization/Viewer/FrameBuffer.o \
$(OUTDIR)/./Visualization/Viewer/GlobalCore.o \
$(OUTDIR)/./Visualization/Viewer/IDManager.o \
$(OUTDIR)/./Visualization/Viewer/KeyEvent.o \
$(OUTDIR)/./Visualization/Viewer/Light.o \
$(OUTDIR)/./Visualization/Viewer/Material.o \
$(OUTDIR)/./Visualization/Viewer/Mouse.o \
$(OUTDIR)/./Visualization/Viewer/MouseEvent.o \
$(OUTDIR)/./Visualization/Viewer/ObjectManager.o \
$(OUTDIR)/./Visualization/Viewer/RendererManager.o \
$(OUTDIR)/./Visualization/Viewer/ScreenCore.o \
$(OUTDIR)/./Visualization/Viewer/Texture2D.o \
$(OUTDIR)/./Visualization/Viewer/TextureBase.o \
$(OUTDIR)/./Visualization/Viewer/Trackball.o \
$(OUTDIR)/./Visualization/Viewer/Xform.o \
$(OUTDIR)/./Visualization/Viewer/XformControl.o \



$(OUTDIR)/./Visualization/Viewer/%.o: ./Visualization/Viewer/%.cpp ./Visualization/Viewer/%.h
	$(MKDIR) $(OUTDIR)/./Visualization/Viewer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Visualization/Renderer/%.o: ./Visualization/Renderer/%.cpp ./Visualization/Renderer/%.h
	$(MKDIR) $(OUTDIR)/./Visualization/Renderer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Visualization/Pipeline/%.o: ./Visualization/Pipeline/%.cpp ./Visualization/Pipeline/%.h
	$(MKDIR) $(OUTDIR)/./Visualization/Pipeline
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Visualization/Object/%.o: ./Visualization/Object/%.cpp ./Visualization/Object/%.h
	$(MKDIR) $(OUTDIR)/./Visualization/Object
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Visualization/Mapper/%.o: ./Visualization/Mapper/%.cpp ./Visualization/Mapper/%.h
	$(MKDIR) $(OUTDIR)/./Visualization/Mapper
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Visualization/Importer/%.o: ./Visualization/Importer/%.cpp ./Visualization/Importer/%.h
	$(MKDIR) $(OUTDIR)/./Visualization/Importer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Visualization/Filter/%.o: ./Visualization/Filter/%.cpp ./Visualization/Filter/%.h
	$(MKDIR) $(OUTDIR)/./Visualization/Filter
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Visualization/Exporter/%.o: ./Visualization/Exporter/%.cpp ./Visualization/Exporter/%.h
	$(MKDIR) $(OUTDIR)/./Visualization/Exporter
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Utility/%.o: ./Utility/%.cpp ./Utility/%.h
	$(MKDIR) $(OUTDIR)/./Utility
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Thread/%.o: ./Thread/%.cpp ./Thread/%.h
	$(MKDIR) $(OUTDIR)/./Thread
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Numeric/%.o: ./Numeric/%.cpp ./Numeric/%.h
	$(MKDIR) $(OUTDIR)/./Numeric
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Network/%.o: ./Network/%.cpp ./Network/%.h
	$(MKDIR) $(OUTDIR)/./Network
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Matrix/%.o: ./Matrix/%.cpp ./Matrix/%.h
	$(MKDIR) $(OUTDIR)/./Matrix
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Image/%.o: ./Image/%.cpp ./Image/%.h
	$(MKDIR) $(OUTDIR)/./Image
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./FileFormat/XML/%.o: ./FileFormat/XML/%.cpp ./FileFormat/XML/%.h
	$(MKDIR) $(OUTDIR)/./FileFormat/XML
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./FileFormat/TIFF/%.o: ./FileFormat/TIFF/%.cpp ./FileFormat/TIFF/%.h
	$(MKDIR) $(OUTDIR)/./FileFormat/TIFF
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./FileFormat/STL/%.o: ./FileFormat/STL/%.cpp ./FileFormat/STL/%.h
	$(MKDIR) $(OUTDIR)/./FileFormat/STL
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./FileFormat/PNM/%.o: ./FileFormat/PNM/%.cpp ./FileFormat/PNM/%.h
	$(MKDIR) $(OUTDIR)/./FileFormat/PNM
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./FileFormat/KVSML/%.o: ./FileFormat/KVSML/%.cpp ./FileFormat/KVSML/%.h
	$(MKDIR) $(OUTDIR)/./FileFormat/KVSML
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./FileFormat/DICOM/%.o: ./FileFormat/DICOM/%.cpp ./FileFormat/DICOM/%.h
	$(MKDIR) $(OUTDIR)/./FileFormat/DICOM
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./FileFormat/BMP/%.o: ./FileFormat/BMP/%.cpp ./FileFormat/BMP/%.h
	$(MKDIR) $(OUTDIR)/./FileFormat/BMP
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./FileFormat/AVSUCD/%.o: ./FileFormat/AVSUCD/%.cpp ./FileFormat/AVSUCD/%.h
	$(MKDIR) $(OUTDIR)/./FileFormat/AVSUCD
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./FileFormat/AVSField/%.o: ./FileFormat/AVSField/%.cpp ./FileFormat/AVSField/%.h
	$(MKDIR) $(OUTDIR)/./FileFormat/AVSField
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./FileFormat/%.o: ./FileFormat/%.cpp ./FileFormat/%.h
	$(MKDIR) $(OUTDIR)/./FileFormat
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<


install::
	$(MKDIR) $(INSTALL_DIR)/include/Core/./FileFormat
	$(INSTALL) ./FileFormat/*.h $(INSTALL_DIR)/include/Core/./FileFormat
	$(MKDIR) $(INSTALL_DIR)/include/Core/./FileFormat/AVSField
	$(INSTALL) ./FileFormat/AVSField/*.h $(INSTALL_DIR)/include/Core/./FileFormat/AVSField
	$(MKDIR) $(INSTALL_DIR)/include/Core/./FileFormat/AVSUCD
	$(INSTALL) ./FileFormat/AVSUCD/*.h $(INSTALL_DIR)/include/Core/./FileFormat/AVSUCD
	$(MKDIR) $(INSTALL_DIR)/include/Core/./FileFormat/BMP
	$(INSTALL) ./FileFormat/BMP/*.h $(INSTALL_DIR)/include/Core/./FileFormat/BMP
	$(MKDIR) $(INSTALL_DIR)/include/Core/./FileFormat/DICOM
	$(INSTALL) ./FileFormat/DICOM/*.h $(INSTALL_DIR)/include/Core/./FileFormat/DICOM
	$(MKDIR) $(INSTALL_DIR)/include/Core/./FileFormat/KVSML
	$(INSTALL) ./FileFormat/KVSML/*.h $(INSTALL_DIR)/include/Core/./FileFormat/KVSML
	$(MKDIR) $(INSTALL_DIR)/include/Core/./FileFormat/PNM
	$(INSTALL) ./FileFormat/PNM/*.h $(INSTALL_DIR)/include/Core/./FileFormat/PNM
	$(MKDIR) $(INSTALL_DIR)/include/Core/./FileFormat/STL
	$(INSTALL) ./FileFormat/STL/*.h $(INSTALL_DIR)/include/Core/./FileFormat/STL
	$(MKDIR) $(INSTALL_DIR)/include/Core/./FileFormat/TIFF
	$(INSTALL) ./FileFormat/TIFF/*.h $(INSTALL_DIR)/include/Core/./FileFormat/TIFF
	$(MKDIR) $(INSTALL_DIR)/include/Core/./FileFormat/XML
	$(INSTALL) ./FileFormat/XML/*.h $(INSTALL_DIR)/include/Core/./FileFormat/XML
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Image
	$(INSTALL) ./Image/*.h $(INSTALL_DIR)/include/Core/./Image
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Matrix
	$(INSTALL) ./Matrix/*.h $(INSTALL_DIR)/include/Core/./Matrix
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Network
	$(INSTALL) ./Network/*.h $(INSTALL_DIR)/include/Core/./Network
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Numeric
	$(INSTALL) ./Numeric/*.h $(INSTALL_DIR)/include/Core/./Numeric
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Thread
	$(INSTALL) ./Thread/*.h $(INSTALL_DIR)/include/Core/./Thread
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Utility
	$(INSTALL) ./Utility/*.h $(INSTALL_DIR)/include/Core/./Utility
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Visualization
	$(INSTALL) ./Visualization/*.h $(INSTALL_DIR)/include/Core/./Visualization
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Visualization/Exporter
	$(INSTALL) ./Visualization/Exporter/*.h $(INSTALL_DIR)/include/Core/./Visualization/Exporter
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Visualization/Filter
	$(INSTALL) ./Visualization/Filter/*.h $(INSTALL_DIR)/include/Core/./Visualization/Filter
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Visualization/Importer
	$(INSTALL) ./Visualization/Importer/*.h $(INSTALL_DIR)/include/Core/./Visualization/Importer
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Visualization/Mapper
	$(INSTALL) ./Visualization/Mapper/*.h $(INSTALL_DIR)/include/Core/./Visualization/Mapper
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Visualization/Object
	$(INSTALL) ./Visualization/Object/*.h $(INSTALL_DIR)/include/Core/./Visualization/Object
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Visualization/Pipeline
	$(INSTALL) ./Visualization/Pipeline/*.h $(INSTALL_DIR)/include/Core/./Visualization/Pipeline
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Visualization/Renderer
	$(INSTALL) ./Visualization/Renderer/*.h $(INSTALL_DIR)/include/Core/./Visualization/Renderer
	$(MKDIR) $(INSTALL_DIR)/include/Core/./Visualization/Viewer
	$(INSTALL) ./Visualization/Viewer/*.h $(INSTALL_DIR)/include/Core/./Visualization/Viewer
