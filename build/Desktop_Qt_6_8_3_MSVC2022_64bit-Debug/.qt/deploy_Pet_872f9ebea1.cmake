include("D:/Git/QT_Projects/Pet/build/Desktop_Qt_6_8_3_MSVC2022_64bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Pet-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE D:/Git/QT_Projects/Pet/build/Desktop_Qt_6_8_3_MSVC2022_64bit-Debug/Pet.exe
    GENERATE_QT_CONF
)
