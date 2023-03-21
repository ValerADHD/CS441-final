#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>

#include "../graphics/models/model.hpp"
#include "../graphics/renderContext.hpp"

class Scene {
    public:
        Model *model;
        GLuint shader_prog;

        float phong_kamb;
        float phong_kdif;
        float phong_kspec;
        float phong_aspec;

        Scene();
        ~Scene();

        void render(RenderContext *rc);
        virtual void showUI();
};

class GoochScene : public Scene {
    public:
        GoochScene();

        float warm_col[3];
        float cool_col[3];

        void showUI();
};

class VertPhongScene : public Scene {
    public:
        VertPhongScene();
};

class FragPhongScene : public Scene {
    public:
        FragPhongScene();
};

class CelScene : public Scene {
    public:
        CelScene();

        int cel_steps;

        void showUI();
};

#endif