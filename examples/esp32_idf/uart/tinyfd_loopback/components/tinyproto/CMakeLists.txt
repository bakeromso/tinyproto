# Register the src component
idf_component_register(
    SRCS 
"src/hal/esp32/esp32_hal.inl"
"src/hal/esp32/esp32_serial.inl"
"src/hal/tiny_list.c"
"src/hal/tiny_serial.c"
"src/hal/tiny_serial_cpp.cpp"
"src/hal/tiny_types.c"
"src/hal/tiny_types_cpp.cpp"
"src/interface/TinySerial.cpp"
"src/link/TinyFdLinkLayer.cpp"
"src/link/TinyHdlcLinkLayer.cpp"
"src/link/TinyLinkLayer.cpp"
"src/link/TinySerialFdLink.cpp"
"src/link/TinySerialHdlcLink.cpp"
"src/link/TinySerialLinkLayer.cpp"
"src/proto/crc/tiny_crc.c"
"src/proto/fd/tiny_fd.c"
"src/proto/fd/tiny_fd_frames.c"
"src/proto/hdlc/high_level/hdlc.c"
"src/proto/hdlc/low_level/hdlc.c"
"src/proto/light/tiny_light.c"
"src/TinyLightProtocol.cpp"
"src/TinyProtocol.cpp"
"src/TinyProtocolFd.cpp"
"src/TinyProtocolHdlc.cpp"
    
    INCLUDE_DIRS "src"
                 "src/proto"
                 "src/hal"
                 "src/hal/esp32"
                 "src/proto/hdlc/high_level"
                 "src/proto/hdlc/low_level"
                 "src/proto/fd"
                 "src/proto/light"
                 "src/proto/crc"
                 "src/link"
                 "src/interface"
    REQUIRES driver esp_timer
)

# Add definitions
add_definitions(
    -DTINY_LOG_LEVEL_DEFAULT=0
    -DTINY_HDLC_DEBUG=0
    -DTINY_FD_DEBUG=0
    -DTINY_DEBUG=0
    -DCONFIG_ENABLE_FCS32
    -DCONFIG_ENABLE_FCS16
    -DCONFIG_ENABLE_CHECKSUM
    -DCONFIG_ENABLE_STATS
)