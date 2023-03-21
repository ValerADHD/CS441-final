#version 400

in vec3 vertex_position;
in vec3 vertex_normal;
in vec3 color;
in vec2 screen_uv;
in float lighting;

out vec4 frag_color;

void main() {
  vec3 norm = normalize(vertex_normal);

  frag_color = vec4(color * lighting, 1.0);
}
