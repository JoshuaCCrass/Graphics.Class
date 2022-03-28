#include "App.hpp"

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float vertices[] = {
  // positions           // texture coords
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
   0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
   0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

// world space positions of our cubes
std::vector<glm::vec3> brickPositions = {
  // Wall 1
  glm::vec3(  1.0f,  1.0f,  1.0f), //
  glm::vec3(  1.0f,  2.0f,  1.0f),
  glm::vec3(  1.0f,  3.0f,  1.0f),
  glm::vec3(  2.0f,  1.0f,  1.0f), //
  glm::vec3(  2.0f,  2.0f,  1.0f),
  glm::vec3(  2.0f,  3.0f,  1.0f),
  glm::vec3(  3.0f,  1.0f,  1.0f), //
  glm::vec3(  3.0f,  2.0f,  1.0f),
  glm::vec3(  3.0f,  3.0f,  1.0f),
  glm::vec3(  4.0f,  1.0f,  1.0f), //
  glm::vec3(  4.0f,  2.0f,  1.0f),
  glm::vec3(  4.0f,  3.0f,  1.0f),
  glm::vec3(  5.0f,  1.0f,  1.0f), //
  glm::vec3(  5.0f,  2.0f,  1.0f),
  glm::vec3(  5.0f,  3.0f,  1.0f),
  glm::vec3(  6.0f,  1.0f,  1.0f), //
  glm::vec3(  6.0f,  2.0f,  1.0f),
  glm::vec3(  6.0f,  3.0f,  1.0f),
  glm::vec3(  7.0f,  1.0f,  1.0f), //
  glm::vec3(  7.0f,  2.0f,  1.0f),
  glm::vec3(  7.0f,  3.0f,  1.0f),
  glm::vec3(  8.0f,  1.0f,  1.0f), //
  glm::vec3(  8.0f,  2.0f,  1.0f),
  glm::vec3(  8.0f,  3.0f,  1.0f),
  // Wall 2
};

App::App()
{
  Engine::Log("Object Made");
}
App::~App()
{
  Engine::Log("Object Destroyed");
}

void App::Run()
{
  if (appState == AppState::ON)
    Engine::FatalError("App already running.");
  
  previousTime = high_resolution_clock::now();

  Engine::Init();

  unsigned int windowFlags = 0;

  // windowFlags |= Engine::WindowFlags::FULLSCREEN;

  // windowFlags |= Engine::WindowFlags::BORDERLESS;

  window.Create("Engine", 800, 600, windowFlags);

  Load();

  appState = AppState::ON;

  Loop();
}

void App::Load()
{
  // configure opengle global state
  glEnable(GL_DEPTH_TEST);

  // build and compile our shader program
  // ------------------------------------
  shader.Compile("assets/shaders/house_hw.vs","assets/shaders/house_hw.fs");
  shader.AddAttribute("aPos");
  shader.AddAttribute("aTexCoord");
  shader.Link();

  // unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // texture coord
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // load texture 1
  texture1 = Engine::LoadPNGToGLTexture("assets/textures/GoodVibes/grass_block_top.png", GL_RGBA, GL_RGBA);
  // load texture 2
  texture2 = Engine::LoadPNGToGLTexture("assets/textures/GoodVibes/bricks.png", GL_RGBA, GL_RGBA);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);

  previousTime = high_resolution_clock::now();
}

void App::Loop()
{
  while (appState == AppState::ON)
  {
    currentTime = high_resolution_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - previousTime).count() / 1000000000.0;
    previousTime = currentTime;
    Engine::Log(std::to_string(deltaTime));

    Update();
    Draw();
    // Get SDL to swap our buffer
    window.SwapBuffer();
    LateUpdate();
    FixedUpdate(0.0f);
    InputUpdate();
  }
}
void App::Update()
{
  if (inputManager.isKeyPressed(SDLK_w))
  {
    camera.ProcessKeyboard(Engine::Camera_Movement::FORWARD, deltaTime);
  }

  if (inputManager.isKeyPressed(SDLK_s))
  {
    camera.ProcessKeyboard(Engine::Camera_Movement::BACKWARD, deltaTime);
  }

  if (inputManager.isKeyPressed(SDLK_a))
  {
    camera.ProcessKeyboard(Engine::Camera_Movement::LEFT, deltaTime);
  }

  if (inputManager.isKeyPressed(SDLK_d))
  {
    camera.ProcessKeyboard(Engine::Camera_Movement::RIGHT, deltaTime);
  }
}
void App::Draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // bind textures on corresponding texture units
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1.id);

  // be sure to activate the shader before any calls to glUniform
  shader.Use();

  glUniform1i(glGetUniformLocation(shader.GetProgramID(), "texture1"), 0);

  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  projection = glm::perspective(glm::radians(camera.Zoom), (float)window.GetScreenWidth()/(float)window.GetScreenHeight(), 0.1f, 100.0f);
  view = camera.GetViewMatrix();

  glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(),"projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(),"view"), 1, GL_FALSE, glm::value_ptr(view));

  // render boxes
  glBindVertexArray(VAO);

  for (unsigned int x = 0; x < 10; x++)
  {
    for (unsigned int z = 0; z < 10; z++)
    {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(x,0.0,z));
      glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(),"model"), 1, GL_FALSE, glm::value_ptr(model));

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
  }

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture2.id);

  for (glm::uint i = 0; i < brickPositions.size(); i++)
  {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, brickPositions[i]);
      glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(),"model"), 1, GL_FALSE, glm::value_ptr(model));

      glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  shader.UnUse();
}

void App::LateUpdate() {}
void App::FixedUpdate(float dt) {}
void App::InputUpdate()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      appState = AppState::OFF;
      break;
    case SDL_MOUSEMOTION:
      camera.ProcessMouseMovement(
        event.motion.xrel,
        -event.motion.yrel
      );
      break;
    case SDL_KEYUP:
      inputManager.releasedKey(event.key.keysym.sym);
      break;
    case SDL_KEYDOWN:
      inputManager.pressKey(event.key.keysym.sym);
      break;
    }
  }
}