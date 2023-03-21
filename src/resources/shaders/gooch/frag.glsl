#version 400

in vec3 vertex_position;
in vec3 vertex_normal;
in vec3 color;
in vec2 screen_uv;

out vec4 frag_color;

uniform float kdif = 0.7;
uniform float kspec = 1.0;
uniform float aspec = 10.0;
uniform float warm_col_coeff = .2;
uniform float cool_col_coeff = .6;

uniform vec3 light_dir = vec3(0.7, .7, 0.0);
uniform vec3 camera_position = vec3(0.0, 0.0, 0.25);

uniform vec3 warm = vec3(1.0, 1.0, 0.0);
uniform vec3 cool = vec3(0.0, 0.0, 1.0);

void main() {
  vec3 norm = normalize(vertex_normal);
  
  float diffuse = dot(norm, light_dir);
  vec3 kwarm = warm + warm_col_coeff * color;
  vec3 kcool = cool + cool_col_coeff * color;
  diffuse = (1.0 + diffuse) / 2.0;
  vec3 col = (diffuse) * kwarm + (1.0 - diffuse) * kcool;

  vec3 frag_dir = normalize(vertex_position - camera_position);
  vec3 reflection = reflect(light_dir, norm);
  
  float specular = max(0.0, pow(dot(frag_dir, reflection), aspec));

  frag_color = vec4(col * (1.0 + kspec * specular), 1.0);
}
