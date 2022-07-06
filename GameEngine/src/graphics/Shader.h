#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

struct Shader
{
	std::string vertexSource;
	std::string fragmentSource;

	unsigned int vertexId;
	unsigned int fragmentId;

	std::string errorMsg;

	static struct Shader FromFile(const std::string& filepath)
	{
		enum class ShaderType
		{
			None = -1,
			Vertex = 0,
			Fragment = 1
		};

		std::ifstream stream(filepath);
		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::None;


		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::Vertex;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::Fragment;
			}
			else
			{
				ss[(int)type] << line << '\n';
			}
		}

		Shader shader = { ss[0].str(), ss[1].str() };
		shader.Compile();
		return shader;
	}

	bool Compile()
	{
		return CompileSource(GL_VERTEX_SHADER) && CompileSource(GL_FRAGMENT_SHADER);
	}

	bool CompileSource(unsigned int type)
	{
		vertexId = glCreateShader(type);
		const char* src = (type == GL_VERTEX_SHADER ? vertexSource : fragmentSource).c_str();
		glShaderSource(vertexId, 1, &src, nullptr);
		glCompileShader(vertexId);

		int result;
		glGetShaderiv(vertexId, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(vertexId, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(vertexId, length, &length, message);
			errorMsg = "Failed to compile " + (type == GL_VERTEX_SHADER ? "vertex" : "fragment") + "shader" + std::endl;
			glDeleteShader(vertexId);
			return false;
		}

		return true;
	}
};