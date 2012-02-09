#  DON'T EDIT THIS FILE.
#  THIS IS GENERATED BY "Configuration/configure_BuildRule.py".


OBJECTS = \
$(OUTDIR)\.\Renderer\EnsembleAverageBuffer.obj \
$(OUTDIR)\.\Renderer\HAVSVolumeRenderer.obj \
$(OUTDIR)\.\Renderer\ParticleBasedRenderer.obj \
$(OUTDIR)\.\Renderer\ParticleVolumeRenderer.obj \
$(OUTDIR)\.\Renderer\PointRenderer.obj \
$(OUTDIR)\.\Renderer\PolygonRenderer.obj \
$(OUTDIR)\.\Renderer\PreIntegrationTable.obj \
$(OUTDIR)\.\Renderer\ProjectedTetrahedraTable.obj \
$(OUTDIR)\.\Renderer\RayCastingRenderer.obj \
$(OUTDIR)\.\Renderer\StochasticLineEngine.obj \
$(OUTDIR)\.\Renderer\StochasticLineRenderer.obj \
$(OUTDIR)\.\Renderer\StochasticPointEngine.obj \
$(OUTDIR)\.\Renderer\StochasticPointRenderer.obj \
$(OUTDIR)\.\Renderer\StochasticPolygonEngine.obj \
$(OUTDIR)\.\Renderer\StochasticPolygonRenderer.obj \
$(OUTDIR)\.\Renderer\StochasticRendererBase.obj \
$(OUTDIR)\.\Renderer\StochasticRenderingCompositor.obj \
$(OUTDIR)\.\Renderer\StochasticRenderingEngine.obj \
$(OUTDIR)\.\Renderer\StochasticTetrahedraEngine.obj \
$(OUTDIR)\.\Renderer\StochasticTetrahedraRenderer.obj \
$(OUTDIR)\.\Viewer\BufferObject.obj \
$(OUTDIR)\.\Viewer\FragmentShader.obj \
$(OUTDIR)\.\Viewer\FrameBufferObject.obj \
$(OUTDIR)\.\Viewer\GeometryShader.obj \
$(OUTDIR)\.\Viewer\IndexBufferObject.obj \
$(OUTDIR)\.\Viewer\PixelBufferObject.obj \
$(OUTDIR)\.\Viewer\ProgramObject.obj \
$(OUTDIR)\.\Viewer\RenderBuffer.obj \
$(OUTDIR)\.\Viewer\ShaderObject.obj \
$(OUTDIR)\.\Viewer\ShaderSource.obj \
$(OUTDIR)\.\Viewer\Texture3D.obj \
$(OUTDIR)\.\Viewer\TextureRectangle.obj \
$(OUTDIR)\.\Viewer\VertexBufferObject.obj \
$(OUTDIR)\.\Viewer\VertexShader.obj \



{.\Viewer\}.cpp{$(OUTDIR)\.\Viewer\}.obj::
	IF NOT EXIST $(OUTDIR)\.\Viewer $(MKDIR) $(OUTDIR)\.\Viewer
	$(CPP) /c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) /Fo$(OUTDIR)\.\Viewer\ @<<
$<
<<

{.\Renderer\}.cpp{$(OUTDIR)\.\Renderer\}.obj::
	IF NOT EXIST $(OUTDIR)\.\Renderer $(MKDIR) $(OUTDIR)\.\Renderer
	$(CPP) /c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) /Fo$(OUTDIR)\.\Renderer\ @<<
$<
<<


install::
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLEW\. $(MKDIR) $(INSTALL_DIR)\include\SupportGLEW\.
	$(INSTALL) .\*.h $(INSTALL_DIR)\include\SupportGLEW\.
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLEW\.\Renderer $(MKDIR) $(INSTALL_DIR)\include\SupportGLEW\.\Renderer
	$(INSTALL) .\Renderer\*.h $(INSTALL_DIR)\include\SupportGLEW\.\Renderer
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\HAVSVolumeRenderer $(MKDIR) $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\HAVSVolumeRenderer
	$(INSTALL) .\Renderer\HAVSVolumeRenderer\*.h $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\HAVSVolumeRenderer
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\ParticleVolumeRenderer $(MKDIR) $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\ParticleVolumeRenderer
	$(INSTALL) .\Renderer\ParticleVolumeRenderer\*.h $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\ParticleVolumeRenderer
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\PointRenderer $(MKDIR) $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\PointRenderer
	$(INSTALL) .\Renderer\PointRenderer\*.h $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\PointRenderer
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\PolygonRenderer $(MKDIR) $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\PolygonRenderer
	$(INSTALL) .\Renderer\PolygonRenderer\*.h $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\PolygonRenderer
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\RayCastingRenderer $(MKDIR) $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\RayCastingRenderer
	$(INSTALL) .\Renderer\RayCastingRenderer\*.h $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\RayCastingRenderer
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\Shader $(MKDIR) $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\Shader
	$(INSTALL) .\Renderer\Shader\*.h $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\Shader
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\StochasticRenderingEngine $(MKDIR) $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\StochasticRenderingEngine
	$(INSTALL) .\Renderer\StochasticRenderingEngine\*.h $(INSTALL_DIR)\include\SupportGLEW\.\Renderer\StochasticRenderingEngine
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLEW\.\Viewer $(MKDIR) $(INSTALL_DIR)\include\SupportGLEW\.\Viewer
	$(INSTALL) .\Viewer\*.h $(INSTALL_DIR)\include\SupportGLEW\.\Viewer
