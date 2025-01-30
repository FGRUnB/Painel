cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(CircularGauge)

# Define o padrão de compilação como C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajusta a política para evitar o aviso sobre o OpenGL legado
cmake_policy(SET CMP0072 NEW)

# Busca todos os arquivos .cpp no diretório src
file(GLOB SOURCES "src/*.cpp")

# Adiciona o executável
add_executable(CircularGauge ${SOURCES})

# Linka a biblioteca OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(CircularGauge OpenGL::GL)

# Inclui o diretório onde está o imgui.h
target_include_directories(CircularGauge PRIVATE imgui imgui/backends)

# Adiciona os arquivos principais do ImGui
target_sources(CircularGauge PRIVATE
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
)

# Adiciona os arquivos de backend do ImGui
target_sources(CircularGauge PRIVATE
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

# Inclui o diretório src para cabeçalhos
target_include_directories(CircularGauge PRIVATE src)

# Linka a biblioteca GLFW (necessário para o ImGui backend)
find_package(glfw3 REQUIRED)
target_link_libraries(CircularGauge glfw)

# Linka a biblioteca OpenGL para o backend do ImGui
target_link_libraries(CircularGauge GL)

# Mensagem informativa
message(STATUS "Build configurado com sucesso!")
