#include "libstk.h"

libstk::libstk() {
	texture = nullptr;
	width   = 0;
	height  = 0;
}


libstk::~libstk() {
	if (texture != nullptr)
		delete [] texture;
	
	width   = 0;
	height  = 0;
	texture = nullptr;
}

/*
 * destroy
 * dealloc all resource used
 * no return
 */
void libstk::destroy() {
	if (texture != nullptr) {
		delete [] texture;
		texture = nullptr;
	}

	width = 0;
	height = 0;

}


/*
 * PRIVATE FUNCTION
 * loadBMP
 * load bitmap file
 * return true if success
 * return false if failed to load bitmap
 */
bool libstk::loadBMP(const std::string& dir) {
	unsigned char *data = nullptr; 
	FILE *bmp = NULL;
	unsigned int size = 0;
	unsigned int bmpRawSize = 0;
	unsigned int bmpRawOffset = 0;

	bmp = fopen(dir.c_str(), "rb");


	if (bmp == NULL) {
		std::cout << "failed while loading bitmap: " << dir << std::endl;
		return false;
	}


	fseek(bmp, 0, SEEK_END);
	size = ftell(bmp);
	rewind(bmp);

	data = new unsigned char[size];

	size_t result = fread(data, 1, size, bmp);

	if (result != size) {
		std::cout << "Error while reading the file bitmap file" << std::endl;
		delete [] data;
		data = nullptr;
		fclose(bmp);
		return false;
	}

	if ( data[0] != 'B' || data[1] != 'M' ) {
		std::cout << "invalid bitmap filed " << std::endl;
		delete [] data;
		data = nullptr;
		fclose(bmp);
		return false;
	}

	width  = *(unsigned int*)(&data[0x12]);
	height = *(unsigned int*)(&data[0x16]); 
	bmpRawOffset = *(unsigned int*)(&data[0x0A]);
	bmpRawSize   = *(unsigned int*)(&data[0x22]);

	if (bmpRawOffset == 0) bmpRawOffset = 54;
	if (bmpRawSize == 0) bmpRawSize = width * height * 3;

	texture = new unsigned char [bmpRawSize];

	std::memcpy(texture, (data + bmpRawOffset), bmpRawSize);

	delete [] data;
	data = nullptr;
	fclose(bmp);
	format = IMAGE_FORMAT_BMP;

	return true;
}

/*
 * PRIVATE FUNCTION
 * loadPNG
 * load png file
 * return true if success
 * return false if failed to load png
 */
bool libstk::loadPNG(const std::string& dir) {
	/*
	 * TODO: improve the code
	 */
	std::vector<unsigned char> raw;

	unsigned int error = lodepng::decode(raw, width, height, dir.c_str());

	if (error)
		std::cout << "decode error " << error << ": " << lodepng_error_text(error) << std::endl;


	texture = new unsigned char[raw.size()];

	std::memcpy(texture, &raw[0], raw.size());

	format = IMAGE_FORMAT_PNG;
	return true;
}

/*
 * PRIVATE FUNCTION
 * loadTIM
 * load TIM file 
 * return true if success
 * return false if failed to load TIM
 */
bool libstk::loadTIM(const std::string& dir) {
	unsigned char *data = nullptr; 
	FILE *tim = NULL;
	unsigned int size = 0;
	unsigned int **colorTable;

	tim = fopen(dir.c_str(), "rb");


	if (tim == NULL) {
		std::cout << "failed while loading tim: " << dir << std::endl;
		return false;
	}

	fseek(tim, 0, SEEK_END);
	size = ftell(tim);
	rewind(tim);

	data = new unsigned char[size];

	size_t result = fread(data, 1, size, tim);

	if (result != size) {
		std::cout << "Error while reading the file bitmap file" << std::endl;
		delete [] data;
		data = nullptr;
		fclose(tim);
		return false;
	}

	if (*(unsigned int *)(&data[0]) != 0x10) {
		std::cout << "Invalid TIM file" << std::endl;
		delete [] data;
		data = nullptr;
		fclose(tim);
		return false;
	}

	unsigned short numCluts = *(unsigned short*)(data+0x18);

	colorTable = new unsigned int*[numCluts];

	unsigned short colorByte = 0;

	for (unsigned int i = 0; i < numCluts; i++) {
		colorTable[i] = new unsigned int [256];

		for (unsigned int a = 0; a < 256; a++) {
			colorByte = *(unsigned short*)(data + 20 + a * 2 + (512 * i));

			unsigned char r = ((colorByte >> 10) & 0x1F);
			unsigned char g = ((colorByte >> 5)  & 0x1F);
			unsigned char b = (colorByte         & 0x1F);


			colorTable[i][a] = (r << 16) | (g << 8) | b;
		}
	}


	unsigned short offsetRel = (20 + numCluts * 512);

	width  = *(unsigned short*)(data + offsetRel + 8);
	height = *(unsigned short*)(data + offsetRel + 10);

	texture = new unsigned char  [width * height * 6];

	unsigned int offset = 0;
	unsigned char yOffset = 0;
	unsigned int color = 0;

	for (unsigned short y = 0; y < height; y++) {
		for (unsigned short x; x < (width * 2) ; x++) {
			yOffset = *(unsigned char*)(data + offsetRel + 12 + x + (y * width * 2));

			color = colorTable[x / 128][yOffset];

			texture[offset + 2] = (color & 0x00FF0000) >> 16;
			texture[offset + 1] = (color & 0x0000FF00) >> 8;
			texture[offset]     = (color & 0x000000FF);

			offset += 3;
		}
	}


	for (unsigned int i = 0; i < numCluts; i++) {
		delete [] colorTable[i];
		colorTable[i] = nullptr;
	}

	delete [] colorTable;
	colorTable = nullptr;
	delete [] data;
	data = nullptr;
	fclose(tim);
	format = IMAGE_FORMAT_TIM;
	return true;
}


/*
 * loadIMG
 * load file image 
 * current supported formats: .BMP, .TIM, .PNG
 * return true if success
 * return false if error
 */
bool libstk::loadIMG(const std::string& dir ) {
	if (dir.size() == 0) {
		std::cout << "invalid dir !" << std::endl;
		return false;
	}

	/*
	 * check if it's a BITMAP
	 */
	if ((!dir.compare(dir.size() - 4, 4, ".BMP")) || (!dir.compare(dir.size() - 4, 4, ".bmp"))) {
		return loadBMP(dir);
	}

	/*
	 * check if it's a PNG
	 */
	if ((!dir.compare(dir.size() - 4, 4, ".PNG")) || (!dir.compare(dir.size() - 4, 4, ".png"))) {
		return loadPNG(dir);
	}

	/*
	 * check if it's a TIM
	 */
	if (!dir.compare(dir.size() - 4, 4, ".TIM")) {
		return loadTIM(dir);
	}

	return false;
}

/*
 * getWidth
 * return image width
 */
unsigned int libstk::getWidth() const { return width; }
/*
 * getHeight
 * return image height
 */
unsigned int libstk::getHeight() const { return height; }
/*
 * getTexture
 * return pointer to raw texture
 */
unsigned char* libstk::getTexture() const { return texture; }

/*
 * getFormat
 * return image format
 */
IMAGE_FORMAT libstk::getFormat() const { return format; }