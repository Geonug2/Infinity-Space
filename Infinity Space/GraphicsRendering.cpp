#include "GraphicsRendering.h"
#include <stdexcept>

GraphicsRendering::GraphicsRendering(ID3D12Device* device) : device(device) {
    CreateBuffers();
}

void GraphicsRendering::CreateBuffers() {
    // Näidis vertex andmed
    struct Vertex {
        float position[3];
        float color[3];
    };

    Vertex vertices[] = {
        { { 0.0f, 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
    };

    // Looge vertex buffer
    vertexBuffer = new VertexBuffer(device, vertices, sizeof(vertices));

    // Näidis index andmed
    UINT indices[] = { 0, 1, 2 };

    // Looge index buffer
    indexBuffer = new IndexBuffer(device, indices, sizeof(indices));
}

void GraphicsRendering::Render() {
    // Renderdamise loogika, sealhulgas vertex ja index bufferite kasutamine
    // Siin tuleks lisada kood, mis edastab vertexBuffer ja indexBuffer GPU-le
}

GraphicsRendering::~GraphicsRendering() {
    delete vertexBuffer;
    delete indexBuffer;
}