#include "orbit_camera.hpp"

OrbitCamera *r_create_orbit_camera(glm::vec3 origin, float radius, glm::vec2 orbit_angles_deg) {
    OrbitCamera *oc = (OrbitCamera *)malloc(sizeof(OrbitCamera));
    oc->origin = origin;
    oc->radius = radius;
    oc->orbit_angles_deg = orbit_angles_deg;
    
    glm::vec4 position = glm::vec4(0.0, 0.0, radius, 1.0);
    position = glm::rotate(glm::mat4(1.0), glm::radians(orbit_angles_deg.x), glm::vec3(1.0, 0.0, 0.0)) * position;
    position = glm::rotate(glm::mat4(1.0), glm::radians(orbit_angles_deg.y), glm::vec3(0.0, 1.0, 0.0)) * position;

    glm::vec3 final_position = origin + glm::vec3(position.x, position.y, position.z);
    oc->position = final_position;

    return oc;
}

glm::mat4 r_get_orbit_view_matrix(OrbitCamera *oc) {
    glm::vec4 position = glm::vec4(0.0, 0.0, oc->radius, 1.0);
    position = glm::rotate(glm::mat4(1.0), glm::radians(oc->orbit_angles_deg.x), glm::vec3(1.0, 0.0, 0.0)) * position;
    position = glm::rotate(glm::mat4(1.0), glm::radians(oc->orbit_angles_deg.y), glm::vec3(0.0, 1.0, 0.0)) * position;
    
    glm::vec3 final_position = oc->origin + glm::vec3(position.x, position.y, position.z);
    oc->position = final_position;
    return glm::lookAt(oc->position, oc->origin, glm::vec3(0.0, 1.0, 0.0));
}

void r_update_orbit_camera(OrbitCamera *oc, glm::vec2 mouse_delta_px) {
    oc->orbit_angles_deg.x -= mouse_delta_px.y;
    oc->orbit_angles_deg.y -= mouse_delta_px.x;
}