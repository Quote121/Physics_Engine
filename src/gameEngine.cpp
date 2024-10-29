#include "gameEngine.hpp"
#include "objects/gameObjects.hpp"
#include "renderer/shader.hpp"
#include "time.hpp"
#include "inputHandler.hpp"

void GameEngine::SetCurrentRenderTarget(std::shared_ptr<Renderer> renderer)
{
    m_renderTarget = renderer;
}

std::shared_ptr<Renderer> GameEngine::GetCurrentRenderTarget()
{
    return m_renderTarget;
}

void GameEngine::Init()
{
    Screen::s_Initalize();

    GameObjectFactory::RegisterObject(GameObjectType::MESHOBJECT, MeshObject::Create);
    GameObjectFactory::RegisterObject(GameObjectType::CAMERAOBJECT, CameraObject::Create);

    // We can then create an object like so:
    m_meshObject = std::static_pointer_cast<MeshObject>(GameObjectFactory::CreateObject(GameObjectType::MESHOBJECT));
    auto cameraObject = GameObjectFactory::CreateObject(GameObjectType::CAMERAOBJECT);

    ObjectLoader::LoadMesh("./assets/models/teapot/teapot.obj", m_meshObject);

    // this->SetCurrentRenderTarget(cameraObject->GetComponent<RendererComponent>()->renderer);

    // std::dynamic_pointer_cast<MeshObject>(ourMeshObject)->MeshPrint();
}


void GameEngine::GameLoop()
{
    //
    // <Temp> Example render code
    //

    // Example of shader compilation
    Shader shader("./assets/shaders/defaultShader/default.vert", "./assets/shaders/defaultShader/default.frag");
    Shader shader2("./assets/shaders/defaultShader/default.shader");
    Shader shader3("./assets/shaders/3DShader/default/default.shader");

    Renderer renderer;
    VertexArray VAO;
    VertexBuffer VBO;
    VertexBufferLayout VBL;

    // float verts[] =
    // {
    // -0.5f, -0.5f, 0.0f,
    //  0.5f, -0.5f, 0.0f,
    //  0.0f,  0.5f, 0.0f
    // };

    // VBL.AddFloat(3);
    // VBO.SetData<float>(verts, sizeof(verts));
    // VAO.AddBuffer(&VBO, &VBL);
    //
    // <\Temp>
    //
    m_meshObject->GetComponent<PositionComponent>()->m_position = {0, 0, 5};
    while (!Screen::s_GetQuitStatus())
    {
        Time::UpdateFrameTime();
        // std::cout << Time::GetFramesPerSecond() << std::endl;

        Screen::s_ClearColour({0.2f, 0.0f, 0.4f});
        Screen::s_UpdateViewPort();

        shader2.Use();
        // shader3.Use();

        this->GetCurrentRenderTarget()->DrawArrays(&m_meshObject->m_VAO, m_meshObject->m_indices.size());
        // glDrawArrays(GL_TRIANGLES, 0, 3);

        Screen::s_SwapWindow();

        InputPublisher::GetInstance()->ReadInputs();

    }
    Screen::s_CleanUp();
}
