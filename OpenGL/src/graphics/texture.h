#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

class Texture {
public:
	Texture();
	Texture(const char* path, const char* name, bool defaulParams = true);

	void generate();
	void load(bool flip = true);

	void setFilters(GLenum all);
	void setFilters(GLenum mag, GLenum min);

	void setWrap(GLenum all);
	void setWrap(GLenum s, GLenum t);

	void bind();
	
	int id;
	unsigned int tex;
	const char* name;

private:
	static int currentId;

	const char* path;
	int width;
	int height;
	int nChannels;
};

#endif // !TEXTURE_H