#include <GL/glew.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>

#include "camera/Camera.h"
#include "graphic/Shader.h"
#include "graphic/Texture.h"
#include "loader/ShaderLoader.h"
#include "loader/TextureLoader.h"
#include "property/WindowProperty.h"
#include "reader/FileReader.h"
#include "window/Window.h"

// GLM
#include <event/EventManager.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "cube/Chunks.h"
#include "graphic/CubeRenderer.h"

float crosshairVertices[] = {
    // x    y
    -0.01f, -0.01f,
    0.01f, 0.01f,

    -0.01f, 0.01f,
    0.01f, -0.01f,
};

int crosshairAttributes[] = {
    2, 0 //null terminator
};

int main() {
    // PROPERTIES
    const YAML::Node config = YAML::LoadFile("res/window-property.yml");
    WindowProperty window_property{};
    window_property.parse(config);

    // WINDOW
    Window::initialize(window_property);

    // EVENTS
    EventManager::initialize();

    // SHADER
    const std::string vertexShaderCode = FileReader::readFile("res/shader/main.vert");
    const std::string fragmentShaderCode = FileReader::readFile("res/shader/main.frag");
    const Shader *shaderProgram = ShaderLoader::loadShaderProgram(vertexShaderCode, fragmentShaderCode);

    const std::string crosshairVertexShaderCode = FileReader::readFile("res/shader/crosshair.vert");
    const std::string crosshairFragmentShaderCode = FileReader::readFile("res/shader/crosshair.frag");
    const Shader *crosshairShaderProgram = ShaderLoader::loadShaderProgram(
        crosshairVertexShaderCode, crosshairFragmentShaderCode);

    // TEXTURE
    const Texture *texture = TextureLoader::loadTexture("res/image/block.png");

    // CUBE RENDER
    auto *chunks = new Chunks(8, 1, 8);
    auto meshes = new Mesh *[chunks->totalChunks];
    for (size_t i = 0; i < chunks->totalChunks; i++)
        meshes[i] = nullptr;
    CubeRenderer renderer(1024 * 1024 * 8);

    // COLOR
    Window::clear(0.5f, 0.5f, 0.5f, 1.0f);

    // VIEW
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // CAMERA
    auto crosshair = new Mesh(crosshairVertices, 4, crosshairAttributes);
    auto *camera = new Camera(vec3(0, 0, 1), radians(70.0f));

    // LOOP
    float lastTime = glfwGetTime();
    float delta = 0.0f;

    float camX = 0.0f;
    float camY = 0.0f;

    float speed = 5;

    while (!Window::isShouldClose) {
        float currentTime = glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;

        // EVENT
        if (EventManager::isKeyJustPressed(GLFW_KEY_ESCAPE)) {
            Window::setShouldClose(true);
        }
        if (EventManager::isKeyJustPressed(GLFW_KEY_TAB)) {
            EventManager::toggleCursor();
        }

        if (EventManager::isKeyPressed(GLFW_KEY_W)) {
            camera->position += camera->front * delta * speed;
        }
        if (EventManager::isKeyPressed(GLFW_KEY_S)) {
            camera->position -= camera->front * delta * speed;
        }
        if (EventManager::isKeyPressed(GLFW_KEY_D)) {
            camera->position += camera->right * delta * speed;
        }
        if (EventManager::isKeyPressed(GLFW_KEY_A)) {
            camera->position -= camera->right * delta * speed;
        }

        if (EventManager::_isCursorLocked) {
            camY += -EventManager::_deltaY / Window::height * 2;
            camX += -EventManager::_deltaX / Window::height * 2;

            if (camY < -radians(89.0f)) {
                camY = -radians(89.0f);
            }
            if (camY > radians(89.0f)) {
                camY = radians(89.0f);
            }

            camera->rotationMatrix = mat4(1.0f);
            camera->rotate(camY, camX, 0);
        } {
            vec3 hitPosition;
            vec3 hitNormal;
            vec3 cubeCoords;
            if (Cube *cube = chunks->rayCast(camera->position, camera->front, 10.0f, hitPosition, hitNormal,
                                               cubeCoords);
                cube != nullptr) {
                if (EventManager::isMouseButtonJustPressed(GLFW_MOUSE_BUTTON_1)) {
                    chunks->setCube(static_cast<int>(cubeCoords.x), static_cast<int>(cubeCoords.y),
                                     static_cast<int>(cubeCoords.z), 0);
                }
                if (EventManager::isMouseButtonJustPressed(GLFW_MOUSE_BUTTON_2)) {
                    chunks->setCube(static_cast<int>(cubeCoords.x) + static_cast<int>(hitNormal.x),
                                     static_cast<int>(cubeCoords.y) + static_cast<int>(hitNormal.y),
                                     static_cast<int>(cubeCoords.z) + static_cast<int>(hitNormal.z), 2);
                }
            }
        }

        Chunk *closes[27];
        for (size_t i = 0; i < chunks->totalChunks; i++) {
            Chunk *chunk = chunks->chunks[i];
            if (!chunk->modified)
                continue;
            chunk->modified = false;
            if (meshes[i] != nullptr)
                delete meshes[i];

            for (auto &close: closes)
                close = nullptr;
            for (size_t j = 0; j < chunks->totalChunks; j++) {
                Chunk *other = chunks->chunks[j];

                int ox = other->x - chunk->x;
                int oy = other->y - chunk->y;
                int oz = other->z - chunk->z;

                if (abs(ox) > 1 || abs(oy) > 1 || abs(oz) > 1)
                    continue;

                ox += 1;
                oy += 1;
                oz += 1;
                closes[(oy * 3 + oz) * 3 + ox] = other;
            }
            Mesh *mesh = renderer.render(chunk, const_cast<const Chunk **>(closes));
            meshes[i] = mesh;
        }

        Window::clear();

        // RENDER
        shaderProgram->bind();
        shaderProgram->setUniformMatrix("uProjectionMatrix", camera->getProjectionMatrix());
        shaderProgram->setUniformMatrix("uViewMatrix", camera->getViewMatrix());

        texture->bind();

        mat4 uModelMatrix;
        for (size_t i = 0; i < chunks->totalChunks; i++) {
            Chunk *chunk = chunks->chunks[i];
            Mesh *mesh = meshes[i];
            uModelMatrix = translate(mat4(1.0f), vec3(chunk->x * CHUNK_W + 0.5f, chunk->y * CHUNK_H + 0.5f,
                                                      chunk->z * CHUNK_D + 0.5f));
            shaderProgram->setUniformMatrix("uModelMatrix", uModelMatrix);
            mesh->draw(GL_TRIANGLES);
        }

        crosshairShaderProgram->bind();
        crosshair->draw(GL_LINES);

        Window::update();
        EventManager::pullEvents();
    }

    delete shaderProgram;
    delete texture;
    delete chunks;
    delete crosshair;
    delete crosshairShaderProgram;
    Window::destroy();

    return 0;
}
