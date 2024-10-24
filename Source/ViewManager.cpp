///////////////////////////////////////////////////////////////////////////////
// viewmanager.h
// ============
// manage the viewing of 3D objects within the viewport
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////

#include "ViewManager.h"

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>    

// Declaration of the global variables and defines
namespace
{
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 800;
    const char* g_ViewName = "view";
    const char* g_ProjectionName = "projection";

    // Camera object for viewing and interacting with the 3D scene
    Camera* g_pCamera = nullptr;

    // Variables for mouse movement processing
    float gLastX = WINDOW_WIDTH / 2.0f;
    float gLastY = WINDOW_HEIGHT / 2.0f;
    bool gFirstMouse = true;

    // Time between current frame and last frame
    float gDeltaTime = 0.0f;
    float gLastFrame = 0.0f;

    // Speed multiplier for camera movement (updated by scroll)
    float gCameraSpeedMultiplier = 1.0f;

    // Flag for orthographic projection mode
    bool bOrthographicProjection = false;
}

/***********************************************************
 *  ViewManager()
 *
 *  The constructor for the class
 ***********************************************************/
ViewManager::ViewManager(ShaderManager* pShaderManager)
{
    m_pShaderManager = pShaderManager;
    m_pWindow = nullptr;
    g_pCamera = new Camera();

    // Default camera view parameters
    g_pCamera->Position = glm::vec3(0.5f, 5.5f, 10.0f);
    g_pCamera->Front = glm::vec3(0.0f, -0.5f, -2.0f);
    g_pCamera->Up = glm::vec3(0.0f, 1.0f, 0.0f);
    g_pCamera->Zoom = 80;
}

/***********************************************************
 *  ~ViewManager()
 *
 *  The destructor for the class
 ***********************************************************/
ViewManager::~ViewManager()
{
    if (g_pCamera)
    {
        delete g_pCamera;
        g_pCamera = nullptr;
    }
    m_pShaderManager = nullptr;
    m_pWindow = nullptr;
}

/***********************************************************
 *  CreateDisplayWindow()
 *
 *  This method is used to create the main display window.
 ***********************************************************/
GLFWwindow* ViewManager::CreateDisplayWindow(const char* windowTitle)
{
    GLFWwindow* window = nullptr;

    // Attempt to create the displayed OpenGL window
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowTitle, NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    // Set the mouse position callback
    glfwSetCursorPosCallback(window, &ViewManager::Mouse_Position_Callback);


    glfwSetScrollCallback(window, ViewManager::Mouse_Scroll_Callback);


    // Capture all mouse events
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Enable blending for supporting transparent rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_pWindow = window;

    return window;
}

/***********************************************************
 *  Mouse_Scroll_Callback()
 *
 *  This method now adjusts the camera movement speed instead
 *  of the zoom level.
 ***********************************************************/
void ViewManager::Mouse_Scroll_Callback(GLFWwindow* window, double xOffset, double yOffset)
{
    // Adjust the camera speed multiplier based on the scroll wheel
    gCameraSpeedMultiplier += static_cast<float>(yOffset) * 0.1f; // Sensitivity adjustment

    // Clamp the speed multiplier to a reasonable range
    if (gCameraSpeedMultiplier < 0.1f)
        gCameraSpeedMultiplier = 0.1f;
    if (gCameraSpeedMultiplier > 5.0f)
        gCameraSpeedMultiplier = 5.0f;
}

/***********************************************************
 *  Mouse_Position_Callback()
 *
 *  This method is automatically called from GLFW whenever
 *  the mouse is moved within the active GLFW display window.
 ***********************************************************/
void ViewManager::Mouse_Position_Callback(GLFWwindow* window, double xMousePos, double yMousePos)
{
    if (gFirstMouse)
    {
        gLastX = xMousePos;
        gLastY = yMousePos;
        gFirstMouse = false;
    }

    // Calculate the X offset and Y offset values for camera movement
    float xOffset = xMousePos - gLastX;
    float yOffset = gLastY - yMousePos; // reversed since y-coordinates go from bottom to top

    gLastX = xMousePos;
    gLastY = yMousePos;

    g_pCamera->ProcessMouseMovement(xOffset, yOffset);
}

/***********************************************************
 *  ProcessKeyboardEvents()
 *
 *  This method processes any keyboard events in the event queue.
 ***********************************************************/
void ViewManager::ProcessKeyboardEvents()
{
    if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_pWindow, true);
    }

    if (g_pCamera == nullptr) return;

    // Camera movement controls, adjusted with the speed multiplier
    float adjustedSpeed = gCameraSpeedMultiplier * gDeltaTime;

    if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(FORWARD, adjustedSpeed);
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(BACKWARD, adjustedSpeed);
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(LEFT, adjustedSpeed);
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(RIGHT, adjustedSpeed);
    }

    // 3D camera up/down movement
    if (glfwGetKey(m_pWindow, GLFW_KEY_Q) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(UP, adjustedSpeed);
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_E) == GLFW_PRESS)
    {
        g_pCamera->ProcessKeyboard(DOWN, adjustedSpeed);
    }

    // Toggle between orthographic and perspective view
    if (glfwGetKey(m_pWindow, GLFW_KEY_O) == GLFW_PRESS)
    {
        bOrthographicProjection = !bOrthographicProjection;
    }
}

/***********************************************************
 *  PrepareSceneView()
 *
 *  This method prepares the 3D scene by setting the appropriate
 *  view and projection matrices.
 ***********************************************************/
void ViewManager::PrepareSceneView()
{
    glm::mat4 view = g_pCamera->GetViewMatrix();
    glm::mat4 projection;

    // Per-frame timing
    float currentFrame = glfwGetTime();
    gDeltaTime = currentFrame - gLastFrame;
    gLastFrame = currentFrame;

    // Process keyboard inputs
    ProcessKeyboardEvents();

    // Set up the correct projection based on the current mode
    if (bOrthographicProjection)
    {
        projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    }
    else
    {
        projection = glm::perspective(glm::radians(g_pCamera->Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    }

    // Set the view and projection matrices into the shader
    if (m_pShaderManager)
    {
        m_pShaderManager->setMat4Value(g_ViewName, view);
        m_pShaderManager->setMat4Value(g_ProjectionName, projection);
        m_pShaderManager->setVec3Value("viewPosition", g_pCamera->Position);
    }
}

