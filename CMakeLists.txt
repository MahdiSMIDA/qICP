cmake_minimum_required( VERSION 3.0 )

option( INSTALL_ICP_PLUGIN "Check to install ICP plugin" OFF )

if (INSTALL_ICP_PLUGIN )
        project( ICP ) 

        include_directories( ${CloudCompare_SOURCE_DIR} )
       # set(CloudCompare_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qCC)

        file( GLOB CC_PLUGIN_CUSTOM_HEADER_LIST ${CloudCompare_SOURCE_DIR}/ccOverlayDialog*.h )
        file( GLOB CC_PLUGIN_CUSTOM_SOURCE_LIST ${CloudCompare_SOURCE_DIR}/ccOverlayDialog*.cpp )

        include_directories( src )
        
        add_subdirectory( src )
        add_subdirectory( ui )
        
        include( ../../CMakePluginTpl.cmake )
        
        
        find_package(PCL 1.2 REQUIRED)

    include_directories(${PCL_INCLUDE_DIRS})
    link_directories(${PCL_LIBRARY_DIRS})
    add_definitions(${PCL_DEFINITIONS})



endif()
