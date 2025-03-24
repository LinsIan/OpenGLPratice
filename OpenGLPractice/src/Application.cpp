#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

	GLenum err = glewInit();

	if (GLEW_OK != err)
    {
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}

	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	unsigned char* glVersion;
	GLCall(glVersion = (unsigned char*)glGetString(GL_VERSION));
	std::cout << "Status: Using GL " << glVersion << std::endl;

    {
        float position[] = 
        {
            -50.0f, -50.0f, 0.0f, 0.0f, // 0
             50.0f, -50.0f, 1.0f, 0.0f, // 1
             50.0f,  50.0f, 1.0f, 1.0f, // 2
            -50.0f,  50.0f, 0.0f, 1.0f  // 3
        };

        unsigned int indeces[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        // take source alpha value
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(position, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2); // position
        layout.Push<float>(2); // texture coordinate
        va.AddBuffer(vb, layout);

	    IndexBuffer ib(indeces, 6);

		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f); // 正交投影
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // move camera

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/textures/ChernoLogo.png");
        unsigned int slot = 0;
        texture.Bind(slot);
        shader.SetUniform1i("u_Texture", slot);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

		ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        float r = 0;
        float increment = 0.05f;
        glm::vec3 translationA(200, 200, 0);
        glm::vec3 translationB(400, 200, 0);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

            shader.Bind();

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA); // move model
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, ib, shader);
            }
            
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB); // move model
                glm::mat4 mvp = proj * view * model;
                shader.SetUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, ib, shader);
            }

            if (r >= 1) increment = -0.05f;
            else if (r <= 0) increment = 0.05f;

            r += increment;

			{
                ImGui::SliderFloat3("Model translation A:", &translationA.x, 0.0f, 960.0f);
                ImGui::SliderFloat3("Model translation B:", &translationB.x, 0.0f, 960.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			}

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}