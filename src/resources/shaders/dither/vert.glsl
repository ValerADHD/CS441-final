#version 400

layout (location = 0) in vec3 POSITION;
layout (location = 1) in vec3 NORMAL;

uniform mat4 view;
uniform mat4 projection;

out vec3 vertex_position;
out vec3 vertex_normal;
out vec3 vertex_color;
out vec2 screen_uv;

void main() {
  vertex_position = (view * vec4(POSITION, 1.0)).xyz;
  vertex_normal = (transpose(inverse(view)) * vec4(NORMAL, 0.0)).xyz;
  vertex_color = vec3(.7);
  gl_Position = projection * view * vec4(POSITION, 1.0);
  screen_uv = (gl_Position.xy / gl_Position.w + 1.0) / 2.0;
}
