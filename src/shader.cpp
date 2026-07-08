#include "shader.h"

#include <glad/glad.h>
#include <fmt/core.h>
#include <glm/gtc/type_ptr.hpp>
#include "utils.h"

using namespace std;

Shader::Shader(const string &shader_name, ShaderKind kind) : kind(kind)
{
	this->ID = create_shader(shader_name, kind);
}

unsigned int Shader::create_shader(const string &shader_name, ShaderKind kind)
{
	unsigned int program = glCreateProgram();

	auto compileShader = [&](unsigned int shader, const string &type) -> bool
	{
		glCompileShader(shader);
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			int length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			string log(length, ' ');
			glGetShaderInfoLog(shader, length, nullptr, log.data());
			Utils::errorMessage(
				"Shader compilation failed (" + type + ") for '" + shader_name + "'",
				log);
			return false;
		}
		return true;
	};

	bool ok = true;

	if (kind == ShaderKind::Graphics)
	{
		// vertex shader
		string vertSrc = Utils::readFileToString(shader_name + ".vs");
		if (vertSrc.empty())
		{
			Utils::errorMessage("File error", "Vertex shader file '" + shader_name + ".vs' is empty or missing.");
			glDeleteProgram(program);
			return 0;
		}
		const char *vertCStr = vertSrc.c_str();
		unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vertCStr, nullptr);
		if (!compileShader(vertShader, "Vertex"))
		{
			glDeleteShader(vertShader);
			ok = false;
		}

		// fragment shader
		string fragSrc = Utils::readFileToString(shader_name + ".fs");
		if (fragSrc.empty())
		{
			Utils::errorMessage("File error", "Fragment shader file '" + shader_name + ".fs' is empty or missing.");
			glDeleteProgram(program);
			glDeleteShader(vertShader);
			return 0;
		}
		const char *fragCStr = fragSrc.c_str();
		unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragCStr, nullptr);
		if (!compileShader(fragShader, "Fragment"))
		{
			glDeleteShader(fragShader);
			ok = false;
		}

		if (!ok)
		{
			glDeleteProgram(program);
			glDeleteShader(vertShader);
			glDeleteShader(fragShader);
			return 0;
		}

		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);

		int linkSuccess;
		glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
		if (!linkSuccess)
		{
			int length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			string log(length, ' ');
			glGetProgramInfoLog(program, length, nullptr, log.data());
			Utils::errorMessage(
				"Program linking failed for '" + shader_name + "'",
				log);
			glDeleteProgram(program);
			program = 0;
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}
	else
	{ // compute
		string compSrc = Utils::readFileToString(shader_name + ".cs");
		if (compSrc.empty())
		{
			Utils::errorMessage("File error", "Compute shader file '" + shader_name + ".cs' is empty or missing.");
			glDeleteProgram(program);
			return 0;
		}
		const char *compCStr = compSrc.c_str();
		unsigned int compShader = glCreateShader(GL_COMPUTE_SHADER);
		glShaderSource(compShader, 1, &compCStr, nullptr);
		if (!compileShader(compShader, "Compute"))
		{
			glDeleteShader(compShader);
			glDeleteProgram(program);
			return 0;
		}

		glAttachShader(program, compShader);
		glLinkProgram(program);

		int linkSuccess;
		glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
		if (!linkSuccess)
		{
			int length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			string log(length, ' ');
			glGetProgramInfoLog(program, length, nullptr, log.data());
			Utils::errorMessage(
				"Program linking failed for '" + shader_name + "'",
				log);
			glDeleteProgram(program);
			program = 0;
		}

		glDeleteShader(compShader);
	}

	if (program == 0)
	{
		Utils::errorMessage(
			"Shader creation failed",
			"Shader program '" + shader_name + "' could not be created.");
	}

	return program;
}
void Shader::use() { glUseProgram(Shader::ID); }

int Shader::getUniformLocation(const string &name) const
{
	auto it = m_uniformLocationCache.find(name);
	if (it != m_uniformLocationCache.end())
		return it->second;

	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		Utils::errorMessage("Uniform location warning", "Uniform '" + name + "' not found in shader.");
	}
	m_uniformLocationCache[name] = location;
	return location;
}

// setters

void Shader::setBool(const string &name, bool value)
{
	use(); // ensure program is active
	glUniform1i(getUniformLocation(name), (int)value);
}

void Shader::setInt(const string &name, int value)
{
	use();
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const string &name, float value)
{
	use();
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setDouble(const string &name, double value)
{
	use();
	glUniform1d(getUniformLocation(name), value);
}

// my vectors

void Shader::setVec2(const string &name, const glm::vec2 &value)
{
	use();
	glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec2(const string &name, float x, float y)
{
	use();
	glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVec3(const string &name, const glm::vec3 &value)
{
	use();
	glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec3(const string &name, float x, float y, float z)
{
	use();
	glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setVec4(const string &name, const glm::vec4 &value)
{
	use();
	glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec4(const string &name, float x, float y, float z, float w)
{
	use();
	glUniform4f(getUniformLocation(name), x, y, z, w);
}

// matrix setters

void Shader::setMat2(const string &name, const glm::mat2 &mat, bool transpose)
{
	use();
	glUniformMatrix2fv(getUniformLocation(name), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat3(const string &name, const glm::mat3 &mat, bool transpose)
{
	use();
	glUniformMatrix3fv(getUniformLocation(name), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat4(const string &name, const glm::mat4 &mat, bool transpose)
{
	use();
	glUniformMatrix4fv(getUniformLocation(name), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
}