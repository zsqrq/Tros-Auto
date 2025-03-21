cmake_minimum_required(VERSION 3.22)
project(UnixIpcPosixShm)

add_executable(unix_network_pxshm_shmcreate shmcreate.cpp)
target_link_libraries(unix_network_pxshm_shmcreate
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxshm_shmcreate
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxshm/${BIN_INSTALL_DIR})

add_executable(unix_network_pxshm_shmunlink shmunlink.cpp)
target_link_libraries(unix_network_pxshm_shmunlink
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxshm_shmunlink
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxshm/${BIN_INSTALL_DIR})

add_executable(unix_network_pxshm_shmwrite shmwritre.cpp)
target_link_libraries(unix_network_pxshm_shmwrite
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxshm_shmwrite
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxshm/${BIN_INSTALL_DIR})

add_executable(unix_network_pxshm_shmread shmread.cpp)
target_link_libraries(unix_network_pxshm_shmread
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxshm_shmread
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxshm/${BIN_INSTALL_DIR})

add_executable(unix_network_pxshm_test3 test3.cpp)
target_link_libraries(unix_network_pxshm_test3
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxshm_test3
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxshm/${BIN_INSTALL_DIR})

add_executable(unix_network_pxshm_server1 server1.cpp)
target_link_libraries(unix_network_pxshm_server1
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxshm_server1
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxshm/${BIN_INSTALL_DIR})

add_executable(unix_network_pxshm_client1 client1.cpp)
target_link_libraries(unix_network_pxshm_client1
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxshm_client1
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxshm/${BIN_INSTALL_DIR})

add_executable(unix_network_pxshm_server2 server2.cpp)
target_link_libraries(unix_network_pxshm_server2
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxshm_server2
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxshm/${BIN_INSTALL_DIR})

add_executable(unix_network_pxshm_client2 client2.cpp)
target_link_libraries(unix_network_pxshm_client2
    PUBLIC unix-network-ipc-lib
)
install(TARGETS unix_network_pxshm_client2
    RUNTIME
    DESTINATION examples/cpp/unix_network/example/pxshm/${BIN_INSTALL_DIR})