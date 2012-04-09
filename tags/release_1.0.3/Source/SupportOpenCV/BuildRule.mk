#  DON'T EDIT THIS FILE.
#  THIS IS GENERATED BY "Configuration/configure_BuildRule.py".


OBJECTS := \
$(OUTDIR)/./Object/VideoObject.o \
$(OUTDIR)/./Renderer/VideoRenderer.o \
$(OUTDIR)/./Viewer/CaptureDevice.o \
$(OUTDIR)/./Viewer/Window.o \



$(OUTDIR)/./Viewer/%.o: ./Viewer/%.cpp ./Viewer/%.h
	$(MKDIR) $(OUTDIR)/./Viewer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Renderer/%.o: ./Renderer/%.cpp ./Renderer/%.h
	$(MKDIR) $(OUTDIR)/./Renderer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Object/%.o: ./Object/%.cpp ./Object/%.h
	$(MKDIR) $(OUTDIR)/./Object
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<


install::
	$(MKDIR) $(INSTALL_DIR)/include/SupportOpenCV/.
	$(INSTALL) ./*.h $(INSTALL_DIR)/include/SupportOpenCV/.
	$(MKDIR) $(INSTALL_DIR)/include/SupportOpenCV/./Object
	$(INSTALL) ./Object/*.h $(INSTALL_DIR)/include/SupportOpenCV/./Object
	$(MKDIR) $(INSTALL_DIR)/include/SupportOpenCV/./Renderer
	$(INSTALL) ./Renderer/*.h $(INSTALL_DIR)/include/SupportOpenCV/./Renderer
	$(MKDIR) $(INSTALL_DIR)/include/SupportOpenCV/./Viewer
	$(INSTALL) ./Viewer/*.h $(INSTALL_DIR)/include/SupportOpenCV/./Viewer