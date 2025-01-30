#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

// Definir IM_PI caso não esteja disponível
#ifndef IM_PI
#define IM_PI 3.14159265358979323846f
#endif

// Função para desenhar velocímetro circular
void DrawCircularGauge(ImDrawList* drawList, ImVec2 center, float radius, float value, float maxValue, const char* label, const char* unit, ImU32 color) {
    // Ângulos ajustados para estender o arco verde mais para baixo
    float startAngle = IM_PI * 0.75f;  // Começa um pouco mais abaixo (10:30 horas)
    float endAngle = IM_PI * 2.25f;   // Termina um pouco mais abaixo (4:30 horas)

    // Cálculo do ângulo do progresso
    float angle = startAngle + (endAngle - startAngle) * (value / maxValue);

    // Arco de fundo (cinza)
    drawList->PathArcTo(center, radius, startAngle, endAngle, 100);
    drawList->PathStroke(IM_COL32(80, 80, 80, 255), false, 10.0f);

    // Arco de progresso (verde ou na cor definida)
    drawList->PathArcTo(center, radius, startAngle, angle, 100);
    drawList->PathStroke(color, false, 10.0f);

    // Texto central (valor atual)
    char valueText[16];
    snprintf(valueText, sizeof(valueText), "%.0f", value);
    ImVec2 textSize = ImGui::CalcTextSize(valueText);
    drawList->AddText(ImVec2(center.x - textSize.x / 2, center.y - textSize.y / 2), IM_COL32(255, 255, 255, 255), valueText);

    // Unidade abaixo do texto
    ImVec2 unitSize = ImGui::CalcTextSize(unit);
    drawList->AddText(ImVec2(center.x - unitSize.x / 2, center.y + textSize.y / 2 + 5), IM_COL32(200, 200, 200, 255), unit);
}


// Função para criar um card com informações
void DrawInfoCard(const char* title, const char* value, const char* details, ImU32 color) {
    ImGui::BeginChild(title, ImVec2(200, 120), true, ImGuiWindowFlags_NoScrollbar);
    ImGui::Text("%s", title); // Corrigido
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::TextColored(ImColor(color), "%s", value); // Corrigido
    ImGui::Text("%s", details); // Corrigido
    ImGui::EndChild();
}

// Função principal
int main() {
    // Inicialização do GLFW
    if (!glfwInit()) {
        std::cerr << "Erro ao inicializar o GLFW!" << std::endl;
        return -1;
    }

    // Configuração do GLFW para usar OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Criação da janela GLFW
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Painel", NULL, NULL);
    if (!window) {
        std::cerr << "Erro ao criar janela GLFW!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Habilita V-Sync

    // Inicialização do Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Inicializa os backends do ImGui
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Variáveis para o painel
    float speed = 999.0f;          // Velocidade atual
    float maxSpeed = 999.0f;       // Velocidade máxima
    float batteryHigh = 50.0f;     // Bateria de alta voltagem
    float batteryLow = 100.0f;     // Bateria de baixa voltagem
    float motorRPM = 9999.0f;      // Rotação do motor

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        // Processa eventos do GLFW
        glfwPollEvents();

        // Inicia um novo frame do ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Layout principal
        ImGui::SetNextWindowSize(ImVec2(1280, 720), ImGuiCond_Always);
        ImGui::Begin("Painel", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

        // Divisão em colunas
        ImGui::Columns(3, nullptr, false);

        // Coluna 1: High Voltage e Motor
        DrawInfoCard("High Voltage", "50%", "75.5v | 35ºC | 100A", IM_COL32(0, 255, 0, 255));
        ImGui::Spacing();
        DrawInfoCard("Motor", "9999 RPM", "35ºC | 75.5v", IM_COL32(0, 255, 0, 255));

        ImGui::NextColumn();

        // Coluna 2: Velocímetro
        ImVec2 center = ImGui::GetCursorScreenPos();
        center.x += 150;
        center.y += 150;
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        DrawCircularGauge(drawList, center, 100.0f, speed, maxSpeed, "999", "km/h", IM_COL32(0, 255, 0, 255));
        ImGui::Dummy(ImVec2(300, 300));

        ImGui::NextColumn();

        // Coluna 3: Low Voltage e System
        DrawInfoCard("Low Voltage", "100%", "12.5v | 35ºC | 3A", IM_COL32(0, 255, 0, 255));
        ImGui::Spacing();
        DrawInfoCard("System", "OK", "HV: Battery\nLV: OK\nSecondary systems: OK", IM_COL32(0, 255, 0, 255));

        ImGui::Columns(1);

        // Botões distribuídos simetricamente
        ImGui::SetCursorPos(ImVec2(200, 600)); // Posição do primeiro botão
        if (ImGui::Button("Brake", ImVec2(150, 50))) {}

        ImGui::SetCursorPos(ImVec2(400, 600)); // Posição do segundo botão
        if (ImGui::Button("Acceleration", ImVec2(150, 50))) {}

        ImGui::SetCursorPos(ImVec2(600, 600)); // Posição do terceiro botão
        if (ImGui::Button("Autocross", ImVec2(150, 50))) {}

        ImGui::SetCursorPos(ImVec2(800, 600)); // Posição do quarto botão
        if (ImGui::Button("Skidpad", ImVec2(150, 50))) {}

        ImGui::SetCursorPos(ImVec2(1000, 600)); // Posição do quinto botão
        if (ImGui::Button("Enduro", ImVec2(150, 50))) {}

        ImGui::End();

        // Renderiza o frame do ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Troca os buffers
        glfwSwapBuffers(window);
    }

    // Limpeza
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
