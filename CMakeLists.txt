
add_subdirectory(deps/glm_mat_1)
add_subdirectory(deps/kalman_glm)
add_subdirectory(transform_filter_glm)

option(WITH_IM_PARAM "Build library for im_param declarations." ON)

if(WITH_IM_PARAM)
    add_subdirectory(im_param_transform_filter_glm)
endif()
