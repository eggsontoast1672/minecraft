#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
  Shader(const char *vertex_path, const char *fragment_path);
  inline ~Shader() { glDeleteProgram(m_id); }

  inline void use() const { glUseProgram(m_id); }
  void set_uniform(const char *name, glm::mat4 matrix) const;

private:
  unsigned int m_id;
};
