#include "Application.h"
#include <iostream>

bool Application::IsRunning() { return running; }

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    running = Graphics::OpenWindow();

    particle = new Particle(50, 100, 1.0);
    particle->velocity = Vec2(20.0, 1.0);

    std::cout << "screen size is: Width = " << Graphics::Width()
              << ", Height = " << Graphics::Height() << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// Input processing
///////////////////////////////////////////////////////////////////////////////
void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update() {

    particle->position += particle->velocity;

    if (particle->position.x + 4.0f > Graphics::Width() ||
        particle->position.x - 4.0f < 0.0f) {
        particle->velocity.x *= -1;
    }

    if (particle->position.y + 4.0f > Graphics::Height() ||
        particle->position.y - 4.0f < 0.0f) {
        particle->velocity.y *= -1;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);
    Graphics::DrawFillCircle(200, 200, 40, 0xFFFFFFFF);
    Graphics::DrawFillCircle(particle->position.x, particle->position.y, 4,
                             0xFFFFFFFF);
    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() {

    delete particle;

    Graphics::CloseWindow();
}