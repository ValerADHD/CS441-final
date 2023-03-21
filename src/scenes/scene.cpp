#include "scene.hpp"
#include "../graphics/shaders/shader.hpp"
#include "../include/imgui.h"

Scene::Scene() {
    phong_kamb = 0.3;
    phong_kdif = 0.7;
    phong_kspec = 1.0;
    phong_aspec = 10.0;
}

GoochScene::GoochScene() {
    model = r_load_model("./resources/models/bun_zipper.obj");
    shader_prog = r_create_shader_program("./resources/shaders/gooch/vert.glsl", "./resources/shaders/gooch/frag.glsl");

    warm_col[0] = 1.0; warm_col[1] = 1.0; warm_col[2] = 0.0;
    cool_col[0] = 0.0; cool_col[1] = 0.0; cool_col[2] = 1.0;
}

VertPhongScene::VertPhongScene() {
    model = r_load_model("./resources/models/bun_decimated.obj");
    shader_prog = r_create_shader_program("./resources/shaders/vert_phong/vert.glsl", "./resources/shaders/vert_phong/frag.glsl");
}

FragPhongScene::FragPhongScene() {
    model = r_load_model("./resources/models/bun_decimated.obj");
    shader_prog = r_create_shader_program("./resources/shaders/frag_phong/vert.glsl", "./resources/shaders/frag_phong/frag.glsl");
}

CelScene::CelScene() {
    model = r_load_model("./resources/models/buddha.obj");
    shader_prog = r_create_shader_program("./resources/shaders/cel/vert.glsl", "./resources/shaders/cel/frag.glsl");

    cel_steps = 3;
}

Scene::~Scene() {
    r_delete_model(model);
    glDeleteProgram(shader_prog);
}

void Scene::render(RenderContext *rc) {
    glBindVertexArray(model->_vao);
    r_set_active_shader_program(rc, shader_prog);

    glDrawElements(GL_TRIANGLES, model->num_indices, GL_UNSIGNED_INT, NULL);
}

void Scene::showUI() {
    ImGui::BeginChild("Phong Options", ImVec2(240, 104), true);

    ImGui::SliderFloat("Ambient", &phong_kamb, 0.0, 0.5);
    ImGui::SliderFloat("Diffuse", &phong_kdif, 0.0, 1.0);
    ImGui::SliderFloat("Specular", &phong_kspec, 0.0, 5.0);
    ImGui::SliderFloat("Shine", &phong_aspec, 5.0, 50.0);

    GLint kamb_loc = glGetUniformLocation(shader_prog, "kamb");
    if(kamb_loc != -1) {
        glUniform1fv(kamb_loc, 1, &phong_kamb);
    }
    GLint kdif_loc = glGetUniformLocation(shader_prog, "kdif");
    if(kdif_loc != -1) {
        glUniform1fv(kdif_loc, 1, &phong_kdif);
    }
    GLint kspec_loc = glGetUniformLocation(shader_prog, "kspec");
    if(kspec_loc != -1) {
        glUniform1fv(kspec_loc, 1, &phong_kspec);
    }
    GLint aspec_loc = glGetUniformLocation(shader_prog, "aspec");
    if(aspec_loc != -1) {
        glUniform1fv(aspec_loc, 1, &phong_aspec);
    }

    ImGui::EndChild();
}

void GoochScene::showUI() {
    Scene::showUI();

    ImGui::BeginChild("Gooch Options", ImVec2(240, 360), true);

    ImGui::ColorPicker3("Warm Color", warm_col, 
        ImGuiColorEditFlags_PickerHueWheel |
        ImGuiColorEditFlags_DisplayHSV
    );
    ImGui::ColorPicker3("Cool Color", cool_col, 
        ImGuiColorEditFlags_PickerHueWheel |
        ImGuiColorEditFlags_DisplayHSV
    );

    GLint warm_col_loc = glGetUniformLocation(shader_prog, "warm");
    if(warm_col_loc != -1) {
        glUniform3fv(warm_col_loc, 1, warm_col);
    }
    GLint cool_col_loc = glGetUniformLocation(shader_prog, "cool");
    if(cool_col_loc != -1) {
        glUniform3fv(cool_col_loc, 1, cool_col);
    }

    ImGui::EndChild();
}

void CelScene::showUI() {
    Scene::showUI();

    ImGui::BeginChild("Cel Options", ImVec2(240, 80));

    ImGui::SliderInt("Shading Steps", &cel_steps, 2, 8);
    float steps = cel_steps;    

    int cel_steps_loc = glGetUniformLocation(shader_prog, "cel_steps");
    if(cel_steps_loc != -1) {
        glUniform1fv(cel_steps_loc, 1, &steps);
    }

    ImGui::EndChild();
}