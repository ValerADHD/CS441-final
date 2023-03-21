#version 400

layout (location = 0) in vec3 POSITION;
layout (location = 1) in vec3 NORMAL;

uniform mat4 view;
uniform mat4 projection;

out vec3 vertex_position;
out vec3 vertex_normal;
out vec2 screen_uv;
out vec3 color;
out float lighting;

uniform float kamb = 0.3;
uniform float kdif = 0.7;
uniform float kspec = 1.0;
uniform float aspec = 10.0;

uniform vec3 light_dir = vec3(0.7, .7, 0.0);
uniform vec3 camera_position = vec3(0.0, 0.0, 0.25);

void main() {
  vertex_position = (view * vec4(POSITION, 1.0)).xyz;
  vertex_normal = (transpose(inverse(view)) * vec4(NORMAL, 0.0)).xyz;
  color = vec3(1.0);
  gl_Position = projection * view * vec4(POSITION, 1.0);
  screen_uv = (gl_Position.xy / gl_Position.w + 1.0) / 2.0;

  float diffuse = max(0.0, dot(vertex_normal, light_dir));

  vec3 frag_dir = normalize(vertex_position - camera_position);
  vec3 reflection = reflect(light_dir, vertex_normal);
  
  float specular = max(0.0, pow(dot(frag_dir, reflection), aspec));

  lighting = kamb + kdif * diffuse + kspec * specular;
}
