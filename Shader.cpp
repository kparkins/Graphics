/*
 Copyright (C) 2006 So Yamaoka
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 Modified: Rex West (2015)
 
 */

#include "shader.h"

GLhandleARB shader::m_currentlyBoundShaderID = 0x0;

shader::shader(const char *vert, const char *frag, bool isFile) {
	if(isFile) {
        //Read in the vertex and fragment shaders
        //We must delete these after we are finished compiling the shaders
		char* vv = read(vert);
		char* vf = read(frag);
        
        //Setup the shader
		setup(vv, vf);
        
        //Delete the file data arrays we allocted
		delete[] vv;
		delete[] vf;
	} else {
        //Treat the vert and frag parameters as shader code and directly compile them
		setup(vert, frag);
    }
}

shader::~shader() {
	glDeleteObjectARB(m_pid);
}

void shader::bind() {
    if(m_currentlyBoundShaderID != m_pid) {
        m_currentlyBoundShaderID = m_pid;
        glUseProgramObjectARB(m_pid);
    }
}

void shader::unbind() {
    if(m_currentlyBoundShaderID != (void*)(0x0)) {
        m_currentlyBoundShaderID = (void*)(0x0);
        glUseProgramObjectARB(0);
    }
}

void shader::print_log(const char* tag) {
	char glslLog[1024];
	GLsizei glslLogSize;
    
    //Extract the error log for this shader's m_pid
	glGetInfoLogARB(m_pid, 1024, &glslLogSize, glslLog);
    
    //If the log isn't empty, print the contents
    if(glslLogSize > 0) {
        std::cerr << tag << "(" << m_pid << ") -  Shader error log:" << std::endl << glslLog << std::endl;
    } else {
        std::cerr << tag << "(" << m_pid << ") -  Shaders compiled successfully!" << std::endl;
    }
}

char* shader::read(const char *filename) {
	char* shaderFile = 0;
	
    //Open the file
	FILE* fp = fopen(filename, "rb");
	if(!fp) {
        std::cerr << "File doesn't exist [" << filename << "]" << std::endl;
        std::exit(-1);
    }
    
	//Obtain the file m_size
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);
    
	//Alloc memory - will be deleted while setting the shader up
	shaderFile = new char[size+1];
    
	//Copy the file to the shaderFile
	fread(shaderFile, sizeof(char), size, fp);
	shaderFile[size]='\0'; //Eliminate the garbage at EOF
	fclose(fp);
    
	return shaderFile;
}

void shader::setup(const char *vs, const char *fs) {
    //Create two new Shader Object IDs
	GLhandleARB vid = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	GLhandleARB fid = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	
    //Pass the shader source code to OpenGL
	glShaderSourceARB(vid, 1, &vs, 0);
	glShaderSourceARB(fid, 1, &fs, 0);
	
    //Compile the shader files
	glCompileShaderARB(vid);
	glCompileShaderARB(fid);
    
	char glslLog[1024];
	GLsizei glslLogSize;
    
    //Get the error log for the Vertex shader
	glGetInfoLogARB(vid, 1024, &glslLogSize, glslLog);
    if (glslLogSize) {
		std::cerr << "Vertex program log: " << glslLog << std::endl;
    }
    //Get the error log for the Fragment shader
	glGetInfoLogARB(fid, 1024, &glslLogSize, glslLog);
    if (glslLogSize) {
		std::cerr << "Fragment program log: " << glslLog << std::endl;
    }
    //Create a new Shader Program
	m_pid = glCreateProgramObjectARB();
    
    //Attach the Vertex and Fragment shaders to the Shader Program
	glAttachObjectARB(m_pid, vid);
	glAttachObjectARB(m_pid, fid);
    
	//Delete shader objects since they have been attached to a program
	glDeleteObjectARB(vid);
	glDeleteObjectARB(fid);
	
	//Link it!
	glLinkProgramARB(m_pid);
}

