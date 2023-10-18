#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
public:
    void draw(const glm::mat4& view);
};

#endif //RENDERER_H
