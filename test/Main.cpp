#define SDL_MAIN_HANDLED 

#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

// This context is required to run tests which involves gl* functions call
// Need to initialize SDL, create window (can be hidden), GL context, and glew
// This class is responsible to keep this context until tests stops
class GLContext
{
public:
    using WindowGuard = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
    using ContextGuard = std::unique_ptr<std::remove_pointer_t<SDL_GLContext>, decltype(&SDL_GL_DeleteContext)>;

    GLContext()
        : m_window(nullptr, &SDL_DestroyWindow)
        , m_glContext(nullptr, &SDL_GL_DeleteContext)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw std::runtime_error("Failed to init SDL: " + std::string(SDL_GetError()));
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        m_window = WindowGuard(
            SDL_CreateWindow(
                "Whatevs",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                800,
                600,
                SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN),
            &SDL_DestroyWindow
        );

        if (!m_window)
        {
            throw std::runtime_error("Failed to create invisible window");
        }

        m_glContext = ContextGuard(
            SDL_GL_CreateContext(m_window.get()),
            &SDL_GL_DeleteContext
        );

        const GLenum glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK)
        {
            throw std::runtime_error("Failed to initialize glew");
        }
    }

    ~GLContext()
    {
        SDL_Quit();
    }

private:
    WindowGuard m_window;
    ContextGuard m_glContext;
};

int main(int argc, char** argv)
{
    try
    {
        GLContext context;

        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Failed to run tests: " << e.what() << std::endl;
        return -1;
    }
}