#  DON'T EDIT THIS FILE.
#  THIS IS GENERATED BY "Configuration/configure_BuildRule.py".


OBJECTS = \
$(OUTDIR)\.\Renderer\AxisRenderer.obj \
$(OUTDIR)\.\Viewer\Application.obj \
$(OUTDIR)\.\Viewer\Global.obj \
$(OUTDIR)\.\Viewer\GlobalBase.obj \
$(OUTDIR)\.\Viewer\Histogram.obj \
$(OUTDIR)\.\Viewer\LegendBar.obj \
$(OUTDIR)\.\Viewer\OrientationAxis.obj \
$(OUTDIR)\.\Viewer\Screen.obj \
$(OUTDIR)\.\Viewer\ScreenBase.obj \
$(OUTDIR)\.\Viewer\Text.obj \
$(OUTDIR)\.\Viewer\Timer.obj \
$(OUTDIR)\.\Viewer\TransferFunctionEditor.obj \
$(OUTDIR)\.\Viewer\Window.obj \



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
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLUT\. $(MKDIR) $(INSTALL_DIR)\include\SupportGLUT\.
	$(INSTALL) .\*.h $(INSTALL_DIR)\include\SupportGLUT\.
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLUT\.\Renderer $(MKDIR) $(INSTALL_DIR)\include\SupportGLUT\.\Renderer
	$(INSTALL) .\Renderer\*.h $(INSTALL_DIR)\include\SupportGLUT\.\Renderer
	IF NOT EXIST $(INSTALL_DIR)\include\SupportGLUT\.\Viewer $(MKDIR) $(INSTALL_DIR)\include\SupportGLUT\.\Viewer
	$(INSTALL) .\Viewer\*.h $(INSTALL_DIR)\include\SupportGLUT\.\Viewer
