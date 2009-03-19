#  DON'T EDIT THIS FILE.
#  THIS IS GENERATED BY "Configuration/configure_BuildRule.py".


OBJECTS := \
$(OUTDIR)/./Renderer/AxisRenderer.o \
$(OUTDIR)/./Viewer/Global.o \
$(OUTDIR)/./Viewer/GlobalBase.o \
$(OUTDIR)/./Viewer/Histogram.o \
$(OUTDIR)/./Viewer/LegendBar.o \
$(OUTDIR)/./Viewer/OrientationAxis.o \
$(OUTDIR)/./Viewer/Screen.o \
$(OUTDIR)/./Viewer/ScreenBase.o \
$(OUTDIR)/./Viewer/Text.o \



$(OUTDIR)/./Viewer/%.o: ./Viewer/%.cpp ./Viewer/%.h
	$(MKDIR) $(OUTDIR)/./Viewer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./Renderer/%.o: ./Renderer/%.cpp ./Renderer/%.h
	$(MKDIR) $(OUTDIR)/./Renderer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<


install::
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLUT/.
	$(INSTALL) ./*.h $(INSTALL_DIR)/include/SupportGLUT/.
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLUT/./Renderer
	$(INSTALL) ./Renderer/*.h $(INSTALL_DIR)/include/SupportGLUT/./Renderer
	$(MKDIR) $(INSTALL_DIR)/include/SupportGLUT/./Viewer
	$(INSTALL) ./Viewer/*.h $(INSTALL_DIR)/include/SupportGLUT/./Viewer
