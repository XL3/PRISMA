#include "shader.hpp"

std::string Shader::LoadFile(const char* filePath) {
  std::string shader = "";

  // Load the file:
  std::ifstream fileStream(filePath, std::ios::in);
  if (!fileStream.is_open()) {
    std::cerr << "Could not read file " << filePath << ". File does not exist.\n";
    return "";
  }

  // Fill the string line by line:
  std::string currentLine = "";
  while (!fileStream.eof()) {
    std::getline(fileStream, currentLine);
    shader.append(currentLine + "\n");
  }

  fileStream.close();
  return shader;
}

GLuint Shader::LoadShader(const char* vertexPath, const char* fragmentPath) {
  // Create and load the two shaders:
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  std::string vertexShaderStr = LoadFile(vertexPath);
  std::string fragmentShaderStr = LoadFile(fragmentPath);

  const char* vertexShaderSource = vertexShaderStr.c_str();
  const char* fragmentShaderSource = fragmentShaderStr.c_str();

  GLint compileStatus = GL_FALSE;
  GLint linkStatus = GL_FALSE;
  int logLength = 0;

  // Compile the vertex shader:
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // Verify that it was compiled successfully:
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
  glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

  if (compileStatus == GL_FALSE) {
    std::string vertexShaderError;
    vertexShaderError.resize((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertexShader, logLength, NULL, &vertexShaderError[0]);
    std::cout << &vertexShaderError[0] << std::endl;
  }

  // Compile the fragment shader:
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // Verify that it was compiled successfully:
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
  glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

  if (compileStatus == GL_FALSE) {
    std::string fragmentShaderError;
    fragmentShaderError.resize((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragmentShader, logLength, NULL, &fragmentShaderError[0]);
    std::cout << &fragmentShaderError[0] << std::endl;
  }

  // Creating and linking the shader program:
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  // Verify that it linked successfully:
  glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

  if (linkStatus == GL_FALSE) {
    std::string programError;
    programError.resize((logLength > 1) ? logLength : 1);
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;
  }

  // Finishing up
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}
