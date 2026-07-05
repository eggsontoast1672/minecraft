#include <minecraft/shader.hpp>

#include <stdexcept>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <minecraft/filesystem.hpp>

static GLuint load_shader(GLenum kind, const char *path) {
  std::string source = load_from_path(path);
  const char *source_c_str = source.c_str();
  GLuint shader = glCreateShader(kind);
  glShaderSource(shader, 1, &source_c_str, nullptr);
  glCompileShader(shader);

  // TODO: Check for errors
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == 0) {
    char info_log[256];
    glGetShaderInfoLog(shader, sizeof info_log, nullptr, info_log);
    glDeleteShader(shader);
    throw std::runtime_error(info_log);
  }

  return shader;
}

Shader::Shader(const char *vertex_path, const char *fragment_path) {
  GLuint vertex_shader = load_shader(GL_VERTEX_SHADER, vertex_path);
  GLuint fragment_shader = load_shader(GL_FRAGMENT_SHADER, fragment_path);

  m_id = glCreateProgram();
  glAttachShader(m_id, vertex_shader);
  glAttachShader(m_id, fragment_shader);
  glLinkProgram(m_id);

  glDetachShader(m_id, fragment_shader);
  glDetachShader(m_id, vertex_shader);
  glDeleteShader(fragment_shader);
  glDeleteShader(vertex_shader);
  
  GLint status;
  glGetProgramiv(m_id, GL_LINK_STATUS, &status);
  if (status == 0) {
    char info_log[256];
    glGetProgramInfoLog(m_id, sizeof info_log, nullptr, info_log);
    glDeleteProgram(m_id);
    throw std::runtime_error(info_log);
  }
}

void Shader::set_uniform(const char *name, glm::mat4 matrix) const {
  GLint location = glGetUniformLocation(m_id, name);
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
