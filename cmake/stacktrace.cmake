INCLUDE (CheckIncludeFiles)
CHECK_INCLUDE_FILES("stacktrace" USE_STACKTRACES LANGUAGE CXX)
if(USE_STACKTRACES AND (CMAKE_CXX_STANDARD EQUAL 23) )
	message("Using stacktraces")
	add_definitions(-DUSE_STACKTRACES)
	#only for gcc
	IF (CMAKE_COMPILER_IS_GNUCXX)
		SET(ADDITION_LIBS "stdc++exp" CACHE STRING "additional libraries")
	ENDIF()
else()	
	message("Not using stacktraces")
endif()