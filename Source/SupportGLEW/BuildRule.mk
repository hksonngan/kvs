#  DON'T EDIT THIS FILE.
#  THIS IS GENERATED BY "Configuration/configure_BuildRule.py".


OBJECTS := \
$(OUTDIR)/./Renderer/EnsembleAverageBuffer.o \
$(OUTDIR)/./Renderer/ParticleVolumeRenderer.o \
$(OUTDIR)/./Renderer/RayCastingRenderer.o \
$(OUTDIR)/./Viewer/BufferObject.o \
$(OUTDIR)/./Viewer/FragmentShader.o \
$(OUTDIR)/./Viewer/FrameBufferObject.o \
$(OUTDIR)/./Viewer/GeometryShader.o \
$(OUTDIR)/./Viewer/IndexBufferObject.o \
$(OUTDIR)/./Viewer/PixelBufferObject.o \
$(OUTDIR)/./Viewer/ProgramObject.o \
$(OUTDIR)/./Viewer/RenderBuffer.o \
$(OUTDIR)/./Viewer/ShaderObject.o \
$(OUTDIR)/./Viewer/ShaderSource.o \
$(OUTDIR)/./Viewer/Texture3D.o \
$(OUTDIR)/./Viewer/VertexBufferObject.o \
$(OUTDIR)/./Viewer/VertexShader.o \



$(OUTDIR)/./Viewer/%.o: ./Viewer/%.cpp ./Viewer/%.h
	$(MKDIR) $(OUTDIR)/./Viewer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Renderer/%.o: ./Renderer/%.cpp ./Renderer/%.h
	$(MKDIR) $(OUTDIR)/./Renderer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<


install::
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/.
	$(INSTALL) ./*.h $(INSTALL_DIR)/include/SupportGLEW/.
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Renderer
	$(INSTALL) ./Renderer/*.h $(INSTALL_DIR)/include/SupportGLEW/./Renderer
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Renderer/ParticleVolumeRenderer
	$(INSTALL) ./Renderer/ParticleVolumeRenderer/*.h $(INSTALL_DIR)/include/SupportGLEW/./Renderer/ParticleVolumeRenderer
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLEW/./Viewer
	$(INSTALL) ./Viewer/*.h $(INSTALL_DIR)/include/SupportGLEW/./Viewer
