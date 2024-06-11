cmake_minimum_required(VERSION 3.14)

set(QWEBRTC_SOURCES
    include/audio_frame.h
    include/audio_track_source_interop.h
    include/data_channel_interop.h
    include/device_audio_track_source_interop.h
    include/device_video_track_source_interop.h
    include/export.h
    include/external_video_track_source_interop.h
    include/interop_api.h
    include/local_audio_track_interop.h
    include/local_video_track_interop.h
    include/logging_interop.h
    include/object_interop.h
    include/peer_connection_interop.h
    include/ref_counted_object_interop.h
    include/remote_audio_track_interop.h
    include/remote_video_track_interop.h
    include/result.h
    include/transceiver_interop.h
    include/video_frame.h
    include/video_track_source_interop.h
    src/interop/audio_track_source_interop.cpp
    src/interop/data_channel_interop.cpp
    src/interop/device_audio_track_source_interop.cpp
    src/interop/device_video_track_source_interop.cpp
    src/interop/external_video_track_source_interop.cpp
    src/interop/global_factory.cpp
    src/interop/global_factory.h
    src/interop/interop_api.cpp
    src/interop/local_audio_track_interop.cpp
    src/interop/local_video_track_interop.cpp
    src/interop/logging_interop.cpp
    src/interop/object_interop.cpp
    src/interop/peer_connection_interop.cpp
    src/interop/ref_counted_object_interop.cpp
    src/interop/remote_audio_track_interop.cpp
    src/interop/remote_video_track_interop.cpp
    src/interop/transceiver_interop.cpp
    src/interop/video_track_source_interop.cpp
    src/media/audio_track_read_buffer.cpp
    src/media/audio_track_read_buffer.h
    src/media/audio_track_source.cpp
    src/media/audio_track_source.h
    src/media/device_audio_track_source.cpp
    src/media/device_audio_track_source.h
    src/media/device_video_track_source.cpp
    src/media/device_video_track_source.h
    src/media/external_video_track_source.cpp
    src/media/external_video_track_source.h
    src/media/local_audio_track.cpp
    src/media/local_audio_track.h
    src/media/local_video_track.cpp
    src/media/local_video_track.h
    src/media/media_track.cpp
    src/media/media_track.h
    src/media/remote_audio_track.cpp
    src/media/remote_audio_track.h
    src/media/remote_video_track.cpp
    src/media/remote_video_track.h
    src/media/transceiver.cpp
    src/media/transceiver.h
    src/media/video_track_source.cpp
    src/media/video_track_source.h
    src/audio_frame_observer.cpp
    src/audio_frame_observer.h
    src/callback.h
    src/data_channel.cpp
    src/data_channel.h
    src/mrs_errors.cpp
    src/mrs_errors.h
    src/pch.cpp
    src/pch.h
    src/peer_connection.cpp
    src/peer_connection.h
    src/ref_counted_base.h
    src/refptr.h
    src/sdp_utils.cpp
    src/sdp_utils.h
    src/targetver.h
    src/toggle_audio_mixer.cpp
    src/toggle_audio_mixer.h
    src/tracked_object.cpp
    src/tracked_object.h
    src/utils.cpp
    src/utils.h
    src/video_frame_observer.cpp
    src/video_frame_observer.h)

add_library(cwebrtc SHARED ${QWEBRTC_SOURCES})

find_path(
  WEBRTC_INCLUDE_DIR
  NAMES api/jsep.h
  HINTS ${PROJECT_SOURCE_DIR}/extern/libwebrtc/include)
list(APPEND WEBRTC_INCLUDE_DIR
     ${PROJECT_SOURCE_DIR}/extern/libwebrtc/include/third_party/libyuv/include)

if(X86_64)
  set(ARCH_STRING "x64")
elseif(X86)
  set(ARCH_STRING "x86")
elseif(AARCH64)
  set(ARCH_STRING "arm64")
endif()

find_library(
  WEBRTC_LIBRARY_DEBUG
  NAMES libwebrtc.a
  HINTS ${PROJECT_SOURCE_DIR}/extern/libwebrtc/lib/${ARCH_STRING}/debug
  PATHS ${CMAKE_SYSTEM_LIBRARY_DIRS})
find_library(
  WEBRTC_LIBRARY_RELEASE
  NAMES libwebrtc.a
  HINTS ${PROJECT_SOURCE_DIR}/extern/libwebrtc/lib/${ARCH_STRING}/release
  PATHS ${CMAKE_SYSTEM_LIBRARY_DIRS})

