#include "shader.h"

const char* read_shader(const char* Path)
{
    std::string Code;
    
    std::ifstream ShaderFile;
    
    // ��֤ifstream��������׳��쳣��
   ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        // ���ļ�
        ShaderFile.open(Path);
        std::stringstream ShaderStream;
        // ��ȡ�ļ��Ļ������ݵ���������
        ShaderStream << ShaderFile.rdbuf();
        
        // �ر��ļ�������
        ShaderFile.close();
        
        // ת����������string
        Code = ShaderStream.str();

    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    std::string* tmp = new std::string(Code);
    return tmp->c_str();
}
void compile_shader(const char * shadercode,unsigned int &shader, GLenum shaderType)
{
    
    int success;
    char infoLog[512];

    // ������ɫ��
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shadercode, NULL);
    glCompileShader(shader);
    // ��ӡ�����������еĻ���
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
}
Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* tcs, const char* tes, const char* gs)
{
    // 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��

    const char* vShaderCode = read_shader(vertexPath);
    const char* fShaderCode = read_shader(fragmentPath);


    // 2. ������ɫ��
    unsigned int vertex, fragment;
    compile_shader(vShaderCode, vertex, GL_VERTEX_SHADER);

    compile_shader(fShaderCode, fragment, GL_FRAGMENT_SHADER);

    // ��ɫ������
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if (tcs)
    {
        const char* cShaderCode = read_shader(tcs);
        const char* eShaderCode = read_shader(tes);


        // 2. ������ɫ��
        unsigned int tesc, tese;
        compile_shader(cShaderCode, tesc, GL_TESS_CONTROL_SHADER);
        compile_shader(eShaderCode, tese, GL_TESS_EVALUATION_SHADER);
        glAttachShader(ID, tese);
        glAttachShader(ID, tesc);
    }
    if (gs)
    {
        const char* gShaderCode = read_shader(gs);
        

        unsigned int geom;
        compile_shader(gShaderCode, geom, GL_GEOMETRY_SHADER);

        
        glAttachShader(ID, geom);

    }
    int success;
    char infoLog[512];
    glLinkProgram(ID);
    // ��ӡ���Ӵ�������еĻ���
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // ɾ����ɫ���������Ѿ����ӵ����ǵĳ������ˣ��Ѿ�������Ҫ��
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


void Shader::use()
{
    glUseProgram(ID);
}
 

        void Shader::setBool(const std::string & name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void Shader::setInt(const std::string & name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void Shader::setFloat(const std::string & name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void Shader::setVec3(const std::string& name, float x,float y,float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x,y,z);
    }
    
    ComputeShader::ComputeShader(const char* cspath)
    {
        const char* cscode = read_shader(cspath);
        unsigned int cs;
        compile_shader(cscode, cs, GL_COMPUTE_SHADER);
        ID = glCreateProgram();
        glAttachShader(ID, cs);
        glLinkProgram(ID);
        int success;
        char infoLog[512];
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

    }