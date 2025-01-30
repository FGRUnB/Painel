# Nome do projeto
cmake_minimum_required(VERSION 3.10)
project(Painel)

# Configuração do C++ (versão 11 ou superior)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Diretório onde está o código-fonte principal
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Diretório onde está o Dear ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)

# Adiciona os arquivos fontes do Dear ImGui
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Adiciona o arquivo principal do projeto
set(SOURCES
    ${SRC_DIR}/main.cpp
)

# Adiciona a biblioteca ImGui
add_library(imgui STATIC ${IMGUI_SOURCES})

# Inclui os diretórios de cabeçalhos do Dear ImGui
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)

# Adiciona o executável principal
add_executable(${PROJECT_NAME} ${SOURCES})

# Vincula as bibliotecas necessárias ao executável
target_link_libraries(${PROJECT_NAME} imgui glfw OpenGL::GL)

# Busca automaticamente as dependências do OpenGL e GLFW
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