message(STATUS "WEBRTC_INCLUDE_DIR: ${WEBRTC_INCLUDE_DIR}")
message(STATUS "WEBRTC_LIBRARY_DEBUG: ${WEBRTC_LIBRARY_DEBUG}")
message(STATUS "WEBRTC_LIBRARY_RELEASE: ${WEBRTC_LIBRARY_RELEASE}")

if(OS_LINUX)
  if(X86_64)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(WEBRTC_LIBRARY ${WEBRTC_LIBRARY_DEBUG})
      add_definitions(
        -DUSE_UDEV
        -DUSE_AURA=1
        -DUSE_GLIB=1
        -DUSE_OZONE=1
        -D__STDC_CONSTANT_MACROS
        -D__STDC_FORMAT_MACROS
        -D_FILE_OFFSET_BITS=64
        -D_LARGEFILE_SOURCE
        -D_LARGEFILE64_SOURCE
        -D_GNU_SOURCE
        -DDYNAMIC_ANNOTATIONS_ENABLED=1
        -DWEBRTC_ENABLE_PROTOBUF=1
        -DWEBRTC_STRICT_FIELD_TRIALS=0
        -DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE
        -DRTC_ENABLE_VP9
        -DRTC_DAV1D_IN_INTERNAL_DECODER_FACTORY
        -DWEBRTC_HAVE_SCTP
        -DWEBRTC_LIBRARY_IMPL
        -DWEBRTC_ENABLE_SYMBOL_EXPORT
        -DWEBRTC_ENABLE_AVX2
        -DWEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=0
        -DWEBRTC_POSIX
        -DWEBRTC_LINUX
        -DABSL_ALLOCATOR_NOTHROW=1
        -DLIBYUV_DISABLE_NEON
        -DWEBRTC_USE_PIPEWIRE
        -DWEBRTC_USE_GIO
        -DGOOGLE_PROTOBUF_NO_RTTI
        -DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        -DGOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0
        -DHAVE_PTHREAD)
    else()
      set(WEBRTC_LIBRARY ${WEBRTC_LIBRARY_RELEASE})
      add_definitions(
        -DUSE_UDEV
        -DUSE_AURA=1
        -DUSE_GLIB=1
        -DUSE_OZONE=1
        -D__STDC_CONSTANT_MACROS
        -D__STDC_FORMAT_MACROS
        -D_FORTIFY_SOURCE=2
        -D_FILE_OFFSET_BITS=64
        -D_LARGEFILE_SOURCE
        -D_LARGEFILE64_SOURCE
        -D_GNU_SOURCE
        -DNVALGRIND
        -DDYNAMIC_ANNOTATIONS_ENABLED=0
        -DWEBRTC_ENABLE_PROTOBUF=1
        -DWEBRTC_STRICT_FIELD_TRIALS=0
        -DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE
        -DRTC_ENABLE_VP9
        -DRTC_DAV1D_IN_INTERNAL_DECODER_FACTORY
        -DWEBRTC_HAVE_SCTP
        -DWEBRTC_LIBRARY_IMPL
        -DWEBRTC_ENABLE_SYMBOL_EXPORT
        -DWEBRTC_ENABLE_AVX2
        -DWEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=0
        -DWEBRTC_POSIX
        -DWEBRTC_LINUX
        -DABSL_ALLOCATOR_NOTHROW=1
        -DLIBYUV_DISABLE_NEON
        -DWEBRTC_USE_PIPEWIRE
        -DWEBRTC_USE_GIO
        -DGOOGLE_PROTOBUF_NO_RTTI
        -DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        -DGOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0
        -DHAVE_PTHREAD)
    endif()
  elseif(AARCH64)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(WEBRTC_LIBRARY ${WEBRTC_LIBRARY_DEBUG})
      add_definitions(
        -DUSE_UDEV
        -DUSE_AURA=1
        -DUSE_GLIB=1
        -DUSE_OZONE=1
        -D__STDC_CONSTANT_MACROS
        -D__STDC_FORMAT_MACROS
        -D_FILE_OFFSET_BITS=64
        -D_LARGEFILE_SOURCE
        -D_LARGEFILE64_SOURCE
        -D_GNU_SOURCE
        -DDYNAMIC_ANNOTATIONS_ENABLED=1
        -DWEBRTC_ENABLE_PROTOBUF=1
        -DWEBRTC_STRICT_FIELD_TRIALS=0
        -DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE
        -DRTC_ENABLE_VP9
        -DRTC_DAV1D_IN_INTERNAL_DECODER_FACTORY
        -DWEBRTC_HAVE_SCTP
        -DWEBRTC_ARCH_ARM64
        -DWEBRTC_HAS_NEON
        -DWEBRTC_LIBRARY_IMPL
        -DWEBRTC_ENABLE_SYMBOL_EXPORT
        -DWEBRTC_ENABLE_AVX2
        -DWEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=0
        -DWEBRTC_POSIX
        -DWEBRTC_LINUX
        -DABSL_ALLOCATOR_NOTHROW=1
        -DWEBRTC_USE_PIPEWIRE
        -DWEBRTC_USE_GIO
        -DGOOGLE_PROTOBUF_NO_RTTI
        -DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        -DGOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0
        -DHAVE_PTHREAD)
    else()
      set(WEBRTC_LIBRARY ${WEBRTC_LIBRARY_RELEASE})
      add_definitions(
        -DUSE_UDEV
        -DUSE_AURA=1
        -DUSE_GLIB=1
        -DUSE_OZONE=1
        -D__STDC_CONSTANT_MACROS
        -D__STDC_FORMAT_MACROS
        -D_FORTIFY_SOURCE=2
        -D_FILE_OFFSET_BITS=64
        -D_LARGEFILE_SOURCE
        -D_LARGEFILE64_SOURCE
        -D_GNU_SOURCE
        -DNVALGRIND
        -DDYNAMIC_ANNOTATIONS_ENABLED=0
        -DWEBRTC_ENABLE_PROTOBUF=1
        -DWEBRTC_STRICT_FIELD_TRIALS=0
        -DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE
        -DRTC_ENABLE_VP9
        -DRTC_DAV1D_IN_INTERNAL_DECODER_FACTORY
        -DWEBRTC_HAVE_SCTP
        -DWEBRTC_ARCH_ARM64
        -DWEBRTC_HAS_NEON
        -DWEBRTC_LIBRARY_IMPL
        -DWEBRTC_ENABLE_SYMBOL_EXPORT
        -DWEBRTC_ENABLE_AVX2
        -DWEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=0
        -DWEBRTC_POSIX
        -DWEBRTC_LINUX
        -DABSL_ALLOCATOR_NOTHROW=1
        -DWEBRTC_USE_PIPEWIRE
        -DWEBRTC_USE_GIO
        -DGOOGLE_PROTOBUF_NO_RTTI
        -DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        -DGOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0
        -DHAVE_PTHREAD)
    endif()
  endif()
