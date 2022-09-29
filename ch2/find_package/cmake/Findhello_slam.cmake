message("now using Findhello_slam.cmake find hello_slam lib")

FIND_PATH(LIBHELLO_SLAM_INCLUDE_DIR libHelloSLAM.h /usr/local/inlcude/)
message("./h dir ${LIBHELLO_SLAM_INCLUDE_DIR}")

FIND_LIBRARY(LIBHELLO_SLAM_LIBRARY libhello_slam.a /usr/local/lib/)
message("lib dir: ${LIBHELLO_SLAM_LIBRARY}")

if(LIBHELLO_SLAM_INCLUDE_DIR AND LIBHELLO_SLAM_LIBRARY)
    set(LIBHELLO_SLAM_FOUND true)
endif(LIBHELLO_SLAM_INCLUDE_DIR AND LIBHELLO_SLAM_LIBRARY)