/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to install, execute and perform the Spine Runtimes
 * Software (the "Software") solely for internal use. Without the written
 * permission of Esoteric Software (typically granted by licensing Spine), you
 * may not (a) modify, translate, adapt or otherwise create derivative works,
 * improvements of the Software or develop new applications using the Software
 * or (b) remove, delete, alter or obscure any trademarks or any copyright,
 * trademark, patent or other intellectual property or proprietary rights
 * notices on or in the Software, including any copy thereof. Redistributions
 * in binary or source form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <spine/spine-cocos2dx.h>
#include <spine/extension.h>

USING_NS_CC;

void _spAtlasPage_createTexture (spAtlasPage* self, const char* path) {
    printf("_spAtlasPage_createTexture : %s\n", path);
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(path);
	texture->retain();
	self->rendererObject = texture;
	self->width = texture->getPixelsWide();
	self->height = texture->getPixelsHigh();
}

void _spAtlasPage_createTexture_Not_Assets (spAtlasPage* self, const char* path) {
    
//    std::string _path = CCFileUtils::sharedFileUtils()->getWritablePath();
//    _path.append(path);
    
    printf("_spAtlasPage_createTexture_Not_Assets : %s\n", path);
    
//    CCTexture2D *texture = new CCTexture2D();
//    unsigned long size;
//    unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(_path.c_str(), "rb", &size);
//    CCImage *img = new CCImage();
//    img->initWithImageData(data, size);
//    texture->initWithImage(img);
//    texture->retain();
//    self->rendererObject = texture;
//    self->width = texture->getPixelsWide();
//    self->height = texture->getPixelsHigh();

    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage_Not_Asset(path);
    texture->retain();
    self->rendererObject = texture;
    self->width = texture->getPixelsWide();
    self->height = texture->getPixelsHigh();
//    texture->release();
}

void _spAtlasPage_createTexture_Not_Assets_Zip (spAtlasPage* self, const char* zip_path, const char* path) {
    
    std::string _zip_path = CCFileUtils::sharedFileUtils()->getWritablePath();
    _zip_path.append(zip_path);
    
    CCTexture2D *texture = new CCTexture2D();
    unsigned long size;
    unsigned char * tData = CCFileUtils::sharedFileUtils()->getFileDataFromZip(_zip_path.c_str(), path, &size, NULL);
    CCImage *img = new CCImage;
    img->initWithImageData(tData, size);
    texture->initWithImage(img);
    texture->retain();
    self->rendererObject = texture;
    self->width = texture->getPixelsWide();
    self->height = texture->getPixelsHigh();
}

void _spAtlasPage_disposeTexture (spAtlasPage* self) {
	((CCTexture2D*)self->rendererObject)->release();
}

char* _spUtil_readFile (const char* path, int* length) {
	unsigned long size;
	char* data = reinterpret_cast<char*>(CCFileUtils::sharedFileUtils()->getFileData(
	CCFileUtils::sharedFileUtils()->fullPathForFilename(path).c_str(), "r", &size));
	*length = size;
//    printf("_spUtil_readFile data : %s", data);
	return data;
}

char* _spUtil_readFile_Not_Assets (const char* path, int* length) {
    std::string _path = CCFileUtils::sharedFileUtils()->getWritablePath();
    _path.append(path);
    printf("_spUtil_readFile_Not_Assets : %s\n", _path.c_str());
    unsigned long size;
    char* data = reinterpret_cast<char*>(CCFileUtils::sharedFileUtils()->getFileData(_path.c_str(), "r", &size));
    *length = size;
    
//    printf("_spUtil_readFile_Not_Assets data : %s\n", data);
    return data;
}

char* _spUtil_readFile_Not_Assets_Zip (const char* zip_path, const char* path, int* length) {
    std::string _zip_path = CCFileUtils::sharedFileUtils()->getWritablePath();
    _zip_path.append(zip_path);
    
    printf("_spUtil_readFile_Not_Assets_Zip : %s, file : %s\n", _zip_path.c_str(), path);
    
    unsigned long size;
    char* data = reinterpret_cast<char*>(CCFileUtils::sharedFileUtils()->getFileDataFromZip(_zip_path.c_str(), path, &size, NULL));
    *length = size;
    
    printf("_spUtil_readFile_Not_Assets_Zip data : %s\n", data);
    return data;
}