elseif(OS_MACOS)
  if(X86_64)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(WEBRTC_LIBRARY ${WEBRTC_LIBRARY_DEBUG})
      add_definitions(
        -D__STDC_CONSTANT_MACROS
        -D__STDC_FORMAT_MACROS
        -DDYNAMIC_ANNOTATIONS_ENABLED=1
        -DWEBRTC_ENABLE_PROTOBUF=1
        -DWEBRTC_STRICT_FIELD_TRIALS=0
        -DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE
        -DRTC_ENABLE_VP9
        -DRTC_DAV1D_IN_INTERNAL_DECODER_FACTORY
        -DWEBRTC_HAVE_SCTP
        -DWEBRTC_LIBRARY_IMPL
        -DWEBRTC_ENABLE_SYMBOL_EXPORT
        -DWEBRTC_ENABLE_AVX2
        -DWEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=0
        -DWEBRTC_POSIX
        -DWEBRTC_MAC
        -DABSL_ALLOCATOR_NOTHROW=1
        -DLIBYUV_DISABLE_NEON
        -DGOOGLE_PROTOBUF_NO_RTTI
        -DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        -DGOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0
        -DHAVE_PTHREAD)
    else()
      set(WEBRTC_LIBRARY ${WEBRTC_LIBRARY_RELEASE})
      add_definitions(
        -D__STDC_CONSTANT_MACROS
        -D__STDC_FORMAT_MACROS
        -D_FORTIFY_SOURCE=2
        -DNVALGRIND
        -DDYNAMIC_ANNOTATIONS_ENABLED=0
        -DWEBRTC_ENABLE_PROTOBUF=1
        -DWEBRTC_STRICT_FIELD_TRIALS=0
        -DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE
        -DRTC_ENABLE_VP9
        -DRTC_DAV1D_IN_INTERNAL_DECODER_FACTORY
        -DWEBRTC_HAVE_SCTP
        -DWEBRTC_LIBRARY_IMPL
        -DWEBRTC_ENABLE_SYMBOL_EXPORT
        -DWEBRTC_ENABLE_AVX2
        -DWEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=0
        -DWEBRTC_POSIX
        -DWEBRTC_MAC
        -DABSL_ALLOCATOR_NOTHROW=1
        -DLIBYUV_DISABLE_NEON
        -DGOOGLE_PROTOBUF_NO_RTTI
        -DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        -DGOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0
        -DHAVE_PTHREAD)
    endif()
  elseif(AARCH64)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(WEBRTC_LIBRARY ${WEBRTC_LIBRARY_DEBUG})
      add_definitions(
        -D__STDC_CONSTANT_MACROS
        -D__STDC_FORMAT_MACROS
        -DDYNAMIC_ANNOTATIONS_ENABLED=1
        -DWEBRTC_ENABLE_PROTOBUF=1
        -DWEBRTC_STRICT_FIELD_TRIALS=0
        -DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE
        -DRTC_ENABLE_VP9
        -DRTC_DAV1D_IN_INTERNAL_DECODER_FACTORY
        -DWEBRTC_HAVE_SCTP
        -DWEBRTC_ARCH_ARM64
        -DWEBRTC_HAS_NEON
        -DWEBRTC_LIBRARY_IMPL
        -DWEBRTC_ENABLE_SYMBOL_EXPORT
        -DWEBRTC_ENABLE_AVX2
        -DWEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=0
        -DWEBRTC_POSIX
        -DWEBRTC_MAC
        -DABSL_ALLOCATOR_NOTHROW=1
        -DGOOGLE_PROTOBUF_NO_RTTI
        -DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        -DGOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0
        -DHAVE_PTHREAD)
    else()
      set(WEBRTC_LIBRARY ${WEBRTC_LIBRARY_RELEASE})
      add_definitions(
        -D__STDC_CONSTANT_MACROS
        -D__STDC_FORMAT_MACROS
        -D_FORTIFY_SOURCE=2
        -DNVALGRIND
        -DDYNAMIC_ANNOTATIONS_ENABLED=0
        -DWEBRTC_ENABLE_PROTOBUF=1
        -DWEBRTC_STRICT_FIELD_TRIALS=0
        -DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE
        -DRTC_ENABLE_VP9
        -DRTC_DAV1D_IN_INTERNAL_DECODER_FACTORY
        -DWEBRTC_HAVE_SCTP
        -DWEBRTC_ARCH_ARM64
        -DWEBRTC_HAS_NEON
        -DWEBRTC_LIBRARY_IMPL
        -DWEBRTC_ENABLE_SYMBOL_EXPORT
        -DWEBRTC_ENABLE_AVX2
        -DWEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=0
        -DWEBRTC_POSIX
        -DWEBRTC_MAC
        -DABSL_ALLOCATOR_NOTHROW=1
        -DGOOGLE_PROTOBUF_NO_RTTI
        -DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
        -DGOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0
        -DHAVE_PTHREAD)
    endif()
  endif()
