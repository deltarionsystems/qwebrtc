cmake_minimum_required(VERSION 3.14)

project(
  qwebrtc
  LANGUAGES CXX C
  VERSION 0.1.0)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Platform detection
if(NOT DEFINED TARGET_SYSTEM_NAME)
  if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(OS_LINUX ON)
    add_definitions(-DOS_LINUX -DLINUX)

    if(TIZEN)
      message(STATUS "Compiling for Tizen OS version: ${TIZEN_VERSION}")
      add_definitions(-DOS_TIZEN -DTIZEN)
    endif()
  elseif(CMAKE_SYSTEM_NAME MATCHES "Android")
    set(OS_ANDROID ON)
    add_definitions(-DOS_ANDROID -DANDROID)
  elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(OS_WINDOWS ON)
    add_definitions(-DOS_WINDOWS -DDEVICE_TYPE_PC)
  elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(OS_MACOS ON)
    add_definitions(-DOS_DARWIN -DOS_MACOS -DMACOSX)
    enable_language(OBJC)
    enable_language(OBJCXX)
  elseif(CMAKE_SYSTEM_NAME MATCHES "iOS")
    set(OS_IOS ON)
    add_definitions(-DOS_DARWIN -DOS_IOS -DIOS)
    enable_language(OBJC)
    enable_language(OBJCXX)
  elseif(CMAKE_SYSTEM_NAME MATCHES "tvOS")
    set(OS_TVOS ON)
    add_definitions(-DOS_DARWIN -DOS_TVOS)
    enable_language(OBJC)
    enable_language(OBJCXX)
  elseif(CMAKE_SYSTEM_NAME MATCHES "watchOS")
    set(OS_WATCHOS ON)
    add_definitions(-DOS_DARWIN -DOS_WATCHOS)
    enable_language(OBJC)
    enable_language(OBJCXX)
  endif()
endif()

if(QWEBRTC_SKIP_SYSTEM_PROCESSOR_DETECTION)
  message(STATUS "QWEBRTC: skip system processor detection")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "amd64.*|x86_64.*|AMD64.*")
  set(X86_64 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i686.*|i386.*|x86.*")
  set(X86 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64.*|AARCH64.*|arm64.*|ARM64.*)")
  set(AARCH64 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm.*|ARM.*)")
  set(ARM 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(powerpc|ppc)64le")
  set(PPC64LE 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(powerpc|ppc)64")
  set(PPC64 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(powerpc|ppc)")
  set(PPC 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(mips.*|MIPS.*)64le")
  set(MIPS64LE 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(mips.*|MIPS.*)64")
  set(MIPS64 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(mips.*|MIPS.*)")
  set(MIPS 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(riscv.*|RISCV.*)")
  set(RISCV 1)
else()
  if(NOT QWEBRTC_SUPPRESS_MESSAGE_UNRECOGNIZED_SYSTEM_PROCESSOR)
    message(WARNING "QWEBRTC: unrecognized target processor configuration")
  endif()
endif()

# Platform specific configurations
if(WIN32)
  # Support Windows 7 or later
  set(CMAKE_SYSTEM_VERSION
      7
      CACHE STRING INTERNAL FORCE)
endif()

if(APPLE)
  set(CMAKE_MACOSX_RPATH 1)

  if(NOT DEFINED QWEBRTC_DEPLOYMENT_TARGET OR QWEBRTC_DEPLOYMENT_TARGET
                                              STREQUAL "")
    if(OS_MACOS)
      set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15)
    elseif(OS_IOS)
      set(QWEBRTC_DEPLOYMENT_TARGET 13.0)
    endif()
  else()
    if(OS_MACOS)
      set(CMAKE_OSX_DEPLOYMENT_TARGET ${QWEBRTC_DEPLOYMENT_TARGET})
    endif()
  endif()
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Multimedia
                                                  Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Multimedia
                                                       Concurrent)

add_subdirectory(src)
add_subdirectory(cwebrtc)
# add_subdirectory(apprtc)
