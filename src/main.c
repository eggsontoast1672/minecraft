#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>
#include <cglm/struct.h>
#include <glad/glad.h>

#include "minecraft/camera.h"
#include "minecraft/shader.h"

const float vertices[] = {
    -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f, 1.0f,
};

const unsigned int indices[] = {
    0, 1, 3, 3, 1, 2, 1, 5, 2, 2, 5, 6, 5, 4, 6, 6, 4, 7,
    4, 0, 7, 7, 0, 3, 3, 2, 7, 7, 2, 6, 4, 5, 0, 0, 5, 1,
};

typedef struct mesh {
  GLuint vertex_array;
  GLuint vertex_buffer;
  GLuint element_buffer;
} mesh_t;

mesh_t create_mesh(void) {
  mesh_t mesh;

  glGenVertexArrays(1, &mesh.vertex_array);
  glBindVertexArray(mesh.vertex_array);
  glGenBuffers(1, &mesh.vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
  glGenBuffers(1, &mesh.element_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.element_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices,
               GL_STATIC_DRAW);
  return mesh;
}

void delete_mesh(mesh_t mesh) {
  glDeleteBuffers(1, &mesh.element_buffer);
  glDeleteBuffers(1, &mesh.vertex_buffer);
  glDeleteVertexArrays(1, &mesh.vertex_array);
}

void configure_vertex_layout(void) {
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
}

mat4s get_projection_matrix(void) {
  return glms_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void process_input(GLFWwindow *window, camera_t *camera) {
  const float speed = 0.1f;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera->position.z -= speed;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera->position.x -= speed;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera->position.z += speed;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera->position.x += speed;
  }
}

int main(void) {
  GLFWwindow *window;
  mesh_t mesh;
  program_t program;
  mat4s view, projection;
  camera_t camera = {{{0.0f, 0.0f, 10.0f}}, {{0.0f, 0.0f, -1.0f}}};

  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return 1;
  }
  window = glfwCreateWindow(800, 600, "Minecraft", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to create window\n");
    return 1;
  }
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize OpenGL\n");
    return 1;
  }
  mesh = create_mesh();
  configure_vertex_layout();
  program = shader_program_create("assets/default.vert", "assets/default.frag");
  glUseProgram(program);
  projection = get_projection_matrix();
  glUniformMatrix4fv(glGetUniformLocation(program, "u_projection"), 1, GL_FALSE,
                     (const GLfloat *)projection.raw);
  while (!glfwWindowShouldClose(window)) {
    process_input(window, &camera);
    glClear(GL_COLOR_BUFFER_BIT);
    /* Recalculate the view matrix since it may have changed */
    view = camera_get_matrix(camera);
    glUniformMatrix4fv(glGetUniformLocation(program, "u_view"), 1, GL_FALSE,
                       (const GLfloat *)view.raw);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
    glfwSwapBuffers(window);

    glfwPollEvents();
  }
  glDeleteProgram(program);
  delete_mesh(mesh);
  glfwTerminate();
  return 0;
}