endif()
add_definitions(-DQT_NO_SIGNALS_SLOTS_KEYWORDS)

if(WEBRTC_INCLUDE_DIR AND (WEBRTC_LIBRARY_DEBUG OR WEBRTC_LIBRARY_RELEASE))
  add_library(WebRTC STATIC IMPORTED)
  set_target_properties(
    WebRTC
    PROPERTIES IMPORTED_LOCATION "${WEBRTC_LIBRARY}"
               IMPORTED_LOCATION_DEBUG "${WEBRTC_LIBRARY_DEBUG}"
               IMPORTED_LOCATION_RELEASE "${WEBRTC_LIBRARY_RELEASE}"
               IMPORTED_INCLUDE_DIRECTORIES "${WEBRTC_INCLUDE_DIR}")
else()
  message(
    WARNING
      "WebRTC library not found. Communication features might be disabled.")
endif()

include_directories(${WEBRTC_INCLUDE_DIR})
include_directories("/usr/include/glib-2.0")
include_directories("/usr/lib/x86_64-linux-gnu/glib-2.0/include")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(cwebrtc PRIVATE QWEBRTC_LIBRARY QT_NO_KEYWORDS)
else()
  target_compile_definitions(cwebrtc PRIVATE QWEBRTC_LIBRARY QT_NO_KEYWORDS)
endif()

if(OS_LINUX)
  target_link_libraries(
    cwebrtc
    PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui
            Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::Concurrent
            WebRTC)
elseif(OS_MACOS)
  target_link_libraries(
    cwebrtc
    PRIVATE
      Qt${QT_VERSION_MAJOR}::Core
      Qt${QT_VERSION_MAJOR}::Gui
      Qt${QT_VERSION_MAJOR}::Multimedia
      Qt${QT_VERSION_MAJOR}::Concurrent
      WebRTC
      "-framework CoreFoundation -framework AudioUnit -framework CoreAudio -framework AudioToolbox  -framework IOSurface"
  )
endif()
