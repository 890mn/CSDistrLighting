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

# Utility rule file for Script-UpdateTranslations.

# Include any custom commands dependencies for this target.
include src/CMakeFiles/Script-UpdateTranslations.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Script-UpdateTranslations.dir/progress.make

src/CMakeFiles/Script-UpdateTranslations:
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\src && D:\normal_program\QT\6.7.3\msvc2019_64\bin\lupdate.exe D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src -ts CSDL-FluentUI_en_US.ts
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\src && D:\normal_program\QT\6.7.3\msvc2019_64\bin\lupdate.exe D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/src -ts CSDL-FluentUI_zh_CN.ts
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\src && D:\normal_program\QT\6.7.3\msvc2019_64\bin\lrelease.exe CSDL-FluentUI_en_US.ts
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\src && D:\normal_program\QT\6.7.3\msvc2019_64\bin\lrelease.exe CSDL-FluentUI_zh_CN.ts
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\src && "C:\Program Files (x86)\CMake\bin\cmake.exe" -E make_directory D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/i18n
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\src && "C:\Program Files (x86)\CMake\bin\cmake.exe" -E copy CSDL-FluentUI_en_US.qm CSDL-FluentUI_zh_CN.qm D:/study_data/CS_Major/Hardware/ESP32/CSDistrLighting/Software/CSDL-FluentUI/bin/Debug/i18n

Script-UpdateTranslations: src/CMakeFiles/Script-UpdateTranslations
Script-UpdateTranslations: src/CMakeFiles/Script-UpdateTranslations.dir/build.make
.PHONY : Script-UpdateTranslations

# Rule to build all files generated by this target.
src/CMakeFiles/Script-UpdateTranslations.dir/build: Script-UpdateTranslations
.PHONY : src/CMakeFiles/Script-UpdateTranslations.dir/build

src/CMakeFiles/Script-UpdateTranslations.dir/clean:
	cd /d D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src && $(CMAKE_COMMAND) -P CMakeFiles\Script-UpdateTranslations.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/Script-UpdateTranslations.dir/clean

src/CMakeFiles/Script-UpdateTranslations.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\Software\CSDL-FluentUI\src D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src D:\study_data\CS_Major\Hardware\ESP32\CSDistrLighting\build\src\CMakeFiles\Script-UpdateTranslations.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/Script-UpdateTranslations.dir/depend

