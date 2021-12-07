cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME transform_filter_glm)
project( ${PROJECT_NAME} )

include("compiler_options.cmake")

add_library(
    ${PROJECT_NAME} 
    STATIC
    
    src/abstract_transform_filter.cpp
    src/abstract_transform_filter_observe_predict.cpp
    src/transform_filter_take_previous.cpp
    src/transform_filter_independent_kalman_rpy.cpp
    src/simple_transform_forward_backward_smoother_independent_kalman_rpy.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
find_package(glm REQUIRED)    
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm_mat_1)
target_link_libraries(${PROJECT_NAME} PUBLIC kalman_glm)
