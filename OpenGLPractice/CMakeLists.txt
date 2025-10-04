cmake_minimum_required(VERSION 3.16)
project(OpenGLPractice)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置调试构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 设置macOS特定配置
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0")
    # 添加macOS特定的编译器标志
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
endif()

# 添加编译器标志 - 添加调试符号
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# 添加包含目录
include_directories(
    src
    src/Graphics
    src/Common
    src/UI
    src/Models
    src/3rdParty
    Dependencies/GLAD/include
    Dependencies/GLFW/include
)

# 查找OpenGL
find_package(OpenGL REQUIRED)

# 查找或使用本地GLFW
if(APPLE)
    # 在macOS上使用Homebrew安装的GLFW
    find_package(glfw3 REQUIRED)
else()
    # 使用项目中的GLFW库
    set(GLFW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLFW/include")
    set(GLFW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLFW/lib-vc2022/glfw3.lib")
endif()

# 源文件
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.c"
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 设置目标特定的编译器标志
if(APPLE)
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -Wall 
        -Wextra 
        -Wno-deprecated
        -g          # 添加调试符号
        -O0         # 禁用优化
    )
    
    # 添加预处理器定义
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
        GL_SILENCE_DEPRECATION
        DEBUG
    )
endif()

# 链接库
if(APPLE)
    target_link_libraries(${PROJECT_NAME} 
        OpenGL::GL
        glfw
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(${PROJECT_NAME} 
        OpenGL::GL
        ${GLFW_LIBRARIES}
    )
endif()