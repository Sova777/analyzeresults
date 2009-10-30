.build-conf:
	@echo 'Tool collection MinGW was missing when this makefile was generated'
	@echo 'Please specify existing tool collection in project properties'
	@exit 1

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release//football

# Subprojects
.clean-subprojects:
