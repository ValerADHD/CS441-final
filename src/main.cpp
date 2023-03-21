#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <stdlib.h>

#include "include/stb_image.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/imgui.h"
#include "include/imgui_impl_glfw.h"
#include "include/imgui_impl_opengl3.h"

#include "graphics/renderContext.hpp"
#include "graphics/shaders/shader.hpp"
#include "graphics/display/display.hpp"
#include "graphics/models/model.hpp"
#include "graphics/camera/orbit_camera.hpp"
#include "scenes/scene.hpp"


#define WIDTH 800
#define HEIGHT 800

void _print_shader_info_log(GLuint shader_index) {
  int max_len = 2048;
  int actual_len = 0;
  char shader_log[2048];
  glGetShaderInfoLog(shader_index, max_len, &actual_len, shader_log);
  printf("shader info log for GL index %u:\n%s\n", shader_index, shader_log);
}

//Input flags
enum InputFlags {
  INPUT_NONE = 0,
  INPUT_LEFT = 1,
  INPUT_RIGHT = 2,
  INPUT_FORWARD = 4,
  INPUT_BACK = 8
};

int main() {
  // start GL context and O/S window using the GLFW helper library
  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  GLFWwindow *window = r_initialize_window(WIDTH, HEIGHT);
  glfwMakeContextCurrent(window);
  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();

  // get version info
  const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte *version = glGetString(GL_VERSION);   // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);


  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGui_ImplGlfw_InitForOpenGL(window, true);  
  ImGui_ImplOpenGL3_Init("#version 130");

  OrbitCamera *oc = r_create_orbit_camera(glm::vec3(0.0), 0.25, glm::vec2(-15.0, 210.0));

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glClearColor(47.0 / 255.0, 48.0 / 255.0, 97.0 / 255.0, 1.0);

  RenderContext *rc = (RenderContext*)malloc(sizeof(RenderContext));
  
  rc->projection_matrix = glm::perspective(
    glm::radians(70.0f), 
    1.0f,
    0.1f, 100.0f
  );

  rc->view_matrix = r_get_orbit_view_matrix(oc);

  int scene_idx = 0;
  int num_scenes = 4;

  Scene* scenes[4] {
    new VertPhongScene(),
    new FragPhongScene(),
    new CelScene(),
    new GoochScene()
  };

  double mouseX = 0.0, mouseY = 0.0;

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    
    ImGui::SetNextWindowPos(ImVec2(WIDTH / 2.0, 0.0), 0, ImVec2(0.5, 0.0));
    ImGui::Begin("scene_select", NULL, 
      ImGuiWindowFlags_NoDecoration |
      ImGuiWindowFlags_AlwaysAutoResize
    );

    if(ImGui::Button("Prev Scene")) {
      scene_idx += num_scenes - 1;
      scene_idx %= num_scenes;
    }
    ImGui::SameLine();
    if(ImGui::Button("Next Scene")) {
      scene_idx++;
      scene_idx %= num_scenes;
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(WIDTH, 0.0), 0, ImVec2(1.0, 0.0));
    ImGui::Begin("Config", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize);
    scenes[scene_idx]->showUI();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if(!ImGui::IsAnyItemHovered() && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
      double newMouseX, newMouseY;
      glfwGetCursorPos(window, &newMouseX, &newMouseY);
      glm::vec2 mouseDelta = glm::vec2(newMouseX - mouseX, newMouseY - mouseY);
      r_update_orbit_camera(oc, mouseDelta);
    }

    glfwGetCursorPos(window, &mouseX, &mouseY);

    r_set_view_matrix(rc, r_get_orbit_view_matrix(oc));

    scenes[scene_idx]->render(rc);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  free(oc);
  free(rc);
  for(int i = 0; i < num_scenes; i++) {
    scenes[i]->~Scene();
  }
  
  ImGui_ImplGlfw_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();

  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}
