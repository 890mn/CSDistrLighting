# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build

# Include any dependencies generated for this target.
include src/CMakeFiles/CSDL-FluentUI.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/CSDL-FluentUI.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/CSDL-FluentUI.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/CSDL-FluentUI.dir/flags.make

src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp: D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src/qml.qrc
src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp: src/CMakeFiles/CSDL-FluentUI_autogen.dir/AutoRcc_qml_EWIEGA46WW_Info.json
src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp: D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src/back.png
src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp: D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src/BrushGrunge.ttf
src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp: D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src/SmileySans-Oblique.ttf
src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp: D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src/logo.ico
src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp: D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src/App.qml
src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp: D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src/InitialLayout.qml
src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp: D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src/SimulationLayout.qml
src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp: D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src/main.qml
src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp: D:/normal_program/QT/6.7.3/msvc2019_64/bin/rcc.exe
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic RCC for qml.qrc"
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && "C:\Program Files (x86)\CMake\bin\cmake.exe" -E cmake_autorcc D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/build/src/CMakeFiles/CSDL-FluentUI_autogen.dir/AutoRcc_qml_EWIEGA46WW_Info.json Debug

src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.obj: src/CMakeFiles/CSDL-FluentUI.dir/flags.make
src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.obj: src/CMakeFiles/CSDL-FluentUI.dir/includes_CXX.rsp
src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.obj: src/CSDL-FluentUI_autogen/mocs_compilation.cpp
src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.obj: src/CMakeFiles/CSDL-FluentUI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.obj"
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.obj -MF CMakeFiles\CSDL-FluentUI.dir\CSDL-FluentUI_autogen\mocs_compilation.cpp.obj.d -o CMakeFiles\CSDL-FluentUI.dir\CSDL-FluentUI_autogen\mocs_compilation.cpp.obj -c D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src\CSDL-FluentUI_autogen\mocs_compilation.cpp

src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.i"
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src\CSDL-FluentUI_autogen\mocs_compilation.cpp > CMakeFiles\CSDL-FluentUI.dir\CSDL-FluentUI_autogen\mocs_compilation.cpp.i

src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.s"
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src\CSDL-FluentUI_autogen\mocs_compilation.cpp -o CMakeFiles\CSDL-FluentUI.dir\CSDL-FluentUI_autogen\mocs_compilation.cpp.s

src/CMakeFiles/CSDL-FluentUI.dir/main.cpp.obj: src/CMakeFiles/CSDL-FluentUI.dir/flags.make
src/CMakeFiles/CSDL-FluentUI.dir/main.cpp.obj: src/CMakeFiles/CSDL-FluentUI.dir/includes_CXX.rsp
src/CMakeFiles/CSDL-FluentUI.dir/main.cpp.obj: D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src/main.cpp
src/CMakeFiles/CSDL-FluentUI.dir/main.cpp.obj: src/CMakeFiles/CSDL-FluentUI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/CSDL-FluentUI.dir/main.cpp.obj"
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/CSDL-FluentUI.dir/main.cpp.obj -MF CMakeFiles\CSDL-FluentUI.dir\main.cpp.obj.d -o CMakeFiles\CSDL-FluentUI.dir\main.cpp.obj -c D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\src\main.cpp

src/CMakeFiles/CSDL-FluentUI.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CSDL-FluentUI.dir/main.cpp.i"
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\src\main.cpp > CMakeFiles\CSDL-FluentUI.dir\main.cpp.i

src/CMakeFiles/CSDL-FluentUI.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CSDL-FluentUI.dir/main.cpp.s"
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\src\main.cpp -o CMakeFiles\CSDL-FluentUI.dir\main.cpp.s

src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.obj: src/CMakeFiles/CSDL-FluentUI.dir/flags.make
src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.obj: src/CMakeFiles/CSDL-FluentUI.dir/includes_CXX.rsp
src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.obj: src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp
src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.obj: src/CMakeFiles/CSDL-FluentUI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.obj"
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.obj -MF CMakeFiles\CSDL-FluentUI.dir\CSDL-FluentUI_autogen\EWIEGA46WW\qrc_qml.cpp.obj.d -o CMakeFiles\CSDL-FluentUI.dir\CSDL-FluentUI_autogen\EWIEGA46WW\qrc_qml.cpp.obj -c D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src\CSDL-FluentUI_autogen\EWIEGA46WW\qrc_qml.cpp

src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.i"
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src\CSDL-FluentUI_autogen\EWIEGA46WW\qrc_qml.cpp > CMakeFiles\CSDL-FluentUI.dir\CSDL-FluentUI_autogen\EWIEGA46WW\qrc_qml.cpp.i

src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.s"
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src\CSDL-FluentUI_autogen\EWIEGA46WW\qrc_qml.cpp -o CMakeFiles\CSDL-FluentUI.dir\CSDL-FluentUI_autogen\EWIEGA46WW\qrc_qml.cpp.s

# Object files for target CSDL-FluentUI
CSDL__FluentUI_OBJECTS = \
"CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.obj" \
"CMakeFiles/CSDL-FluentUI.dir/main.cpp.obj" \
"CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.obj"

# External object files for target CSDL-FluentUI
CSDL__FluentUI_EXTERNAL_OBJECTS =

D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/mocs_compilation.cpp.obj
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: src/CMakeFiles/CSDL-FluentUI.dir/main.cpp.obj
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: src/CMakeFiles/CSDL-FluentUI.dir/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp.obj
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: src/CMakeFiles/CSDL-FluentUI.dir/build.make
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6Quickd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/qml/FluentUI/libfluentuiplugin.a
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6QmlModelsd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6Qmld.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6QmlBuiltinsd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6Networkd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6OpenGLd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6Guid.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6Quickd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6QmlModelsd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6OpenGLd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6Qmld.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6QmlBuiltinsd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6Networkd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6PrintSupportd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6Widgetsd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6Guid.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6Cored.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: D:/normal_program/QT/6.7.3/msvc2019_64/lib/Qt6EntryPointd.lib
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: src/CMakeFiles/CSDL-FluentUI.dir/linkLibs.rsp
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: src/CMakeFiles/CSDL-FluentUI.dir/objects1.rsp
D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe: src/CMakeFiles/CSDL-FluentUI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\bin\Debug\CSDL-FluentUI.exe"
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\CSDL-FluentUI.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/CSDL-FluentUI.dir/build: D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/CSDL-FluentUI.exe
.PHONY : src/CMakeFiles/CSDL-FluentUI.dir/build

src/CMakeFiles/CSDL-FluentUI.dir/clean:
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && $(CMAKE_COMMAND) -P CMakeFiles\CSDL-FluentUI.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/CSDL-FluentUI.dir/clean

src/CMakeFiles/CSDL-FluentUI.dir/depend: src/CSDL-FluentUI_autogen/EWIEGA46WW/qrc_qml.cpp
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\src D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src\CMakeFiles\CSDL-FluentUI.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/CSDL-FluentUI.dir/depend
