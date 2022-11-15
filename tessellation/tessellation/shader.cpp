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
Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* tcs, const char* tes, const char* gs)
{
    // 1. ���ļ�·���л�ȡ����/Ƭ����ɫ��

    const char* vShaderCode = read_shader(vertexPath);
    const char* fShaderCode = read_shader(fragmentPath);


    // 2. ������ɫ��
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // ������ɫ��
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // ��ӡ�����������еĻ���
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // ��ӡ�����������еĻ���
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

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
        int success;
        char infoLog[512];

        // ������ɫ��
        tesc = glCreateShader(GL_TESS_CONTROL_SHADER);
        glShaderSource(tesc, 1, &cShaderCode, NULL);
        glCompileShader(tesc);
        // ��ӡ�����������еĻ���
        glGetShaderiv(tesc, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(tesc, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::tesc::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        tese = glCreateShader(GL_TESS_EVALUATION_SHADER);
        glShaderSource(tese, 1, &eShaderCode, NULL);
        glCompileShader(tese);
        // ��ӡ�����������еĻ���
        glGetShaderiv(tese, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(tese, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::tese::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
        glAttachShader(ID, tese);
        glAttachShader(ID, tesc);
    }
    if (gs)
    {
        const char* gShaderCode = read_shader(gs);
        


        // 2. ������ɫ��
        unsigned int geom;
        int success;
        char infoLog[512];

        // ������ɫ��
        geom = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geom, 1, &gShaderCode, NULL);
        glCompileShader(geom);
        // ��ӡ�����������еĻ���
        glGetShaderiv(geom, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(geom, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::gs::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        
        glAttachShader(ID, geom);

    }

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
   