// ./cocos2dx/textures/CCTexture2D.cpp -> import

CCTexture2D * CCTextureCache::addImage_Not_Asset(const char * path)
{
    CCAssert(path != NULL, "TextureCache: file image MUST not be NULL");
    
    CCTexture2D * texture = NULL;
    CCImage* pImage = NULL;
    
    std::string pathKey = path;
    
    std::string _path = CCFileUtils::sharedFileUtils()->getWritablePath();
    _path.append(path);
    
    pathKey = _path;//CCFileUtils::sharedFileUtils()->fullPathForFilename(pathKey.c_str());
    
    CCLog("addImage_Not_Asset : %s", pathKey.c_str());
    if (pathKey.size() == 0)
    {
        return NULL;
    }
    texture = (CCTexture2D*)m_pTextures->objectForKey(pathKey.c_str());
    
    std::string fullpath = pathKey; // (CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(path));
    if (! texture)
    {
        std::string lowerCase(pathKey);
        for (unsigned int i = 0; i < lowerCase.length(); ++i)
        {
            lowerCase[i] = tolower(lowerCase[i]);
        }
        // all images are handled by UIImage except PVR extension that is handled by our own handler
        do
        {
            if (std::string::npos != lowerCase.find(".pvr"))
            {
                texture = this->addPVRImage(fullpath.c_str());
            }
            else if (std::string::npos != lowerCase.find(".pkm"))
            {
                // ETC1 file format, only supportted on Android
                texture = this->addETCImage(fullpath.c_str());
            }
            else
            {
                CCImage::EImageFormat eImageFormat = CCImage::kFmtUnKnown;
                if (std::string::npos != lowerCase.find(".png"))
                {
                    eImageFormat = CCImage::kFmtPng;
                }
                else if (std::string::npos != lowerCase.find(".jpg") || std::string::npos != lowerCase.find(".jpeg"))
                {
                    eImageFormat = CCImage::kFmtJpg;
                }
                else if (std::string::npos != lowerCase.find(".tif") || std::string::npos != lowerCase.find(".tiff"))
                {
                    eImageFormat = CCImage::kFmtTiff;
                }
                else if (std::string::npos != lowerCase.find(".webp"))
                {
                    eImageFormat = CCImage::kFmtWebp;
                }
                
                pImage = new CCImage();
                CC_BREAK_IF(NULL == pImage);
                
                bool bRet = pImage->initWithImageFile(fullpath.c_str(), eImageFormat);
                CC_BREAK_IF(!bRet);
                
                texture = new CCTexture2D();
                
                if( texture &&
                   texture->initWithImage(pImage) )
                {
#if CC_ENABLE_CACHE_TEXTURE_DATA
                    // cache the texture file name
                    VolatileTexture::addImageTexture(texture, fullpath.c_str(), eImageFormat);
#endif
                    m_pTextures->setObject(texture, pathKey.c_str());
                    texture->release();
                }
                else
                {
                    CCLOG("cocos2d: Couldn't create texture for file:%s in CCTextureCache", path);
                }
            }
        } while (0);
    }
    
    CC_SAFE_RELEASE(pImage);
    
    //pthread_mutex_unlock(m_pDictLock);
    return texture;
}
