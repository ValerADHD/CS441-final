#ifndef ORBIT_CAMERA_H
#define ORBIT_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

typedef struct {
    glm::vec2 orbit_angles_deg;
    float radius;
    glm::vec3 origin;
    glm::vec3 position;
} OrbitCamera;

OrbitCamera *r_create_orbit_camera(glm::vec3 origin, float radius, glm::vec2 orbit_angles);

glm::mat4 r_get_orbit_view_matrix(OrbitCamera *oc);

void r_update_orbit_camera(OrbitCamera *oc, glm::vec2 mouse_delta_px);

#endif