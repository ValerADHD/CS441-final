#version 400

in vec3 vertex_position;
in vec3 vertex_normal;
in vec3 color;
in vec2 screen_uv;

out vec4 frag_color;

uniform float kamb = 0.3;
uniform float kdif = 0.7;
uniform float kspec = 1.0;
uniform float aspec = 10.0;

uniform vec3 light_dir = vec3(0.7, .7, 0.0);
uniform vec3 camera_position = vec3(0.0, 0.0, 0.25);


void main() {
  vec3 norm = normalize(vertex_normal);
  
  float diffuse = max(0.0, dot(norm, light_dir));

  vec3 frag_dir = normalize(vertex_position - camera_position);
  vec3 reflection = reflect(light_dir, norm);
  
  float specular = max(0.0, pow(dot(frag_dir, reflection), 10.0));

  frag_color = vec4(color * (kamb + diffuse * kdif + 1.0 * specular), 1.0);
}
